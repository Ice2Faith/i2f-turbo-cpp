#ifndef _FORMULA_CALCULATOR_HPP_
#define _FORMULA_CALCULATOR_HPP_
/*
--------------------------
name:��ʽ������
author:Ugex.Savelar
date:2020-7-25
--------------------------
����˫ջ������ջ������ջ��ʵ�ֵ��ַ�����ʽ������
ԭ��
ɨ���������빫ʽ����������ɨ��
��������֣�ֱ����ջ������ջ
����Ƿ���
	�������ջΪ�գ������������ţ���������ջ������ջ
	�������ջ��Ϊ��
		�ͷ���ջջ�����ţ��Ƚ����ȼ�
			�������ջ�����ȼ���ֱ����ջ������ջ
			�������ջ�����ȼ���������ջȡ���������֣��ӷ���ջȡ��һ�����ţ��������㣬
				����������������ջ������ǰ������ջ������ջ
			�����ǰɨ�赽�ķ����������ţ�
				����ȡ�������ֺ�һ�������㣬֪������ջջ������Ϊ�����ţ�
				����ջ���������ţ�
Ҳ����˵�����ֺ������ţ���������ջ�������ţ�ʼ�ղ���ջ��
���������ţ����Ͳ��ϵ�ջ���㣬֪����ȥջ�е����ĵ�һ�������ţ���
����ʱ�򣬵�ǰ�ķ������ȼ��ߣ�ֱ����ջ�����ȼ�����ջ���㣬����ջ

α�������̣�
	ֱ�� ���빫ʽɨ�����
		��� ɨ�赽�ַ�
			��ȡ����
			��ջ-����ջ
			�ƶ��±�
		����
			��ȡ��ǰ����
			��� ��֧�ֵ�ǰ����
				�˳�ѭ����ֱ�ӷ���
			��� ����ջ��
				��ջ��ǰ����
			����
				��ȡ����ջ������
				���ջ�����ź͵�ǰ���ŵ����ȼ�
				��� ���ȼ���ȡ����ı�־
					�˳�ѭ����ֱ�ӷ���
				������� �������ŵ����ȼ���־
					��ջ����ջ
				������� ��ǰ�������ȼ� ���� ջ������
					��ջ�������ֺ�һ�����Ž��м��㣬����������������ջ����ջ--�鿴ע��1
					��� ��ǰ���� �� ������
						������һ��ѭ������������ѭ��
					��ջ ��ǰ���� �� ����ջ
				������� ��ǰ�������ȼ� ���� ջ������
					��ջ ��ǰ���� �� ����ջ
			�ƶ��±�
	ֱ�� ����ջ Ϊ��
		��ջ�������ֺ�һ�����Ž��м��㣬����������������ջ����ջ--�鿴ע��1
					
	���� ����ջջ������������յĽ��

-----ע��1��
	��ջ����2 �� ����ջ
	��ջ����1 �� ����ջ
	��ջ������� �� ����ջ
	���� ����1 ������� ����2 ���浽 ���
	��ջ ��� �� ����ջ
----ע�⣬����������������1������2�ģ���Ϊ������������Ҫ���ֵ�
*/
#include"AlgoContainer.hpp"
#include"AlgoString.hpp"

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<float.h>
#include<math.h>

class FormulaCalculator
{
public:
	static AlgoString<char, int> buildPrepareFormula(AlgoString<char, int>& preFormula, AlgoArray<AlgoString<char, int>, int> & flags, AlgoArray<AlgoString<char, int>, int> & values)
	{
		AlgoString<char, int> ret(preFormula);
		for (int i = 0; i < flags.size(); i++)
		{
			ret.replace(flags[i], values[i],-1);
		}
		return ret;
	}
	static double hex2Number(char * str, int base = 16)
	{
		int addCount = 0;
		return getNumber(str, &addCount, base);
	}
	static char * number2Hex(double num,char * hex,int base=16,int decimal=4)
	{
		if (hex == NULL || base<2 || base>16 || decimal < 0)
			return hex;

		static char map[] = { "0123456789ABCDEF" };

		char temp[128] = { 0 };
		int otc = (int)num;
		double flo = num - otc;
		int retlen = 0;
		int len = 0;
		while (otc != 0)
		{
			int pnum=otc%base;
			temp[len++] = map[pnum];
			otc = (int)otc / base;
		}
		int tlen = len-1;
		if (tlen <= 0)
			hex[retlen++] = '0';
		while (tlen >= 0)
		{
			hex[retlen++] = temp[tlen];
			tlen--;
		}
		hex[retlen++] = '.';
		int dotIndex = retlen;
		int i = 0;
		while (flo != 0.0&&i<decimal)
		{
			int pnum = (int)(flo*base);
			hex[retlen++] = map[pnum];
			flo = flo*base - pnum;
			i++;
		}
		if (dotIndex == retlen)
			hex[retlen++] = '0';
		hex[retlen] = 0;

		return hex;
	}
	/////////////////////////////////////////////
public:
	static const char * getUseHelpStr()
	{
		static char help[] = {"��ʽ������ʹ�ü�飺\tUgex.Savelar\n\
\t����˫Ŀ������ţ�+ - * / % ^ ( )\n\
\t\t�ӡ������ˡ�����ȡģ������\n\
\t\t�÷���3+2*5-(2^3)%5\n\
\t��չ˫Ŀ������ţ�sqrt log adds muls and or xor lmov	rmov	max	min	avg	recipadds	recipmuls	minsum	maxfac	peradd	persub	rand	dayofmonth\n\
\t\tN�θ����������ۼӡ��۳ˡ�λ�롢λ��λ������ơ����ơ����ֵ����Сֵ��ƽ��ֵ��1/n�ۼӵ�1/m��1/n�۳˵�1/m����С�����������Լ���������ٷֱȡ����Ͱٷֱȡ��������ֵ��ָ�����ָ���µ�������\n\
\t\t�÷���2 sqrt 4 + 1adds5+ 7 and 3 + 2 lmov 2 + 4 rmov 1 + 5 max 3 + 3 min 4 + 5 avg 3 + 2 recipadds 5 + 2 recipmuls 5 + 2 minsum 3 + 12 maxfac 6 + 100 peradd 2.3 + 100 persub 1.98 + 0 rand 10 + 2021 dayofmonth 2\n\
\t\t˵����2sqrt4��ʾ4��2�θ���1adds5��ʾ1+...+5\n\
\t\t\t2log8��ʾ����2Ϊ��8�Ķ���,7and3��ʾ7λ��3\n\
\t��չ��Ŀ�������\n\
\t\tnot ! neg per abs radian angle sin cos tan arcsin arccos arctan recip epow ln numpi nume numgsec xpowx	randz	randf	ceil	floor	round	dhead	ftail	dayofyear	kmhtoms	mstokmh	fttoct	cttoft	feibo\n\
\t\t��λȡ�� �׳� ���� �ٷֺ� ����ֵ ת���� ת�Ƕ� ���Ǻ����� ���� e��x���� ��Ȼ���� n��Բ���� n����Ȼ���� n���ƽ�ָ��� x��x�η� ��0-m����������� n�����0-1֮��С�� ��ȡ�� ��ȡ�� �������� ȡ�������� ȡС������ ĳ��һ�������� km/hתm/s m/sתkm/h ����ת���� ����ת���� 쳲�������N��\n\
\t\t�÷���3!+5neg+50per+(60radian)sin\n\
\t\t˵����3!��ʾ��3�Ľ׳ˣ�5neg��ʾ��5,50per��ʾ�ٷ�֮50\n\
\t\t\t60radian��ʾ��60ת��Ϊ�����ƣ�(60radian)sin��ʾ��sin60�Ƕ�\n\
\t\t[ע��]:���Ǻ����������Ҫʹ�û����ƣ�ӵ�������ת��\n\
\t�ڽ����ţ�\n\
\t\tdehex\n\
\t\t����2-16���������÷���16 dehex0c\n\
\t\t��ע�⡿��dehex��֮�󡿽����������������пո�ȷ��ţ��������\n\
\t\t��ע�⡿��dehex��֮ǰ�������пո�ȷ��ţ������������һ��\n\
\t\t����д����16 dehexc ,16 dehex 0c\n\
\t\t��ȷд����16dehex0c ,8 dehex14 ,2dehex1100\n\
\t\t����÷���֮���һ����Ч�ַ�����0-9������ǰ�����0�����ϵ�c����������\n\
\t\t���򽫻ᰴ�������ȥ����ʶ�𣬶�����\n\
\tע�����\n\
\t\t����������ִ�Сд\n\
\t\t�ո�հ׷��ſ���������ӣ�ֻҪ���ж������\n\
\t\t�հ׷���ָ��ASCII�ַ����ո� �س� ���� �Ʊ��\n\
\t\t����������isSuccess��־λ�����Ϊfalse������ʧ�ܣ�������\n\
\t\t�����ʹ��getLastErrStr()��ȡ��������\n\
\t\tʹ��getLastResult()��ȡ�����������������������м������\n\
\t\t\t���δ�������󣬾�����ȷ���\n\
\t�ۺ�ʹ�ð�����\n\
\t\t7 and 3 + 1 or 2 + 3 xor 0 + (0 not) and 3 + \
(60radian)sin + (30radian)cos + (30radian)tan + 3!+ 25per + 10neg + 180radian + \
2 sqrt 4 + 2 log 8 + 1 adds 5 + 1 muls 3 + \
((3.14 * 2 - 6 / (2 % 10)) + (3 ^ 1)) / (4 / 2) + \
((3 + 5 * (4 % (3 + 7)) / (2 ^ 2)) / 2 / 2) ^ 3 + \
3 * 2 * 2 / 4 + 5 * (2 - 4) + 6 / 3 + 12 % 10 + 2 ^ 3+\
1 recip + 1 epow + 1 nume ln + 2 numpi + 1 numgsec+\
16 dehex0c + 8 dehex14 - 2 dehex1100\n\
\t\t������Ϊ��79.460495\n\
"};
		return help; 
	}
	FormulaCalculator()
	{
		srand((unsigned int)time(NULL));
		cleanAll();

		m_flags.setSize(0);

		m_flags.push(AlgoString<char, int>("+"));
		m_flags.push(AlgoString<char, int>("-"));
		m_flags.push(AlgoString<char, int>("*"));
		m_flags.push(AlgoString<char, int>("/"));
		m_flags.push(AlgoString<char, int>("%"));
		m_flags.push(AlgoString<char, int>("^"));
		m_flags.push(AlgoString<char, int>("("));
		m_flags.push(AlgoString<char, int>(")"));

		m_flags.push(AlgoString<char, int>("sqrt"));
		m_flags.push(AlgoString<char, int>("log"));
		m_flags.push(AlgoString<char, int>("adds"));
		m_flags.push(AlgoString<char, int>("muls"));

		m_flags.push(AlgoString<char, int>("and"));
		m_flags.push(AlgoString<char, int>("or"));
		m_flags.push(AlgoString<char, int>("xor"));
		m_flags.push(AlgoString<char, int>("lmov"));
		m_flags.push(AlgoString<char, int>("rmov"));
		m_flags.push(AlgoString<char, int>("max"));
		m_flags.push(AlgoString<char, int>("min"));
		m_flags.push(AlgoString<char, int>("avg"));
		m_flags.push(AlgoString<char, int>("recipadds"));
		m_flags.push(AlgoString<char, int>("recipmuls"));
		m_flags.push(AlgoString<char, int>("minsum"));
		m_flags.push(AlgoString<char, int>("maxfac"));
		m_flags.push(AlgoString<char, int>("peradd"));
		m_flags.push(AlgoString<char, int>("persub"));
		m_flags.push(AlgoString<char, int>("rand"));
		m_flags.push(AlgoString<char, int>("dayofmonth"));

		m_indexOfSingleNumberOperatorBegin = m_flags.size(); //��Ŀ˫Ŀ������ָ��¼

		m_flags.push(AlgoString<char, int>("not"));
		m_flags.push(AlgoString<char, int>("!"));
		m_flags.push(AlgoString<char, int>("neg"));
		m_flags.push(AlgoString<char, int>("per"));
		m_flags.push(AlgoString<char, int>("abs"));
		m_flags.push(AlgoString<char, int>("radian"));
		m_flags.push(AlgoString<char, int>("angle"));
		m_flags.push(AlgoString<char, int>("sin"));
		m_flags.push(AlgoString<char, int>("cos"));
		m_flags.push(AlgoString<char, int>("tan"));
		m_flags.push(AlgoString<char, int>("arcsin"));
		m_flags.push(AlgoString<char, int>("arccos"));
		m_flags.push(AlgoString<char, int>("arctan"));

		m_flags.push(AlgoString<char, int>("recip"));
		m_flags.push(AlgoString<char, int>("epow"));
		m_flags.push(AlgoString<char, int>("ln"));
		m_flags.push(AlgoString<char, int>("numpi"));
		m_flags.push(AlgoString<char, int>("nume"));
		m_flags.push(AlgoString<char, int>("numgsec"));

		m_flags.push(AlgoString<char, int>("xpowx"));
		m_flags.push(AlgoString<char, int>("randz"));
		m_flags.push(AlgoString<char, int>("randf"));
		m_flags.push(AlgoString<char, int>("ceil"));
		m_flags.push(AlgoString<char, int>("floor"));
		m_flags.push(AlgoString<char, int>("round"));
		m_flags.push(AlgoString<char, int>("dhead"));
		m_flags.push(AlgoString<char, int>("ftail"));
		m_flags.push(AlgoString<char, int>("dayofyear"));
		m_flags.push(AlgoString<char, int>("kmhtoms"));
		m_flags.push(AlgoString<char, int>("mstokmh"));
		m_flags.push(AlgoString<char, int>("fttoct"));
		m_flags.push(AlgoString<char, int>("cttoft"));
		m_flags.push(AlgoString<char, int>("feibo"));


		int len = m_flags.size();
		m_ruleTable = new char[len*len];

		char tpTable[100][100] = 
		{
			//	+		-		*		/		%		^		(		)			sqrt		log		adds		muls			and		or		xor			lmov		rmov		max		min		avg		recipadds		recipmuls		minsum		maxfac		peradd		persub		rand		dayofmonth			not		!		neg		per		abs		radian		angle		sin		cos		tan		arcsin		arccos		arctan			recip		epow		ln		numpi		nume		numgsec			xpowx		randz		randf		ceil		floor		round		dhead		ftail		dayofyear		kmhtoms		mstokmh		fttoct		cttoft		feibo	},	//	�ⲿ	
			{ 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	+	*/
			{ 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	-	*/
			{ 1, 1, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	*	*/
			{ 1, 1, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	/	*/
			{ 1, 1, 1, 1, 1, 1, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	%	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	^	*/
			{ 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },	/*	(	*/
			{ 0, 0, 0, 0, 0, 0, 9, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	)	*/
			//	��չ˫Ŀ																																																																																																																																//		
			{ 1, 1, 1, 1, 1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	sqrt	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	log	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	adds	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	muls	*/

			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	and	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	or	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	xor	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	lmov	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	rmov	*/
			{ 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	max	*/
			{ 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	min	*/
			{ 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	avg	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	recipadds	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	recipmuls	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	minsum	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	maxfac	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	peradd	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	persub	*/
			{ 1, 1, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	rand	*/
			{ 1, 1, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	dayofmonth	*/
			//	��Ŀ����																																																																																																																																//		
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	not	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	!	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	neg	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	per	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	abs	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	radian	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	angle	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	sin	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	cos	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	tan	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	arcsin	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	arccos	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	arctan	*/
			//	��չ��Ŀ																																																																																																																																//		
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	recip	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	epow	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	ln	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	numpi	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	nume	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	numgsec	*/

			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	xpowx	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	randz	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	randf	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	ceil	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	floor	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	round	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	dhead	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	ftail	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	dayofyear	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	kmhtoms	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	mstokmh	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	fttoct	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	cttoft	*/
			{ 1, 1, 1, 1, 1, 0, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/*	feibo	*/

		};

		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < len; j++)
			{
				At(i, j) = tpTable[i][j];
			}
		}
		
	}
	~FormulaCalculator()
	{
		delete[] m_ruleTable;
		cleanAll();
	}
	/*
	�����������ʽ�����ɽ��м��㣬���ؼ�������
	��������Ҫ���ܼ����Ƿ�ɹ��ı�־��
	һ���������󣬷���ֵΪ0���ɹ���־Ϊfalse
	���������ͨ��getLastErrStr()��ȡ��������
	���ܹ����У��Ǵ���һ������֮ǰ����ȷ����ģ�
	�����ͨ��getLastResult()��ȡ���������˷������֮ǰ�����־�ɹ�����ô�������յļ�����
	base��������ָ������ʹ�õĽ��ƣ�Ĭ��ʮ���ƣ��⽫�����������������ֲ��ֵĽ���
	*/
	double calculate(AlgoString<char, int> formula, bool * isSuccess, int base = 10)
	{
		return calculate(formula.getData(), isSuccess, base);
	}
	double calculate(char * formula,bool * isSuccess,int base=10)
	{
		m_flagStack.clear();
		m_numberStack.clear();

		if (AlgoString<char,int>(formula).trim().getLength() == 0)
		{
			sprintf(lastErr, "���봮���ȱ��ضϻ���������մ���������\0");
			*isSuccess = false;
			return 0;
		}
		lastErr[0] = 0;

		int i = 0;
		while (formula[i])
		{
			int addCount = 0;
			if (isNumberChar(formula[i], base))
			{
				double num = getNumber(&formula[i], &addCount, base);
				m_numberStack.push(num);
				i += addCount;
			}
			else
			{
				AlgoString<char, int> flg = getFlag(&formula[i], &addCount, base);
				flg.trim();
				if (flg.getLength() > 0)
				{
					if (flg.equalsIgnoreCase("dehex"))
					{
						int base =(int) m_numberStack.pop();
						int haddCount = 0;
						double num=getNumber(&formula[i + addCount], &haddCount, base);
						m_numberStack.push(num);
						i += addCount+haddCount;
						continue;
					}
					if (isLegalOperator(flg) == false)
					{
						sprintf(lastErr, "δʶ����������%s\0", flg.getData());
						*isSuccess = false;
						return 0;
					}

					if (m_flagStack.size() == 0)
						m_flagStack.push(flg);
					else
					{
						AlgoString<char, int> top = m_flagStack.top();
						int priority = getPriortyTag(flg, top);
						if (priority == -1)
						{
							sprintf(lastErr, "���ʽ����index:%d,value:%s\0", i, flg.getData());
							*isSuccess = false;
							return 0;
						}
						else if (priority == 9)
						{
							m_flagStack.pop();
						}
						else if (priority == 0)
						{
							if (calculateOnceStack() == false)
							{
								sprintf(lastErr, "��ʽ���󣬲�ƥ��Ĳ�����,�����������쳣��index:%d,value:%s\0", i, flg.getData());
								*isSuccess = false;
								return 0;
							}
							//ע�⣬���continue������Ҫ����Ҫ�����Ǵ��������������ڵ�����
							//���ں�����±��ƶ���ͳһ�ģ�������ﲻ�жϽ���continue
							//���ᵼ���±������ǰ�ߣ����¼������ų��ִ���
							if (flg.equalsIgnoreCase(")"))
								continue;
							m_flagStack.push(flg);
						}
						else if (priority == 1)
						{
							m_flagStack.push(flg);
						}
					}
					
				}
				i += addCount;	
			}
		}
		//�������ջ��ʣ�������
		//�ر�ע�⣺��ʱջ�еķ�����Ȼ�������ȼ���ϵ�����ֱ�Ӳ���ȡ��ջ�����㣬��ô����û�����ȼ���Ҳ��ӦΪ����ѭ�����ҵļ����������¼������
		//�����ģ�2*2-4*1+2 sqrt 4�����ᵼ�¼������̱�Ϊ��((2*2)-((4*1)+(2 sqrt 4)))=-2,��������ȷ�Ľ��2=(((2*2)-(4*1))+(2 sqrt 4))
		//���ִ����������ģ���ˣ���ȷ���ƺ��������ǣ�
		/*
		��� ����ջ���������ڵ���2�� �Ǿ���Ҫ�Ƚ����ȼ�������������У���ջ��==��ʵ��ջ����Ԫ�أ���ջ��==����ջ����ջ��Ԫ��
			��� ��ջ�������ȼ� ���� ��ջ�������ȼ�
				��ô ֱ�ӵ�������ջ�������ֺͷ���ջһ�����Ž��м��㣬����������ջ�����Ų�����ջ�ˣ���Ҫע�⡿
			����
				��ô �ȱ������ջ��������ջ��ջ������ȥ�����ĵ�ջ���㣬����������ջ���ٰ���ǰ����ķ��ź�������ջ��
		����
			ֱ�ӵ�ջ���㣬�ó����ս��
				
		*/
		while (m_flagStack.size() > 0)
		{
			bool isCalSec = false;
			if (m_flagStack.size() >= 2)//�������ջ�����������ϵ���������Ǿ���Ҫ���ȼ��Ƚ�
			{
				//�ȵ�ջ�Ƚ����ȼ�
				AlgoString<char, int> endTop = m_flagStack.pop();
				AlgoString<char, int> preTop = m_flagStack.pop();
				int priority = getPriortyTag(endTop, preTop);
				if (priority == 1)
				{
					//��ջ�������ȼ��ߣ���ָ�ջ
					m_flagStack.push(preTop);
					m_flagStack.push(endTop);

					//��ջ����,��ջ���
					isCalSec = calculateOnceStack();
				}
				else if (priority == 0)
				{
					//��ջ�������ȼ��ͣ��򱣴���ջ��ջ������Ϊ������ʵ�ֵ�ʱ���ǵ�ջ�Ƚϵ����ȼ��������Ҫ�ظ���ջ����Ϊ��ʱջ��
					double topNum = m_numberStack.pop();
					m_flagStack.push(preTop);

					//��ջ���㣬��ջ���
					isCalSec = calculateOnceStack();

					//�ָ����������ջ��
					m_numberStack.push(topNum);
					m_flagStack.push(endTop);
				}
				else
				{
					//���������β��ʱ�򣬷���ջ�������������ˣ�����������Ǵ��ڣ��Ǿ��ǳ�����
					sprintf(lastErr, "��ջ�쳣���߷���ջ�쳣\0");
					*isSuccess = false;
					return 0;
				}
			}
			else
			{
				//�������ջֻ��һ�������ˣ�û��������ֱ�Ӽ��㣬�õ����ս��
				isCalSec = calculateOnceStack();
			}

			if (isCalSec == false)
			{
				sprintf(lastErr, "��ʽ���󣬲�ƥ��Ĳ�����,�����������쳣��index:end,value:end\0");
				*isSuccess = false;
				return 0;
			}
		}

		if (m_numberStack.size() ==0)
		{
			sprintf(lastErr, "����ʶ��Ĺ�ʽ����������\0");
			*isSuccess = false;
			return 0;
		}
		if (m_numberStack.size() !=1)
		{
			sprintf(lastErr, "��ʽ���ڴ����������������Ȼ��������������\0");
			*isSuccess = false;
			return 0;
		}
		*isSuccess = true;
		return m_numberStack.top();
	}
	double getLastResult()
	{
		if (m_numberStack.size() == 0)
			return 0;
		return m_numberStack.top();
	}
	const char * getLastErrStr()
	{
		return lastErr;
	}
private:
	static AlgoString<char, int> getFlag(char * str, int * addCount, int base = 10)
	{
		AlgoString<char, int> ret;
		ret[0] = 0;
		if (isNumberChar(*str, base) == true)
		{
			*addCount = 0;
			return ret;
		}
		int i = 0;
		if (!ret.isA2Z(str[i]) && !ret.isa2z(str[i]))
		{
			ret[i] = str[i];
			ret[i + 1] = 0;
			*addCount = 1;
			return ret;
		}
		while (str[i]!=0 && isNumberChar(str[i], base)==false)
		{
			if (!ret.isA2Z(str[i]) && !ret.isa2z(str[i]))
			{
				break;
			}
			ret[i] = str[i];
			i++;
		}
		*addCount = i;
		ret[i] = 0;
		return ret;
	}
	static double getNumber(char * str, int * addCount,int base=10)
	{
		double ret=0;
		if (isNumberChar(*str,base) == false)
		{
			*addCount = 0;
			return 0;
		}
		int i = 0;
		while (isNumberChar(str[i],base))
		{
			ret *= base;
			ret += getNumCharValue(str[i],base);
			i++;
		}
		if (str[i] == '.')
		{
			i++;
			double lbit = 1;
			while (isNumberChar(str[i],base))
			{
				lbit *= base;
				ret += getNumCharValue(str[i], base) / lbit;
				i++;
			}
		}
		*addCount = i;
		return ret;
	}
	static int getNumCharValue(char ch, int base=10)
	{
		static char map[] = { "0123456789ABCDEF" };
		if (ch >= 'a'&&ch <= 'z')
			ch &= ~32;
		int i = 0;
		while (map[i] && i<base)
		{
			if (ch == map[i])
				return i;
			i++;
		}
		return -1;
	}
	static bool isNumberChar(char ch,int base=10)
	{
		static char map[] = {"0123456789ABCDEF"};
		if (ch >= 'a'&&ch <= 'z')
			ch &= ~32;
		int i = 0;
		while (map[i]&&i<base)
		{
			if (ch == map[i])
				return true;
			i++;
		}
		return false;
	}
private:
	bool isLegalOperator(AlgoString<char, int>& ope)
	{
		for (int i = 0; i < m_flags.size(); i++)
		{
			if (ope.equalsIgnoreCase(m_flags[i]))
				return true;
		}
		return false;
	}
	bool calculateOnceStack()
	{
		AlgoString<char, int> top = m_flagStack.top();
		if (isSingleNumberOperator(top))//��Ŀ������ţ�ֻȡ��һ�����������㼴��
		{
			if (m_numberStack.size() < 1)
			{
				return false;
			}
			double num2 = 0;
			double num1 = m_numberStack.pop();
			AlgoString<char, int> ope = m_flagStack.pop();

			double result = calculateOperator(num1, num2, ope);
			m_numberStack.push(result);
			
		}
		else
		{
			if (m_numberStack.size() < 2)
			{
				return false;
			}
			double num2 = m_numberStack.pop();
			double num1 = m_numberStack.pop();
			AlgoString<char, int> ope = m_flagStack.pop();

			double result = calculateOperator(num1, num2, ope);
			m_numberStack.push(result);
		}

		return true;
	}
	bool isSingleNumberOperator(AlgoString<char, int>& ope)
	{
		for (int i = m_indexOfSingleNumberOperatorBegin; i < m_flags.size(); i++)
		{
			if (ope.equalsIgnoreCase(m_flags[i]))
				return true;
		}
		return false;
	}
	double calculateOperator(double num1, double num2, AlgoString<char, int>& ope)
	{
		static const double dc_NUM_PI =		3.141592653549626;
		static const double dc_NUM_E =		2.718281828459045;
		static const double dc_NUM_GSEC =	0.618033988749894;
		//+	-	*	/	%	^	(	)		sqrt	log	adds	muls		and	or	not	xor		!	neg	per	abs	radian	angle	sin	cos	tan	arcsin	arccos	arctan recip	epow	ln	numpi	nume	numgsec
		if (ope.equalsIgnoreCase("+"))
		{
			return num1 + num2;
		}
		else if (ope.equalsIgnoreCase("-"))
		{
			return num1 - num2;
		}
		else if (ope.equalsIgnoreCase("*"))
		{
			return num1 * num2;
		}
		else if (ope.equalsIgnoreCase("/"))
		{
			return num1 / num2;
		}
		else if (ope.equalsIgnoreCase("%"))
		{
			return ((long)num1) % ((long)num2);
		}
		else if (ope.equalsIgnoreCase("^"))
		{
			return pow(num1, num2);
		}
		else if (ope.equalsIgnoreCase("sqrt"))//n�θ���m==m��1/n����
		{
			return pow(num2, 1.0 / num1);
		}
		else if (ope.equalsIgnoreCase("log"))
		{
			return log(num2) / log(num1);
		}
		else if (ope.equalsIgnoreCase("adds"))
		{
			double ret = 0;
			int step = num1 <= num2 ? 1 : -1;
			long beg = (long)num1;
			long end = (long)num2;
			for (int i = beg; i <= end; i += step)
				ret += i;
			return ret;
		}
		else if (ope.equalsIgnoreCase("muls"))
		{
			double ret = 1;
			int step = num1 <= num2 ? 1 : -1;
			long beg = (long)num1;
			long end = (long)num2;
			for (int i = beg; i <= end; i += step)
				ret *= i;
			return ret;
		}
		else if (ope.equalsIgnoreCase("and"))
		{
			return ((long)num1)&((long)num2);
		}
		else if (ope.equalsIgnoreCase("or"))
		{
			return ((long)num1) | ((long)num2);
		}
		else if (ope.equalsIgnoreCase("xor"))
		{
			return ((long)num1) ^ ((long)num2);
		}
		else if (ope.equalsIgnoreCase("lmov"))
		{
			return ((long)num1) << ((long)num2);
		}
		else if (ope.equalsIgnoreCase("rmov"))
		{
			return ((long)num1) >> ((long)num2);
		}
		else if (ope.equalsIgnoreCase("max"))
		{
			return (num1>num2)?num1:num2;
		}
		else if (ope.equalsIgnoreCase("min"))
		{
			return (num1<num2) ? num1 : num2;
		}
		else if (ope.equalsIgnoreCase("avg"))
		{
			return (num1+num2)/2.0;
		}
		else if (ope.equalsIgnoreCase("recipadds"))
		{
			double ret = 0;
			int step = num1 <= num2 ? 1 : -1;
			long beg = (long)num1;
			long end = (long)num2;
			for (int i = beg; i <= end; i += step)
				ret += 1.0/i;
			return ret;
		}
		else if (ope.equalsIgnoreCase("recipmuls"))
		{
			double ret = 1;
			int step = num1 <= num2 ? 1 : -1;
			long beg = (long)num1;
			long end = (long)num2;
			for (int i = beg; i <= end; i += step)
				ret *= 1.0 / i;
			return ret;
		}
		else if (ope.equalsIgnoreCase("minsum"))
		{
			long ret = -1;
			long n1 = abs((long)num1);
			long n2 = abs((long)num2);
			long min = n1 < n2 ? n1 : n2;
			for (long i = min; i>0; i++){
				if (i%n1 == 0 && i%n2 == 0){
					ret = i;
					break;
				}
			}
			return ret;
		}
		else if (ope.equalsIgnoreCase("maxfac"))
		{
			long ret = -1;
			long n1 = abs((long)num1);
			long n2 = abs((long)num2);
			long max = n1 > n2 ? n1 : n2;
			for (long i = max; i>0; i--){
				if (n1%i == 0 && n2%i == 0){
					ret = i;
					break;
				}
			}
			return ret;
		}
		else if (ope.equalsIgnoreCase("peradd"))
		{
			return num1*(1.0+(num2/100.0));
		}
		else if (ope.equalsIgnoreCase("persub"))
		{
			return num1*(1.0 - (num2 / 100.0));
		}
		else if (ope.equalsIgnoreCase("rand"))
		{
			long min = num1 < num2 ? (long)num1 : (long)num2;
			return rand() % (abs((long)num1 - (long)num2)) + min;
		}
		else if (ope.equalsIgnoreCase("dayofmonth"))
		{
			long ret = -1;
			long year = (long)num1;
			long month = (long)num2;
			switch (month)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				ret = 31;
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				ret = 30;
				break;
			case 2:
				if (isLeapYear(year)){
					ret = 29;
				}
				else{
					ret = 28;
				}
				break;
			default:
				ret = -1;
				break;
			}
			return ret;
		}
		else if (ope.equalsIgnoreCase("not"))
		{
			return ~((long)num1);
		}
		else if (ope.equalsIgnoreCase("!")) //!	neg	per	abs	radian	angle	sin	cos	tan	arcsin	arccos	arctan
		{
			double ret = 1;
			long beg = 1;
			long end = (long)num1;
			for (int i = beg; i <= end; i++)
				ret *= i;
			return ret;
		}
		else if (ope.equalsIgnoreCase("neg"))
		{
			return 0 - num1;
		}
		else if (ope.equalsIgnoreCase("per"))
		{
			return num1 / 100.0;
		}
		else if (ope.equalsIgnoreCase("abs"))
		{
			return abs(num1);
		}
		else if (ope.equalsIgnoreCase("radian"))
		{
			return num1 / 180.0*3.141592653549;
		}
		else if (ope.equalsIgnoreCase("angle"))
		{
			return num1 / 3.141562653549*180.0;;
		}
		else if (ope.equalsIgnoreCase("sin"))
		{
			return sin(num1);
		}
		else if (ope.equalsIgnoreCase("cos"))
		{
			return cos(num1);
		}
		else if (ope.equalsIgnoreCase("tan"))
		{
			return tan(num1);
		}
		else if (ope.equalsIgnoreCase("arcsin"))
		{
			return asin(num1);
		}
		else if (ope.equalsIgnoreCase("arccos"))
		{
			return acos(num1);
		}
		else if (ope.equalsIgnoreCase("arctan"))
		{
			return atan(num1);
		}
		else if (ope.equalsIgnoreCase("recip"))//recip	epow	ln	numpi	nume	numgsec
		{
			return 1.0/num1;
		}
		else if (ope.equalsIgnoreCase("epow"))
		{
			return pow(dc_NUM_E,num1);
		}
		else if (ope.equalsIgnoreCase("ln"))
		{
			return log(num1) / log(dc_NUM_E);
		}
		else if (ope.equalsIgnoreCase("numpi"))
		{
			return num1*dc_NUM_PI;
		}
		else if (ope.equalsIgnoreCase("nume"))
		{
			return num1*dc_NUM_E;
		}
		else if (ope.equalsIgnoreCase("numgsec"))
		{
			return num1*dc_NUM_GSEC;
		}
		else if (ope.equalsIgnoreCase("xpowx"))
		{
			return pow(num1,num1);
		}
		else if (ope.equalsIgnoreCase("randz"))
		{
			return rand() % ((long)num1);
		}
		else if (ope.equalsIgnoreCase("randf"))
		{
			return num1*((rand() % RAND_MAX)*1.0 / RAND_MAX);
		}
		else if (ope.equalsIgnoreCase("ceil"))
		{
			double fnum = abs(num1 - (long)num1);
			return ((long)num1)+(fnum<10e-8?0:1);
		}
		else if (ope.equalsIgnoreCase("floor"))
		{
			return (long)num1;
		}
		else if (ope.equalsIgnoreCase("round"))
		{
			return (long)(num1+0.5);
		}
		else if (ope.equalsIgnoreCase("dhead"))
		{
			return (long)num1;
		}
		else if (ope.equalsIgnoreCase("ftail"))
		{
			return num1-(long)num1;
		}
		else if (ope.equalsIgnoreCase("dayofyear"))
		{
			long year = (long)num1;
			return isLeapYear(year)?366:365;
		}
		else if (ope.equalsIgnoreCase("kmhtoms"))
		{
			return num1/3.6;
		}
		else if (ope.equalsIgnoreCase("mstokmh"))
		{
			return num1 * 3.6;
		}
		else if (ope.equalsIgnoreCase("fttoct"))
		{
			return (num1-32)/1.8;
		}
		else if (ope.equalsIgnoreCase("cttoft"))
		{
			return num1*1.8+32;
		}
		else if (ope.equalsIgnoreCase("feibo"))
		{
			long idx = abs((long)num1);
			return feiboSeqIdx(idx);
		}
		return 0;
	}
	long feiboSeqIdx(long idx){
		if (idx <= 2){
			return 1;
		}
		return feiboSeqIdx(idx - 1) + feiboSeqIdx(idx - 2);
	}
	bool isLeapYear(long year){
		if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)){
			return true;
		}
		return false;
	}
	int getPriortyTag(AlgoString<char, int>& cur, AlgoString<char, int> & top)
	{
		int curI = getFlagIndex(cur);
		int topI = getFlagIndex(top);
		if (curI == -1 || topI == -1)
			return -1;
		return At(curI, topI);
	}
	int getFlagIndex(AlgoString<char, int> & flg)
	{
		int ret = -1;
		for (int i = 0; i < m_flags.size(); i++)
		{
			if (flg.equalsIgnoreCase(m_flags[i]))
			{
				ret = i;
				break;
			}
		}
		return ret;
	}

	void cleanAll()
	{
		m_flags.setSize(0);
		lastErr[0] = 0;
		m_ruleTable = NULL;
		m_flagStack.clear();
		m_numberStack.clear();
		m_indexOfSingleNumberOperatorBegin = 0;
	}
private:

	char lastErr[1024];
	//cur line ,top row
	char & At(int cur, int top)
	{
		return m_ruleTable[cur*m_flags.size()+top];
	}
	int m_indexOfSingleNumberOperatorBegin;
	char * m_ruleTable;
	AlgoArray<AlgoString<char, int>, int> m_flags;
	AlgoList<double, int> m_numberStack;
	AlgoList<AlgoString<char, int>, int> m_flagStack;
};

#endif // _FORMULA_CALCULATOR_HPP_