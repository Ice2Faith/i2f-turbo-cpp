#include<iostream>
using namespace std;
/*
����ģʽ��
��֤����ϵͳ��ֻ����һ�����󱻴������޷�������������
�������Ͷ�������ʵ�ַ�ʽ
����Ϊ��
���캯��˽�л������ⲿ�޷����д�������
�ṩ��̬�������ʵ���Ľӿ�
�Լ����͵�˽�����Խ��о�̬��ʼ��
��������ͷŷ�ʽ��
һ����˵�����õ���ģʽ֮�󣬲������ͷŵ����⣬��Ϊ�������н���֮����Զ��ͷ�
Ҳ����ǿ�������ͷţ�ͨ���ڲ����������������ķ�ʽʵ�ֵķ�ʽʵ��
*/
class LazyMan
{
private:
	LazyMan(){ 
		cout << "Lazy Man" << endl;
	}//���캯��˽�л�
public:
	static LazyMan * GetInstance()//�ṩ���ʷ�ʽ
	{
		if (layman == NULL)
			layman = new LazyMan();//����ģʽ��ֻ����Ҫʱ����
		return layman;
	}
	
private:
	static LazyMan * layman;
	class GarbegeCollecton//�������ʱ�����Ķ�����Զ�������������
	{
	public:
		~GarbegeCollecton()
		{
			if (layman != NULL)
				delete layman;
		}
	};
	static GarbegeCollecton  gc;//�������ʱ���Զ�������������ʵ��ֱ���ͷţ���Ȼ���һ��
};
LazyMan * LazyMan::layman=NULL;

class HungryMan
{
private:
	HungryMan(){
		cout << "Hungry man" << endl;
	};
public:
	static HungryMan * GetInstance()//����ģʽ�������ʱ�ʹ�����ʾ��
	{
		return hunman;
	}
private:
	static HungryMan * hunman;
};
HungryMan * HungryMan::hunman = new HungryMan();

int main()
{
	LazyMan * lay = LazyMan::GetInstance();
	system("pause");
	return 0;
}