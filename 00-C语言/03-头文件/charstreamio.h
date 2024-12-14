#ifndef _CHARSTREAMIO_H_
#define _CHARSTREAMIO_H_
/**
    char * / array I/O operation
    Copyright By Ice2Faith
    in stream part:
    stream:source array
    counter:read count
    save:save array
    newstrspace:new source array point end of this read
    maxlen:max read string length
    you can read a element from array,which is int/double/string/lines type.
    maybe you need provide counter for read.
    out stream part:
    you can output element to array,only on mode space provide type,and if it's double/float type,you need provide Fractional precision.
    elem:a element stress which int/double/char/string
    mode:present data type of OSTRMODE,(OSTRLF,OSTRF,OSTRC,OSTRS)
    Fract_prec:Fractional precision when is float number
    stream:output to stream array.
*/
#include <stdio.h>
#include <string.h>
typedef int OSTRMODE;
const OSTRMODE OSTRLF=1,OSTRF=2,OSTRD=3,OSTRC=4,OSTRS=5;
int istrint(char * stream,int counter,int * save,char ** newstrspace);
int istrdouble(char * stream,int counter,double * save,char ** newstrspace);
int istrchar(char * stream,char * save,char ** newstrspace);
int istrgets(char * stream,char * save,char ** newstrspace);
int istrgetline(char * stream,int maxlen,char * save,char ** newstrspace);
void ostr(void * elem,OSTRMODE mode,int Fract_prec,char * stream);
int istrint(char * stream,int counter,int * save,char ** newstrspace)
{
    int i=0;
    int num=0;
    int deline=0;
    while(*stream)
    {
        if(*stream>='0'&&*stream<='9')
        {
            num=0;
            deline=0;
            if(*(stream-1)=='-')
                deline=1;
            while(*stream>='0'&&*stream<='9')
            {
                num*=10;
                num+=(int)(*stream-'0');
                stream++;
            }
            if(deline)
                num=0-num;
            *save=num;
            save++;
            i++;
            if(i==counter)
                break;
        }
        else
            stream++;
    }
    *newstrspace=stream;
    return i;
}
int istrdouble(char * stream,int counter,double * save,char ** newstrspace)
{
    int i=0;
    double num=0;
    int deline=0;
    while(*stream)
    {
        if(*stream>='0'&&*stream<='9')
        {
            num=0;
            deline=0;
            if(*(stream-1)=='-')
                deline=1;
            while(*stream>='0'&&*stream<='9')
            {
                num*=10;
                num+=(int)(*stream-'0');
                stream++;
            }
            if(*stream=='.')
            {
                stream++;
                double tmp=0.1;
                while(*stream>='0'&&*stream<='9')
                {
                    num+=tmp*(int)(*stream-'0');
                    tmp*=0.1;
                    stream++;
                }
            }
            if(deline)
                num=0-num;
            *save=num;
            save++;
            i++;
            if(i==counter)
                break;
        }
        else
            stream++;
    }
    *newstrspace=stream;
    return i;
}
int istrchar(char * stream,char * save,char ** newstrspace)
{
    *save=*(stream++);
    *newstrspace=stream;
    return (*stream)=='\0'?0:1;
}
int istrgets(char * stream,char * save,char ** newstrspace)
{
    int i=0;
    while(*stream)
    {
        *(save++)=*(stream++);
        i++;
        if(*stream==' '||*stream=='\n')
            break;
    }
    *save='\0';
    *newstrspace=stream;
    return i;
}
int istrgetline(char * stream,int maxlen,char * save,char ** newstrspace)
{
    int i=0;
    while(*stream)
    {
        *(save++)=*(stream++);
        i++;
        if(*stream=='\n'||i==maxlen)
            break;
    }
    *save='\0';
    *newstrspace=stream;
    return i;
}
void ostr(void * elem,OSTRMODE mode,int Fract_prec,char * stream)
{
    char temp[1024*1024]= {0};
    char style[10]= {0};
    if(mode==OSTRF)
    {
        sprintf(style,"%%.%df",Fract_prec);
        sprintf(temp,style,*((float *)elem));
    }
    else if(mode==OSTRLF)
    {
        sprintf(style,"%%.%dlf",Fract_prec);
        sprintf(temp,style,*((double *)elem));
    }
    else if(mode==OSTRD)
    {
        sprintf(temp,"%d",*((int *)elem));
    }
    else if(mode==OSTRC)
    {
        sprintf(temp,"%c",*((char *)elem));
    }
    else if(mode==OSTRS)
    {
        sprintf(temp,"%s",(char *)elem);
    }
    strcat(stream,temp);
}

#endif // _CHARSTREAMIO_H_
