#ifndef _PATHINFO_H_
#define _PATHINFO_H_
/*
>>c:\acc\bcc
fpath: c:\acc
name: bcc
*/
void GetPathPart(char * path,char * fpath,char * name,char * tail);
void GetPathPart(char * path,char * fpath,char * name,char * tail)
{
    char tpath[4096]= {0};
    strcpy(tpath,path);
    int p=0;
    while(tpath[p])
    {
        if(tpath[p]==':')
            break;
        p++;
    }
    if(tpath[p+1]!='\\')
    {
        int len=strlen(tpath);
        int i=len;
        while(i!=p)
        {
            tpath[i+1]=tpath[i];
            i--;
        }
        tpath[p+1]='\\';
    }
    int len=strlen(tpath);
    int stail=-1;
    int sname=-1;
    int spath=-1;
    int i=0;
    while(tpath[i])
    {
        if(tpath[i]=='\\')
            sname=i;
        if(tpath[i]=='.')
            stail=i;
        i++;
    }
    int k=0;
    int j=0;
    if(stail!=-1)
    {
        j=stail+1;
        while(tpath[j])
        {
            tail[k]=tpath[j];
            k++;
            j++;
        }
    }
    else
        stail=len;
    tail[k]=0;

    k=0;
    j=0;
    if(sname!=-1)
    {
        j=sname+1;
        while(j<stail)
        {
            name[k]=tpath[j];
            k++;
            j++;
        }
    }
    else
    {
        j=0;
        while(j<stail)
        {
            name[k]=tpath[j];
            k++;
            j++;
        }
        sname=0;
    }

    name[k]=0;

    k=0;
    while(k<sname)
    {
        fpath[k]=tpath[k];
        k++;
    }
    fpath[k]=0;
}
#endif // _PATHINFO_H_
