#include"HuffmanZip.h"

void InitEnvironment()
{
    /*����ռ�ͳ�ʼ������*/
    RealData=(Data *)malloc(sizeof(Data));
    HuffRoot=NULL;
    HuffCodeLen=0;
}
void ClearEnvironment()
{
    /*�ͷſռ����Ч������*/
    free(RealData);
    RealData=NULL;
    HuffRoot=NULL;
    RemoveHuffTree(HuffRoot);
    HuffCodeLen=0;
}
WORD8 Array8ToWORD8(char arr[8])
{
    /*8λ01���ж�Ӧת��ΪWORD8��һλ*/
    WORD8 temp=0;
    for(int i=0; i<8; i++)
    {
        if(arr[i]=='0')
            temp|=0<<(7-i);
        else if(arr[i]=='1')
            temp|=1<<(7-i);
    }
    return temp;
}
I2FZIP_ERROR ZipFile(char * filepath,char * newfile)
{
    /*��ȡѹ�����ݳ�ʼ������*/
    InitEnvironment();
    if(GetDataFile(filepath)==I2FZIP_INVAILD_FILE)
        return I2FZIP_INVAILD_FILE;
    HuffRoot=BuildHuffTree();
    GetHuffCode(HuffRoot,&HuffCodeLen);
    /*�򿪴�ѹ���ļ��ͱ����ļ�*/
    FILE * SI=fopen(filepath,"rb");
    FILE * DI=fopen(newfile,"wb");
    /*д�����ڽ�ѹ�ı�Ҫ��Ϣ��ѹ�����*/
    fwrite(&flag,sizeof(flag),1,DI);
    fwrite(&RealData->len,sizeof(RealData->len),1,DI);
    for(int i=0; i<RealData->len; i++)
    {
        fwrite(&RealData->Chars[i],sizeof(RealData->Chars[i]),1,DI);
        fwrite(&RealData->Weights[i],sizeof(RealData->Weights[i]),1,DI);
    }
    /*�������д�����ݵ�Ԫ*/
    WORD8 read=0;
    WORD8 write=0;
    char temp[8]= {0};
    /*���建������Ԫ*/
    char buffer[64]= {0};
    /*���嵥Ԫ���ȸ���*/
    int bufferlen=0;
    int templen=0;
    while(!feof(SI))
    {
        if(bufferlen<40)    /*��������һ���ַ��Ƿ���ܳ�����������С*/
        {
            fread(&read,sizeof(WORD8),1,SI);    /*��ȡ�ַ����ҵ���Ӧ��Huffman����*/
            if(feof(SI))
                break;
            int i=0;
            while(i<HuffCodeLen)
            {
                if(hufcode[i].Char==read)
                    break;
                i++;
            }
            for(int j=hufcode[i].HuffLen-1; j>=0; j--)  /*���뻺��������Ϊ�ǵ����������ﵹ����*/
            {
                buffer[bufferlen]=hufcode[i].HuffCode[j];
                bufferlen++;
            }
        }

        if(bufferlen>=8)    /*��黺�������ݴ�С�Ƿ����*/
        {
            for(int j=0; j<8; j++)      /*��ȡ����������*/
            {
                temp[j]=buffer[j];
            }
            bufferlen-=8;
            for(int j=0; j<bufferlen; j++)      /*���������ռ�*/
            {
                buffer[j]=buffer[j+8];
            }
            write=Array8ToWORD8(temp);      /*ת��������*/
            fwrite(&write,sizeof(WORD8),1,DI);
        }

    }
    if(bufferlen<8)     /*����ļ���ȡ�����󻺳����Ƿ񻹴����ַ�*/
    {
        for(int j=0; j<8; j++)  /*����ʣ���ַ�*/
        {
            if(j<bufferlen)
                temp[j]=buffer[j];
            else
                temp[j]='0';
        }

        write=Array8ToWORD8(temp);
        fwrite(&write,sizeof(WORD8),1,DI);
    }
    fclose(SI);     /*�ر��ļ��������������в���*/
    fclose(DI);
    ClearEnvironment();
    return I2FZIP_SUCCESS;
}
/////////////////////////////////////////////////////////////////////////////////
void WORD8ToArray8(WORD8 tempc,char arr[8])
{
    WORD8 temp=tempc;
    for(int i=0; i<8; i++)  /*����WORD8������ת��Ϊ8λ�ַ�*/
    {
        if(temp&(1<<(7-i)))
            arr[i]='1';
        else
            arr[i]='0';
    }
}
I2FZIP_ERROR UnzipFile(char * filepath,char * newfile)
{
    InitEnvironment();      /*��ʼ������������ļ��Ƿ����*/
    FILE * SI=fopen(filepath,"rb");
    if(SI==NULL)
        return I2FZIP_INVAILD_FILE;
    /*����Ƿ����Ѿ�ѹ�����ļ�*/
    char iszip[7]= {0};
    fread(&iszip,sizeof(iszip),1,SI);
    if(strcmp(iszip,flag)!=0)
        return I2FZIP_NOT_ZIPED;
    /*��ȡ��ѹbitҪ��Ϣ�������ѹ����*/
    FILE * DI=fopen(newfile,"wb");
    fread(&RealData->len,sizeof(RealData->len),1,SI);
    for(int i=0; i<RealData->len; i++)
    {
        fread(&RealData->Chars[i],sizeof(RealData->Chars[i]),1,SI);
        fread(&RealData->Weights[i],sizeof(RealData->Weights[i]),1,SI);
    }
    HuffRoot=BuildHuffTree();
    GetHuffCode(HuffRoot,&HuffCodeLen);
    /*�������д����Ԫ*/
    WORD8 read=0;
    WORD8 write=0;
    /*����ת����Ԫ*/
    char temp[8]= {0};
    /*ת�����ָ��*/
    TreeNode * node=HuffRoot;
    while(!feof(SI))
    {
        fread(&read,sizeof(read),1,SI);     /*��ȡ�뵥Ԫ��ת��*/
        if(feof(SI))
            break;
        WORD8ToArray8(read,temp);
        for(int i=0; i<8; i++)      /*����*/
        {
            if(!node->Lchild && !node->Rchild)
            {
                write=node->ch;
                fwrite(&write,sizeof(write),1,DI);
                node=HuffRoot;
            }
            if(temp[i]=='0')
                node=node->Lchild;
            else if(temp[i]=='1')
                node=node->Rchild;

        }
    }
    fclose(SI);     /*�ƺ���*/
    fclose(DI);
    ClearEnvironment();
    return I2FZIP_SUCCESS;
}

//ɾ��Huff��
void RemoveHuffTree(TreeNode * node)
{
    if(!node)       /*�ݹ�ɾ���ڵ�*/
        return;
    TreeNode * lnode=node->Lchild,* rnode=node->Rchild;
    free(node);
    if(lnode)
        RemoveHuffTree(lnode);
    if(rnode)
        RemoveHuffTree(rnode);

}
//�������
I2FZIP_ERROR GetDataFile(char * filepath)
{
    RealData->len=0;        /*��ʼ���洢��Ԫ*/
    for(int i=0; i<256+1; i++)
    {
        RealData->Chars[i]=0;
        RealData->Weights[i]=0;
    }
    FILE * SI=fopen(filepath,"rb");     /*����ļ���*/
    if(SI==NULL)
        return I2FZIP_INVAILD_FILE;
    WORD8 temp=0;
    while(!feof(SI))            /*8λ�޷����ַ�λ��0-255֮��*/
    {
        fread(&temp,sizeof(WORD8),1,SI);    /*��ȡ��Ӧ�ַ���������Ƶ��*/
        if(feof(SI))
            break;
        RealData->Chars[(int)temp]=temp;    /*�����ظ���ֵ�ˣ����ǲ������*/
        RealData->Weights[(int)temp]++;
    }
    fclose(SI);
    for(int i=0; i<256+1; i++)      /*�Զ���������Ƭ������*/
    {
        if(RealData->Weights[i]!=0)
        {
            RealData->Chars[RealData->len]=RealData->Chars[i];
            RealData->Weights[RealData->len]=RealData->Weights[i];
            if(RealData->len!=i)
            {
                RealData->Weights[i]=0;
                RealData->Chars[i]=0;
            }

            RealData->len++;
        }
    }
    return I2FZIP_SUCCESS;
}
//�������ڵ�
TreeNode * CreateNode()
{
    TreeNode * temp=(TreeNode *)malloc(sizeof(TreeNode));
    temp->ch=0;
    temp->weight=0;
    temp->Lchild=NULL;
    temp->Parent=NULL;
    temp->Rchild=NULL;
    return temp;
}
//����Huffman��
TreeNode * BuildHuffTree()
{
    TreeNode * root=NULL;
    TreeNode * temp=NULL;
    TreeNode * tempnode[256+1]; /*Ϊ���������нڵ㴴���ռ�*/
    for(int i=0; i<RealData->len; i++) /*��������Ҷ�ӽڵ㲢��������*/
    {
        tempnode[i]=CreateNode();
        tempnode[i]->ch=RealData->Chars[i];
        tempnode[i]->weight=RealData->Weights[i];
    }

    int fmin=0,smin=0;  /*��СȨ�غʹ�СȨ���±�*/
    for(int i=1; i<RealData->len; i++)
    {
        fmin=-1,smin=-1;                    /*������СȨ��*/
        for(int j=0; j<RealData->len; j++)  /*���ҵ�һ�����ڵĽڵ�*/
        {
            if(tempnode[j])
            {
                fmin=j;
                break;
            }

        }
        for(int j=0; j<RealData->len; j++)  /*�ҵ�������С�Ľڵ�*/
        {
            if(tempnode[j] && tempnode[j]->weight<=tempnode[fmin]->weight)
            {
                fmin=j;
            }
        }
        for(int j=0; j<RealData->len; j++) /*���Ҵ�СȨ��*/
        {
            if(tempnode[j] && j!=fmin)
            {
                smin=j;
                break;
            }
        }
        for(int j=0; j<RealData->len; j++)
        {
            if(tempnode[j] && j!=fmin && tempnode[j]->weight<=tempnode[smin]->weight)
            {
                smin=j;
            }
        }
        /*�ϲ���С��С�ڵ��γ��½ڵ�*/
        {
            temp=CreateNode();
            temp->Lchild=tempnode[fmin];
            temp->Rchild=tempnode[smin];
            temp->weight=tempnode[fmin]->weight+tempnode[smin]->weight;
            tempnode[fmin]->Parent=temp;
            tempnode[smin]->Parent=temp;
            tempnode[fmin]=temp;    /*�ϲ���Ľڵ㱣����ԭ�������½ڵ��У���С�ڵ����*/
            tempnode[smin]=NULL;
            root=tempnode[fmin];    /*��һ���ĸ��ڵ㣬���һ�κϲ�֮��˽ڵ���Ǹ��ڵ�*/
        }

    }
    return root;
}

//����Huffman����ȡHuffman����
void GetHuffCode(TreeNode * HFMTree,int * i)    /*���ڽ�����������ݹ鴦����������i��ʶҪ�����Huffman�����λ�õ��±꣬��ʼ���������ڵ���±�0*/
{
    if(HFMTree) /*��鵱ǰ�ڵ��Ƿ����*/
    {
        if(!HFMTree->Lchild && !HFMTree->Rchild)    /*�����Ҷ�ӽڵ�*/
        {
            hufcode[*i].Char=HFMTree->ch;       /*���������Ϣ*/
            hufcode[*i].Weight=HFMTree->weight;
            TreeNode * tempchild,*tempparent;   /*ѭ���Ҹ��ڵ�ʱ�õ���һ���ڵ����һ���ڵ�*/
            tempchild=HFMTree;
            tempparent=HFMTree->Parent;
            int counter=0;      /*��¼���볤��*/
            while(tempparent)   /*�ҵ����ڵ����*/
            {
                if(tempparent->Lchild==tempchild)   /*����Ϊ0�Һ���Ϊ1*/
                {
                    hufcode[*i].HuffCode[counter++]='0';
                }
                else
                {
                    hufcode[*i].HuffCode[counter++]='1';
                }
                tempchild=tempparent;
                tempparent=tempchild->Parent;
            }
            hufcode[*i].HuffCode[counter]='\0';     /*�ַ��������������г��ȿ��ƣ�������Բ���*/
            hufcode[*i].HuffLen=counter;
            (*i)++;
        }
        GetHuffCode(HFMTree->Lchild,i); /*�ݹ���Ҷ�ӽڵ�*/
        GetHuffCode(HFMTree->Rchild,i);
    }
}
void GetPathInfo(char * path,char * save,PATH_INFO infotype)
{
    int i=0;
    while(path[i])  /*��ȡ·������*/
        i++;
    if(infotype==PATH_FATHER)       /*�ж�Ҫ��ȡ����������*/
    {
        int j=i;
        while(path[j]!='\\'&&path[j]!=':'&&j>=0)    /*�ҵ��Ӻ���ǰ��һ���ļ��ָ�λ��*/
        {
            j--;
        }
        if(j<=0)    /*����Ƿ������·��*/
        {
            save[0]='.';
            save[1]='\0';
            return;
        }
        int m=0;
        while(m<j)  /*���Ƹ�Ŀ¼��Ϣ*/
        {
            save[m]=path[m];
            m++;
        }
        save[m]='\0';
    }
    else if(infotype==PATH_NAME)
    {
        int j=i,n=i;
        int frist=1;
        while(path[j]!='\\'&&path[j]!=':'&&j>=0)    /*���Ӻ���ǰ��һ���ļ��ָ�*/
        {
            if(path[j]=='.'&&frist==1)  /*����Ƿ��Ǻ�׺��ʶ�����һ��.����*/
            {
                n=j;
                frist=0;
            }

            j--;
        }
        int m=0;    /*�����ļ�����֪����׺λ�ã�û�к�׺Ҳ������*/
        while(j+1+m<n)
        {
            save[m]=path[j+1+m];
            m++;
        }
        save[m]='\0';
    }
    else if(infotype==PATH_TAIL)
    {
        int j=i;
        while(path[j]!='\\'&&path[j]!=':'&&path[j]!='.'&&j>=0)
        {
            j--;
        }
        if(path[j]!='.')    /*�ж��Ƿ����ļ���׺*/
        {
            save[0]='\0';
            return;
        }
        int m=0;
        while(path[j+m])    /*�����ļ���׺������.*/
        {
            save[m]=path[j+m];
            m++;
        }
        save[m]='\0';
    }
}
