#include<stdio.h>
int GetPathInfo(char * path,char * save[],int savesize);
int GetPathPart(char * path,char * fpath,char * name,char * tail);
int main(int argc,char * argv[])
{
    system("color f1");
    system("Path part tool dev Ice2Faith");
    if(argc>1)
    {
        char fpath[256]= {0};
        char name[256]= {0};
        char tail[20]= {0};
        for(int i=1; i<argc; i++)
        {
            printf("Path:\t%s\n",argv[i]);
            GetPathPart(argv[i],fpath,name,tail);
            printf("FPath:\t%s\n",fpath);
            printf("Name:\t%s\n",name);
            printf("Tail:\t%s\n",tail);
            printf("------------------------------\n");
        }
        system("pause");
    }

    return 0;
}
int GetPathPart(char * path,char * fpath,char * name,char * tail)
{
    char * save[100]= {0};
    char  save_t[100][256]= {0};
    for(int i=0; i<100; i++)
        save[i]=save_t[i];
    GetPathInfo(path,save,sizeof(save_t[0]));
    int i=0;
    while(save[0][i])
    {
        tail[i]=save[0][i];
        i++;
    }
    tail[i]='\0';
    i=1;
    while(save[1][i])
    {
        name[i-1]=save[1][i];
        i++;
    }
    name[i-1]='\0';
    i=2;
    while(save[i][0])
        i++;
    int j=0;
    for(int k=i; k>=2; k--)
    {
        i=0;
        while(save[k][i])
        {
            fpath[j]=save[k][i];
            j++;
            i++;
        }
    }
    fpath[j]='\\';
    fpath[j+1]='\0';
}
int GetPathInfo(char * path,char * save[],int savesize)
{
    char Path[4096]= {0};
    int i=0,j=0,k=0,l=0;
    while(path[i])
    {
        Path[i]=path[i];
        i++;
        if(i==4095)
        {
            Path[i]='\0';
            return 0;
        }
    }
    Path[i]='\0';
    while(Path[i]!='.'&&Path[i]!='\\'&&i>0)
        i--;
    k=i;
    j=0;
    while(Path[k])
    {
        save[l][j]=Path[k];
        j++;
        k++;
        if(j==savesize-1)
        {
            save[l][j]='\0';
            return 0;
        }
    }
    while(1)
    {
        l++;
        Path[i]='\0';
        while(Path[i]!='\\'&&i>0)
            i--;
        j=0;
        k=i;
        while(Path[k])
        {
            save[l][j]=Path[k];
            j++;
            k++;
            if(j==savesize-1)
            {
                save[l][j]='\0';
                return 0;
            }
        }
        save[l][j]='\0';
        if(i<=0)
            break;
    }
}
