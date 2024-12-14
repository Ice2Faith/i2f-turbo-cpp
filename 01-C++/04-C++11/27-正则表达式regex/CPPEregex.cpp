#include<iostream>
#include<regex>
#include<string>
using namespace std;
/*
操作string对象
对模式regex(basic_regex)进行初始化，通过regex_match进行匹配，
产生smatch(match_results)对象
*/
void Tregex()
{
    string files[]={"read.txt","pic01.png","lead01.txt","config","company.txt"};
    regex txtf_rgx("[a-z]+\\.txt");//匹配模式，匹配长度不为零的小写字母组成的后缀为.txt的串
    for(auto & fname:files)//regex_match匹配成功返回true
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
