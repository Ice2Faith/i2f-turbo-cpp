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
            printf("请输入文件名称，#号独立的空行结束\n");
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
    printf("按任意键退出\n>/ ");
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
        /*检查文件后缀，处理是否是标准后缀，如果是解压后去除后缀*/
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
            strcat(newpath,".IUzip");       //非标准后缀进行后缀添加
        }
        printf("Process:%s\n",path[i]);
        UnzipFile(path[i],newpath);
    }
    printf("--------UNZIP----DONE---------------------------\n");
}
char Meau()
{
    SetConsoleTextColor(3,15);
    printf("\n\t冰念文件压缩软件(.Izip/.IUzip)\n\n");
    SetConsoleTextColor(12,15);
    printf("\t\t1.压缩文件\n");
    SetConsoleTextColor(9,15);
    printf("\t\t2.解压文件\n");
    SetConsoleTextColor(10,15);
    printf("\t\t3.查看帮助\n");
    SetConsoleTextColor(1,15);
    printf("\t\t0.退出程序\n");
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
    printf("\t使用指南：\n");
    SetConsoleTextColor(9,15);
    printf("\t\t将文件拖动到本程序图标上即可启动运行进行加密操作\n");
    printf("\t\t当前也可以直接输入文件名进行操作\n");
    printf("\t\t也可用通过命令行运行方式运行：\n");
    printf("\t\t\t本程序名 待处理文件名1 待处理文件名2 ...\n");
    SetConsoleTextColor(12,15);
    printf("\t注意事项：\n");
    SetConsoleTextColor(9,15);
    printf("\t\t本程序执行的是无损压缩技术\n");
    printf("\t\t使用Huffman算法实现\n");
    printf("\t\t因此对于一些文件可能会出现压缩效果不佳的情况\n");
    printf("\t\t比如：压缩后大小不但没有变小反而变大的情况\n");
    printf("\t\t这是因为压缩文件会附加解压必要信息所致\n");
    printf("\t\t无损压缩基本都不可避免\n");
    printf("\t\t也就是对图片视频等多媒体文件处理效果一般不佳\n");
    SetConsoleTextColor(12,15);
    printf("\t特别声明：\n");
    SetConsoleTextColor(9,15);
    printf("\t\t本程序不兼容任何其他压缩软件\n");
    printf("\t\t因此，本软件压缩的文件只能本软件解压\n");
    printf("\t\t本软件纯净，纯手写算法纯C语言编写\n");
    SetConsoleTextColor(12,15);
    printf("\t其他说明：\n");
    SetConsoleTextColor(14,15);
    printf("\t\t制作者：\tIce2Faith\n");
    printf("---------------------------------------------------------\n");
    fflush(stdin);
    SetConsoleTextColor(1,15);
}
