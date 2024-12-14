#include"Base64.h"
Base64::Base64()
{
	InitEnv();
}
Base64::Base64(OperateType type)
{
	InitEnv();
	m_opeType = type;
	SetOperateType(m_opeType);
}
void Base64::InitEnv()
{
	char table[65] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" };
	for (int i = 0; i < 65; i++)
	{
		m_Table[i] = table[i];
	}
	m_endChar = '=';
	m_opeType = OT_NormalString;
}
bool Base64::SetOperateType(OperateType type)
{
	if (m_opeType == OT_NormalString)
	{
		m_endChar = '=';
		m_Table[62] = '+';
		m_Table[63] = '/';
	}
	else if (m_opeType == OT_URL)
	{
		m_Table[62] = '-';
		m_Table[63] = '_';
		m_endChar = '=';
	}
	else if (m_opeType == OT_RegExp)
	{
		m_Table[62] = '!';
		m_Table[63] = '-';
		m_endChar = '=';
	}
	else if (m_opeType == OT_XML_NmToken)
	{
		m_Table[62] = '.';
		m_Table[63] = '-';
		m_endChar = '=';
	}
	else if (m_opeType == OT_XML_Name)
	{
		m_Table[62] = '_';
		m_Table[63] = ':';
		m_endChar = '=';
	}
	else if (m_opeType == OT_China)
	{
		m_Table[62] = '.';
		m_Table[63] = '_';
		m_endChar = '=';
	}
	else
		return false;
	return true;
}
bool Base64::SetEndChar(char endChar)
{
	if (endChar > 32 && endChar < 128)
	{
		m_endChar = endChar;
		return true;
	}
	for (int i = 0; i < 64; i++)
	{
		if (m_Table[i] == endChar)
			return false;
	}
	return false;
}
bool Base64::SetBase64Table(char * table)
{
	int i = 0;
	while (table[i])
	{
		i++;
	}
	if (i < 64)
		return false;
	for (i = 0; i < 64; i++)
	{
		m_Table[i] = table[i];
	}
	m_Table[64] = 0;
	return true;
}
bool Base64::DataToBase64(void * pData, int nDataSize, char * pString, int nMaxCount)
{
	if (nDataSize / 3.0 * 4 > nMaxCount)
	{
		return false;
	}
	unsigned char * pStr = (unsigned char*)pData;
	unsigned char in[3] = { 0 };
	unsigned char out[4] = { 0 };
	int i = 0, k = 0;
	int isend = 0;
	int endspace = -1;
	while (!isend)
	{
		for (int j = 0; j<4; j++)
		{
			if (j<3)
				in[j] = 0;
			out[j] = 0;
		}
		for (int j = 0; j<3; j++)
		{
			in[j] = pStr[i];
			i++;
			if (i>nDataSize)
			{
				isend = 1;
				endspace = j;
				break;
			}
		}
		unsigned int temp = 0;
		temp = (((unsigned int)in[0]) << (2 * 8)) | (((unsigned int)in[1]) << (1 * 8)) | ((unsigned int)in[2]);
		out[0] = m_Table[((temp&(63 << (6 * 3))) >> (6 * 3))];
		out[1] = m_Table[((temp&(63 << (6 * 2))) >> (6 * 2))];
		out[2] = m_Table[((temp&(63 << (6 * 1))) >> (6 * 1))];
		out[3] = m_Table[(temp & 63)];
		if (endspace == 0)
			break;
		if (endspace == 1)
		{
			out[2] = m_endChar;
			out[3] = m_endChar;
		}
		if (endspace == 2)
		{
			out[3] = m_endChar;
		}
		for (int j = 0; j<4; j++)
		{
			pString[k] = out[j];
			k++;
		}

	}
	pString[k] = 0;
	return true;
}
bool Base64::Base64ToData(char * pString, int nStrLen, void * pData, int nDataSize)
{
	if (nStrLen / 4.0 * 3> nDataSize)
	{
		return false;
	}
	unsigned char * pDStr = (unsigned char *)pData;
	unsigned char in[4] = { 0 };
	int iin[4] = { 0 };
	unsigned char out[3] = { 0 };
	int i = 0, k = 0;
	int isend = 0;
	while (!isend)
	{
		for (int j = 0; j<4; j++)
		{
			if (j<3)
				out[j] = 0;
			in[j] = 0;
			iin[j] = 0;
		}
		for (int j = 0; j<4; j++)
		{
			in[j] = pString[i];
			i++;
			if (pString[i] == '\0' || pString[i] == m_endChar)
			{
				isend = 1;
				break;
			}
		}
		for (int j = 0; m_Table[j] != '\0'; j++)
		{
			if (in[0] == m_Table[j])
				iin[0] = j;
			if (in[1] == m_Table[j])
				iin[1] = j;
			if (in[2] == m_Table[j])
				iin[2] = j;
			if (in[3] == m_Table[j])
				iin[3] = j;
		}
		int temp = 0;
		temp = ((iin[0]) << (3 * 6)) | ((iin[1]) << (2 * 6)) | ((iin[2]) << (1 * 6)) | (iin[3]);
		out[0] = ((temp&(255 << (8 * 2))) >> (8 * 2));
		out[1] = ((temp&(255 << (8 * 1))) >> (8 * 1));
		out[2] = (temp & 255);
		for (int j = 0; j<3; j++)
		{
			pDStr[k] = out[j];
			k++;
		}

	}
	return false;
}
