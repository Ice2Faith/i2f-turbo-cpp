#ifndef _EVERYTHING_LOCKER_HPP_
#define _EVERYTHING_LOCKER_HPP_
#include"types32.h"
/*
������ʷ������ļ��ܽ�����
	���У�֧����ʷ��������в������,���Һ��������һ���Ĺ�ϵ��Ҳ����˵�������һ�����ͬ��������ܳ�������ȫ��������ݣ����⽫�����ӱ�������ܵ����Ѷȣ�Ҳ���Ǹ��Ӱ�ȫ
	������ʷ������Ĵ��ڣ����һ������ʹ������ʷ��������ܣ���ô��Ҫ���ܣ��ͱ���ӵ�ж�Ӧ�ֽ�֮ǰ����ʷ�����룬�������ܽ��ܳɹ�
	Ҳ������ˣ�����������ݣ�����һ�£�ֻ�Ƕ���һ�����ֽڣ���ô����������ֽ���ǰ�棬���ᵼ���������ݼ��ܺ���ȫ��ͬ������������Լ��ں��棬��ôֻ��Ӱ���������ֽڶ���
	��Ҳ������ʷ������ĺ���
	���ǣ�������������־λ���п���
	��ʷ������:
		����������Hash��ԭ���������뽫���¼�������ֵ�볤����ص�ֵ
		������������ܽ��ܼ���
		���Һͱ����ܽ������ݵĳ���Ҳ��һЩ��ϵ�������ݵ�ֵû�й�ϵ��
continueLast������ʹ����һ�μ���֮��������룬
	��λֵΪBOOL_TRUEʱ�������ڽ�һ�����ݷ�Ϊ���С�����ݽ��м��ܵ���������硾���϶�ȡ�ļ����ݽ��м��ܡ�
	����Ȼ���������ܺͽ���ʱʹ�õĶγ���һ�£���һ��λ������񣬽��Խ���û��Ӱ�죬�����Լ��ܺ��������Ӱ�죬�Ͼ���ʷ�����벻��������ģ�
cleanLast����λΪBOOL_TRUEʱ��ֱ�������ʷ�����룬
	Ҳ����һ���µĿ�ʼ����ֱ�Ӻ�������ֵΪBOOL_FALSE,�����Ĳ���ֵ������Ч���������ᱻʹ�ã���˻����µ��ã�
	lock(NULL, 0, NULL, 0, BOOL_FALSE, BOOL_TRUE);
��Ҳ���Կ�����continueLast��cleanLast��־λ������Ĭ��ֵ�ģ�Ϊ��ʲô�أ�
	����Ϊ�ˣ��������ʱ�򣬶���ֱ�Ӽ���һ�����ݼ��ɣ�����Ҫʲô�ֶΣ�����Ҫʹ����ʷ�����룬�������Ĭ�ϲ��������һ�����ݽ��д����ʱ��
	����Բ��ù���������־λ��ֱ��ʹ�ü���
	����Ȼ�漰������Ҫ�󣬷ֶλ������ʱ������Ҫע���ˡ�
*/
class EverythingLocker
{
public:
	EverythingLocker()
	{
		m_innearKey = makeInearKey(&m_sizeInnearKey);
	}
	~EverythingLocker()
	{
		delete[] m_innearKey;
		m_innearKey = NULL;
		m_sizeInnearKey = 0;
	}
	/*
	������飨unlock����Ҳһ�£���
		��sizeData�ֽڴ�С��data������sizePass�ֽڴ�С��pass�������
		����˵����
			data:���ݵ�ַ,�����ʹ�ü��ɽ�������������ת������:(UINT8_T *)(void *)
			sizeData:���ݴ�С���ֽڣ�,����ʹ�ü��ɣ�sizeof()
			pass:�����ַ
			sizePass:�����С(�ֽ�)
			continueLast:�Ƿ������һ��ִ�к�������룬��Ϊ������ʷ������������
			cleanLast:�Ƿ������һ��ִ�е�������
		����ֵ��
			�����Ƿ�ɹ�����cleanLast��־λΪBOOL_TRUE����ֱ�������һ��ִ�в�����BOOL_FALSE
	*/
	BOOL_T lock(UINT8_T * data, INT32_T sizeData, UINT8_T * pass, INT32_T sizePass, BOOL_T continueLast = BOOL_FALSE,BOOL_T cleanLast=BOOL_FALSE)
	{
		static INT32_T lastIndexKey = 0;
		static UINT8_T lastFactor = 0;
		if (cleanLast == BOOL_TRUE)
		{
			lastIndexKey = 0;
			lastFactor = 0;
			return BOOL_FALSE;
		}

		if (data == NULL || pass == NULL || sizeData <= 0 || sizePass <= 0)
			return BOOL_FALSE;

		UINT8_T * password = getTrulyPassword(pass, sizePass);

		if (continueLast == BOOL_FALSE)
		{
			lastIndexKey = 0;
			lastFactor = 0;
		}
		for (INT32_T i = 0; i < sizeData; i++)
		{
			data[i] = data[i] ^ ((UINT8_T)(password[lastIndexKey]) ^ lastFactor);
			data[i] = ((data[i] & 0xf) << 4) | ((data[i] >> 4) & 0xf);

			lastFactor = (UINT8_T)(password[lastIndexKey] + lastFactor * 13);
			lastIndexKey = (lastIndexKey + 1) % sizePass;
		}
		delete[] password;
		return BOOL_TRUE;
	}
	/*
	�ο�lock��������
	*/
	BOOL_T unlock(UINT8_T * data, INT32_T sizeData, UINT8_T * pass, INT32_T sizePass, BOOL_T continueLast = BOOL_FALSE, BOOL_T cleanLast = BOOL_FALSE)
	{
		
		static INT32_T lastIndexKey = 0;
		static UINT8_T lastFactor = 0;
		if (cleanLast == BOOL_TRUE)
		{
			lastIndexKey = 0;
			lastFactor = 0;
			return BOOL_FALSE;
		}

		if (data == NULL || pass == NULL || sizeData <= 0 || sizePass <= 0)
			return BOOL_FALSE;

		
		UINT8_T * password=getTrulyPassword(pass, sizePass);
		if (continueLast == BOOL_FALSE)
		{
			lastIndexKey = 0;
			lastFactor = 0;
		}
		for (INT32_T i = 0; i < sizeData; i++)
		{
			data[i] = ((data[i] & 0xf) << 4) | ((data[i] >> 4) & 0xf);
			data[i] = data[i] ^ ((UINT8_T)(password[lastIndexKey]) ^ lastFactor);

			lastFactor = (UINT8_T)(password[lastIndexKey] + lastFactor * 13);
			lastIndexKey = (lastIndexKey + 1) % sizePass;
		}
		delete[] password;
		return BOOL_TRUE;
	}
	/*
	ǰ��˵�ˣ�Ҫֱ�������ʷ�����룬����Ҫд�ܶ࣬���Ҷ��ǲ��õĲ���
	��ˣ�Ϊ�˼�������̣�����ʹ�ü�����������װһ��
	�������
	�Ժ������������ʽ���ã�
	EverythingLocker locker;
	locker.cleanLockCode().lock(data,......);
	*/
	EverythingLocker& cleanLockCode()
	{
		lock(NULL, 0, NULL, 0, BOOL_FALSE, BOOL_TRUE);
		return *this;
	}
	EverythingLocker& cleanUnlockCode()
	{
		unlock(NULL, 0, NULL, 0, BOOL_FALSE, BOOL_TRUE);
		return *this;
	}
	EverythingLocker& cleanLockAndUnlockCode()
	{
		lock(NULL, 0, NULL, 0, BOOL_FALSE, BOOL_TRUE);
		unlock(NULL, 0, NULL, 0, BOOL_FALSE, BOOL_TRUE);
		return *this;
	}
private:
	UINT8_T * m_innearKey;
	INT32_T m_sizeInnearKey;

	UINT8_T * getTrulyPassword(UINT8_T * pass, INT32_T sizePass)
	{
		UINT8_T * password = new UINT8_T[sizePass];
		for (INT32_T i = 0; i < sizePass; i++)
		{
			password[i] = pass[i];
		}
		inearLockKey(password, sizePass);
		return password;
	}
	void inearLockKey(UINT8_T * data, INT32_T size)
	{
		INT32_T inSize = 0;
		UINT8_T * inKey = makeInearKey(&inSize);
		INT32_T j = 0;
		for (INT32_T i = 0; i < size; i++)
		{
			data[i] ^= inKey[j];
			j = (j + 1) % inSize;
		}
		delete[] inKey;
	}
	UINT8_T * makeInearKey(INT32_T * size)
	{
		INT32_T maxSize = 1024;
		UINT8_T * ret = new UINT8_T[maxSize];
		UINT8_T arr[] = { '#', 'C', 'o', 'p', 'y', 'r', 'i', 'g', 'h', 't', '@', 'U', 'g', 'e', 'x', '.', 'S', 'a', 'v', 'e', 'l', 'a', 'r', '-', '2', '0', '2', '0',0 };
		INT32_T sizeArr = sizeof(arr);

		
		arr[0] = getChechSum(&arr[1],sizeArr-1);

		UINT8_T fac = 0;
		INT32_T i = 0;
		INT32_T j = 0;
		while (i < maxSize)
		{
			ret[i] = arr[j];
			arr[j] = (UINT8_T)(arr[j] * 31) ^ fac;

			fac = fac * 7 + arr[j];

			i++;
			j = (j + 1) % sizeArr;
		}
		*size = i;
		return ret;
	}
	UINT8_T getChechSum(UINT8_T * data, INT32_T sizeData)
	{
		UINT8_T checkSum = 0;
		for (INT32_T k = 0; k < sizeData; k++)
		{
			checkSum = (UINT8_T)(checkSum * 17 + data[k] * 31);
			checkSum = ((checkSum & 0xf) << 4) | ((checkSum >> 4) & 0xf);
		}
		return checkSum;
	}
};


#endif // _EVERYTHING_LOCKER_HPP_