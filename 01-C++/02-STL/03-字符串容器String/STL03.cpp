#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
/**
string����--�ַ�����������
*/
////////////////////////////////////////////////////////////////

void Test01()
{
    string str1,str2,str3;
    //c���ת
    str1="abcdefg";
    str2="cde";
    char temp[1024]={0};
    sprintf(temp,"%s\0",str1.c_str());
    cout <<"���ת��"<<temp<<endl;
    //���쳣���
    try
    {
        str1.at(100)='A';
    }catch(...)
    {
        cout << "����Խ��"<<endl;
    }
    //����
    //�״�
    cout <<"�״�ƥ��"<< str1.find("cd") <<endl;
    //���һ��
    cout <<"���һ��ƥ��"<< str1.rfind("cd") <<endl;
    //�滻
    //0λ�ÿ�ʼ2���ַ��滻Ϊ222
    str1.replace(0,2,"222");
    cout <<"�滻��"<< str1<<endl;
    //�Ƚ�
    cout <<"�Ƚ�"<< str1.compare(str2)<<endl;
    //��ȡ�Ӵ�
    //��ȡ0��ʼ��3��
    str3=str1.substr(0,3);
    cout <<"�Ӵ�"<<str3<<endl;
    //����
    //2λ�ò��봮
    str1.insert(2,"aaa");
    cout <<"����"<<str1<<endl;
    //ɾ��
    //��2��ʼ3��
    str1.erase(2,3);
    cout <<"ɾ��"<<str1<<endl;
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
