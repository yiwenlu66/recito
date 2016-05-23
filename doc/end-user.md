#用户文档

##简介

本项目是一款多功能的命令行单词记忆与查询软件，实现了如下功能：

- 记忆模式：基于著名的[SuperMemo2算法](https://www.supermemo.com/english/ol/sm2.htm)，根据用户输入的对单词的熟悉程度，自动对单词进行分组；支持对选定组别的单词进行复习。
- 词典模式：查询用户输入的单词，或选择历史记录中的条目进行查询。
- 测试模式：由用户选定组别和单词数量，进行在线单词测试。给出答题正确率。
- 文本模式：统计用户指定的文本文件中的单词，给出解释。
- 所有单词可由用户自行添加和编辑例句。
- 词库为方便人类阅读和编辑的纯文本文件，一行一个单词。用户可以自定义词库。随软件附属提供辅助生成词库的脚本。

程序主体部分全部由C++及其标准库实现，可以跨平台编译和运行。

##编译

###环境要求

构建和编译需要如下依赖：

- `cmake >= 3.1`
- `make`或其他构建工具（如Visual Studio）
- 支持C++11标准的C++编译器

理论上可以在满足以上依赖的任何平台下编译和运行。受条件所限，我们在如下平台下进行了测试：

- Linux, `gcc 5.3.0`
- Windows 10, Visual Studio 2015
- Cygwin, `gcc 5.3.0`

###生成项目文件

```bash
cd recito/
cmake .
```

###编译

```bash
make
```

或用IDE打开生成的项目文件进行操作。


##运行

用法：
```plain
./recito [--help] [-d <main database file name>] [-h <history file name>]
```

命令行参数：
- `--help`：显示帮助
- `-d`：主词库文件（默认：`res/dict.txt`）
- `-h`：历史记录文件（默认：`history.txt`）

##关于各个模式的使用说明

###主菜单

程序开始运行后即进入主菜单，界面如下：

```plain
Please choose a mode:
m) memory mode
d) dictionary mode
e) exam mode
t) text mode
q) quit

```

通过键盘输入一个字母后敲击Enter键即可进入相应的模式。

**注：**由于默认加载完整词库，当前版本（尤其在Windows下）主菜单可能加载缓慢。用户可以通过裁剪词库（见“自定义词库”一节）提高运行速度。

###记忆模式

####记忆算法简介

#####单词分组

所有单词根据用户的熟悉程度分成6组，由程序根据用户反馈自动调整组别：

- **unseen**: 所有用户未曾复习过的单词默认属于这一分组。
- **learn**: 用户正在学习，即初次见到且不熟悉的单词。
- **young**: 用户在较短的一段时间之前学习，仍有待巩固的单词。
- **mature**: 用户在较长的一段时间之前学习，已经比较熟悉的单词。
- **relearn**: 用户之前已经掌握，又遗忘的单词。
- **suspended**: 因被用户标记为“不认识”的次数太多而被特殊处理的单词。

这种分组方式借鉴了著名的记忆软件Anki。关于这些分组的详细说明，请参见[Anki的帮助文档](http://ankisrs.net/docs/manual.html#types-of-cards)。


#####间隔时间和难度系数
在分组的同时，程序也根据用户反馈调整单词的复习间隔时间和难度系数。这些数据对用户不可见，但是决定了单词复习的顺序。它们根据SuperMemo2算法计算得到。关于其详细说明，请参见[SuperMemo2](https://www.supermemo.com/english/ol/sm2.htm)。


####记忆界面及其操作

选择`m) memory mode`后，进入如下界面：

```plain
Please choose a category:
u) unseen
l) learn
y) young
m) mature
r) relearn
s) suspended
a) all
```

选择相应组别后即可开始复习。

显示单词后，如：

```plain
example
a) show answer
m) back to main menu
```

请回忆单词的含义，然后选择`a) show answer`，检查自己的回忆是否正确：

```plain
example
Explanation: 1. One or a portion taken to show the character or quality of the whole; a sample; a specimen.; 2. That which is to be followed or imitated as a model; a pattern or copy.; 3. That which resembles or corresponds with something else; a precedent; a model.; 4. That which is to be avoided; one selected for punishment and to serve as a warning; a warning.; 5. An instance serving for illustration of a rule or precept, especially a problem to be solved, or a case to be determined, as an exercise in the application of the rules of any study or branch of science; as, in trigonometry and   grammar, the principles and rules are illustrated by examples             .;
Example:
e) edit example
0) I do not know this word.
1) I managed to recall it with some hesitation.
2) I'm quite familiar with it.
3) I'm perfectly familiar with it!
m) back to main menu

```

如果需要编辑当前单词的例句，可以选择`e) edit example`，然后输入例句。以后例句就会在这个单词页面的"Example"一栏显示。

根据提示文字，选择`0`, `1`, `2`, `3`中的一个，告知程序自己对这个单词的熟悉程度，即可进入下一个单词。

一个组别的单词全部学习完后，将显示：

```plain
Congratulations! you have completed this mission.
m) back to main menu
```

如果一开始就看到此界面，说明选择的组别内没有单词。请重新选择组别（如all）开始学习。

如果中途不想继续复习，也可选择`m) back to main menu`返回主菜单。

**注：** 务必先返回主菜单，而非直接杀死程序。否则此次复习的结果将不会被保存到数据库中。


###词典模式

词典模式支持输入一个单词或从历史记录中选择条目。

词典模式的单词解释界面类似于记忆模式，同样可以编辑单词例句。

###测试模式

测试模式与记忆模式类似，进入时需要选择组别。选择组别后，还须选择测试单词的数目，如：

```plain
Please input the number of words you want to test yourself on:  (0~50)
```

这表示所选的组别内共有50个单词。输入一个不大于50的正整数即可开始测试。

单词测试界面中，如：

```plain
insiccation
a) 1. A small compartment in a desk or case for the keeping of letters, documents, etc.; -- so called from the resemblance of a row of them to the compartments in a dovecote.; 1. To place in the pigeonhole of a case or cabinet; hence, to put away; to lay aside indefinitely; as, to pigeonhole a letter or a report.;

b) 1. A term of reproach for a low or vulgar labor person.; 1. An excavating machine designed to remove particulate material from within a confined area, as in a tunnel or mine.;

c) 1. The act or process of drying in.;

d) 1. One who plates or coats articles with gold or silver; as, a silver plater          .; 2. A machine for calendering paper.; 1. A horse that runs chiefly in plate, esp. selling-plate, races; hence, an inferior race horse.;

m) back to main menu
```

从a, b, c, d中选择一个你认为正确的答案，随机程序会判断正确与否并显示正确答案。

测试完成后，程序会显示正确率：

```plain
Congratulations! You've completed the test with 20.00% accuracy
m) back to main menu
```


###文本模式

文本模式中，程序对指定的文本文件进行单词统计。文本中出现的单词，如果在词典中可以查询到，其解释会被逐一显示。如果查询不到，该单词将被忽略。

随程序附带的`sample.txt`可用于测试这一功能。

输入`sample.txt`作为文件名后：

```plain
dolor
Explanation: 1. Pain; grief; distress; anguish.;
Example:
e) edit example
n) next page
m) back to main menu
```

即"dolor"是该文件中第一个可以在词典中查询到的单词。同记忆模式、词典模式中一样，可以编辑例句。输入`n`可以显示下一单词：

```plain
sit
Explanation: 1. obs. 3d pers. sing. pres. of Sit, for sitteth.; 1. To rest upon the haunches, or the lower extremity of the trunk of the body; -- said of human beings, and sometimes of other animals; as, to sit on a sofa, on a chair, or on the ground.; 2. To perch; to rest with the feet drawn up, as birds do on a branch, pole, etc.; 3. To remain in a state of repose; to rest; to abide; to rest in any position or condition.; 4. To lie, rest, or bear; to press or weigh; -- with on; as, a weight or burden sits lightly upon him.; 5. To be adjusted; to fit; as, a coat sts well or ill.; 6. To cover and warm eggs for hatching, as a fowl; to brood; to incubate.; 7. To have position, as at the point blown from; to hold a relative position; to have direction.; 8. To occupy a place or seat as a member of an official body; as, to sit in Congress.; 9. To hold a session; to be in session for official business; -- said of legislative assemblies, courts, etc.; as, the court sits in January; the aldermen sit to-night.; 10. To take a position for the purpose of having some artistic representation of one's self made, as a picture or a bust; as, to sit to a painter.; 1. To sit upon; to keep one's seat upon; as, he sits a horse well.; 2. To cause to be seated or in a sitting posture; to furnish a seat to; -- used reflexively.; 3. To suit (well or  ill); to become.;
Example:
e) edit example
p) previous page
n) next page
m) back to main menu
```

单词之间可用`n`和`p`跳转，直到显示最后一个单词：

```plain
id
Explanation: 1. any document testifying to teh identity of the bearer, especially a card or badge.; 1. A small fresh-water cyprinoid fish (Leuciscus idus or Idus idus) of Europe. A domesticated variety, colored like the goldfish, is called orfe in Germany.; 1. That part of a person's psyche which is the unconscious source of impulses seeking gratification or pleasure; the impulses are usually modified by the ego and superego before being acted upon.;
Example:
e) edit example
p) previous page
m) back to main menu
```

此时只能转到前页，不能转到后页。

##自定义词库

词库和历史记录文件都是纯文本文件，便于手动编辑或用脚本生成。

###词库文件的格式

词库文件中，一行代表一个单词，依次包含以下字段：

- 单词
- 例句
- 解释
- 分组信息
	- 从0到5分别代表unseen, learn, young, mature, relearn, suspended
- 复习间隔和难度系数信息（用`;`分隔）
	- 分号前后分别对应[SuperMemo2算法](https://www.supermemo.com/english/ol/sm2.htm)中的$EF$和$I$，对于未曾复习的单词都用0表示。

字段与字段之间用Tab字符（`'\t'`）分隔。

###历史记录文件的格式

历史记录文件中，一行代表一个单词，依次包含以下字段：

- 单词
- 时间戳（最后一次查询时间的毫秒表示）

字段与字段之间用Tab字符（`'\t'`）分隔。

###词库生成脚本

默认的词库数据来源为[GCIDE](https://en.wikipedia.org/wiki/GCIDE)(GNU Collaborative International Dictionary of English)，以[GNU GPL协议](https://en.wikipedia.org/wiki/GNU_General_Public_License)发布。

词库文件由GCIDE的json版本（来自[https://github.com/javierjulio/dictionary/tree/master/dist/gcide](https://github.com/javierjulio/dictionary/tree/master/dist/gcide)）通过脚本`res/dict_generator.py`生成。修改脚本中的`FILE_LIST`，可以生成只包含部分字母开头的单词的子词库。

