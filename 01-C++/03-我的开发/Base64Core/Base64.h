#ifndef _BASE64_H_
#define _BASE64_H_
/*
	base64原理解析：
		表达式：3*8=4*6恒成立
		2^6=64
		因此，对于一个24位长的数据，可以用3个8位的数据（字符）进行表示，也可以用4个6位的数据（字符）表示。
		所以，实现思路为：
		不断选取数据的3个字符大小空间（3*8=24bit）转换为4个字符(4*6=24bit)（为了显示，6位数据进行拓展为8位成为一个字符）
		逆向时不断选取四个字符，转换为3个字符即可
*/
class Base64
{
public:
	//操作类型枚举，通过类作用域运算符获取，普通字符串，URL，正则，XML族，中文字符。
	enum OperateType{ OT_NormalString, OT_URL, OT_RegExp, OT_XML_NmToken, OT_XML_Name, OT_China };
	Base64();
	Base64(OperateType type);
	//设置操作类型
	bool SetOperateType(OperateType type);
	//设置结束类型，默认等号
	bool SetEndChar(char endChar);
	//设置Base64基本映射表，长度大于等于64，超过64位会被截断
	bool SetBase64Table(char * table);
	//数据类型转换为base64字符串，nMaxCount应该大于等于nDataSize*4/3
	//参数：pData：数据地址，nDataSize：数据大小，pString：存放字符串数组，nMaxCount：字符串最大大小
	bool DataToBase64(void * pData, int nDataSize, char * pString, int nMaxCount);
	//base64字符串转换为数据类型，nDataSize应该大于等于nStrLen*3/4
	//参数：pString：base64字符串数组，nStrLen：字符串长度，pData：数据地址，nDataSize：数据大小
	bool Base64ToData(char * pString, int nStrLen, void * pData, int nDataSize);
private:
	void InitEnv();
	char m_Table[65];
	OperateType m_opeType;
	char m_endChar;
};

#endif // _BASE64_H_