# 头文件说明

## 公共定义

### Def.h

| 名称 | 值 | 说明 |
| --- | ---: | --- |
| TRUE | 1 | - |
| FALSE | 0 | - |
| OK | 1 | 操作完成 |
| ERROR | 0 | 操作失败 |
| WARNING | -1 | 操作未完成 |
| OVERFLOW | -2 | 上溢出 |
| UNDERFLOW | -3 | 下溢出 |
| INFEASIBLE | -4 | 元素位置错误 |

### List.h

顺序表（基于动态数组）的定义与操作接口。`SqList` 指向顺序表，表中元素类型为 `ElemType`。

| 接口 | 说明 |
| --- | --- |
| `InitList`、`FreeList` | 初始化顺序表、释放顺序表 |
| `ClearList`、`ListEmpty`、`ListLen` | 清空、判断是否为空、获取长度 |
| `GetElem`、`PutElem` | 获取或修改指定位置的元素 |
| `LocateElem` | 按给定关系函数查找元素，返回下标；未找到返回 `0` |
| `PrevElem`、`NextElem` | 获取指定元素的前驱或后继 |
| `ListInsert`、`ListDelete` | 插入元素、删除指定位置的元素 |
| `ListTraverse` | 对表中元素执行访问函数 |

### LinkList.h

单链表的结点 `LNode` 由数据域和后继指针组成，`LinkList` 为链表指针类型。

| 接口 | 说明 |
| --- | --- |
| `InitList`、`FreeList` | 初始化链表、释放整条链表 |
| `ClearList`、`ListEmpty`、`ListLen` | 清空、判断是否为空、获取长度 |
| `GetElem`、`PutElem` | 获取或修改指定位置的元素 |
| `LocateElem` | 按给定关系函数查找元素 |
| `PrevElem`、`NextElem` | 获取指定元素的前驱或后继 |
| `ListInsert`、`ListDelete` | 插入元素、删除指定位置的元素 |
| `ListTraverse` | 对链表元素执行访问函数 |

### Queue.h

链式队列的定义与操作接口。`LinkQueue` 保存队头和队尾指针。

| 接口 | 说明 |
| --- | --- |
| `InitQueueL`、`FreeQueueL` | 初始化队列、释放队列 |
| `ClearQueueL`、`QueueRmptyL`、`QueueLenL` | 清空、判断是否为空、获取队列长度 |
| `GetHeadL` | 获取队头元素；队列为空时返回 `ERROR` |
| `EnQueueL`、`DeQueueL` | 入队、出队并返回队头元素 |
| `QueueTrav` | 对队列元素执行访问函数 |

### Stack.h

顺序栈的定义与操作接口。`SqStack` 指向栈结构，初始容量由 `STACK_INIT_SIZE` 指定。

| 接口 | 说明 |
| --- | --- |
| `InitStack`、`FreeStack` | 初始化空栈、释放栈 |
| `ClearStack`、`StackEmpty`、`StackLen` | 清空、判断是否为空、获取栈长度 |
| `GetTop` | 获取栈顶元素；栈空时返回 `0` |
| `Push`、`Pop` | 入栈、出栈并返回栈顶元素 |
| `StackTraverse` | 从栈底到栈顶执行访问函数 |

### GList.h

广义表结点的基本定义。`ElemTag` 区分原子（`ATOM`）和子表（`LIST`），结点通过联合体保存原子值或子表指针；本头文件未声明操作函数。

### GLinkList.h

链式广义表的结点定义与操作接口。结点可保存原子或子表，并通过 `next` 指向同层的后继结点。

| 接口 | 说明 |
| --- | --- |
| `InitGLinkList`、`NewGLinkList` | 初始化广义表、根据 `SqString` 创建广义表 |
| `FreeGLinkList`、`CopyGLinkList` | 释放广义表、复制广义表 |
| `GlinkListLen`、`GlinkListDepth`、`GlinkListEmpty` | 获取长度、获取深度、判断是否为空 |
| `GetGLinkListHead`、`GetGLinkListTail` | 获取表头原子、获取表尾 |
| `InsertFirst_GLinkList`、`DeleteFirst_GLinkList` | 在表头插入原子、删除表头并返回原子 |
| `TraverseGLinkList` | 遍历广义表中的原子并执行访问函数 |

### SqString.h

顺序字符串的定义与操作接口。`SqString` 使用以 `\0` 结尾的字符数组存储字符串；长度和位置按字节计算。

| 接口 | 说明 |
| --- | --- |
| `InitString`、`DestroyString`、`ClearString` | 初始化、销毁、清空字符串 |
| `StrAssign`、`StrCopy` | 从 C 字符串赋值、复制字符串 |
| `StrEmpty`、`StrLength`、`StrCompare` | 判空、获取字节长度、按字典序比较 |
| `Concat`、`SubString` | 拼接字符串、截取子串 |
| `Index` | 从指定位置查找子串；位置从 `1` 开始，未找到返回 `0` |
| `StrInsert`、`StrDelete`、`Replace` | 插入、删除、替换子串 |



