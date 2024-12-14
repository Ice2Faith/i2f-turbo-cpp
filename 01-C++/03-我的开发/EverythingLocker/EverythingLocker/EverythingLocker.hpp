#ifndef _EVERYTHING_LOCKER_HPP_
#define _EVERYTHING_LOCKER_HPP_
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
	��λֵΪtrueʱ�������ڽ�һ�����ݷ�Ϊ���С�����ݽ��м��ܵ���������硾���϶�ȡ�ļ����ݽ��м��ܡ�
	����Ȼ���������ܺͽ���ʱʹ�õĶγ���һ�£���һ��λ������񣬽��Խ���û��Ӱ�죬�����Լ��ܺ��������Ӱ�죬�Ͼ���ʷ�����벻��������ģ�
cleanLast����λΪtrueʱ��ֱ�������ʷ�����룬
	Ҳ����һ���µĿ�ʼ����ֱ�Ӻ�������ֵΪfalse,�����Ĳ���ֵ������Ч���������ᱻʹ�ã���˻����µ��ã�
	lock(NULL, 0, NULL, 0, false, true);
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
			data:���ݵ�ַ,�����ʹ�ü��ɽ�������������ת������:(unsigned char *)(void *)
			sizeData:���ݴ�С���ֽڣ�,����ʹ�ü��ɣ�sizeof()
			pass:�����ַ
			sizePass:�����С(�ֽ�)
			continueLast:�Ƿ������һ��ִ�к�������룬��Ϊ������ʷ������������
			cleanLast:�Ƿ������һ��ִ�е�������
		����ֵ��
			�����Ƿ�ɹ�����cleanLast��־λΪtrue����ֱ�������һ��ִ�в�����false
	*/
	bool lock(unsigned char * data, long sizeData, unsigned char * pass, long sizePass, bool continueLast = false,bool cleanLast=false)
	{
		static long lastIndexKey = 0;
		static unsigned char lastFactor = 0;
		if (cleanLast == true)
		{
			lastIndexKey = 0;
			lastFactor = 0;
			return false;
		}

		if (data == NULL || pass == NULL || sizeData <= 0 || sizePass <= 0)
			return false;

		unsigned char * password = getTrulyPassword(pass, sizePass);

		if (continueLast == false)
		{
			lastIndexKey = 0;
			lastFactor = 0;
		}
		for (long i = 0; i < sizeData; i++)
		{
			data[i] = data[i] ^ ((unsigned char)(password[lastIndexKey]) ^ lastFactor);
			data[i] = ((data[i] & 0xf) << 4) | ((data[i] >> 4) & 0xf);

			lastFactor = (unsigned char)(password[lastIndexKey] + lastFactor * 13);
			lastIndexKey = (lastIndexKey + 1) % sizePass;
		}
		delete[] password;
		return true;
	}
	/*
	�ο�lock��������
	*/
	bool unlock(unsigned char * data, long sizeData, unsigned char * pass, long sizePass, bool continueLast = false, bool cleanLast = false)
	{
		
		static long lastIndexKey = 0;
		static unsigned char lastFactor = 0;
		if (cleanLast == true)
		{
			lastIndexKey = 0;
			lastFactor = 0;
			return false;
		}

		if (data == NULL || pass == NULL || sizeData <= 0 || sizePass <= 0)
			return false;

		
		unsigned char * password=getTrulyPassword(pass, sizePass);
		if (continueLast == false)
		{
			lastIndexKey = 0;
			lastFactor = 0;
		}
		for (long i = 0; i < sizeData; i++)
		{
			data[i] = ((data[i] & 0xf) << 4) | ((data[i] >> 4) & 0xf);
			data[i] = data[i] ^ ((unsigned char)(password[lastIndexKey]) ^ lastFactor);

			lastFactor = (unsigned char)(password[lastIndexKey] + lastFactor * 13);
			lastIndexKey = (lastIndexKey + 1) % sizePass;
		}
		delete[] password;
		return true;
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
		lock(NULL, 0, NULL, 0, false, true);
		return *this;
	}
	EverythingLocker& cleanUnlockCode()
	{
		unlock(NULL, 0, NULL, 0, false, true);
		return *this;
	}
	EverythingLocker& cleanLockAndUnlockCode()
	{
		lock(NULL, 0, NULL, 0, false, true);
		unlock(NULL, 0, NULL, 0, false, true);
		return *this;
	}
private:
	unsigned char * m_innearKey;
	long m_sizeInnearKey;

	unsigned char * getTrulyPassword(unsigned char * pass, long sizePass)
	{
		unsigned char * password = new unsigned char[sizePass];
		for (long i = 0; i < sizePass; i++)
		{
			password[i] = pass[i];
		}
		inearLockKey(password, sizePass);
		return password;
	}
	void inearLockKey(unsigned char * data, long size)
	{
		long inSize = 0;
		unsigned char * inKey=makeInearKey(&inSize);
		long j = 0;
		for (long i = 0; i < size; i++)
		{
			data[i] ^= inKey[j];
			j = (j + 1) % inSize;
		}
		delete[] inKey;
	}
	unsigned char * makeInearKey(long * size)
	{
		long maxSize = 1024;
		unsigned char * ret = new unsigned char[maxSize];
		unsigned char arr[] = { "#Copyright@Ugex.Savelar-2020" };
		long sizeArr = sizeof(arr);

		
		arr[0] = getChechSum(&arr[1],sizeArr-1);

		unsigned char fac = 0;
		long i = 0;
		long j = 0;
		while (i < maxSize)
		{
			ret[i] = arr[j];
			arr[j] = (unsigned char)(arr[j] * 31)^fac;

			fac = fac * 7 + arr[j];

			i++;
			j = (j + 1) % sizeArr;
		}
		*size = i;
		return ret;
	}
	unsigned char getChechSum(unsigned char * data,long sizeData)
	{
		unsigned char checkSum = 0;
		for (long k = 0; k < sizeData; k++)
		{
			checkSum = (unsigned char)(checkSum * 17 + data[k] * 31);
			checkSum = ((checkSum & 0xf) << 4) | ((checkSum >> 4) & 0xf);
		}
		return checkSum;
	}
};


#endif // _EVERYTHING_LOCKER_HPP_