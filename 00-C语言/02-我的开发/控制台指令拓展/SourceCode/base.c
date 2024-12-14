#include"base64.h"
void help()
{
    printf("\texchange mode string string ...\n");
    printf("\texchange values:\n");
    printf("\t\tB : to base64\n");
    printf("\t\tS : to string\n");
    printf("\tmode values:\n");
    printf("\t\tS : normal strings\n");
    printf("\t\tU : url strings\n");
    printf("\t\tE : exp strings\n");
    printf("\t\tC : china strings\n");
    printf("\t\tT : XML NMToken\n");
    printf("\t\tM : XML Name\n");
    printf("\tstring values:\n");
    printf("\t\tsome strings\n");
    printf("\tsuch as:\n");
    printf("\tbase B S this is a test\n");
    printf("\tbase S U dGhpcw==\n");
}
int main(int argc,char * argv[])
{
    rename(argv[0],"base.exe");
    if(argc<=1)
        return 0;
    if(argv[1][0]=='?')
        help();
    if(argc<4)
        return 0;
    int lock=1;
    if(argv[1][0]=='B'||argv[1][0]=='b')
    {
        lock=1;
    }else if(argv[1][0]=='S'||argv[1][0]=='s')
    {
        lock=0;
    }else
        return 0;
    BASE_MODE mode=BASE_NORMAL_STR;
    switch((char)(argv[2][0]&(~32)))
    {
    case 'S':
        mode=BASE_NORMAL_STR;
        break;
    case 'U':
        mode=BASE_URL;
        break;
    case 'E':
        mode=BASE_EXP;
        break;
    case 'C':
        mode=BASE_CHINA;
        break;
    case 'T':
        mode=BASE_XML_NMTOKEN;
        break;
    case 'M':
        mode=BASE_XML_NAME;
        break;
    default:
        return 0;
    }
    for(int i=3;i<argc;i++)
    {
        char save[4096]={0};
        if(lock==1)
        {
            Base64(argv[i],save,4096-1,mode);
        }
        else if(lock==0)
        {
            Anti_Base64(argv[i],save,1024-1,mode);
        }
        printf("%s\n",save);
    }

    return 0;
}
