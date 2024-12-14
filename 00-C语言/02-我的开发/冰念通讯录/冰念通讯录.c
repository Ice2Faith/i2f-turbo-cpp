#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <io.h>
#define MAXRECORD 1024
typedef struct
{
    char name[40];  //����
    char phone1[20];    //�绰����1
    char phone2[20];    //�绰����2
    char about[100];    //��ע
} Record;   //��Ϣ�洢
typedef struct node
{
    Record Item;    //��Ϣ����
    struct node * next;  //��һ���ڵ�
} Contact;  //����ڵ�
typedef struct
{
    Contact * search[MAXRECORD];    //�ҵ��Ľڵ��ַ��Ϣ
    int count;  //�ҵ�����Ϣ����
} Search;   //����������Ϣ�洢

Contact * InitContact(void);    //�����ڵ���ʼ��ͷ���
char Meau(void);    //�˵�ѡ��
void ViewAll(Contact * List);   //��ʾ������ϵ�ˣ���������ͨѶ¼
void ViewRecord(Contact * ViewNode);    //��ʾһ����ϵ����Ϣ������Ҫ��ʾ�Ľڵ�
void ModifyRecord(Contact * ModifyNode);    //�޸�һ����Ϣ������Ҫ�޸ĵĽڵ�
void DelRecord(Contact * DelParent);    //ɾ��һ����Ϣ�������丸�ڵ�
void AddRecord(Contact * List); //���һ����Ϣ��ͷ�巨������ͨѶ¼
void ReadContact(Contact * List);   //β�巨�����Ϣ������ͨѶ¼
void WriteContact(Contact * List);  //д��ͨѶ¼��Ϣ
void SearchNode(Contact * List,Search * slist); //������Ϣ����ȷ������֧�����������룬��ע
int CountList(Contact * List);  //ͳ��ͨѶ¼��Ϣ����
void Help();    //�����ı�

int main(int argv,char * argc[])
{
    system("title ����ͨѶ¼ Dev: Ice2Faith");
    system("color f5");
    system("mode con cols=80");
    Contact * List=InitContact();   //����ͷ����ʼ��
    ReadContact(List);  //��ȡ��Ϣ���ļ�
    char sel;
    while(1)
    {
        sel=Meau();
        switch(sel)
        {
        case '1':
        {
            ViewAll(List);
            break;
        }
        case '2':
        {
            AddRecord(List);
            break;
        }
        case '3':
        {
            Search slist;   //����������
            SearchNode(List,&slist);
            int seld;
            printf("������Ҫɾ������ţ�\n");
            scanf("%d",&seld);
            fflush(stdin);
            if(seld>=0&&seld<slist.count)
            {
              DelRecord(slist.search[seld]);
              printf("ɾ���ɹ���\n");
            }else
                printf("ѡ�񲻺Ϸ���\n");
            break;
        }
        case '4':
        {
            Search slist;
            SearchNode(List,&slist);
            break;
        }
        case '5':
        {
            Search slist;
            SearchNode(List,&slist);
            int sels;
            printf("������Ҫ�޸ĵ���ţ�\n");
            scanf("%d",&sels);
            fflush(stdin);
            if(sels>=0&&sels<slist.count)
            {
              ModifyRecord((slist.search[sels])->next);
            }else
                printf("���벻�Ϸ���\n");
            break;
        }
        case '6':
        {
            Help();
            break;
        }
        case '0':
        {
            WriteContact(List);
            printf("��¼�ѱ��棬�����˳�\n");
            Sleep(1200);
            break;
        }
        }
        WriteContact(List); //�˴�Ϊ��ֹû�������˳���������ʧ��������
        if(sel=='0')
            break;
        else
            system("pause");
        system("cls");
    }


    return 0;
}
void SearchNode(Contact * List,Search * slist)
{
    slist->count=0; //������С���ÿ�
    Contact * P=NULL;   //�½ڵ�
    Contact * F=List;   //β�ڵ�
    fflush(stdin);
    printf("��������Ҫ��ѯ�����ݣ���ȷ���ң�\n");
    char key[100]= {0};
    gets(key);
    P=List->next;
    while(P)
    {
        if(strcmp(P->Item.name,key)==0) //�����Ǽ���������һ����Ͼͼ�¼��elseʹ��Ϊ��ֹ�ظ����Ҽ�¼
        {
            slist->search[(slist->count)++]=F;
        }
        else if(strcmp(P->Item.phone1,key)==0)
        {
            slist->search[(slist->count)++]=F;
        }
        else if(strcmp(P->Item.phone2,key)==0)
        {
            slist->search[(slist->count)++]=F;
        }
        else if(strcmp(P->Item.about,key)==0)
        {
            slist->search[(slist->count)++]=F;
        }
        P=P->next;
        F=F->next;
    }
    printf("���ҵ���ϵ�ˣ�\n");
    for(int i=0; i<slist->count; i++)
    {
        printf("%d\t",i);
        ViewRecord((slist->search[i])->next);   //�ҵ������丸�ڵ㣬���Ҫ����ӽڵ�
    }

}
void ReadContact(Contact * List)
{
    char pathinfo[1024]= {"C:\\ContactData"};
    char mind[2048];
    sprintf(mind,"%s\\ContactList.bin",pathinfo);

    if(access(mind,F_OK)!=0)    //����ļ��Ƿ���ڣ������ھͲ����ж�ȡ
        return;
    FILE * Path=fopen(mind,"r");
    int count=0;
    int i=0;
    fscanf(Path,"%d",&count);   //�ȶ�ȡ��¼�������ڶ�ȡ��Ӧ��������Ϣ
    Contact * P=NULL;
    Contact * R=List;   //β�ڵ�
    while(!feof(Path)&&i<count)
    {
        P=InitContact();
        R->next=P;
        R=P;
        fscanf(Path,"%s %s %s %s",P->Item.name,P->Item.phone1,P->Item.phone2,P->Item.about);
        i++;
    }

}
int CountList(Contact * List)
{
    int count=0;
    List=List->next;
    while(List)
    {
        count++;
        List=List->next;
    }
    return count;
}
void WriteContact(Contact * List)
{
    char pathinfo[1024]= {"C:\\ContactData"};
    char mind[2048];
    sprintf(mind,"md \"%s\"\0",pathinfo);
    if(access("C:\\ContactData",F_OK)!=0)
        system(mind);
    sprintf(mind,"%s\\ContactList.bin",pathinfo);
    FILE * Path=fopen(mind,"w");
    int count=CountList(List);
    fprintf(Path,"%d\n",count); //��д���¼��������д���¼
    Contact * P=List->next;
    while(P)
    {
        fprintf(Path,"%s %s %s %s\n",P->Item.name,P->Item.phone1,P->Item.phone2,P->Item.about);
        P=P->next;
    }
    fclose(Path);
}
void ViewAll(Contact * List)
{
    Contact * P=List->next;
    while(P)
    {
        ViewRecord(P);
        P=P->next;
    }
    printf("\nȫ����ϵ������ʾ\n");
}
void ViewRecord(Contact * ViewNode)
{
    printf("����:%s\t���� 1:%s\t���� 2:%s\t��ע:%s\n",ViewNode->Item.name,ViewNode->Item.phone1,ViewNode->Item.phone2,ViewNode->Item.about);
}
void ModifyRecord(Contact * ModifyNode)
{
    ViewRecord(ModifyNode); //����ʾ��Ϣ������
    char temp[100];
    char modi='8';
    modi='9';
    fflush(stdin);
    printf("�޸����������� *�����򲻸���\n");
    modi=getch();
    if(modi=='*')
    {
        fflush(stdin);
        printf("������������\n");
        gets(temp);
        if(strlen(temp))    //�������ĳ��ȣ����Ϊ���򲻽��и��ǣ�����
            strcpy(ModifyNode->Item.name,temp);
        printf("���޸�\n");
    }
    modi='9';
    fflush(stdin);
    printf("�޸ĺ���1������ *�����򲻸���\n");
    modi=getch();
    if(modi=='*')
    {
        fflush(stdin);
        printf("���������1��\n");
        gets(temp);
        if(strlen(temp))
            strcpy(ModifyNode->Item.phone1,temp);
        printf("���޸�\n");
    }
    modi='9';
    fflush(stdin);
    printf("�޸ĺ���2������ *�����򲻸���\n");
    modi=getch();
    if(modi=='*')
    {
        fflush(stdin);
        printf("���������2��\n");
        gets(temp);
        if(strlen(temp))
            strcpy(ModifyNode->Item.phone2,temp);
        printf("���޸�\n");
    }
    modi='9';
    fflush(stdin);
    printf("�޸ı�ע������ *�����򲻸���\n");
    modi=getch();
    if(modi=='*')
    {
        fflush(stdin);
        printf("�����뱸ע��\n");
        gets(temp);
        if(strlen(temp))
            strcpy(ModifyNode->Item.about,temp);
        printf("���޸�\n");
    }
    printf("�޸���ɣ�\n");
    ViewRecord(ModifyNode);
}
void DelRecord(Contact * DelParent)
{
    Contact * P=DelParent->next;    //ɾ���ڵ�
    DelParent->next=P->next;
    free(P);
}
void AddRecord(Contact * List)
{
    char deful[]= {"#*#\0"};
    Contact * P=InitContact();
    P->next=List->next;
    List->next=P;
    printf("������������\n");
    gets(P->Item.name);
    printf("���������1��\n");
    gets(P->Item.phone1);
    printf("���������2��\n");
    gets(P->Item.phone2);
    printf("�����뱸ע��\n");
    gets(P->Item.about);
    if(!strlen(P->Item.name))   //����Ƿ����������ݣ�Ϊ�������Ĭ��
        strcpy(P->Item.name,deful);
    if(!strlen(P->Item.phone1))
        strcpy(P->Item.phone1,deful);
    if(!strlen(P->Item.phone2))
        strcpy(P->Item.phone2,deful);
    if(!strlen(P->Item.about))
        strcpy(P->Item.about,deful);
    printf("�Ѵ�����\n");
    ViewRecord(P);  //��ʾ��ӵ���Ϣ��Ϊ����
}
Contact * InitContact(void)
{
    Contact * H=(Contact *)malloc(sizeof(Contact));
    H->next=NULL;
    return H;
}
char Meau(void)
{
    printf("-------------------------------------------\n");
    printf("\t\t����ͨѶ¼\n\n");
    printf("\t1.�鿴ȫ����ϵ��\n");
    printf("\t2.�����ϵ��\n");
    printf("\t3.ɾ����ϵ��\n");
    printf("\t4.������ϵ��\n");
    printf("\t5.�޸���ϵ��\n");
    printf("\t6.�鿴����\n");
    printf("\t0.���沢�˳�\n");
    printf("-------------------------------------------\n");
    printf(">/ ");
    char sel='9';
    while(sel<'0'||sel>'6') //ǿ�ƻ�ȡ��ȷѡ��
        sel=getch();
    printf("%c\n",sel); //�������뷴��
    fflush(stdin);
    return sel;
}
void Help()
{
    system("cls");
    printf("-------------------------------------------\n");
    printf("\t\tHELP\n\n");
    printf("\t���ͨѶ¼�ļ�λ�ã�\n");
    printf("\tC:\\ContactData\\ContactList.bin\n");
    printf("\t��ˣ��벻Ҫɾ�������������ݶ�ʧ\n");
    printf("\t���û�����뽫���� \"#*#\" ���\n");
    printf("\n\tBuild Date:\t2019/01/29 17:23\n");
    printf("\tDev:\t\tIce2Faith/����\n");
    printf("-------------------------------------------\n");
}
