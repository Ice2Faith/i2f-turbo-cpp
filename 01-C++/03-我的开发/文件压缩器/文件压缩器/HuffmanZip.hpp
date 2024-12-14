#ifndef _HUFFMAN_ZIP_H_
#define _HUFFMAN_ZIP_H_
/*  */
#include<stdio.h>
#include"AlgoTypes32.hpp"
#include<stdlib.h>

/*
�ձ�ʹ�õ�ѹ���㷨��
���ǣ���������ļ�
���⣬����ֻ�м����ַ��ģ����ǲ�����ѹ���ˣ�ѹ���˷���������ʹ�ÿռ�
*/
class HuffmanZip //: public Object
{
public:
	typedef struct __tree_node
	{
		BYTE_T ch;
		UINT32_T weight;
		struct __tree_node * lchild, *rchild, *parent;
	}TREE_NODE, *PTREE_NODE;
	typedef struct __code_map
	{
		BYTE_T ch;
		INT32_T codeLen;
		BYTE_T code[256];
		//��������£�256���ַ������ܻᵼ������ַ���huff�볤�ȴﵽ255
		//��Ȼ���ֿ����Ի��������ܴﵽ
	}CODE_MAP,*PCODE_MAP;
public:
	HuffmanZip()
	{
		Init();
	}
	virtual ~HuffmanZip()
	{

	}
	BOOL_T ZipFile(char * srcName, char * drtName)
	{
		FILE * sfp = NULL, *dfp = NULL;
		sfp = fopen(srcName, "rb");
		if (sfp == NULL)
		{
			return BOOL_FALSE;
		}


		UINT32_T weights[256] = { 0 };

		BOOL_T rst = getFileByteWeights(sfp, weights);
		if (rst == BOOL_FALSE)
		{
			fclose(sfp);
			return BOOL_TRUE;
		}

		dfp = fopen(drtName, "wb");
		if (dfp == NULL)
		{
			fclose(sfp);
			return BOOL_FALSE;
		}

		INT32_T leafCount = 0;
		TREE_NODE * root = makeHuffmanTree(weights, &leafCount);
		if (root == NULL)//���ļ���ֱ�Ӹ�����һ�����ļ�����
		{
			fclose(sfp);
			fclose(dfp);
			return BOOL_TRUE;
		}

		CODE_MAP * codeMap = getCodeMap(root, leafCount);

		rewind(sfp);
		writeHeader(dfp, weights, leafCount);

		BYTE_T buf[256] = { 0 };
		INT32_T m_head = 0;
		INT32_T m_tial = 0;

		BYTE_T ncharr[8] = { 0 };
		BYTE_T temp = 0;
		while (!feof(sfp))
		{
			fread(&temp, sizeof(BYTE_T), 1, sfp);
			if (feof(sfp))
				break;
			for (INT32_T i = 0; i < leafCount; i++)
			{
				if (codeMap[i].ch == temp)
				{
					for (INT32_T j = 0; j < codeMap[i].codeLen; j++)
					{
						m_tial = (m_tial + 1) % 256;
						buf[m_tial] = codeMap[i].code[j];
					}
					break;
				}
			}
			while ((m_tial + 256 - m_head) % 256 >= 8)
			{
				for (INT32_T pi = 0; pi < 8; pi++)
				{
					m_head = (m_head + 1) % 256;
					ncharr[pi] = buf[m_head];
				}
				BYTE_T wch = ByteArray8ToByte(ncharr);
				fwrite(&wch, sizeof(BYTE_T), 1, dfp);
			}
		}

		INT32_T llen = (m_tial + 256 - m_head) % 256;
		if (llen > 0)
		{
			for (INT32_T pi = 0; pi < 8; pi++)
			{
				if (pi < llen)
				{
					m_head = (m_head + 1) % 256;
					ncharr[pi] = buf[m_head];
				}
				else
				{
					ncharr[pi] = '0';
				}

			}
			BYTE_T wch = ByteArray8ToByte(ncharr);
			fwrite(&wch, sizeof(BYTE_T), 1, dfp);
		}
		
		//�ļ������һ���ֽ�������¼�ļ�ѹ�����ݵ����һ���ֽڵĿ��ó���
		//��Ϊ�������ڱ��볤�ȵ�ԭ�����һ�����볤�ȿ��ܲ���8λ
		//��ˣ���������һ���������ֽ��ڵĳ��ȼ�¼���ļ�ĩβ�������ڽ�ѹʱ��ͨ�����һ���ֽڻ�ȡӦ��ȡ�೤����
		//������һ���ֽڣ����ñ�����8λ��Ҳ����û�ж���ģ���ô�������һ����8λ����Ч
		//��˴˱������Ǽ�¼�ֽ��ڱ���Ŀ��ó���
		//�ṹ��.... codech lencode eof
		//codech:�������ֽ� lencode:�������ֽڿ��ñ���λ�� eof�ļ���β��־
		//Ҳ����ֵ�ڣ�1-8֮��
		BYTE_T leftLen = llen>0?llen:8;
		fwrite(&leftLen, sizeof(BYTE_T), 1, dfp);

		freeTree(root);
		free(codeMap);
		fclose(sfp);
		fclose(dfp);
		return BOOL_TRUE;
	}
	BOOL_T UnzipFile(char * srcName, char * drtName)
	{
		FILE * sfp = NULL, *dfp = NULL;
		sfp = fopen(srcName, "rb");
		if (sfp == NULL)
		{
			return BOOL_FALSE;
		}

		UINT32_T weights[256] = { 0 };
		BOOL_T rst = readHeader(sfp, weights);
		if (rst == BOOL_FALSE)
		{
			fclose(sfp);
			return BOOL_FALSE;
		}

		dfp = fopen(drtName, "wb");
		if (dfp == NULL)
		{
			fclose(sfp);
			return BOOL_FALSE;
		}


		INT32_T leafCount = 0;
		TREE_NODE * root = makeHuffmanTree(weights, &leafCount);
		if (root == NULL)//���ļ���ֱ�Ӹ�����һ�����ļ�����
		{
			fclose(sfp);
			fclose(dfp);
			return BOOL_TRUE;
		}


		BYTE_T buf[256] = { 0 };
		INT32_T m_head = 0;
		INT32_T m_tial = 0;

		BYTE_T lastch = 0;

		BYTE_T ncharr[8] = { 0 };
		BYTE_T temp = 0;
		TREE_NODE * pnode = root;
		while (!feof(sfp))
		{
			fread(&temp, sizeof(BYTE_T), 1, sfp);
			if (feof(sfp))
				break;
			lastch = temp;

			ByteToByteArray8(temp, ncharr);
			for (INT32_T i = 0; i<8; i++)
			{
				m_tial = (m_tial + 1) % 256;
				buf[m_tial] = ncharr[i];
			}
			//һֱ������������ֽڲ����б���
			//�����Ļ������ļ���ȡ���������д�ŵľ�����������ֽڵı���
			//��ô��16λ�У�ǰ8λ�У�������һ��������Ҫ����ģ�һ���������ģ�����Ҫ�����
			//��ô��Ҫ�����λ�����ɺ�8λ��ȡ��������lastch�е���ֵ
			while ((m_tial + 256 - m_head) % 256 >16)
			{
				m_head = (m_head + 1) % 256;
				BYTE_T cb = buf[m_head];
				if (cb == '0')
				{
					pnode = pnode->lchild;
				}
				else
				{
					pnode = pnode->rchild;
				}

				if (pnode->lchild == NULL && pnode->rchild == NULL)
				{
					BYTE_T wch = pnode->ch;
					fwrite(&wch, sizeof(BYTE_T), 1, dfp);
					pnode = root;
				}

			}
		}
		//ѹ����ʱ���Ѿ�˵�ˣ����һ���ֽ�����ָʾ��������ֽڲ������ĳ��ȣ�������Ⱦ���lastch
		//���������Ǹ�����Ҫ����ĳ��ȣ��ӱ�������ȡ����Ӧ��λ���б��뼴��
		for (BYTE_T i = 0; i < lastch; i++)
		{
			m_head = (m_head + 1) % 256;
			BYTE_T cb = buf[m_head];
			if (cb == '0')
			{
				pnode = pnode->lchild;
			}
			else
			{
				pnode = pnode->rchild;
			}

			if (pnode->lchild == NULL && pnode->rchild == NULL)
			{
				BYTE_T wch = pnode->ch;
				fwrite(&wch, sizeof(BYTE_T), 1, dfp);
				pnode = root;
			}
		}
		freeTree(root);
		fclose(sfp);
		fclose(dfp);
		return BOOL_TRUE;
	}
protected:

private:

	void Init()
	{

	}
	BOOL_T getFileByteWeights(FILE * fp, UINT32_T weights[])
	{
		rewind(fp);
		BOOL_T ret = BOOL_FALSE;

		BYTE_T temp = 0;
		while (!feof(fp))            /*8λ�޷����ַ�λ��0-255֮��*/
		{
			fread(&temp, sizeof(BYTE_T), 1, fp);    /*��ȡ��Ӧ�ַ���������Ƶ��*/
			if (feof(fp))
				break;
			weights[temp]++;
			ret = BOOL_TRUE;
		}
		rewind(fp);

		return ret;
	}
	UINT32_T getTreeNodes(UINT32_T weights[], TREE_NODE * trees[])
	{
		UINT32_T i = 0, trees_size=0;
		while (i < 256)
		{
			if (weights[i] != 0)
			{
				trees[trees_size] = createTreeNode((BYTE_T)i, weights[i]);
				trees_size++;
			}
			i++;
		}
		return trees_size;
	}
	TREE_NODE * makeHuffmanTree(UINT32_T * weights, INT32_T * leafCount)
	{
		TREE_NODE * ret = NULL;
		

		TREE_NODE * trees[256] = { 0 };
		UINT32_T trees_size = getTreeNodes(weights,trees);
		*leafCount = trees_size;
		//���ֻ��һ���ַ�����������Ϊ�ⲻ�ܱ���Ŀ��ܷ���
		if (trees_size == 1)
		{
			TREE_NODE * tpnode = createTreeNode(0, trees[0]->weight);
			tpnode->lchild = trees[0];
			tpnode->rchild =NULL;
			trees[0]->parent = tpnode;
			trees[0] = tpnode;
			return trees[0];
		}
		
		INT32_T fstMinIndex = -1, secMinIndex = -1;
		while (1)
		{
			fstMinIndex = 0;
			secMinIndex = 0;

			for (INT32_T i = 0; i < trees_size; i++)
			{
				if (trees[i]->weight < trees[fstMinIndex]->weight)
				{
					fstMinIndex = i;
				}
			}
			
			if (fstMinIndex == 0)
				secMinIndex = 1;

			for (INT32_T i = 0; i < trees_size; i++)
			{
				//��������������Ѿ��ҵ�����СԪ�أ���ôҲ����˵�����ų���С��Ԫ���У�������С��Ҳ�͵ȼ���������Ԫ���в��Ҵ�С
				if (i == fstMinIndex)
				{
					continue;
				}
				if (trees[i]->weight < trees[secMinIndex]->weight)
				{
					secMinIndex = i;
				}
			}

			//�ϲ�������С�����γ�һ������fstMin=tpnode=fstMin+secMin
			TREE_NODE * tpnode = createTreeNode(0, trees[fstMinIndex]->weight + trees[secMinIndex]->weight);
			tpnode->lchild = trees[fstMinIndex];
			tpnode->rchild = trees[secMinIndex];
			trees[fstMinIndex]->parent = tpnode;
			trees[secMinIndex]->parent = tpnode;
			trees[fstMinIndex] = tpnode;
			trees[secMinIndex] = NULL;

			//��������ÿ�ζ�Ҫ��������ɭ�ֲ��ܻ�ȡ��С���ʹ�С�������ÿ�ζ�����256�ˣ���Ȼ�е��˷���
			//��Ϊ�����Ǻϲ����ʱ����С�ʹ�С�ϲ�������С��λ�ã���С��λ���ÿ���
			//��ˣ����ǰѴ�Сλ�ú����һ��Ԫ�ؽ��н������������һ��Ԫ�ؾ��ǿ�Ԫ�أ���ô���ǵ��ܳ��ȾͿ��Խ��м�С
			//��һ��������ǣ��������������ʱ�򣬲��ÿ��ǿ�ָ��������ˣ�����һ���жϣ�Ҳ�����������ٶ�Ŷ
			//��Ϊ�����Ǳ�֤��Ԫ�س���֮�ڵ�Ԫ�أ�������ЧԪ��
			TREE_NODE * pend = trees[trees_size - 1];
			trees[trees_size - 1] = trees[secMinIndex];
			trees[secMinIndex] = pend;
			trees_size--;

			//�������ʣ��һ�����ˣ��Ǿ������ս����
			//ֻʣһ������������0�±꣬��Ϊ����ǰ���н����������ֱ��ʹ���±�ΪfstMinIndex�ģ�
			//��ô���ܻ���������Ľ���������fstMinIndex�±��Ѿ����ÿգ����´���ķ���ֵ
			if (trees_size == 1)
			{
				ret = trees[0];
				break;
			}
		}
		
		return ret;
	}
	void getCodeMapNext(TREE_NODE * tree, CODE_MAP * map, INT32_T * curSize)
	{
		if (tree == NULL)
			return;
		INT32_T psize = *curSize;
		//Ҷ�ӽڵ�
		if (tree->lchild == NULL && tree->rchild == NULL)
		{
			//ȡ��huff���룬�����������
			map[psize].ch = tree->ch;
			map[psize].codeLen = 0;
			map[psize].code[0] = 0;
			TREE_NODE * tp = tree;
			while (tp)
			{
				if (tp->parent)
				{
					if (tp == tp->parent->lchild)
					{
						map[psize].code[map[psize].codeLen++] = '0';
					}
					else
					{
						map[psize].code[map[psize].codeLen++] = '1';
					}
				}
				tp = tp->parent;
			}
			map[psize].code[map[psize].codeLen] = 0;
			//��һ�����򣬻ָ�����
			for (INT32_T i = 0; i < map[psize].codeLen / 2; i++)
			{
				BYTE_T pch = map[psize].code[i];
				map[psize].code[i] = map[psize].code[map[psize].codeLen - 1 - i];
				map[psize].code[map[psize].codeLen - 1 - i] = pch;
			}
			psize++;
		}

		*curSize = psize;
		getCodeMapNext(tree->lchild,map,curSize);
		getCodeMapNext(tree->rchild, map, curSize);
	}
	CODE_MAP * getCodeMap(TREE_NODE * root, INT32_T leafCount)
	{
		CODE_MAP * ret = (CODE_MAP *)malloc(sizeof(CODE_MAP)*leafCount);
		INT32_T curSize = 0;
		getCodeMapNext(root, ret, &curSize);
		return ret;
	}
	
	BYTE_T ByteArray8ToByte(BYTE_T * arr)
	{
		BYTE_T temp = 0;
		for (INT32_T i = 0; i<8; i++)
		{
			if (arr[i] == '0')
				temp |= 0 << (7 - i);
			else if (arr[i] == '1')
				temp |= 1 << (7 - i);
		}
		return temp;
	}
	void ByteToByteArray8(BYTE_T ch, BYTE_T * arr)
	{
		BYTE_T temp = ch;
		for (INT32_T i = 0; i<8; i++)
		{
			if (temp&(1 << (7 - i)))
				arr[i] = '1';
			else
				arr[i] = '0';
		}
	}
	BOOL_T writeHeader(FILE * fp,UINT32_T * weights,UINT32_T leafCount)
	{
		BYTE_T flgs[] = { 'H', 'Z', 'P', 0 };

		fwrite(flgs, sizeof(BYTE_T), 3, fp);

		UINT32_T plen = leafCount;
		AlgoHost2BigEndian(&plen, sizeof(UINT32_T));
		fwrite(&plen, sizeof(UINT32_T), 1, fp);

		UINT32_T i = 0;
		while (i < 256)
		{
			if (weights[i] != 0)
			{
				BYTE_T bt = i;
				UINT32_T bw = weights[i];
				
				fwrite(&bt, sizeof(BYTE_T), 1, fp);
				AlgoHost2BigEndian(&bw, sizeof(UINT32_T));
				fwrite(&bw, sizeof(UINT32_T), 1, fp);
			}
			i++;
		}
		return BOOL_TRUE;
	}
	BOOL_T readHeader(FILE* fp, UINT32_T * weights)
	{
		BYTE_T flgs[] = { 'H', 'Z', 'P', 0 };
		BYTE_T rflg[8] = { 0 };
		fread(rflg, sizeof(BYTE_T), 3, fp);
		INT32_T i = 0;
		while (flgs[i] != 0)
		{
			if (flgs[i] != rflg[i])
			{
				return BOOL_FALSE;
			}
			i++;
		}

		UINT32_T plen = 0;
		fread(&plen, sizeof(UINT32_T), 1, fp);
		AlgoBigEndian2Host(&plen, sizeof(UINT32_T));

		BYTE_T bt = 0;
		UINT32_T bw = 0;
		for (UINT32_T pi = 0; pi < plen; pi++)
		{
			fread(&bt, sizeof(BYTE_T), 1, fp);
			fread(&bw, sizeof(UINT32_T), 1, fp);
			AlgoBigEndian2Host(&bw, sizeof(UINT32_T));
			weights[bt] = bw;
		}

		return BOOL_TRUE;
	}
	TREE_NODE * createTreeNode(BYTE_T ch,UINT32_T weight)
	{
		TREE_NODE * ret = (TREE_NODE*)malloc(sizeof(TREE_NODE));
		ret->ch = ch;
		ret->weight = weight;
		ret->lchild = NULL;
		ret->rchild = NULL;
		ret->parent = NULL;
		return ret;
	}
	void freeTree(TREE_NODE * root)
	{
		if (root == NULL)
			return;
		TREE_NODE * lchild = root->lchild;
		TREE_NODE * rchild = root->rchild;

		free(root);

		freeTree(lchild);
		freeTree(rchild);
	}
};


#endif // _HUFFMAN_ZIP_H_