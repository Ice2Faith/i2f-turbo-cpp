#include"HuffmanZip.h"
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
char Meau();
void Help();
void FileIZip(int sum,char * path[]);
void FileIUZip(int sum,char * path[]);
void SetConsoleTextColor(int ForeColor,int BackGroundColor);
int main(int argc,char * argv[])
{
    system("title compressed software designer Ice2Faith");
    system("color f1");
    char sel;
    sel=Meau();
    char files[512][378]={0};
    char * filesp[512]={0};
    int filesc=0;
    if(argc<=1)
    {
        if(sel>='1'&&sel<='2')
        {
            printf("�������ļ����ƣ�#�Ŷ����Ŀ��н���\n");
            while(1)
            {
                gets(files[filesc]);
                if(files[filesc][0]=='#')
                    break;
                filesc++;
            }
            for(int i=0; i<filesc; i++)
            {
                filesp[i]=files[i];
            }
        }

    }
    else
    {
        filesc=argc;
        for(int i=0;i<filesc;i++)
        {
            filesp[i]=argv[i];
        }
    }
    switch((int)(sel-'0'))
    {
    case 1:
        FileIZip(filesc,filesp);
        break;
    case 2:
        FileIUZip(filesc,filesp);
        break;
    case 3:
        Help();
        break;
    case 0:
        exit(0);
        break;
    }
    fflush(stdin);
    printf("��������˳�\n>/ ");
    getch();
    return 0;
}
void FileIZip(int sum,char * path[])
{
    printf("Please waiting compressing...\n");
    char newpath[1024]= {0};
    for(int i=1; i<sum; i++)
    {
        strcpy(newpath,path[i]);
        strcat(newpath,".Izip");
        printf("Process:%s\n",path[i]);
        ZipFile(path[i],newpath);
    }
    printf("--------ZIP----DONE---------------------------\n");
}
void FileIUZip(int sum,char * path[])
{
    printf("Please waiting uncompressing...\n");
    char newpath[1024]= {0};
    for(int i=1; i<sum; i++)
    {
        /*����ļ���׺�������Ƿ��Ǳ�׼��׺������ǽ�ѹ��ȥ����׺*/
        strcpy(newpath,path[i]);
        char save[20]= {0};
        GetPathInfo(newpath,save,PATH_TAIL);
        int jk=0;
        while(save[jk])
        {
            if(save[jk]>='a'&&save[jk]<='z')
                save[jk]&=~32;
            jk++;
        }
        if(strcmp(save,".IZIP")==0)
        {
            int lenpath=strlen(newpath);
            while(newpath[lenpath]!='.')
            {
                lenpath--;
            }
            newpath[lenpath]='\0';
        }
        else
        {
            strcat(newpath,".IUzip");       //�Ǳ�׼��׺���к�׺���
        }
        printf("Process:%s\n",path[i]);
        UnzipFile(path[i],newpath);
    }
    printf("--------UNZIP----DONE---------------------------\n");
}
char Meau()
{
    SetConsoleTextColor(3,15);
    printf("\n\t�����ļ�ѹ�����(.Izip/.IUzip)\n\n");
    SetConsoleTextColor(12,15);
    printf("\t\t1.ѹ���ļ�\n");
    SetConsoleTextColor(9,15);
    printf("\t\t2.��ѹ�ļ�\n");
    SetConsoleTextColor(10,15);
    printf("\t\t3.�鿴����\n");
    SetConsoleTextColor(1,15);
    printf("\t\t0.�˳�����\n");
    printf("\t\t>/ ");
    char sel='\0';
    while(sel<'0'||sel>'3')
        sel=getch();
    printf("%c\n",sel);
    return sel;
}
void SetConsoleTextColor(int ForeColor,int BackGroundColor)
{
    if(ForeColor<0 ||ForeColor>15)
        ForeColor=15;
    if(BackGroundColor<0 ||BackGroundColor>15)
        BackGroundColor=0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),ForeColor+BackGroundColor*0x10);
}
void Help()
{
    system("cls");
    SetConsoleTextColor(15,15);
    printf("---------------------------------------------------------\n");
    SetConsoleTextColor(3,15);
    printf("\t\t\tQ&A\n");
    SetConsoleTextColor(12,15);
    printf("\tʹ��ָ�ϣ�\n");
    SetConsoleTextColor(9,15);
    printf("\t\t���ļ��϶���������ͼ���ϼ����������н��м��ܲ���\n");
    printf("\t\t��ǰҲ����ֱ�������ļ������в���\n");
    printf("\t\tҲ����ͨ�����������з�ʽ���У�\n");
    printf("\t\t\t�������� �������ļ���1 �������ļ���2 ...\n");
    SetConsoleTextColor(12,15);
    printf("\tע�����\n");
    SetConsoleTextColor(9,15);
    printf("\t\t������ִ�е�������ѹ������\n");
    printf("\t\tʹ��Huffman�㷨ʵ��\n");
    printf("\t\t��˶���һЩ�ļ����ܻ����ѹ��Ч�����ѵ����\n");
    printf("\t\t���磺ѹ�����С����û�б�С�����������\n");
    printf("\t\t������Ϊѹ���ļ��ḽ�ӽ�ѹ��Ҫ��Ϣ����\n");
    printf("\t\t����ѹ�����������ɱ���\n");
    printf("\t\tҲ���Ƕ�ͼƬ��Ƶ�ȶ�ý���ļ�����Ч��һ�㲻��\n");
    SetConsoleTextColor(12,15);
    printf("\t�ر�������\n");
    SetConsoleTextColor(9,15);
    printf("\t\t�����򲻼����κ�����ѹ�����\n");
    printf("\t\t��ˣ������ѹ�����ļ�ֻ�ܱ������ѹ\n");
    printf("\t\t���������������д�㷨��C���Ա�д\n");
    SetConsoleTextColor(12,15);
    printf("\t����˵����\n");
    SetConsoleTextColor(14,15);
    printf("\t\t�����ߣ�\tIce2Faith\n");
    printf("---------------------------------------------------------\n");
    fflush(stdin);
    SetConsoleTextColor(1,15);
}
