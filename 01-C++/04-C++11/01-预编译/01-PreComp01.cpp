#include<iostream>
using namespace std;
//����__VA_ARGS__�䳤�������__FILE__,__LINE__ʵ�ֱ�����־��ӡ
#define LOG(...){\
    fprintf(stderr,"%s: Line %d:\t",__FILE__,__LINE__);\
    fprintf(stderr,__VA_ARGS__);\
    fprintf(stderr,"\n");\
}
void content01()
{
    cout << "Standard Clib:"<< __STDC_HOSTED__<<endl;//�Ƿ��������C��
    cout << "Standard C:"<< __STDC__<<endl;//�Ƿ���C��׼һ��
    //cout << "C Standard Version:"<<__STDC_VERSION__ endl;//��֧�ֵ�C��׼�汾
    //cout << "ISO/IEC:"<<__STDC_ISO_10646__<<endl;//C++���뻷�����ϵ�ISO��׼
    cout << "Function Name:"<<__func__<<endl;//���ں����ĺ�����
    _Pragma("once")//��������#pragma��ʹ������sizeof()
    LOG("x=%d",3);
    //ʹ��__cplusplus��Լ��ʹ�ø���C++11�ı���������ʹ��
    #if __cplusplus <201103L
        #error "Should use C++11 implementation."
    #endif // __cplusplus
}
int main(int argc,char * argv[])
{
    content01();
    return 0;
}
