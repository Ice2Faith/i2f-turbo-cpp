#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#define APPNAME "�ļ�����������"
//���ص�ǰʱ����Ϣ��modeֵ0���ڣ�1ʱ�䣬2����
int PresentDATE(int mode)
{
    time_t PresentTime;
    PresentTime=time(NULL);
    struct tm * PresentDate;
    PresentDate=localtime(&PresentTime);
    int pdate,ptime;
    pdate=(PresentDate->tm_year+1900)*10000+(PresentDate->tm_mon+1)*100+PresentDate->tm_mday;
    ptime=(PresentDate->tm_hour)*10000+(PresentDate->tm_min)*100+PresentDate->tm_sec;
    if(mode==0)
        return pdate;
    else if(mode==1)
        return ptime;
    else if(mode==2)
        return PresentDate->tm_wday;
    else
        return -1;
}
//�ж��Ƿ����ļ������ļ�����1�����ļ��з���0
int IsFIle(char * filename[])
{
    return fopen(filename[0],"r")==NULL?0:1;
}
//��ʾ����ֵ
void DisplayFile(int argc,char *argv[])
{
    printf(">/ sum: %d\n\n",argc);
    for(int i=0; i<argc; i++)
    {
        printf(">/ %s --> %d\n",argv[i],IsFIle(&argv[i]));
    }

}
//��������������
int RenameFile(int argc,char *argv[])
{
    char choice='v';
    printf("------------------------------\n\n");
    printf("        �ļ�����������        \n\n");
    printf("        Dev: Ice2Faith        \n\n");
    printf("\t��ѡ��\n\n");
    printf("\t1.ԭ�ļ���-����ʱ��\n\n");
    printf("\t2.ԭ�ļ���-����-ʱ��\n\n");
    printf("\t3.ԭ�ļ���-����\n\n");
    printf("\t4.ԭ�ļ���-ʱ��\n\n");
    printf("\t5.ԭ�ļ���-���\n\n");
    printf("\t6.���ļ���-���\n\n");
    printf("\t7.���ļ���-���-����ʱ��\n\n");
    printf("\t8.�޸ĺ�׺\n\n");
    printf("\t9.ע������\n\n");
    printf("\t0.ȡ������\n\n");
    printf("------------------------------\n\n>/ ");
    while(choice<'0'||choice>'9')
        choice=getch();

    int sel=(int)(choice-'0');
    printf("%d\n",sel);
    if(sel==0)
        return 0;
    if(sel==9)
    {
        system("cls");
        printf("------------------------------\n\n");
        printf("           ע������           \n\n");
        printf("     �벻Ҫ�Ķ���������       \n\n");
        printf("   ������ܻᵼ���޷�ʹ��     \n\n");
        printf("       ������ģ���Ļ�       \n\n");
        printf("    Ĭ������ �ļ�����������   \n\n");
        printf("------------------------------\n\n");
        Sleep(2000);
        return 0;
    }
    char name[400]= {'\0'};
    char time[400]= {'\0'};
    char before[400]= {'\0'};
    char behind[400]= {'\0'};
    char File[100][1024]= {'\0'};
    char mind[2048]= {'\0'};
    int len,dsp,psp,j,k,con=0;
    int usernum=1;
    char userdefined[400]= {'\0'};
    char after[20]= {'\0'};
    fflush(stdin);
    switch(sel)
    {

    default:
    {
        break;
    }
    case 5:
    {

        printf("�������ʼ��ţ�\n\n>/ ");
        scanf("%d",&usernum);
        break;
    }

    case 6:
    {
        fflush(stdin);
        printf("���������ļ�����\n\n>/ ");
        gets(userdefined);
        printf("�������ʼ��ţ�\n\n>/ ");
        scanf("%d",&usernum);
        break;
    }

    case 7:
    {
        fflush(stdin);
        printf("���������ļ�����\n\n>/ ");
        gets(userdefined);
        printf("�������ʼ��ţ�\n\n>/ ");
        scanf("%d",&usernum);
        break;
    }

    case 8:
    {
        printf("�������׺��(.XXX)\n\n>/ ");
        fflush(stdin);
        scanf("%s",after);
        break;
    }

    }

    for(int i=0; i<argc; i++)
    {
        //�����������
        for(int b=0; b<400; b++)
        {
            if(name[b]!='\0')
                name[b]='\0';
            if(before[b]!='\0')
                before[b]='\0';
            if(time[b]!='\0')
                time[b]='\0';
            if(behind[b]!='\0')
                behind[b]='\0';
        }
        strcpy(File[i],argv[i]);
        //ͳ��·������
        len=0;
        while(File[i][len]!='\0')
            len++;
        //�����ļ��б�ʶ��λ��
        dsp=0;
        while(File[i][len-dsp]!='\\')
        {
            dsp++;
        }
        dsp=len-dsp+1;
        //����.����λ��
        psp=0;
        while(File[i][len-psp]!='.')
        {
            if(File[i][len-psp]=='\\')
            {
                psp=0;
                break;
            }
            psp++;
        }
        psp=len-psp;
        //����С�����Ժ�ĺ�׺��ȥbehind
        j=0;
        while(File[i][psp+j]!='\0')
        {
            behind[j]=File[i][psp+j];
            j++;
        }
        //����С������ǰ�����ֽ�ȥbefore
        k=0;
        while(File[i][dsp+k]!='.'&&File[i][dsp+k]!='\0')
        {
            before[k]=File[i][dsp+k];
            k++;
        }
        //����Ǳ�����Ļ�������
        if(strcmp(before,APPNAME)==0&&strcmp(behind,".exe")==0)
            continue;

        switch(sel)
        {
        case 1:
        {
            sprintf(time,"-%d%d\0",PresentDATE(0),PresentDATE(1));
            strcat(name,before);
            strcat(name,time);
            strcat(name,behind);
            break;
        }

        case 2:
            //�ϲ�����,ԭ����-����-ʱ��
        {
            sprintf(time,"-%d-%d\0",PresentDATE(0),PresentDATE(1));
            strcat(name,before);
            strcat(name,time);
            strcat(name,behind);
            break;
        }

        case 3:
        {
            sprintf(time,"-%d\0",PresentDATE(0));
            strcat(name,before);
            strcat(name,time);
            strcat(name,behind);
            break;
        }

        case 4:
        {
            sprintf(time,"-%d\0",PresentDATE(1));
            strcat(name,before);
            strcat(name,time);
            strcat(name,behind);
            break;
        }

        case 5:
        {
            sprintf(time,"-%d",usernum+i);
            strcat(name,before);
            strcat(name,time);
            strcat(name,behind);
            break;
        }

        case 6:
        {
            sprintf(time,"%s-%d",userdefined,usernum+i);
            strcat(name,time);
            strcat(name,behind);
            break;
        }

        case 7:
        {
            sprintf(time,"%s-%d-%d%d",userdefined,usernum+i,PresentDATE(0),PresentDATE(1));
            strcat(name,time);
            strcat(name,behind);
            break;
        }

        case 8:
        {
            if(after[0]!='.')
                sprintf(behind,".%s\0",after);
            else
                sprintf(behind,"%s\0",after);
            strcat(name,before);
            strcat(name,behind);
            break;
        }

        }
        //ִ������������
        sprintf(mind,"ren \"%s\" \"%s\"\0",File[i],name);
        system(mind);
    }


}

//������
int main(int argc,char *argv[])
{
    system("color f5");
    system("mode con cols=48 lines=38");
    system("title �ļ����������� Dev: Ice2Faith");
    RenameFile(argc,&argv[0]);
    return 0;
}

