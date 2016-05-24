---
title: 多功能背单词软件的设计与实现
author: 陆逸文\ \ 吴田波
date: 2016年05月
header-includes:
    - \usepackage{ctex}
---


#功能简介

##功能简介

- 记忆模式：根据用户对单词的熟悉程度，自动对单词进行分组；对选定组别的单词进行复习。
- 词典模式：查询用户输入的单词，或选择历史记录条目。
- 测试模式：在线单词测试。给出答题正确率。
- 文本模式：统计文本文件中的单词，给出解释。
- 所有单词可由用户自行添加和编辑例句。
- 词库为方便人类阅读和编辑的纯文本文件，一行一个单词。


#效果展示


#设计思路


##需求分析

> - 算法模块：独立于主程序，作为动态链接库单独编译
>     - 实现时参考[SuperMemo2算法](https://www.supermemo.com/english/ol/sm2.htm)
> - 数据读写：纯文本数据库引擎
> - 界面交互：简单的命令行输入、输出

##需求是多变的！

- 数据读写：~~纯文本数据库引擎~~
    - JSON, SQLite, ...
- 界面交互：~~简单的命令行输入、输出~~
    - GUI, Web, ...

. . .

###接口与实现分离！

---

![Database类的UML图](5.png)

---

![Display类的UML图](9.png)

##MVC模式

###——数据、界面、逻辑的交互

---

![MVC示意图](0.svg)

图片来源：[维基百科](https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller)

##程序的运行过程

![运行过程示意图](1.png)

---

###整体架构设计

![整体架构](2.png)

#模块详解

##主循环

###`MainLoop`类

> - 在整个程序运行过程中只初始化一次
> - 加载数据库，供程序各个部分使用
> - 创建`Control`对象
>     - 一个功能模块$\leftrightarrow$一种逻辑$\leftrightarrow$一个`Control`的派生类
>     - 工厂方法！`ControlFactory`

---

![`MainLoop`](3.png)


##数据存储

###`Record`和`Database`

---

###`Record`

- 文件中的一行：
    `word   explanation example 0   1,1,1   0.2,0.4`
- `Record`对象的结构：

    ```cpp
    struct Record {
        string word;
        string explanation;
        string example;
        Group group;
        vector<int> answers;
        vector<double> algorithmOutput;
    };
    ```

- `Record`的构造函数`Record(string)`和`toString()`方法实现了两者的相互转换。

---

###`Database`

![`Database`](a1.png)

##核心逻辑

###`Control`

---

![`Control`的派生类们](a2.png)

---

##Control的职责

> - 记录程序运行状态
> - 生成视图类
>     - 工厂方法！`ViewFactory`


##视图相关的类

###View, Fragment, Widget

---

![视图层级](8.png)

---

###输入的处理：逐级委派

> - `View::handleInput()`
>     - `Fragment::handleInput()`
>         - `Widget::handleInput()`
> - 一旦输入被成功处理，流程短路。
> - 遍历完所有`Widget`，输入仍未被成功处理：非法输入！


#开发技巧

##测试驱动的开发

> - 开源C++测试框架[Catch](https://github.com/philsquared/Catch)
> - 抽离出程序中相对独立的模块（辅助函数、命令行解析器、算法模块、Database、Record、...）进行正确性测试。

##跨平台解决方案

###`cmake`

- 源代码不需要任何更改
- 生成各个平台的动态链接库

#不足与展望

##不足与展望

> - 词库文件体积较大时，加载缓慢。
>     - 更加高级的数据库解决方案?
>     - 异步I/O

---

> - 定义新的`Record`(ORM), `View`代码繁琐
>     - 更高级的语言技巧：宏...
>     - 参考[https://github.com/paulftw/hiberlite](https://github.com/paulftw/hiberlite)

---

```cpp
class WordRecord {
    friend class hiberlite::access;
    template<class Archive>
    void hibernate(Archive & ar)
    {
        ar & HIBERLITE_NVP(word);
        ar & HIBERLITE_NVP(explanation);
        ar & HIBERLITE_NVP(example);
    }
public:
    string word;
    string explanation;
    string example;
};
HIBERLITE_EXPORT_CLASS(WordRecord)
```

#谢谢！
