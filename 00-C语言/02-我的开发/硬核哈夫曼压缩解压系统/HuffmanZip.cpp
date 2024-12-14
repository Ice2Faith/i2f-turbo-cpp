#include"HuffmanZip.h"

void InitEnvironment()
{
    /*申请空间和初始化参数*/
    RealData=(Data *)malloc(sizeof(Data));
    HuffRoot=NULL;
    HuffCodeLen=0;
}
void ClearEnvironment()
{
    /*释放空间和无效化参数*/
    free(RealData);
    RealData=NULL;
    HuffRoot=NULL;
    RemoveHuffTree(HuffRoot);
    HuffCodeLen=0;
}
WORD8 Array8ToWORD8(char arr[8])
{
    /*8位01序列对应转化为WORD8的一位*/
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
    /*获取压缩数据初始化环境*/
    InitEnvironment();
    if(GetDataFile(filepath)==I2FZIP_INVAILD_FILE)
        return I2FZIP_INVAILD_FILE;
    HuffRoot=BuildHuffTree();
    GetHuffCode(HuffRoot,&HuffCodeLen);
    /*打开待压缩文件和保存文件*/
    FILE * SI=fopen(filepath,"rb");
    FILE * DI=fopen(newfile,"wb");
    /*写入用于解压的必要信息和压缩标记*/
    fwrite(&flag,sizeof(flag),1,DI);
    fwrite(&RealData->len,sizeof(RealData->len),1,DI);
    for(int i=0; i<RealData->len; i++)
    {
        fwrite(&RealData->Chars[i],sizeof(RealData->Chars[i]),1,DI);
        fwrite(&RealData->Weights[i],sizeof(RealData->Weights[i]),1,DI);
    }
    /*定义读入写出数据单元*/
    WORD8 read=0;
    WORD8 write=0;
    char temp[8]= {0};
    /*定义缓冲区单元*/
    char buffer[64]= {0};
    /*定义单元长度跟踪*/
    int bufferlen=0;
    int templen=0;
    while(!feof(SI))
    {
        if(bufferlen<40)    /*检查读入下一个字符是否可能超出缓冲区大小*/
        {
            fread(&read,sizeof(WORD8),1,SI);    /*读取字符并找到对应的Huffman代码*/
            if(feof(SI))
                break;
            int i=0;
            while(i<HuffCodeLen)
            {
                if(hufcode[i].Char==read)
                    break;
                i++;
            }
            for(int j=hufcode[i].HuffLen-1; j>=0; j--)  /*填入缓冲区，因为是倒序，所以这里倒回来*/
            {
                buffer[bufferlen]=hufcode[i].HuffCode[j];
                bufferlen++;
            }
        }

        if(bufferlen>=8)    /*检查缓冲区数据大小是否充足*/
        {
            for(int j=0; j<8; j++)      /*获取缓冲区数据*/
            {
                temp[j]=buffer[j];
            }
            bufferlen-=8;
            for(int j=0; j<bufferlen; j++)      /*整理缓冲区空间*/
            {
                buffer[j]=buffer[j+8];
            }
            write=Array8ToWORD8(temp);      /*转换并保存*/
            fwrite(&write,sizeof(WORD8),1,DI);
        }

    }
    if(bufferlen<8)     /*检查文件读取结束后缓冲区是否还存在字符*/
    {
        for(int j=0; j<8; j++)  /*处理剩余字符*/
        {
            if(j<bufferlen)
                temp[j]=buffer[j];
            else
                temp[j]='0';
        }

        write=Array8ToWORD8(temp);
        fwrite(&write,sizeof(WORD8),1,DI);
    }
    fclose(SI);     /*关闭文件插座并清理运行残留*/
    fclose(DI);
    ClearEnvironment();
    return I2FZIP_SUCCESS;
}
/////////////////////////////////////////////////////////////////////////////////
void WORD8ToArray8(WORD8 tempc,char arr[8])
{
    WORD8 temp=tempc;
    for(int i=0; i<8; i++)  /*根据WORD8二进制转换为8位字符*/
    {
        if(temp&(1<<(7-i)))
            arr[i]='1';
        else
            arr[i]='0';
    }
}
I2FZIP_ERROR UnzipFile(char * filepath,char * newfile)
{
    InitEnvironment();      /*初始化环境并检查文件是否存在*/
    FILE * SI=fopen(filepath,"rb");
    if(SI==NULL)
        return I2FZIP_INVAILD_FILE;
    /*检查是否是已经压缩的文件*/
    char iszip[7]= {0};
    fread(&iszip,sizeof(iszip),1,SI);
    if(strcmp(iszip,flag)!=0)
        return I2FZIP_NOT_ZIPED;
    /*读取解压bit要信息并处理解压环境*/
    FILE * DI=fopen(newfile,"wb");
    fread(&RealData->len,sizeof(RealData->len),1,SI);
    for(int i=0; i<RealData->len; i++)
    {
        fread(&RealData->Chars[i],sizeof(RealData->Chars[i]),1,SI);
        fread(&RealData->Weights[i],sizeof(RealData->Weights[i]),1,SI);
    }
    HuffRoot=BuildHuffTree();
    GetHuffCode(HuffRoot,&HuffCodeLen);
    /*定义读入写出单元*/
    WORD8 read=0;
    WORD8 write=0;
    /*定义转换单元*/
    char temp[8]= {0};
    /*转码跟踪指针*/
    TreeNode * node=HuffRoot;
    while(!feof(SI))
    {
        fread(&read,sizeof(read),1,SI);     /*获取码单元并转换*/
        if(feof(SI))
            break;
        WORD8ToArray8(read,temp);
        for(int i=0; i<8; i++)      /*译码*/
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
    fclose(SI);     /*善后处理*/
    fclose(DI);
    ClearEnvironment();
    return I2FZIP_SUCCESS;
}

//删除Huff树
void RemoveHuffTree(TreeNode * node)
{
    if(!node)       /*递归删除节点*/
        return;
    TreeNode * lnode=node->Lchild,* rnode=node->Rchild;
    free(node);
    if(lnode)
        RemoveHuffTree(lnode);
    if(rnode)
        RemoveHuffTree(rnode);

}
//获得数据
I2FZIP_ERROR GetDataFile(char * filepath)
{
    RealData->len=0;        /*初始化存储单元*/
    for(int i=0; i<256+1; i++)
    {
        RealData->Chars[i]=0;
        RealData->Weights[i]=0;
    }
    FILE * SI=fopen(filepath,"rb");     /*检查文件打开*/
    if(SI==NULL)
        return I2FZIP_INVAILD_FILE;
    WORD8 temp=0;
    while(!feof(SI))            /*8位无符号字符位于0-255之间*/
    {
        fread(&temp,sizeof(WORD8),1,SI);    /*获取对应字符的数量、频数*/
        if(feof(SI))
            break;
        RealData->Chars[(int)temp]=temp;    /*这里重复赋值了，但是不想改了*/
        RealData->Weights[(int)temp]++;
    }
    fclose(SI);
    for(int i=0; i<256+1; i++)      /*对读入数据碎片化整理*/
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
//创建树节点
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
//创建Huffman树
TreeNode * BuildHuffTree()
{
    TreeNode * root=NULL;
    TreeNode * temp=NULL;
    TreeNode * tempnode[256+1]; /*为最大可能所有节点创建空间*/
    for(int i=0; i<RealData->len; i++) /*创建所有叶子节点并保存数据*/
    {
        tempnode[i]=CreateNode();
        tempnode[i]->ch=RealData->Chars[i];
        tempnode[i]->weight=RealData->Weights[i];
    }

    int fmin=0,smin=0;  /*最小权重和次小权重下标*/
    for(int i=1; i<RealData->len; i++)
    {
        fmin=-1,smin=-1;                    /*查找最小权重*/
        for(int j=0; j<RealData->len; j++)  /*先找到一个存在的节点*/
        {
            if(tempnode[j])
            {
                fmin=j;
                break;
            }

        }
        for(int j=0; j<RealData->len; j++)  /*找到真正最小的节点*/
        {
            if(tempnode[j] && tempnode[j]->weight<=tempnode[fmin]->weight)
            {
                fmin=j;
            }
        }
        for(int j=0; j<RealData->len; j++) /*查找次小权重*/
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
        /*合并最小次小节点形成新节点*/
        {
            temp=CreateNode();
            temp->Lchild=tempnode[fmin];
            temp->Rchild=tempnode[smin];
            temp->weight=tempnode[fmin]->weight+tempnode[smin]->weight;
            tempnode[fmin]->Parent=temp;
            tempnode[smin]->Parent=temp;
            tempnode[fmin]=temp;    /*合并后的节点保存在原来的最下节点中，次小节点清空*/
            tempnode[smin]=NULL;
            root=tempnode[fmin];    /*这一步的根节点，最后一次合并之后此节点就是根节点*/
        }

    }
    return root;
}

//根据Huffman树获取Huffman代码
void GetHuffCode(TreeNode * HFMTree,int * i)    /*由于进行先序遍历递归处理，因此这里的i标识要保存的Huffman编码的位置的下标，初始传入树根节点和下标0*/
{
    if(HFMTree) /*检查当前节点是否存在*/
    {
        if(!HFMTree->Lchild && !HFMTree->Rchild)    /*如果是叶子节点*/
        {
            hufcode[*i].Char=HFMTree->ch;       /*保存基本信息*/
            hufcode[*i].Weight=HFMTree->weight;
            TreeNode * tempchild,*tempparent;   /*循环找根节点时用的上一个节点和下一个节点*/
            tempchild=HFMTree;
            tempparent=HFMTree->Parent;
            int counter=0;      /*记录编码长度*/
            while(tempparent)   /*找到根节点结束*/
            {
                if(tempparent->Lchild==tempchild)   /*左孩子为0右孩子为1*/
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
            hufcode[*i].HuffCode[counter]='\0';     /*字符串结束，由于有长度控制，这个可以不用*/
            hufcode[*i].HuffLen=counter;
            (*i)++;
        }
        GetHuffCode(HFMTree->Lchild,i); /*递归找叶子节点*/
        GetHuffCode(HFMTree->Rchild,i);
    }
}
void GetPathInfo(char * path,char * save,PATH_INFO infotype)
{
    int i=0;
    while(path[i])  /*获取路径长度*/
        i++;
    if(infotype==PATH_FATHER)       /*判断要获取的内容类型*/
    {
        int j=i;
        while(path[j]!='\\'&&path[j]!=':'&&j>=0)    /*找到从后往前第一个文件分割位置*/
        {
            j--;
        }
        if(j<=0)    /*检查是否是相对路径*/
        {
            save[0]='.';
            save[1]='\0';
            return;
        }
        int m=0;
        while(m<j)  /*复制父目录信息*/
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
        while(path[j]!='\\'&&path[j]!=':'&&j>=0)    /*检查从后往前第一个文件分割*/
        {
            if(path[j]=='.'&&frist==1)  /*检查是否是后缀标识，最后一个.才算*/
            {
                n=j;
                frist=0;
            }

            j--;
        }
        int m=0;    /*复制文件名，知道后缀位置，没有后缀也能正常*/
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
        if(path[j]!='.')    /*判断是否有文件后缀*/
        {
            save[0]='\0';
            return;
        }
        int m=0;
        while(path[j+m])    /*复制文件后缀，包含.*/
        {
            save[m]=path[j+m];
            m++;
        }
        save[m]='\0';
    }
}
