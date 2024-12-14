#ifndef _CHINESECODEC_H_
#define _CHINESECODEC_H_

#define USE_KEYWORD
#define USE_MOST_SYMBOL
#define USE_OTHER_SYMBOL
#define USE_LANG_EXTEND

#if defined  USE_KEYWORD //key word

#define ����		int
#define �Ͷ̸���	float
#define	�ͳ�����	double
#define ���ַ�		char
#define ����		byte
#define �ͳ���		long
#define ��ö��		enum
#define ö��		enum
#define �Ͳ���		bool
#define ����		const
#define �Ͷ���		short
#define ��̬		static
#define �Ĵ���		register
#define �ṹ��		struct
#define ������		union
#define �޷���		unsigned
#define �Ϳ�		void
#define ������ָ��	void *
#define ��			true
#define ��			false
#define �Զ�		auto
#define ����		return
#define �½�		new
#define ɾ��		delete
#define �ظ�		for
#define ѭ��		while
#define ��			while
#define ��			do
#define ����		continue
#define ����		break
#define ���		if
#define ��			if
#define ����		else
#define ѡ��		switch
#define ѡ����		case
#define ƥ��		switch
#define ����		case
#define Ĭ��		default
#define ��ת		goto
#define ��			class
#define ����		inline
#define ˽��		private
#define ����		protected
#define ����		public
#define ��Ԫ		friend
#define ������		operator
#define ����		this
#define ģ��		template
#define ���Ͷ���	typedef
#define ������		typename
#define ��			virtual
#define ����		virtual
#define ����		try
#define ץȡ		catch
#define �׳�		throw
#define ʹ��		using
#define �����ռ�	namespace
#define ռ��		sizeof
#define ��СΪ		sizeof

#endif //key word

#if defined USE_MOST_SYMBOL //most symbol

#define ��			!
#define ��			||
#define ��			&&
#define ����		||
#define ����		&&
#define ȡ��ַ		&
#define ����		&
#define ָ��		*
#define ȡֵ		*
#define ���ַ		*
#define ģ			%
#define ��			+
#define ��			-
#define ��			*
#define ��			/
#define ģ��		%
#define ����		+
#define ��ȥ		-
#define ����		*
#define ����		/
#define ��ֵ		=
#define ֵΪ		=
#define ����		==
#define ������		!=
#define ����		>
#define С��		<
#define �����		>=
#define С����		<=
#define ��Ա		::
#define ����		::
#define λ��		&
#define λ��		|
#define λ��		~
#define ����		~
#define λ���		^
#define λ����		<<
#define λ����		>>
#define ���		<<
#define ����		>>
#define ����		++
#define �Լ�		--
#define �Լ���		+=
#define �Լ�ȥ		-=
#define �Գ���		*=
#define	�Գ���		/=
#define	��ģ��		%=
#define ������		&=
#define	�Ի���		|=
#define	�����		^=
#define ������		>>=
#define ������		<<=

#endif //most symbol


#if defined USE_OTHER_SYMBOL //other symbol

#define ��			,
#define ��			,
#define ��			.
#define ��ȡ		->
#define	ȡ			.
#define ��			?
#define ��			!
#define ��			;
#define ��			;
#define ��(a)		""#a""
#define ����(a)		[a]
#define ����		()
#define ��			(
#define ��			)
#define ����		()
#define ��			(
#define ��			)
#define ��			[]
#define ����		[]
#define �½�		[
#define �Ͻ�		]
#define ��			[
#define ��			]
#define ��			<>
#define �¼�		<
#define �ϼ�		>
#define ��			<
#define ��			>
#define ��			:
#define ��			:
#define ����			:
#define �̳�		:
#define ������		?
#define	����		:
#define ��ֹ		{}
#define ��			{
#define ֹ			}
#define ֹ��		};

#endif //other symbol

#if defined USE_LANG_EXTEND //lang extend

#define ������		main
#define ��			NULL
#define ���		asm
#define ��׼		std
#define ϵͳ		system

#define ���� 
#define ����  
#define ���� 
#define ʹ�������ռ� using namespace

#define ��ӡ		printf
#define ��ȡ		scanf
#define ����ӡ		sprintf
#define �ļ���ӡ	fprintf
#define �ļ���ȡ	fscanf
#define �ļ�д��	fwrite
#define �ļ���ȡ	fread
#define ��ȡ�ַ�	getchar
#define ��ȡ�ַ���	gets
#define ˢ�»��巨(a)	fflush(a)
#define ������뻺��	fflush(stdin)
#define �ַ�������(a)	strlen(a)
#define �ַ�������(a,b)	strcpy(a,b)
#define �ַ���ƥ��(a,b)	strcmp(a,b)
#define �ַ���ƴ��(a,b)	strcat(a,b)
#define ʱ�䷨(a)	time(a)
#define �������ӷ�(a)	srand(a)
#define	���ҷ�(a)	sin(a)
#define ���ҷ�(a)	cos(a)
#define	���з�(a)	tan(a)
#define �ݳ˷�(a,b)	pow(a,b)
#define	������(a)	sqrt(a)
#define ����ֵ(a)	abs(a)
#define �����		cout
#define ������		cin
#define �����з�	endl
#define �����ַ�	ends
#define ʮ����		dec
#define ʮ������	hex
#define �˽���		otc
#define С��λ����A��	setsprecision(A)	/*����С��λ��������С����*/
#define ���A��		setw(A)				/*�������*/

#define ���ļ� FILE 
#define ���ļ�ָ�� FILE *
#define ���ļ�		fopen
#define �ر��ļ�		fclose


#define ��׼�������ͷ		<stdio.h>
#define ��׼����ͷ			<stdlib.h>
#define ��׼ʱ��ͷ			<time.h>
#define ��׼��ѧͷ			<math.h>
#define ��׼�ַ���ͷ		<string.h>
#define ��׼�������������ͷ <conio.h>
#define ��׼���������		<iostream>
#define ��׼�ļ���			<fstream>
#define ��׼�ļ�������		<ifstream>
#define ��׼�ļ������		<ofstream>
#define	��׼�ַ���			<string>
#define ��׼����			<vector>
#define ��׼����			<functional>
#define ��׼�㷨			<algorithm>
#define ��׼˫�˶���		<deque>
#define ��׼�������		<queue>
#define ��׼ջ				<stack>

#define ���ַ���		string
#define ���ļ���		fstream
#define �������ļ���	ifstream
#define ������ļ���	ofstream
#define ������			vector
#define ��˫�˶���		deque
#define �͵������		queue
#define ��ջ			stack
#define �;�����(a)			vector<a>
#define �;�˫�˶���(a)		deque<a>
#define �;ߵ������(a)		queue<a>
#define �;�ջ(a)				stack<a>
#define ��ʱ��			time_t
#define ��ʱ��ṹ		struct tm
#define ��ʱ��ṹָ��	struct tm *
#define ����ʱ�䷨(a)	localtime(a)
#define ʱ����			tm_year
#define ʱ����			tm_mon
#define ʱ����			tm_mday
#define ʱ��ʱ			tm_hour
#define ʱ���			tm_min
#define ʱ����			tm_sec

#define ��ջ			push
#define ��ջ��(a)		push(a)
#define ��ջ			pop
#define ��ջ��(a)		pop(a)
#define ջ��			top
#define ջ����(a)		top(a)
#define ���С��()		size()
#define �ú�			push_back
#define ��ǰ			push_front
#define ȡ��			pop_back
#define ȡǰ			pop_front
#define �ú�(a)		push_back(a)
#define ��ǰ��(a)		push_front(a)
#define ȡ��(a)		pop_back(a)
#define ȡǰ��(a)		pop_front(a)
#define �Կշ�()		empty()
#define ȡ����()		c_str()
#define ׷�ӷ�(a)		append(a)
#define ȡ����ֵ��(a)	at(a)
#define ��շ�()		clear()
#define ʼ������()		begin()
#define ֹ������()		end()
#define ��������()		capacity()
#define �ⳤ�ȷ�()		length()

#define ������ 3.141592653549

#define ����(c,a,b)	((c)>=(a) && (c)<=(b))
#define �����(c,a,b)	((c)>(a) && (c)<(b))
#define ������(c,a,b)	((c)<=(a) || (c)>=(b))
#define �治����(c,a,b)	((c)<(a) || (c)>(b))

#define �ڴ�����(type,count)	((type##*)malloc(sizeof(type)*(count)))
#define �ڴ��ͷ�(pointer)		free(pointer);

#define �����������	srand((unsigned int)time(NULL))
#define �����		rand()

#endif  //lang extend

#endif // _CHINESECODEC_H_