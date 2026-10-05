# Clavis「磁贴抽屉」机制完整分析 —— 以及如何移植到 DMS

分析对象：`~/Downloads/clavis-shell-2026.9.25/`（Clavis Shell 2026.9.25 源码）
目的：搞清 Clavis 如何实现「磁贴可在抽屉与桌面之间拖进拖出」，评估在 DMS 里复刻的可行性。

---

## 一、核心设计：一张卡片，一个 container 字段

### 1.1 单一事实源：`Modules/SystemCards/SystemCardCatalog.js`

11 张系统卡片的声明式目录，每张带尺寸跨度和监视模块依赖：

```js
{
    id: "cpu",
    name: qsTr("CPU"),
    icon: "memory",
    columnSpan: 2, rowSpan: 1,
    monitorModules: ["cpu"],          // 只在可见时订阅
    preserveDefaultSurface: true,
    excludeHostBlur: true
}
```

卡片清单：time / battery / cpu / gpu / memoryUsed / wifi / network / storage /
storageCapacity / calendar / weather

### 1.2 状态模型：`Modules/SystemCards/SystemCardState.js`（schemaVersion 4）

```js
card = {
    enabled: true,
    container: "sidebar" | "desktop",   // <-- 唯一的归属字段
    screenName: "",
    sidebar: { x, y } | null,           // 抽屉网格坐标，8px 对齐
    desktop: {
        placementSpace: "screen" | "wallpaper",
        screen:    { xNorm, yNorm },    // 归一化 0..1
        wallpaper: { xNorm, yNorm }
    }
}
```

**这是整个设计的关键**：不是「两套对象互相同步」，而是**一个对象 + 一个字符串字段**。
侧边栏和桌面画布各自 `filter(card.container === ...)` 渲染同一份数据，
所以「拖进抽屉 / 拖出到桌面」在数据层只是改一个字符串。

### 1.3 服务层：`Services/SystemCardService.qml`（Singleton）

```js
setContainer(cardId, container, screenName, xNorm, yNorm, placementSpace)
transferToDesktop(cardId, screenName, xNorm, yNorm, positions, requestLayout)
setSidebarLayout(layout)
setDesktopScreenPositions(positions)
commit(nextState, changedId, requestLayout, savedLayout)
```

`commit()` 要点：

- `reconciledLayouts()` 先重排抽屉网格（补空位、压缩间隙）
- 与上次状态逐字节相同则**早退**，避免无谓写盘
- 写 `UiPreferences.setCardLayouts(state, drawerLayout)`
- `desktopLayoutRevision += 1` 触发桌面重排
- `syncMonitorOwnership()` —— **只为可见的卡片订阅系统监视模块**；
  被收进抽屉的卡片不再采集数据，这是性能设计

`transferToDesktop()` 把「container 变更 + 碰撞求解结果」放进**同一个状态事务**提交。
源码注释：*"intermediate overlapping states never become observable or durable"*

---

## 二、抽屉有自己的网格布局

`Modules/Sidebars/Dashboard/drawer/DrawerGridLayout.js`

```js
clampAnchor(definition, x, y)
moveLayout(layout, tileId, x, y, activeIds)   // 返回 null 表示放不下
hydrateSaved(savedLayout, activeIds, anchors)
serializeLayout(layout, activeIds)
```

抽屉内拖动实时算预览：`previewLayout = solved`、`dragTargetValid = solved !== null`，
松手且合法才 `setSidebarLayout(previewLayout)`；放不下则回弹。

---

## 三、跨 surface 拖拽：阶段机 + 坐标空间提升

### 3.1 阶段机：`Services/SystemCardDragState.js`

```
idle --begin--> draggingSidebar --promote--> draggingPresentation
                                                    |
                                               freezeGhost
                                                    v
                                            frozenTransfer --> finishing --> idle
                                                    |
                                                 cancel
                                                    v
                                              canceled --> idle
```

`canTransition()` 严格校验合法转换，非法转换只 `console.warn` 并保持原状态。

### 3.2 会话：`Services/SystemCardDragSession.qml`（Singleton）

| 步骤 | 调用 | 作用 |
|---|---|---|
| 1 | `begin(cardId, item, grabLocalX, grabLocalY)` | 抽屉里按下，记录**源局部抓取点**（此后不可变） |
| 2 | `promoteToPresentation(...)` | 指针离开抽屉范围 -> 把拖拽提升到**屏幕坐标系** |
| 3 | `update(x, y)` | 幽灵跟随光标 |
| 4 | `freezeGhost(topLeftX, topLeftY)` | 松手，冻结幽灵 |
| 5 | `prepareVisualHandoff(cardId)` | **立起视觉屏障**，防止新桌面槽位初始化前闪现 |
| 6 | `SystemCardService.transferToDesktop(...)` | 同步提交 container 变更（屏障仍生效） |
| 7 | `markTransferCommitted(cardId)` | 提交置为**不可回滚** |
| 8 | 桌面槽位 `handoffReady` -> `completeVisualHandoff()` | 交接完成，幽灵淡出 |

### 3.3 抓取点的数学（手感全靠它）

`DrawerView.promoteToPresentation()`：

```js
const size = root.cardSize(tileId);
// 抽屉可能被缩放显示，但桌面用规范尺寸 —— 换算时保持相对抓取比例
const grabX = (mappedGrabPoint.x - sourceRect.x) * size.width  / Math.max(1, sourceRect.width);
const grabY = (mappedGrabPoint.y - sourceRect.y) * size.height / Math.max(1, sourceRect.height);
```

### 3.4 为什么能跨 surface 拖动

- `SidebarHostWindow` 是**全屏** `PanelWindow`（四边 anchors），靠 `mask` 只在打开时接收输入
- 所以整个拖拽期间指针都被这个 surface 捕获，可移动到屏幕任意位置
- 「提升」只是把坐标空间从 sidebar-local 换成 screen-global，并交接视觉所有者

---

## 四、落点求解：网格吸附 + 碰撞

`DrawerView.finishDrag()` 完整链路：

```js
// 1) clamp 进屏幕
let screenX = clamp(0, output.width  - size.width,  ghostX);
let screenY = clamp(0, output.height - size.height, ghostY);
// 2) 网格吸附（可开关）
if (PersonalizationConfig.desktopCardGridSnapEnabled)
    ({x: screenX, y: screenY} = DesktopCardLayout.snapPoint(...));
// 3) 归一化
const normalized = Placement.normalizedPosition(screenX, screenY, output.width, output.height);
// 4) 冻结幽灵 + 立屏障
SystemCardDragSession.freezeGhost(screenX, screenY);
SystemCardDragSession.prepareVisualHandoff(tileId);
// 5) 碰撞求解：新卡片是权威，只挤开已有卡片
const collisionRects = DesktopPresentationService.resolveDropCollision(
    screenName, tileId, screenX, screenY, size.width, size.height);
// 6) 原子提交
SystemCardService.transferToDesktop(tileId, screenName, normalized.xNorm, normalized.yNorm, ...);
// 7) 置为不可回滚 + 请求视觉交接
SystemCardDragSession.markTransferCommitted(tileId);
SystemCardDragSession.requestVisualHandoffCheck(tileId);
```

`Modules/DesktopCards/DesktopCardLayout.js` 是一套完整求解器：

```
snapPoint()            网格吸附
gridMetrics()          网格度量
rectsOverlap()         矩形相交（带 gap）
candidatePoints()      候选落点
busyScore()            拥挤度打分
edgePenalty()          贴边惩罚
movementPenalty()      移动距离惩罚
placeScreenCard()      逐个放置
solveScreenWithGap()   带间隙的整体求解
solve()                入口，按 mode 分派
```

三种桌面布局模式：`free`（自由）/ `screen`（屏幕网格）/ `wallpaper`（壁纸对齐）。

---

## 五、反向：桌面 -> 抽屉

`Modules/DesktopCards/DesktopCard.qml` 右键菜单：

```qml
StyledMenuItem {
    iconName: "dock_to_right"
    text: qsTr("Return to sidebar")
    onTriggered: SystemCardService.setContainer(root.tileId, "sidebar", "")
}
```

桌面卡片自身拖拽（`DragHandler`）通过 `placementController` 回调：
`beginCardDrag()` / `updateCardDrag(x,y)` / `finishCardDrag(x,y)` / `cancelCardDrag()` / `completeCardDrag()`。

---

## 六、值得学的工程细节（都是踩过坑的痕迹）

| 细节 | 位置 | 说明 |
|---|---|---|
| **双标志位消竞态** | `transferPreparing` / `transferCommitted` | 消除「新桌面槽位在提交标志写入前就可见」的窗口 |
| **赋值顺序** | `markTransferCommitted()` | 先设 committed=true 再设 preparing=false；反序会有瞬时 pending=false |
| **源销毁 != 交接完成** | `onSourceItemChanged` | 已提交时**不动** phase/tileId/commit/presentationRect |
| **已提交不可回滚** | `cancel()` | `transferCommitted` 时早退，Escape 也不能回滚 |
| **不在 binding 求值中改属性** | `requestVisualHandoffCheck` | 用信号延后，否则桌面委托可能永久卡在 waiting=true |
| **状态清理顺序** | `clearToIdle()` | 先转 idle 再清 sourceItem，避免源销毁触发递归取消 |
| **纯函数状态操作** | `SystemCardState.js` | 全部 state -> state，便于测试和事务化 |

---

## 七、移植到 DMS：可行性与差距

### 7.1 能对应上的部分

| Clavis | DMS 对应物 | 状态 |
|---|---|---|
| `DashboardSidebar` / `DrawerView`（宽抽屉） | DankDash 的一个 **dash 标签页** | 可用 |
| `SystemCardService`（中心状态） | 插件 **daemon 表面** + `pluginService.savePluginData` | 可用 |
| `SystemCardCatalog`（卡片目录） | 插件里的 JS 模块 | 可用 |
| `DesktopCardHost` / `DesktopCard`（桌面摆件） | 插件 **desktop 表面** | 有差距，见下 |
| `SidebarHostWindow` 全屏输入层 | DankDash 面板是否全屏 | 待验证 |
| 跨 surface 视觉交接 | **DMS 无对应 API** | 需自建 |

### 7.2 三个真实的差距

**差距 1：一个插件实例 != 一张卡**

Clavis 的 `DesktopCardHost` 是**一个全屏 Bottom 层窗口渲染 N 张卡**，位置由状态统一管理（归一化坐标）。
DMS 的 `desktop` 表面是**每个插件实例一个 layer surface**，位置尺寸由 `DesktopPluginWrapper`
用自己的 `desktopX/desktopY/desktopWidth/desktopHeight` 管理，插件**无法**在运行时创建/删除自己的桌面实例。

- 要么「一张卡一个插件实例」（用户手动添加 N 次，无法程序化增删）
- 要么「一个实例 = 一个容器，内部按相对偏移画多张卡」

**差距 2：没有全屏承接层**

Clavis 能跨 surface 拖拽，是因为 `SidebarHostWindow` 是全屏 layer surface 且用 `mask` 控制输入。
DMS 的 DankDash 面板尺寸由布局决定，不是全屏。
需要在插件里自己起一个全屏透明的 `PanelWindow`（Overlay 层）作为拖拽承接层 ——
插件 QML 理论上可以 `import Quickshell` 后直接实例化，但 DMS 插件加载器是否允许创建额外
layer surface 需要**实测**。

**差距 3：DMS 的桌面部件由核心管理**

`desktopClock` / `systemMonitor` 属于 DMS 核心的 `desktopWidgetInstances`，插件的
`setContainer` 管不到它们。抽屉里能收纳的只能是**插件自己的卡片**，不能是 DMS 内建桌面部件。
（除非改 DMS 源码重新编译 —— QML 是编进 `/usr/bin/dms` 二进制的，改不了。）

### 7.3 建议的落地方案

**阶段一（低风险，先出效果）**
- 一个 `composite` 插件，只做 `dash` 表面
- `Mod+Shift+D` 拉出的 DankDash 里多一个「磁贴」标签页
- 标签页内用 `DrawerGridLayout` 思路做网格 + 碰撞求解
- 卡片用 QtQuick 直接画（CPU/内存/磁盘/网络/时间/天气）
- 数据持久化到 `pluginService.savePluginData`
- 此时磁贴全部住在抽屉里，无桌面摆件

**阶段二（加桌面摆件）**
- 加 `desktop` 表面：一个实例 = 一个「摆件板」，内部按相对偏移渲染从抽屉"取出"的卡片
- 用 `daemon` 表面在抽屉与摆件板之间共享状态
- 「取出/收回」用右键菜单或卡片按钮（对应 Clavis 的 `Return to sidebar`）

**阶段三（可选，追求无缝拖拽）**
- 自建全屏 Overlay 承接层，实现 Clavis 式连续拖拽
- 若 DMS 插件不允许额外 layer surface，则此阶段不可行，退化为阶段二的按钮式

### 7.4 结论

Clavis 的实现**可以借鉴思路和算法**（数据模型、网格求解、阶段机、坐标提升），
但**不能照搬代码** —— 两者 surface 模型不同（Clavis 全屏多卡片画布 vs DMS 一实例一 surface）。

最实际的价值：
1. `container` 单字段模型 —— 直接可用，最优雅的部分
2. `DrawerGridLayout` 的碰撞求解 —— 可直接移植
3. 阶段机的双标志位/屏障思路 —— 自建拖拽时照抄
4. 全屏承接层 —— DMS 下需验证，可能做不了
