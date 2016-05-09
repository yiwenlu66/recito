##Design Documentation

##Classes

- `main`
	- main function
		- show usage if `--help` is in command line argument
		- else instantiate `CommandLineParser`
	- `CommandLineParser`
		- `CommandLineParser(int argc, char* argv[]);`
		- `bool keyExists(string key);`
		e.g. for `./recito --help`, `keyExists("--help")` returns `true`
		- `string getValue(string key);`
		e.g. for `./recito -d dict.txt`, `getValue("-d")` returns `"dict.txt"`. Return `""` if the key does not exist or the value is empty.

	- `Record<KeyType>`
		- `virtual Record<KeyType>(string);`
		- `virtual string toString();`
		- `WordRecord: public Record<string>`
			- `virtual WordRecord(string);`
			- `virtual string toString();`
			- `string key;`
			- `string explanation;`
			- `string example;`
			- `Group group;`
			- `vector<int> answers;`
			- `vector<double> algorithmOutput;`
		- `HistoryRecord: public Record<string>`
 			- `virtual HistoryRecord(string);`
			- `virtual string toString();`
			- `string key;`

	- `Database<KeyType, RecordType>`
		- private `map<KeyType, RecordType*> mKeyRecordMap`
		- `virtual void load(string fileName);`
	 	- `RecordType* get(KeyType key);`
	 	- `virtual void add(KeyType key, const RecordType& record);`
		 	raise exception for duplicate key
		- `virtual void update(KeyType key) = 0;`
		- `virtual void commit() = 0;`
		- `TextDatabase: public Database`
			- private `map<KeyType, string> mKeyTextMap`
			- `virtual void update(KeyType key);`
			stage changes for commit (sync the key to `mKeyTextMap`)
			- `virtual void add(KeyType key, const RecordType& record);`
			extend `Database<KeyType, RecordType>::add()` by syncing to `mKeyTextMap`
	- `Widget`
		- `virtual bool handleInput(string)`
			do nothing in the base class; return `true` if the input is handled
		- `virtual string toString()`
		- `Label: public Widget`
			- `Label(string)`
			- `virtual string toString()`
		- `Input: public Widget`
			- `Input(string key, string hintText)`
			- `virtual string toString()`
			- `void handleInput(string)`
	- `Fragment`
		- private `vector<Widget*> widgets`
		- `virtual string toString()`
		- `void handleInput(string)`
	- `View`
		- private `vector<Fragment*> fragments`
		- `virtual string toString()`
		- `void handleInput(string)`
		- private `Display* mDisplay`
		- `void show()`
			- call `mDisplay->show()`
	- `Display`
		- `virtual void show(const View&)`
		- `TextDisplay: public Display`
			- `virtual void show(const View&)`
	- `enum class ViewClass {MAIN_MENU, CHOOSE_CATEGORY, REVIEW_QUESTION, REVIEW_ANSWER, REVIEW_COMPLETE, DICT_MENU, DICT_INPUT, DICT_HISTORY, DICT_WORD, DICT_WORD_NOT_EXIST, EXAM_CHOOSE_NUMBER, EXAM_QUESTION, EXAM_ANSWER, EXAM_COMPLETE, TEXT_CHOOSE_FILE, TEXT_FILE_CHOSEN, TEXT_WORD, EDIT};`
	make subclasses of `View` correspondingly
	- `Control`
		- private `bool mRun`, `View* mView`
		- `void stop()`
		- `void setView(ViewClass)`
		delete old view and set new view (use `ViewFactory`)
		- `const View& getView()`
		- `void showView()`
		- `void waitForInput()`
	- `ViewFactory`
		- `View* make(ViewClass)`
			read information from `Control` and redirect if necessary
	- common utilities
		- `vector<string> split(string s, string delimiter)`
- `algorithm`
details TBA


- classes common to `main` and `algorithm`:
	- `enum class Group {UNSEEN, LEARN, YOUNG, MATURE, RELEARN, SUSPENDED};`

##Coding style
- Please conform to the [Allman coding style](https://en.wikipedia.org/wiki/Indent_style#Allman_style).
- Use `camelCase` for object names, and `UpperCamelCase` for class names. Prefix private member variables with `m`: `mPrivateMemberVariable`.
- Use spaces instead of tabs; 4 spaces for a tab.

