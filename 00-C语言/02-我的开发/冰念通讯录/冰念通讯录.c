#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <io.h>
#define MAXRECORD 1024
typedef struct
{
    char name[40];  //姓名
    char phone1[20];    //电话号码1
    char phone2[20];    //电话号码2
    char about[100];    //备注
} Record;   //信息存储
typedef struct node
{
    Record Item;    //信息储存
    struct node * next;  //下一个节点
} Contact;  //链表节点
typedef struct
{
    Contact * search[MAXRECORD];    //找到的节点地址信息
    int count;  //找到的信息数量
} Search;   //索引查找信息存储

Contact * InitContact(void);    //创建节点或初始化头结点
char Meau(void);    //菜单选择
void ViewAll(Contact * List);   //显示所有联系人，传入整个通讯录
void ViewRecord(Contact * ViewNode);    //显示一条联系人信息，传入要显示的节点
void ModifyRecord(Contact * ModifyNode);    //修改一条信息，传入要修改的节点
void DelRecord(Contact * DelParent);    //删除一条信息，传入其父节点
void AddRecord(Contact * List); //添加一条信息，头插法，传入通讯录
void ReadContact(Contact * List);   //尾插法添加信息，传入通讯录
void WriteContact(Contact * List);  //写出通讯录信息
void SearchNode(Contact * List,Search * slist); //查找信息，精确搜索，支持姓名，号码，备注
int CountList(Contact * List);  //统计通讯录信息数量
void Help();    //帮助文本

int main(int argv,char * argc[])
{
    system("title 冰念通讯录 Dev: Ice2Faith");
    system("color f5");
    system("mode con cols=80");
    Contact * List=InitContact();   //创建头结点初始化
    ReadContact(List);  //读取信息从文件
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
            Search slist;   //创建索引表
            SearchNode(List,&slist);
            int seld;
            printf("请输入要删除的序号：\n");
            scanf("%d",&seld);
            fflush(stdin);
            if(seld>=0&&seld<slist.count)
            {
              DelRecord(slist.search[seld]);
              printf("删除成功！\n");
            }else
                printf("选择不合法！\n");
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
            printf("请输入要修改的序号：\n");
            scanf("%d",&sels);
            fflush(stdin);
            if(sels>=0&&sels<slist.count)
            {
              ModifyRecord((slist.search[sels])->next);
            }else
                printf("输入不合法！\n");
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
            printf("记录已保存，即将退出\n");
            Sleep(1200);
            break;
        }
        }
        WriteContact(List); //此处为防止没有正常退出而导致损失大量数据
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
    slist->count=0; //索引大小先置空
    Contact * P=NULL;   //新节点
    Contact * F=List;   //尾节点
    fflush(stdin);
    printf("请输入你要查询的内容（精确查找）\n");
    char key[100]= {0};
    gets(key);
    P=List->next;
    while(P)
    {
        if(strcmp(P->Item.name,key)==0) //不管是检索到和那一项符合就记录，else使用为防止重复查找记录
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
    printf("已找到联系人：\n");
    for(int i=0; i<slist->count; i++)
    {
        printf("%d\t",i);
        ViewRecord((slist->search[i])->next);   //找到的是其父节点，因此要输出子节点
    }

}
void ReadContact(Contact * List)
{
    char pathinfo[1024]= {"C:\\ContactData"};
    char mind[2048];
    sprintf(mind,"%s\\ContactList.bin",pathinfo);

    if(access(mind,F_OK)!=0)    //检查文件是否存在，不存在就不进行读取
        return;
    FILE * Path=fopen(mind,"r");
    int count=0;
    int i=0;
    fscanf(Path,"%d",&count);   //先读取记录的数量在读取对应数量的信息
    Contact * P=NULL;
    Contact * R=List;   //尾节点
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
    fprintf(Path,"%d\n",count); //先写入记录的数量在写入记录
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
    printf("\n全部联系人已显示\n");
}
void ViewRecord(Contact * ViewNode)
{
    printf("姓名:%s\t号码 1:%s\t号码 2:%s\t备注:%s\n",ViewNode->Item.name,ViewNode->Item.phone1,ViewNode->Item.phone2,ViewNode->Item.about);
}
void ModifyRecord(Contact * ModifyNode)
{
    ViewRecord(ModifyNode); //先显示信息做对照
    char temp[100];
    char modi='8';
    modi='9';
    fflush(stdin);
    printf("修改姓名请输入 *，否则不更改\n");
    modi=getch();
    if(modi=='*')
    {
        fflush(stdin);
        printf("请输入姓名：\n");
        gets(temp);
        if(strlen(temp))    //检查输入的长度，如果为零则不进行覆盖，保留
            strcpy(ModifyNode->Item.name,temp);
        printf("已修改\n");
    }
    modi='9';
    fflush(stdin);
    printf("修改号码1请输入 *，否则不更改\n");
    modi=getch();
    if(modi=='*')
    {
        fflush(stdin);
        printf("请输入号码1：\n");
        gets(temp);
        if(strlen(temp))
            strcpy(ModifyNode->Item.phone1,temp);
        printf("已修改\n");
    }
    modi='9';
    fflush(stdin);
    printf("修改号码2请输入 *，否则不更改\n");
    modi=getch();
    if(modi=='*')
    {
        fflush(stdin);
        printf("请输入号码2：\n");
        gets(temp);
        if(strlen(temp))
            strcpy(ModifyNode->Item.phone2,temp);
        printf("已修改\n");
    }
    modi='9';
    fflush(stdin);
    printf("修改备注请输入 *，否则不更改\n");
    modi=getch();
    if(modi=='*')
    {
        fflush(stdin);
        printf("请输入备注：\n");
        gets(temp);
        if(strlen(temp))
            strcpy(ModifyNode->Item.about,temp);
        printf("已修改\n");
    }
    printf("修改完成：\n");
    ViewRecord(ModifyNode);
}
void DelRecord(Contact * DelParent)
{
    Contact * P=DelParent->next;    //删除节点
    DelParent->next=P->next;
    free(P);
}
void AddRecord(Contact * List)
{
    char deful[]= {"#*#\0"};
    Contact * P=InitContact();
    P->next=List->next;
    List->next=P;
    printf("请输入姓名：\n");
    gets(P->Item.name);
    printf("请输入号码1：\n");
    gets(P->Item.phone1);
    printf("请输入号码2：\n");
    gets(P->Item.phone2);
    printf("请输入备注：\n");
    gets(P->Item.about);
    if(!strlen(P->Item.name))   //检查是否有输入内容，为空则填充默认
        strcpy(P->Item.name,deful);
    if(!strlen(P->Item.phone1))
        strcpy(P->Item.phone1,deful);
    if(!strlen(P->Item.phone2))
        strcpy(P->Item.phone2,deful);
    if(!strlen(P->Item.about))
        strcpy(P->Item.about,deful);
    printf("已创建：\n");
    ViewRecord(P);  //显示添加的信息作为反馈
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
    printf("\t\t冰念通讯录\n\n");
    printf("\t1.查看全部联系人\n");
    printf("\t2.添加联系人\n");
    printf("\t3.删除联系人\n");
    printf("\t4.查找联系人\n");
    printf("\t5.修改联系人\n");
    printf("\t6.查看帮助\n");
    printf("\t0.保存并退出\n");
    printf("-------------------------------------------\n");
    printf(">/ ");
    char sel='9';
    while(sel<'0'||sel>'6') //强制获取正确选项
        sel=getch();
    printf("%c\n",sel); //给予输入反馈
    fflush(stdin);
    return sel;
}
void Help()
{
    system("cls");
    printf("-------------------------------------------\n");
    printf("\t\tHELP\n\n");
    printf("\t你的通讯录文件位置：\n");
    printf("\tC:\\ContactData\\ContactList.bin\n");
    printf("\t因此，请不要删除它，以免数据丢失\n");
    printf("\t如果没有输入将会以 \"#*#\" 填充\n");
    printf("\n\tBuild Date:\t2019/01/29 17:23\n");
    printf("\tDev:\t\tIce2Faith/冰念\n");
    printf("-------------------------------------------\n");
}
