#include<iostream>
#include<regex>
#include<string>
using namespace std;
/*
����string����
��ģʽregex(basic_regex)���г�ʼ����ͨ��regex_match����ƥ�䣬
����smatch(match_results)����
*/
void Tregex()
{
    string files[]={"read.txt","pic01.png","lead01.txt","config","company.txt"};
    regex txtf_rgx("[a-z]+\\.txt");//ƥ��ģʽ��ƥ�䳤�Ȳ�Ϊ���Сд��ĸ��ɵĺ�׺Ϊ.txt�Ĵ�
    for(auto & fname:files)//regex_matchƥ��ɹ�����true
        cout << fname << ":"<<regex_match(fname,txtf_rgx)<<endl;
    cout<<"-------------------"<<endl;
    smatch ptmch;
    for(auto & fname:files)
    {
        if(regex_match(fname,ptmch,txtf_rgx)==true)
        {
            //if(ptmch.size()==2)
            {
                cout <<"0:"<< ptmch[0].str()<<endl;
                cout <<"1:"<< ptmch[1].str()<<endl;

            }
        }
    }
}

int main()
{
    Tregex();
    return 0;
}
