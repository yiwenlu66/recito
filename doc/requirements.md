# 需求文档

## 功能描述
1. 支持对于单词的解释和例句。
2. 在输出单词解释时一并输出用户添加的例句。
3. 命令行模式读取命令，多层次菜单式命令，先是模式选择命令，再是具体的。都有退回上一级目录的命令。
4. 支持字典模式即单纯查询给定单词释义的命令（包括字典中的解释以及用户添加的例句）。
5. 支持进入单词记忆模式，*总词库根据用户熟悉程度自动分为n(n>=1)个大组[按照Anki中的称谓，Unseen/Learn/Young/Mature/Relearn/Suspended]，每个大组内有一定数量的单词，每次记忆训练时选择一个大组（或全部）进行记忆。单次训练时是在这个大组中选去一定数量的单词，每次产生一个单词，用户输入熟悉程度(0~3)，熟悉程度进行记录并调整难度标级。* 有多个记忆模式。
6. 支持进入词汇量测试模式，用户可以挑选一个大组的单词进行词汇测试，每次有一定数量m的题目，用户选择单词的正确意思。程序进行正确率统计(或者把这整个叫做测试策略，也可以改变)。
7. 支持进入编辑模式，例句添加等等。
8. 支持进入文本阅读模式，统计给定文本文件中的生词，并在控制台窗口中输出生词及生词解释。

##算法
- 算法模块提供三个函数：
	1. 间歇函数：基于SM2算法（https://www.supermemo.com/english/ol/sm2.htm）。输入EF,q,I，返回新的EF和I。
	2. 分组函数（参考anki: http://ankisrs.net/docs/manual.html#types-of-cards）：输入原分组、所有历史上的熟悉程度、由间歇函数给出的EI和I，返回新分组。
	3. 选择函数：输入候选的单词列表及其EF,I，以迭代器的形式返回下一个需要记忆的单词。

## 用户界面
- 默认词库文件：`dict.txt`，历史记录文件：`history.txt`。亦可通过命令行参数指定。词库文件不存在时报错。
- 进入时命令行输出:

    ```plain
    Please choose a mode:
    m) memory mode
    d) dictionary mode
    e) exam mode
    t) text mode
    q) quit
    ```

    - 用户输入`m`:
        - 首先：
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
	     - 用户选择分组后：

		        ```plain
		        {{word}}
		
		        a) show answer
		        m) back to main menu
		        ```
		    - 用户输入`a`后：
	
				```plain
				{{word}}
	
				Explanation: {{explanation}}
				
				Example: {{example}}
				e) edit example
	
				0) I do not know this word.
				1) I managed to recall it with some hesitation.
				2) I'm quite familiar with it.
				3) I'm perfectly familiar with it!
				m) back to main menu
				```
	
				- 若用户输入`0`，在结束前再复习一遍这个单词。
	
			- 分组中的所有单词记忆完毕：
	        
			    ```plain
		        Congratulations! you have completed this mission.
	
				m) back to main menu
		        ```

- 用户输入`d`:
	- 首先：
		
		```plain
		i) input word
		h) view history
		m) back to main menu
		```
		- 用户输入`i`：
		```plain
		Please input a word:
		```
		- 用户输入`h`：
		```plain
		0) {{word}}
		1) {{word}}
		2) {{word}}
		3) {{word}}
		4) {{word}}
		[p) previous page]
		[n) next page]
		m) back to main menu
		```

		- 用户输入单词或选择历史条目后：
			```plain
			{{word}}

			Explanation: {{explanation}}
			Example: {{example}}
			e) edit example

			n) look up another word
			m) back to main menu
			```

			或
			```plain
			Word {{word}} does not exist!

			n) look up another word
			m) back to main menu
			```

	- 用户输入`e`：
        - 首先：
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
			以及
			```plain
			Please input the number of words you want to test yourself on (0~{{max}}):
			```
	     - 用户指定分组和数量后：
		     ```plain
		     {{word}}
		     
		     a) {{explanation}}
		     b) {{explanation}}
		     c) {{explanation}}
		     d) {{explanation}}

			 m) back to main menu
		     ```
		     - 根据用户输入的答案：
		     ```plain
		     Correct!
		     ```
		     
			     或
		     
			     ```plain
			     Wrong! The answer is: {{answer}}.
			     ```
	     - 全部完成后：
		     ```plain
		     Congratulations! You've completed the test with {{percentage}}% accuracy.

			 m) back to main menu
		     ```

	- 用户输入`t`:
		- 首先：
		```plain
		Please input the file name:
		```
		- 用户输入文件名后：
			```plain
			Cannot open file!

			r) re-enter file name
			m) back to main menu
			```

			或
		
			```plain
			{{word}}

			{{explanation}}
			{{example}}

			[n) next word]
			m) back to main menu
			```

- 对所有非法输入：
	```plain
	Invalid input. Please re-enter:
	```
