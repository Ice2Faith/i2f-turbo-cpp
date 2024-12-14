#include<iostream>
#include<vector>
#include<iterator>
using namespace std;
/**
vector����--��̬����--����������ͨ����β�����в���
*/
////////////////////////////////////////////////////////////////
//�������Vector�ĺ���ģ�壬T��ʶ���ͣ�TI��ʶ�����͵ĵ���������
template<class T,class TI>
void PrintVector(T & vec)
{
    cout <<"[";
    for(TI i=vec.begin();i!=vec.end();i++)
    {
        cout << (*i);
        if(i+1!=vec.end())
            cout<<",";
    }
    cout <<"]"<<endl;
}
void Test01()
{
    //�ṩpush_back �� pop_back ����
    //������beginָ���һ����endָ�����һ���ĺ�һ��
    //rbegin,rend���������
    //insert������ָ��λ�ò���
    //��ʼ��
    int arr[]={0,1,2,3,4,5};
    //��������ʽ�����10��3
    vector<int> vec1(arr,arr+sizeof(arr)/sizeof(int));
    vector<int> vec2(10,3);
    vector<int> vec3(vec1.begin(),vec1.end());
    vector<int>::iterator tp=vec1.begin();
    //��������ָ�뷽����д
    void (*printVector)(vector<int> &)=&PrintVector<vector<int>,vector<int>::iterator>;
    printVector(vec1);
    printVector(vec2);
    printVector(vec3);
    //��ֵ
    vec2.assign(vec1.begin(),vec1.end());
    vec2.assign(10,3);
    vec2=vec3;
    //����
    vec2.swap(vec3);//ָ����н���--�൱������ָ��
    //��С����
    //size���ظ�����resize�ı�������С��empty�пգ�capacity����
    cout <<"Size:"<< vec1.size() <<endl;
    cout << "IsEmpty:"<< (vec1.empty()?"NULL":"NotNULL") <<endl;
    vec1.resize(3);//������������Ĭ��ֵ���ȵ�ǰС��ض�
    printVector(vec1);
    vec1.resize(8,1);//���1
    printVector(vec1);
    cout<< vec1.capacity() <<endl;//�����������>size
    //�����������壺��������ռ�����Ϳ������������������ٶ�
    //һ������³ɱ�����
    //��ȡ����
    cout << "��ȡ����"<<vec1.at(4) <<endl;  //ӵ���쳣�׳�����
    vec1.at(4)=4;
    cout << vec1[4]<<endl;
    //front back ���ص�һ�������һ��
    cout << vec1.front() << " " << vec1.back() <<endl;
    //�����ɾ��
    //insert push_back pop_back erase clear
    vec1.insert(vec1.begin()+2,60);//֧��������ʣ�֧��[]��ʽ�������֧��+num ��vector,���Լ�2
    vec1.push_back(80);
    printVector(vec1);
    vec1.erase(vec1.begin(),vec1.begin()+2);//ɾ��ǰ2��,��������ɾ������ֵ
    printVector(vec1);
    //����swap�����ռ䣬ɾ�������������ռ�
    vec1.resize(6);
    vector<int>(vec1).swap(vec1);//�����������󽻻���ִ��������������Զ����ͷ�
    //reserveԤ���ռ�
    //�ж��Ƿ���������ռ�
    int count=0;
    int * addr=NULL;
    vector<int> vec4;
    //vec4.reserve(101);//������Ч��������ռ�͸������ݴ���
    for(int i=0;i<100;i++)
    {
        vec4.push_back(i);
        if(addr!=&(vec4[0]))
        {
            count++;
            addr=&(vec4[0]);
        }
    }
    cout <<"����"<<count<<endl;
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
