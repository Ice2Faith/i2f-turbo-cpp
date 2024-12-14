#ifndef _CHINESECODEC_H_
#define _CHINESECODEC_H_

#define USE_KEYWORD
#define USE_MOST_SYMBOL
#define USE_OTHER_SYMBOL
#define USE_LANG_EXTEND

#if defined  USE_KEYWORD //key word

#define 型整		int
#define 型短浮点	float
#define	型长浮点	double
#define 型字符		char
#define 型字		byte
#define 型长整		long
#define 型枚举		enum
#define 枚举		enum
#define 型布尔		bool
#define 常量		const
#define 型短整		short
#define 静态		static
#define 寄存器		register
#define 结构体		struct
#define 联合体		union
#define 无符号		unsigned
#define 型空		void
#define 型万能指针	void *
#define 真			true
#define 假			false
#define 自动		auto
#define 返回		return
#define 新建		new
#define 删除		delete
#define 重复		for
#define 循环		while
#define 当			while
#define 做			do
#define 继续		continue
#define 跳出		break
#define 如果		if
#define 若			if
#define 否则		else
#define 选择		switch
#define 选择项		case
#define 匹配		switch
#define 符合		case
#define 默认		default
#define 跳转		goto
#define 类			class
#define 内联		inline
#define 私有		private
#define 保护		protected
#define 公有		public
#define 友元		friend
#define 操作符		operator
#define 自我		this
#define 模板		template
#define 类型定义	typedef
#define 类型名		typename
#define 虚			virtual
#define 虚拟		virtual
#define 尝试		try
#define 抓取		catch
#define 抛出		throw
#define 使用		using
#define 命名空间	namespace
#define 占用		sizeof
#define 大小为		sizeof

#endif //key word

#if defined USE_MOST_SYMBOL //most symbol

#define 非			!
#define 或			||
#define 与			&&
#define 或者		||
#define 并且		&&
#define 取地址		&
#define 引用		&
#define 指针		*
#define 取值		*
#define 解地址		*
#define 模			%
#define 加			+
#define 减			-
#define 乘			*
#define 除			/
#define 模以		%
#define 加上		+
#define 减去		-
#define 乘上		*
#define 除以		/
#define 赋值		=
#define 值为		=
#define 等于		==
#define 不等于		!=
#define 大于		>
#define 小于		<
#define 大等于		>=
#define 小等于		<=
#define 成员		::
#define 域内		::
#define 位与		&
#define 位或		|
#define 位反		~
#define 析构		~
#define 位异或		^
#define 位左移		<<
#define 位右移		>>
#define 输出		<<
#define 输入		>>
#define 自增		++
#define 自减		--
#define 自加上		+=
#define 自减去		-=
#define 自乘上		*=
#define	自除以		/=
#define	自模以		%=
#define 自与上		&=
#define	自或上		|=
#define	自异或		^=
#define 自右移		>>=
#define 自左移		<<=

#endif //most symbol


#if defined USE_OTHER_SYMBOL //other symbol

#define ，			,
#define 联			,
#define 。			.
#define 提取		->
#define	取			.
#define ？			?
#define ！			!
#define ；			;
#define 终			;
#define 言(a)		""#a""
#define 索引(a)		[a]
#define 含结		()
#define 含			(
#define 结			)
#define （）		()
#define （			(
#define ）			)
#define 界			[]
#define 【】		[]
#define 下界		[
#define 上界		]
#define 【			[
#define 】			]
#define 笺			<>
#define 下笺		<
#define 上笺		>
#define 《			<
#define 》			>
#define ：			:
#define 如			:
#define 列下			:
#define 继承		:
#define 是真则		?
#define	假则		:
#define 起止		{}
#define 起			{
#define 止			}
#define 止终		};

#endif //other symbol

#if defined USE_LANG_EXTEND //lang extend

#define 主函数		main
#define 空			NULL
#define 汇编		asm
#define 标准		std
#define 系统		system

#define 函数 
#define 有术  
#define 有量 
#define 使用命名空间 using namespace

#define 打印		printf
#define 获取		scanf
#define 串打印		sprintf
#define 文件打印	fprintf
#define 文件获取	fscanf
#define 文件写入	fwrite
#define 文件读取	fread
#define 获取字符	getchar
#define 获取字符串	gets
#define 刷新缓冲法(a)	fflush(a)
#define 清空输入缓冲	fflush(stdin)
#define 字符串长度(a)	strlen(a)
#define 字符串拷贝(a,b)	strcpy(a,b)
#define 字符串匹配(a,b)	strcmp(a,b)
#define 字符串拼接(a,b)	strcat(a,b)
#define 时间法(a)	time(a)
#define 设置种子法(a)	srand(a)
#define	正弦法(a)	sin(a)
#define 余弦法(a)	cos(a)
#define	正切法(a)	tan(a)
#define 幂乘法(a,b)	pow(a,b)
#define	开方法(a)	sqrt(a)
#define 绝对值(a)	abs(a)
#define 输出流		cout
#define 输入流		cin
#define 流换行符	endl
#define 流空字符	ends
#define 十进制		dec
#define 十六进制	hex
#define 八进制		otc
#define 小数位数（A）	setsprecision(A)	/*设置小数位数，包含小数点*/
#define 域宽（A）		setw(A)				/*设置域宽*/

#define 型文件 FILE 
#define 型文件指针 FILE *
#define 打开文件		fopen
#define 关闭文件		fclose


#define 标准输入输出头		<stdio.h>
#define 标准链接头			<stdlib.h>
#define 标准时间头			<time.h>
#define 标准数学头			<math.h>
#define 标准字符串头		<string.h>
#define 标准非阻塞输入输出头 <conio.h>
#define 标准输入输出流		<iostream>
#define 标准文件流			<fstream>
#define 标准文件输入流		<ifstream>
#define 标准文件输出流		<ofstream>
#define	标准字符串			<string>
#define 标准向量			<vector>
#define 标准函数			<functional>
#define 标准算法			<algorithm>
#define 标准双端队列		<deque>
#define 标准单向队列		<queue>
#define 标准栈				<stack>

#define 型字符串		string
#define 型文件流		fstream
#define 型输入文件流	ifstream
#define 型输出文件流	ofstream
#define 型向量			vector
#define 型双端队列		deque
#define 型单向队列		queue
#define 型栈			stack
#define 型具向量(a)			vector<a>
#define 型具双端队列(a)		deque<a>
#define 型具单向队列(a)		queue<a>
#define 型具栈(a)				stack<a>
#define 型时间			time_t
#define 型时间结构		struct tm
#define 型时间结构指针	struct tm *
#define 本地时间法(a)	localtime(a)
#define 时间年			tm_year
#define 时间月			tm_mon
#define 时间日			tm_mday
#define 时间时			tm_hour
#define 时间分			tm_min
#define 时间秒			tm_sec

#define 入栈			push
#define 入栈法(a)		push(a)
#define 出栈			pop
#define 出栈法(a)		pop(a)
#define 栈顶			top
#define 栈顶法(a)		top(a)
#define 测大小法()		size()
#define 置后			push_back
#define 置前			push_front
#define 取后			pop_back
#define 取前			pop_front
#define 置后法(a)		push_back(a)
#define 置前法(a)		push_front(a)
#define 取后法(a)		pop_back(a)
#define 取前法(a)		pop_front(a)
#define 试空法()		empty()
#define 取串法()		c_str()
#define 追加法(a)		append(a)
#define 取索引值法(a)	at(a)
#define 清空法()		clear()
#define 始迭代法()		begin()
#define 止迭代法()		end()
#define 测容量法()		capacity()
#define 测长度法()		length()

#define 常量派 3.141592653549

#define 介于(c,a,b)	((c)>=(a) && (c)<=(b))
#define 真介于(c,a,b)	((c)>(a) && (c)<(b))
#define 不介于(c,a,b)	((c)<=(a) || (c)>=(b))
#define 真不介于(c,a,b)	((c)<(a) || (c)>(b))

#define 内存申请(type,count)	((type##*)malloc(sizeof(type)*(count)))
#define 内存释放(pointer)		free(pointer);

#define 设置随机种子	srand((unsigned int)time(NULL))
#define 随机数		rand()

#endif  //lang extend

#endif // _CHINESECODEC_H_