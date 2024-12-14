/****************************************
*   copyright:  Ice2Faith
*   email:      18286715053@163.com
*---------------------------------------
*   如何正确使用压缩解压功能？
*   包含本头文件
*       #include"HuffumanZip.h"
*   你只需要,传入文件路径即可，如下：
*       char path[256]={"C:\\aaa.txt"};
*       ZipFile(path);
*       UnzipFile(path);
*
*   zip 文件格式设计
*       解压必须引导数据
*           RealData 长度
*           RealData 本体
*       文件内容
*   注意：
*       因为格式设计如此
*       因此对一些文件压缩可能会导致文件类容变大
*       这是因为需要存放一些解压必须数据
****************************************/
#ifndef _HUFFMANZIP_H_
#define _HUFFMANZIP_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef unsigned char WORD8;                                        //定义8为长度
typedef  int I2FZIP_ERROR;                                          //定义压缩错误类型
#define I2FZIP_SUCCESS 0
#define I2FZIP_INVAILD_FILE 1                                       //无效文件
#define I2FZIP_NOT_ZIPED 2                                          //未压缩文件
typedef struct node
{
    WORD8 ch;                                                       //字符
    double weight;                                                  //权重，频数，也可以是频率
    struct node * Lchild,* Rchild,* Parent;                         //树节点，左右孩子和双亲节点
} TreeNode;                                                         //树节点

typedef struct
{
    int len;                                                        //有效数据个数
    WORD8 Chars[256+1];                                             //数据字符
    double Weights[256+1];                                          //数据权重
} Data;                                                             //数据存储单元

typedef struct
{
    WORD8 Char;                                                     //字符
    char HuffCode[64];                                              //对应的Huffman编码（倒序）
    double Weight;                                                  //权重
    int HuffLen;                                                    //编码长度
}   HuffCode;                                                       //单个字符的Huffman编码信息单元

//全局变量定义
Data * RealData=NULL;                                               //数据信息保存
TreeNode * HuffRoot=NULL;                                           //Huffman树
HuffCode hufcode[256+1];                                            //Huffman代码
int HuffCodeLen=0;                                                  //Huffman代码长度
void RemoveHuffTree(TreeNode * node);                               //删除Huff树
I2FZIP_ERROR GetDataFile(char * filepath);                          //获得数据，返回文件打开情况
TreeNode * CreateNode();                                            //创建树节点
TreeNode * BuildHuffTree();                                         //创建Huffman树
void GetHuffCode(TreeNode * HFMTree,int * i);                       //根据Huffman树获取Huffman代码


char flag[7]= {"I2FZIP"};                                           //文件压缩标记
void InitEnvironment();                                             //初始化运行环境
void ClearEnvironment();                                            //清理运行残留
WORD8 Array8ToWORD8(char arr[8]);                                   //8位数组10序列转二进制WORD8类型
I2FZIP_ERROR ZipFile(char * filepath,char * newfile);                 //文件压缩，传入文件路径和处理后保存的文件名，返回错误信息
void WORD8ToArray8(WORD8 tempc,char arr[8]);                        //WORD8类型转8位数组01序列
I2FZIP_ERROR UnzipFile(char * filepath,char * newfile);               //文件解压，传入路径和处理后保存的文件名，返回错误类型

typedef int PATH_INFO;                                              //定义文件路径信息获取类型
#define PATH_FATHER 0                                               //获取文件父目录
#define PATH_NAME 1                                                 //获取文件名称（不包含后缀和父路径）
#define PATH_TAIL 2                                                 //获取文件后缀，包含.

void GetPathInfo(char * path,char * save,PATH_INFO infotype);       //获取文件信息，传入文件路径，保存位置，需要的信息类型
#include"HuffmanZip.cpp"                                           //一些编译器不加此句会找不到相应函数
#endif _HUFFMANZIP_H_

