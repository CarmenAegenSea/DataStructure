# 头文件说明

本目录中的头文件定义了该数据结构实验项目中常用的抽象数据类型（ADT），包括顺序表、链表、栈、队列、串、广义表等。对应的实现文件通常位于 include/ 下的 .cpp 文件中。

---

## 1. 公共定义

### Def.h

定义了全局状态码和基础类型，作为其余头文件的公共依赖。

- 常量：
  - TRUE / FALSE
  - OK / ERROR / WARNING
  - OVERFLOW / UNDERFLOW / INFEASIBLE
- 类型别名：
  - Status：状态类型
  - ElemType：元素类型，默认定义为 int

这意味着整个项目中的数据结构默认使用 int 作为基本元素值，并通过状态码判断操作是否成功。

---

## 2. 顺序表与链表

### List.h

定义了顺序表（SqList）的接口，适合在连续内存中管理线性表。

#### 结构体

- SqListNode
  - elem：存储空间基址
  - len：当前长度
  - size：当前容量
  - inc：扩容增量
- SqList：SqListNode 的指针类型

#### 主要函数

- InitList()：初始化顺序表
- FreeList()：释放顺序表
- ClearList()：清空顺序表
- ListEmpty()：判断是否为空
- ListLen()：返回长度
- GetElem()：获取第 i 个元素
- PutElem()：修改第 i 个元素
- LocateElem()：按条件查找元素
- PrevElem()：返回前驱值
- NextElem()：返回后继值
- ListInsert()：插入元素
- ListDelete()：删除元素
- ListTraverse()：遍历表中元素

#### 适用场景

- 元素随机访问需求较强
- 需要较高的存储密度和较少的指针开销
- 适合实现基础线性表操作

### LinkList.h

定义了单链表（LinkList）的接口，适合动态插入和删除。

#### 结构体

- LNode
  - data：数据域
  - next：后继指针
- LinkList：LNode 的指针类型

#### 主要函数

- InitList()：初始化链表
- FreeList()：释放整条链表
- ClearList()：清空链表
- ListEmpty()：判断是否为空
- ListLen()：表长
- GetElem()：获取第 i 个元素
- PutElem()：修改元素值
- LocateElem()：查找满足关系的元素
- PrevElem()：返回前驱值
- NextElem()：返回后继值
- ListInsert()：插入元素
- ListDelete()：删除元素
- ListTraverse()：遍历链表

#### 适用场景

- 插入/删除频繁
- 数据量动态变化较大
- 不需要随机访问时更高效

> 对应实现文件：List.cpp、LinkedList.cpp

---

## 3. 栈与队列

### Stack.h

定义了顺序栈（SqStack）的接口，采用顺序存储结构。

#### 结构体

- SqStackNode
  - elem：栈存储空间
  - top：栈顶指针
  - size：容量
  - inc：扩容增量
- SqStack：SqStackNode 的指针类型

#### 主要函数

- InitStack()：初始化空栈
- FreeStack()：释放栈
- ClearStack()：清空栈
- StackEmpty()：判断是否为空
- StackLen()：返回长度
- GetTop()：返回栈顶元素
- Push()：入栈
- Pop()：出栈
- StackTraverse()：从栈底到栈顶遍历

#### 特点

- 先进后出（LIFO）
- 栈顶操作效率高
- 适用于表达式求值、括号匹配、递归模拟等场景

### Queue.h

定义了链式队列（LinkQueue）的接口。

#### 结构体

- QNode
  - data：数据域
  - next：指向下一个结点
- LinkQueue
  - front：队头指针
  - rear：队尾指针

#### 主要函数

- InitQueueL()：初始化队列
- FreeQueueL()：释放队列
- ClearQueueL()：清空队列
- QueueRmptyL()：判断是否为空
- QueueLenL()：返回长度
- GetHeadL()：返回头元素
- EnQueueL()：入队
- DeQueueL()：出队
- QueueTrav()：遍历队列

#### 特点

- 先进先出（FIFO）
- 适合任务调度、缓冲区处理、层序遍历等

> 对应实现文件：Stack.cpp、Queue.cpp

---

## 4. 串（字符串）

### SqString.h

定义了顺序串（SqString）结构，用于字符串处理。

#### 结构体

- SqString
  - ch：字符存储空间，按 C 字符串方式管理
  - len：当前长度
  - capacity：总容量

#### 主要函数

- InitString()：初始化为空串
- DestroyString()：释放字符串
- ClearString()：清空
- StrAssign()：赋值
- StrCopy()：复制
- StrEmpty()：判断为空
- StrLength()：返回长度
- StrCompare()：比较两个串
- Concat()：连接两个串
- SubString()：截取子串
- Index()：定位子串位置
- StrInsert()：插入字符串
- StrDelete()：删除子串
- Replace()：替换所有出现的子串

#### 特点

- 以 char* 形式存储字符数据
- 使用容量与长度分离的管理方式
- 适合常见的字符串算法和模式匹配操作

> 对应实现文件：SqString.cpp

---

## 5. 广义表

### GList.h

定义了广义表的基础结点类型，使用枚举标志区分原子和子表。

#### 结构体

- ElemTag：ATOM / LIST
- GNode
  - tag：结点类型标志
  - data：联合体
    - atom：原子值
    - list：子表指针
- GList：广义表结点指针类型

#### 特点

- 广义表是线性表的扩展
- 每个结点可能是原子，也可能是子表
- 可表示复杂的层次结构数据

### GLinkList.h

定义了链式广义表（GLinkList）的接口，适合按链表方式存储广义表。

#### 结构体

- ElemTag：ATOM / LIST
- AtomType：原子类型，定义为 int
- GLinkList
  - tag：结点类型标志
  - union：原子值 or 子表指针
  - next：下一个结点指针

#### 主要函数

- InitGLinkList()：初始化广义表
- NewGLinkList()：根据字符串创建广义表
- FreeGLinkList()：释放广义表
- CopyGLinkList()：复制广义表
- GlinkListLen()：获取长度
- GlinkListDepth()：获取深度
- GlinkListEmpty()：判断是否为空
- GetGLinkListHead()：获取头元素
- GetGLinkListTail()：获取尾部
- InsertFirst_GLinkList()：头插元素
- DeleteFirst_GLinkList()：头删元素
- TraverseGLinkList()：遍历广义表

#### 特点

- 能表示嵌套结构
- 适合树型/表型递归数据表示
- 是数据结构课程中“广义表”常见实现形式

> 对应实现文件：GLinkList.cpp

---

## 6. 目录中的实现关系

当前 include/ 目录下的头文件对应的主要实现文件如下：

- List.h -> List.cpp
- LinkList.h -> LinkedList.cpp
- Stack.h -> Stack.cpp
- Queue.h -> Queue.cpp
- SqString.h -> SqString.cpp
- GLinkList.h -> GLinkList.cpp

其中：

- List.h / LinkList.h：线性表的抽象接口
- Stack.h / Queue.h：线性结构的栈和队列接口
- SqString.h：字符串的抽象接口
- GList.h / GLinkList.h：广义表相关抽象接口

