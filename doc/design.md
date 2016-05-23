#多功能单词记忆与查询软件的设计与实现

##概述与需求分析

本项目旨在用C++实现一款多功能的命令行单词记忆与查询软件，提供以下功能：
- 根据用户实际英语能力的变化动态设定单词级别、动态调整记忆策略。
- 以交互方式来查询用户输入单词的解释，记录查询历史。
- 进行在线单词测试。
- 对指定的文本文件进行单词统计并给出解释。
- 允许用户为单词添加例句，并在显示单词含义时一并显示用户添加的例句。
- 单词库为纯文本文件，一行一个单词。
- 实现跨平台的编译链接。

针对上述需求，我们认为：记忆算法、文本数据库的读写、用户界面的显示是三个相对独立于程序核心逻辑的模块。它们都须分离接口和实现，以增强可扩展性。就程序的核心逻辑而言，记忆、查询、测试、文本统计是四个相对独立的功能，但需要公用主数据库，以及单词显示、例句编辑等几个公共的视图。

##整体架构

受到GUI和Web编程中常用的[MVC模式](https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller)（如图\ref{mvc}所示）的启发，我们确定了程序的整体架构。


![MVC示意图\label{mvc}](https://upload.wikimedia.org/wikipedia/commons/a/a0/MVC-Process.svg)

从用户进入程序之后，运行的过程如图\ref{procedure}所示。

主循环`MainLoop`初始化数据库（对应MVC中的Model），并根据用户所选择的功能创建一个控制类`Control`的派生类对象。控制对象根据当前的状态向用户呈现合适的视图类`View`的派生类对象。根据用户输入，控制对象对数据库进行更新，并创建下一个视图对象，依此类推。控制类和视图类对象的创建分别由`ControlFactory`和`ViewFactory`这两个工厂类完成。


![运行流程\label{procedure}](http://g.gravizo.com/g?
@startuml;
actor "User" as U;
participant "MainLoop" as M;
participant "Database" as D;
participant "Control" as C;
participant "View1" as V1;
participant "View2" as V2;
U -> M: launch;
activate M;
M -> D: initialize;
activate D;
M -> C: create;
activate C;
C -> V1: create;
activate V1;
V1 -> U: display;
destroy V1;
U -> C: input;
C -> D: update;
C -> V2: create;
activate V2;
@enduml
)

图\ref{structure}展示了程序的整体架构。下分别对图中的每个主要模块的设计进行更为详细的阐释。

![整体架构\label{structure}](http://g.gravizo.com/g?
/**
*@composed - - 1 ControlFactory
*@composed - - 2 Database
*@composed - - 1 Display
*@composed - - 1 Control
*/
class MainLoop {
}
/**
*@composed - <friend> - ViewFactory
*@composed - - 1 View
*/
class Control {
}
/**
*@depend - - - recito_algorithm
*/
class MemoryControl extends Control {
}
/**
*@depend - - - Group
*/
class recito_algorithm {
}
class XXXControl extends Control {
}
/**
*@depend - - - ControlClass
*/
class ControlFactory {
}
/**
*@composed - - n Record
*/
class Database {
}
class TextDatabase extends Database {
}
/**
*@depend - - - View
*/
class Display {
}
class TextDisplay extends Display {
}
/**
*@composed - - n Widget
*/
class Fragment {
}
class XXXFragment extends Fragment {
}
class Record {
}
class WordRecord extends Record {
}
class HistoryRecord extends Record {
}
/**
*@composed - - n Fragment
*/
class View {
}
class XXXView extends View {
}
/**
*@depend - - - ViewClass
*/
class ViewFactory {
}
class Widget {
}
class Label extends Widget {
}
/**
*@depend - - - Control
*/
class TextInput extends Widget {
}
class MaxNumberInput extends TextInput {
}
/**
*@depend - - - Control
*/
class Option extends Widget {
}
class XXXOption extends Option {
}
/**
*@opt enumerations
*/
enum Group {
}
/**
*@opt enumerations
*/
enum ControlClass {
}
/**
*@opt enumerations
*/
enum ViewClass {
}
)

##主要功能模块的详细描述

###程序主干：`MainLoop`

![MainLoop和ControlFactory\label{mainloop}](http://g.gravizo.com/g?
/**
*@opt all
*@composed - - - ControlFactory
*/
class MainLoop {
  public void run();
  public void stop();
  public void setControl(ControlClass controlClass);
  WordDB mainDatabase;
  HistoryDB historyDatabase;
}
/**
*@opt all
*/
enum ControlClass {
    MAIN_MENU,
    MEMORY,
    DICT,
    EXAM,
    TEXT,
    QUIT
}
/**
*@opt all
*/
class ControlFactory {
  public Control make(ControlClass controlClass);
}
)

如图\ref{mainloop}，`MainLoop`在程序刚开始运行时初始化、加载数据库。初始化完毕后即由主函数调用其`run()`方法。由`setControl()`方法调用`ControlFactory`创建当前使用的控制类对象，其参数是枚举类`ControlClass`的成员。第一次调用时该参数为`ControlClass::MAIN_MENU`（显示主菜单）。对应的控制类对象根据用户输入调用`MainLoop`对象的`setControl()`方法。此时`MainLoop`对象销毁原有的控制类对象，根据给定的参数调用`ControlFactory`创建新的控制类对象。直到`ControlClass::QUIT`对应的控制类的对象被创建，该控制类调用`MainLoop`对象的`stop()`方法，程序运行结束。

唯一的`MainLoop`类对象自始至终控制了整个程序的运行流程。

###数据相关的类：`Database`和`Record`

这两个类负责管理所有词库和历史记录的数据。其中`Database`将数据从文件读入内存，以键-值映射的形式，通过`std::map`容器存储，供程序快速访问。上述映射的值，是`Record`的派生类的指针。每个`Record`的派生类代表一种数据的结构，这个程序中用到的有`WordRecord`和`HistoryRecord`（分别对应单词和历史记录）。

####`Record`

![Record及其派生类\label{record}](http://g.gravizo.com/g?
/**
*@opt all
*@note template<class KeyType>
*/
class Record {
  public Record(string str);
  public string toString();
  public KeyType getKey();
  KeyType key;
}
/**
*@opt all
*/
class WordRecord extends Record {
  public WordRecord(string str);
  public string toString();
  public KeyType getKey();
  string explanation;
  string example;
  Group group;
  vector answers;
  vector algorithmOutput;
}
/**
*@opt all
*/
class HistoryRecord extends Record {
  public HistoryRecord(string str);
  public string toString();
  public KeyType getKey();
  long timestamp;
}
/**
*@opt all
*/
enum Group {
    UNSEEN,
    LEARN,
    YOUNG,
    MATURE,
    RELEARN,
    SUSPENDED,
    ALL 
}
)

如图\ref{record}，`Record`及其派生类的共有接口包括以`std::string`作为参数的构造函数、`getKey()`（返回键）和`toString()`（将记录表示为一个字符串，对应于文件中的一行）。构造函数和`toString()`是一对互逆的操作，实现文件中的一行和内存中`std::map`中一条记录的双向转换。

`WordRecord`和`HistoryRecord`继承`Record`，在基类的基础上分别添加了各自所需的字段（对应的setter和getter函数在图中未画出）。

####`Database`

![Database及其派生类\label{database}](http://g.gravizo.com/g?
/**
*@opt all
*@note template<class KeyType, class RecordType>
*/
class Database {
  public void load(string fileName);
  public RecordType get(KeyType key);
  public void add(KeyType key, RecordType record);
  public void update(KeyType key);
  public void commit();
  map keyRecordMap;
}
/**
*@opt all
*@note template<class KeyType, class RecordType>
*/
class TextDatabase extends Database {
  public void load(string fileName);
  public RecordType get(KeyType key);
  public void add(KeyType key, RecordType record);
  public void update(KeyType key);
  public void commit();
  map keyRecordMap;
  map keyTextMap;
}
)

如图\ref{database}，`Database`类使用的模板方法。键、值的类型都可以改变，只要两者相匹配（即`KeyType`和`RecordType`所对应的键类型相同）即可。`Database`的实现与存储的数据类型（`RecordType`）无关；就文本数据库而言，只要后者支持`toString()`接口即可。

`Database`将数据在底层的存储方式抽象出来，由其派生类处理。现在程序中只实现了`TextDatabase`（即一行一个单词的纯文本数据库）这一个派生类，但在程序架构上容易向其他格式的数据库（如json、SQLite、各种nosql数据库）扩展，只需实现相应的派生类即可，不影响`Database`类的接口，也就不影响程序的其他部分。

`Database`的主要接口描述如下：

- `void load(std::string fileName)`: 将文件内容转换为`std::map<KeyType, RecordType*>`，加载到内存中。
- `RecordType* get(KeyType key)`: 返回给定key所对应的记录。
- `void add(KeyType key, RecordType record)`: 将给定的key-value对加入数据库中；如果key已经存在，抛出异常。
- `virtual void update(KeyType key) = 0`: 将对给定key所作的更改进行暂存，准备写入文件。这个接口的行为取决于派生类所对应数据的存储方式。如，在`TextDatabase`中，这个方法的功能是将`keyRecordMap`中的更改同步到`keyTextMap`中。
- `virtual void commit()`: 将所有更改写入文件。由于这个操作的I/O消耗很大，应控制调用频率。如，当前只有在返回主菜单时才进行写入操作。

特别地，`TextDatabase`除了所有`Database`都具有的`keyRecordMap`之外，还维护了一份`keyTextMap`，即将key映射到记录的字符串表示。其`update()`方法的功能就是调用`Record`的`toString()`方法，将`keyRecordMap`的更改同步到`keyTextMap`。这样，在调用`commit()`方法时，不必对每条记录都调用`toString()`（对于有修改的记录，之前已经调用过了），只需将`keyTextMap`中的字符串逐行写入文件即可，以多消耗一部分空间为代价提高了程序的运行速度。

###核心逻辑：`Control`

![Control及其派生类\label{control}](http://g.gravizo.com/g?
/**
*@opt all
*/
class Control {
  public Control(MainLoop mainLoop);
  public void showView();
  void setView();
  View view;
  ViewClass viewClass;
  MainLoop mainLoop;
}
/**
*@opt all
*/
interface ChooseGroupInterface {
  public void chooseGroup(Group group);
}
/**
*@opt all
*/
interface EditExampleInterface {
  public void editExample();
}
/**
*@opt all
*/
interface PagerInterface {
  public void previousPage();
  public void nextPage();
}
/**
*@opt all
*/
interface StringHandlerInterface {
  public void handleString(string str);
}
/**
*@opt all
*/
enum ControlClass {
    MAIN_MENU,
    MEMORY,
    DICT,
    EXAM,
    TEXT,
    QUIT
}
/**
*@opt all
*/
enum Group {
    UNSEEN,
    LEARN,
    YOUNG,
    MATURE,
    RELEARN,
    SUSPENDED,
    ALL 
}
class MainMenuControl extends Control {
}
class MemoryControl extends Control implements ChooseGroupInterface, EditExampleInterface, StringHandlerInterface {
}
class DictControl extends Control implements EditExampleInterface, PagerInterface, StringHandlerInterface {
}
class ExamControl extends Control implements ChooseGroupInterface {
}
class TextControl extends Control implements PagerInterface, EditExampleInterface, StringHandlerInterface {
}
class QuitControl extends Control {
}
)

如图\ref{control}，`Control`的每个派生类对应程序的一个功能模块。它们负责记录程序的运行状态、向视图类提供所需的数据。各个派生类都拥有各自的数据成员和接口，在图中未画出。

`MainLoop`循环调用当前控制类对象的`showView()`方法。该方法将视图类的内容显示到屏幕，并等待用户输入。用户输入由`View`, `Fragment`, `Widget`逐级委派进行处理（详见“视图相关的类”一节），最后（假设输入合法）由某一个`Widget`调用相应`Control`派生类中的相应方法（图中未画出），再由该方法对输入进行处理后调用`setView()`方法，完成一个循环。

`setView()`销毁之前的视图类对象，根据给定的参数委派工厂方法`ViewFactory`创建新的视图类对象，这样就实现了显示页面的跳转。

下以`ReviewControl`为例说明`Control`派生类的工作机制（如图\ref{memorycontrol}）:

![MemoryControl\label{memorycontrol}](http://g.gravizo.com/g?
/**
*@opt all
*/
class MemoryControl extends Control implements ChooseGroupInterface, EditExampleInterface, StringHandlerInterface {
    public MemoryControl(MainLoop mainLoop);
    public void chooseGroup(Group group);
    public void editExample();
    public void handleString(string str);
    public void backToMainMenu();
    public void addAnswer(int ans);
    public void showAnswer();
    WordIterator mWordIterator;
    string mCurrentWord;
    void continueMemory();
    Group mMemoryGroup;
}
interface ChooseGroupInterface {
}
interface EditExampleInterface {
}
interface StringHandlerInterface {
}
)

`ReviewControl`对应的初始`View`为`ChooseCategoryView`。该`View`中的`Option`（`Widget`的一种派生类）监听到用户所选择的类别，调用`ReviewControl`的`chooseGroup()`方法。`chooseGroup()`根据传入的参数设置数据成员`mGroup`，并调用算法模块中的`WordIterator`得到待复习单词的迭代器的指针，存储在数据成员`mWordIterator`中。

随后，`chooseGroup()`调用`continueMemory()`方法，加载待复习的单词。后者调用`setView()`，在复习尚未完成时设置为`ReviewQuestionView`，复习完成后（即`mWordIterator.next()`返回空字符串）设置为`ReviewCompleteView`。同时`mCurrentWord`被设置为当前的单词。

`ReviewQuestionView`中，用户输入`a`，选择`a) show answer`时，后者（对应于`ReviewShowAnswerOption`）调用`ReviewControl`的`showAnswer()`方法。后者调用`setView()`，设置为`ReviewAnswerView`。值得注意的是，创建`View`的任务是`ViewFactory`完成的。后者是`Control`及其派生类的友元，因而能够便捷地通过访问`ReviewControl`的私有数据成员并结合数据库查询得到创建`View`所需要的信息（在当前场景中即当前单词及其解释、例句）。

接下来，用户输入自己对当前单词的熟悉程度（0到3之间的整数，详见“算法模块”一节）。对应的`Option`调用`ReviewControl`的`addAnswer()`方法。后者与算法模块进行交互，更新单词条目的相关数据（调用`WordRecord`的`addAnswer()`和`setAlgorithmOutput()`方法），将变动上传到数据库（`Database`的`update()`方法）。当前单词处理完后，调用`continueMemory()`方法，依此类推，直到复习完。

当然，如果用户选择了编辑例句或返回主菜单，`editExample()`或`backToMainMenu()`方法将被调用，由它们进行相应的数据更新和视图跳转即可。

其他`Control`派生类的工作原理和实现思路都和`MemoryControl`大同小异。由于细节比较琐碎，这里不再一一赘述。

###视图相关的类：`View`, `Fragment`, `Widget`和`Display`

####视图的层级

如图\ref{mvc}所示，视图是程序中直接与用户发生交互的部分。经过初步的用户界面设计，我们发现，视图中有一些部分是反复出现的。将这些部分重用，不仅可以减少代码冗余，更方便了界面的较大幅度调整（比如本土化）。因此，我们将视图分为三个层级，如图\ref{view_structure}所示。


![视图层级\label{view_structure}](http://g.gravizo.com/g?
/**
*@composed - - n Widget
*/
class Fragment {
}
/**
*@composed - - n Fragment
*/
class View {
}
class Widget {
}
/**
*@opt all
*/
class Label extends Widget {
  string mHintText;
}
/**
*@opt all
*/
class TextInput extends Widget {
  string mHintText;
}
/**
*@opt all
*/
class MaxNumberInput extends TextInput {
  string mHintText;
  int mMaxNumber;
}
/**
*@opt all
*/
class Option extends Widget {
  string mHintText;
  string mKey;
}
)

`View`是顶层的视图，一个`View`包含一个或多个`Fragment`，一个`Fragment`包含一个或多个`Widget`。

`Widget`是视图的最小单位。它又可以分为三种种类：

- `Label`：最简单的视图单位，显示一行文字，不处理输入。
- `TextInput`：显示一行提示文字，并允许用户输入一个字符串。
 - `MaxNumberInput: public TextInput`：在`TextInput`的基础上检查输入是否是不大于给定上界的正整数。
- `Option`：对应于图形界面中的按钮。显示一行提示文字，并绑定一个字符串（一般是一个字母或数字）作为key。输入该字符串，则相当于点击了按钮。

####视图的显示

`View`, `Fragment`和`Widget`描述了视图的逻辑结构，而其呈现通过委托的方式交给`Display`处理。`Display`的结构如图\ref{display}所示。


![Display和TextDisplay\label{display}](http://g.gravizo.com/g?
/**
*@opt all
*/
class Display {
  public void show(View view);
  public string getInput();
  public string reInput();
}
/**
*@opt all
*/
class TextDisplay extends Display {
  public void show(View view);
  public string getInput();
  public string reInput();
}
)

现在，`TextDisplay`是`Display`唯一的派生类。它的功能只是简单地调用`View`的`toString()`方法（`View`的`toString()`会依次调用下属`Fragment`的`toString`，后者又会依次调用下属`Widget`的`toString()`）将结果输出到标准输出，以及从标准输入读取字符串。但是在此基础上不难实现图形界面拓展：重新编写`Display`的派生类即可。

####输入的处理

处理输入时，先由`Display`读入一个字符串，交由`View`的`handleInput()`方法处理。处理方式类似于“责任链原则”：`View`的`handleInput()`依次调用`Fragment`的`handleInput()`，后者再依次调用`Widget`的`handleInput()`。在整个过程中，一旦有`Widget`成功处理了输入（调用了当前`Control`的相应接口），则流程短路、此次输入处理完毕。若遍历完所有`Widget`后输入仍未被处理，则调用`Display`的`reInput()`方法，提示用户输入非法、重新输入。

###算法模块

算法模块供记忆模式使用，负责调整单词的分组、难度系数和复习优先级。这一部分与程序主体相对独立，因此单独编译为动态链接库、在运行时与主程序动态链接。

在实现时，我们采用了著名的[SuperMemo2](https://www.supermemo.com/english/ol/sm2.htm)记忆算法、并借鉴了记忆软件[Anki的分组策略](http://ankisrs.net/docs/manual.html#types-of-cards)。

沿用Anki的分组名称，我们将所有单词分为6组：

- **unseen**: 所有用户未曾复习过的单词默认属于这一分组。
- **learn**: 用户正在学习，即初次见到且不熟悉的单词。
- **young**: 用户在较短的一段时间之前学习，仍有待巩固的单词。
- **mature**: 用户在较长的一段时间之前学习，已经比较熟悉的单词。
- **relearn**: 用户之前已经掌握，又遗忘的单词。
- **suspended**: 因被用户标记为“不认识”的次数太多而被特殊处理的单词。

此外，根据SM2算法，每个单词还拥有$EF$和$I$两个浮点数属性，分别表示单词的难度系数和距离下次复习的间隔。

每次用户复习一个单词，须从0~3中选择一个整数表示自己对该单词的熟悉程度：

```plain
0) I do not know this word.
1) I managed to recall it with some hesitation.
2) I'm quite familiar with it.
3) I'm perfectly familiar with it!
```

根据用户的输入和单词先前的分组和$EF,I$数据，调用`recito_algorithm`模块中的`group()`和`interval()`两个函数，调整分组并计算新的$EF,I$。

此外，`recito_algorithm`模块还提供`WordIterator`类，将需要复习的单词按$I$值升序排序，以迭代器的形式返回给主程序。

##词库和历史记录文件的格式

词库和历史记录文件的一行分别与`WordRecord`和`HistoryRecord`类的结构相对应。通过这两个类的构造函数和`toString()`方法可实现`Record`和文件中存储的字符串之间的双向转换。

###词库文件的格式

词库文件中，一行代表一个单词，依次包含以下字段：

- 单词
- 例句
- 解释
- 分组信息
	- 从0到5分别代表unseen, learn, young, mature, relearn, suspended
- 复习间隔和难度系数信息（用`;`分隔）
	- 分号前后分别对应SM2算法中的$EF$和$I$（参见“算法模块”一节），对于未曾复习的单词都用0表示。

字段与字段之间用Tab字符（`'\t'`）分隔。

###历史记录文件的格式

历史记录文件中，一行代表一个单词，依次包含以下字段：

- 单词
- 时间戳（最后一次查询时间的毫秒表示）

字段与字段之间用Tab字符（`'\t'`）分隔。

##软件测试

为提高程序模块运行的概率，我们在开发的过程中采用了单元测试的方法。使用的是开源C++测试框架[https://github.com/philsquared/Catch](Catch)。

在整合入主程序前，对帮助函数、命令行解析器、算法模块、`Database`、`Record`进行了正确性测试。

##跨平台解决方案

为了实现跨平台的编译链接，我们使用`cmake`生成构建信息。由于所有源代码都是平台无关的，配置好`cmake`后可以在不同平台下用完全相同的源码编译链接。

此外，`cmake`配置灵活、非常便捷地实现了算法模块作为动态链接库的要求。

##现阶段的不足

- 词库文件体积较大时，加载缓慢。可能的解决方案：
	- 使用更加高级的数据库解决方案取代纯文本数据库。
	- 在仍使用文本数据库的情况下，作为折中，将文件I/O单独放在一个线程而不阻塞主线程，减少用户等待。
- 如果需要除了`WordRecord`和`HistoryRecord`之外其他的记录类型，需要为`Record`类定义新的派生类。定义派生类的过程略显繁琐、不够灵活。可能的解决方案：
	- 参考[https://github.com/paulftw/hiberlite](https://github.com/paulftw/hiberlite)，通过使用宏等更加高级的C++语言技巧，增强代码的表达能力，实现ORM(Object Relation Model)的灵活定义。
- 视图相关的类(`View`, `Fragment`, `Widget`)派生类数量庞大，代码非常繁琐。可能的解决方案：
	- 考虑用XML等标记语言描述视图（需要引入相应的解析库）。这样不仅大大简化了新视图的创建，还增强了视图的灵活性：可以更便捷地实现CLI, GUI, Web等多种界面。

