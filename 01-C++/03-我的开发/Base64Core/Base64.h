#ifndef _BASE64_H_
#define _BASE64_H_
/*
	base64ԭ�������
		���ʽ��3*8=4*6�����
		2^6=64
		��ˣ�����һ��24λ�������ݣ�������3��8λ�����ݣ��ַ������б�ʾ��Ҳ������4��6λ�����ݣ��ַ�����ʾ��
		���ԣ�ʵ��˼·Ϊ��
		����ѡȡ���ݵ�3���ַ���С�ռ䣨3*8=24bit��ת��Ϊ4���ַ�(4*6=24bit)��Ϊ����ʾ��6λ���ݽ�����չΪ8λ��Ϊһ���ַ���
		����ʱ����ѡȡ�ĸ��ַ���ת��Ϊ3���ַ�����
*/
class Base64
{
public:
	//��������ö�٣�ͨ�����������������ȡ����ͨ�ַ�����URL������XML�壬�����ַ���
	enum OperateType{ OT_NormalString, OT_URL, OT_RegExp, OT_XML_NmToken, OT_XML_Name, OT_China };
	Base64();
	Base64(OperateType type);
	//���ò�������
	bool SetOperateType(OperateType type);
	//���ý������ͣ�Ĭ�ϵȺ�
	bool SetEndChar(char endChar);
	//����Base64����ӳ������ȴ��ڵ���64������64λ�ᱻ�ض�
	bool SetBase64Table(char * table);
	//��������ת��Ϊbase64�ַ�����nMaxCountӦ�ô��ڵ���nDataSize*4/3
	//������pData�����ݵ�ַ��nDataSize�����ݴ�С��pString������ַ������飬nMaxCount���ַ�������С
	bool DataToBase64(void * pData, int nDataSize, char * pString, int nMaxCount);
	//base64�ַ���ת��Ϊ�������ͣ�nDataSizeӦ�ô��ڵ���nStrLen*3/4
	//������pString��base64�ַ������飬nStrLen���ַ������ȣ�pData�����ݵ�ַ��nDataSize�����ݴ�С
	bool Base64ToData(char * pString, int nStrLen, void * pData, int nDataSize);
private:
	void InitEnv();
	char m_Table[65];
	OperateType m_opeType;
	char m_endChar;
};

#endif // _BASE64_H_