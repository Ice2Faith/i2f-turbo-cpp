#include<iostream>
#include<list>
#include<iterator>
#include<algorithm>
using namespace std;
/**
list�����������������ڴ���֯��ʽ��
push_front push_back pop_front pop_back clear remove erase insert
��֧�����������
*/
////////////////////////////////////////////////////////////////

void Test01()
{
    int arr[]={0,1,2,3,4,5,4,8,5};
    list<int> lis1(arr,arr+sizeof(arr)/sizeof(arr[0])),lis2(10,2);
    list<int> lis3(lis1);
    //��ʼ���ͱ���
    for(list<int>::iterator i=lis1.begin();i!=lis1.end();i++)
    {
        cout << (*i)<<" ";
    }
    cout <<endl;
    //����ɾ��
    lis1.push_back(20);
    lis1.insert((lis1.begin()++)++,30);//��֧�������ֻ��++
    lis1.insert(lis1.begin(),10,2);//����
    //insert ���Ե���������
    lis1.pop_back();
    lis1.erase(lis1.begin(),lis1.begin()++);//ɾ������������
    lis1.remove(5);//ɾ��ƥ����������
    //��С����size empty resize
    //��ֵ�����򣬷�ת
    lis2.assign(10,10);//��ֵ����
    lis3=lis2;
    lis2.swap(lis3);
    cout << lis1.front() << " "<<lis1.back()<<endl;
    lis1.reverse();//��ת
    lis1.sort();//����--Ĭ������--��ѡ��������bool myrules(&,&)
    //��Ա����ԭ���ǲ�֧��������ʵ�����������ֻ�ܳ�Ա����ʵ��
    for(list<int>::iterator i=lis1.begin();i!=lis1.end();i++)
    {
        cout << (*i)<<" ";
    }
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
