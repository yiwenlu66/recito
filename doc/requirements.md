1. 支持中英文对于单词的解释和对应例句，即在一个意思下输出一系列例句。
2. 在输出单词解释时默认输出和标注用户添加的例句，并标注添加时间（在原有释义下添加例句）还有单词难度级别。
3. 命令行模式读取命令，多层次菜单式命令，先是模式选择命令，再是具体的。都有退回上一级目录的命令。
4. 支持字典模式即单纯查询给定单词释义的命令（包括字典中的中英文解释，对应例句以及用户的添加的例句）。
5. 支持进入单词记忆模式，*总词库分为n(n>=1)个大组，每个大组内有一定数量的单词，每次记忆训练时选择一个大组进行记忆。单次训练时是在这个大组中选去一定数量的单词，每次产生一个单词，用户输入是否认识，认识或不认识均进行记录，当一个单词连续几次被标为认识或不认识时调整难度标级，不同难度的单词需要出现在单次训练时的频率不同。* 有多个记忆模式。
6. 支持进入词汇量测试模式，用户可以挑选一个大组的单词进行词汇测试，每次有一定数量m的题目，用户选择单词的正确意思。程序进行正确率统计(或者把这整个叫做测试策略，也可以改变)。
7. 支持进入编辑模式，包括各种策略的调整，单词例句添加等等（这里用户的权限暂定）。
8. 支持进入文本阅读模式，统计给定文本文件中的生词，并在控制台窗口中输出生词及生词解释。
9. 单词难度自动调整，基于用户记忆单词结果和用户单词测试结果。
10. //其实宝宝还想支持多用户模式，即另加一个文件来记录用户信息。
11. //这样可以给出用户单独的评级。

接口：进入时命令行跳出：
“Please choose :M for (Memory method),D for (Dictionary Method),L for (Test Method),E for (Edit Method),T for(Text Method) Q for(quit):"

	input "M":
	"[A word]   do you know (y/n) (q to quit and go back to previous menu):" 
	...
	"Congratualtions you have completed this mission"

	input "D": 
		"Please input the word you want to check(q to quit and go back to previous menu):"
			Explanation 1: Example sentence 1;Example sentence 2...  (if the sentence is added by the user ,show the editor and the time)
			Explanation 2:Example sentence 1;Example sentence 2
			.
			.
			.
			"(any input to go back to previous menu)"



	input "L":
		"[ask a question](q to quit and go back to previous menu)"
		...
		"Congratualtions you have completed this test you score is[a number](any input to go back to previous menu)"

	input "E":
		"M for(change memory stragety),T for (change Test stragety),W for (Adding sentence for certain word),q for(go back to previous menu)"
		input "M":
			"Please input the number of the chosen stragety 1.[Stragetyname1]2.[Stragetyname2]...(q to quit and go back to previous menu)"
			"stragety changed(any input to go back to previous menu)"
		input "T":
			"Please input the number of the chosen stragety 1.[Stragetyname1]2.[Stragetyname2]...(q to quit and go back to previous menu)"
			"stragety changed(any input to go back to previous menu)"
		input "W":
			"Please input the word you are searching":
				Explanation 1: Example sentence 1;Example sentence 2...  (if the sentence is added by the user ,show the editor and the time)
				Explanation 2:Example sentence 1;Example sentence 2
				.
				.
				.
				"Please input a number for the Explanation you1 want to add a sentence(q to quit and go back to previous menu)":
				"Please input the sentence(q to quit and go back to previous menu)":
				"done(any input to go back to previous menu)"
	input"T":
		"Please input a filename(q to quit and go back to previous menu)"
		show:
		the unfamilar word1:all the explanations
		...
		"done(any input to go back to previous menu)"
		
All invalid input will result in the output:
	"invalid (any input to continue)"
then the program will repeat the last operation.



