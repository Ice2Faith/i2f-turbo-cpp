/****************************************
*   copyright:  Ice2Faith
*   email:      18286715053@163.com
*---------------------------------------
*   �����ȷʹ��ѹ����ѹ���ܣ�
*   ������ͷ�ļ�
*       #include"HuffumanZip.h"
*   ��ֻ��Ҫ,�����ļ�·�����ɣ����£�
*       char path[256]={"C:\\aaa.txt"};
*       ZipFile(path);
*       UnzipFile(path);
*
*   zip �ļ���ʽ���
*       ��ѹ������������
*           RealData ����
*           RealData ����
*       �ļ�����
*   ע�⣺
*       ��Ϊ��ʽ������
*       ��˶�һЩ�ļ�ѹ�����ܻᵼ���ļ����ݱ��
*       ������Ϊ��Ҫ���һЩ��ѹ��������
****************************************/
#ifndef _HUFFMANZIP_H_
#define _HUFFMANZIP_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef unsigned char WORD8;                                        //����8Ϊ����
typedef  int I2FZIP_ERROR;                                          //����ѹ����������
#define I2FZIP_SUCCESS 0
#define I2FZIP_INVAILD_FILE 1                                       //��Ч�ļ�
#define I2FZIP_NOT_ZIPED 2                                          //δѹ���ļ�
typedef struct node
{
    WORD8 ch;                                                       //�ַ�
    double weight;                                                  //Ȩ�أ�Ƶ����Ҳ������Ƶ��
    struct node * Lchild,* Rchild,* Parent;                         //���ڵ㣬���Һ��Ӻ�˫�׽ڵ�
} TreeNode;                                                         //���ڵ�

typedef struct
{
    int len;                                                        //��Ч���ݸ���
    WORD8 Chars[256+1];                                             //�����ַ�
    double Weights[256+1];                                          //����Ȩ��
} Data;                                                             //���ݴ洢��Ԫ

typedef struct
{
    WORD8 Char;                                                     //�ַ�
    char HuffCode[64];                                              //��Ӧ��Huffman���루����
    double Weight;                                                  //Ȩ��
    int HuffLen;                                                    //���볤��
}   HuffCode;                                                       //�����ַ���Huffman������Ϣ��Ԫ

//ȫ�ֱ�������
Data * RealData=NULL;                                               //������Ϣ����
TreeNode * HuffRoot=NULL;                                           //Huffman��
HuffCode hufcode[256+1];                                            //Huffman����
int HuffCodeLen=0;                                                  //Huffman���볤��
void RemoveHuffTree(TreeNode * node);                               //ɾ��Huff��
I2FZIP_ERROR GetDataFile(char * filepath);                          //������ݣ������ļ������
TreeNode * CreateNode();                                            //�������ڵ�
TreeNode * BuildHuffTree();                                         //����Huffman��
void GetHuffCode(TreeNode * HFMTree,int * i);                       //����Huffman����ȡHuffman����


char flag[7]= {"I2FZIP"};                                           //�ļ�ѹ�����
void InitEnvironment();                                             //��ʼ�����л���
void ClearEnvironment();                                            //�������в���
WORD8 Array8ToWORD8(char arr[8]);                                   //8λ����10����ת������WORD8����
I2FZIP_ERROR ZipFile(char * filepath,char * newfile);                 //�ļ�ѹ���������ļ�·���ʹ���󱣴���ļ��������ش�����Ϣ
void WORD8ToArray8(WORD8 tempc,char arr[8]);                        //WORD8����ת8λ����01����
I2FZIP_ERROR UnzipFile(char * filepath,char * newfile);               //�ļ���ѹ������·���ʹ���󱣴���ļ��������ش�������

typedef int PATH_INFO;                                              //�����ļ�·����Ϣ��ȡ����
#define PATH_FATHER 0                                               //��ȡ�ļ���Ŀ¼
#define PATH_NAME 1                                                 //��ȡ�ļ����ƣ���������׺�͸�·����
#define PATH_TAIL 2                                                 //��ȡ�ļ���׺������.

void GetPathInfo(char * path,char * save,PATH_INFO infotype);       //��ȡ�ļ���Ϣ�������ļ�·��������λ�ã���Ҫ����Ϣ����
#include"HuffmanZip.cpp"                                           //һЩ���������Ӵ˾���Ҳ�����Ӧ����
#endif _HUFFMANZIP_H_

