/** Name: 微分插值 与 透明*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include"ProgramHelper.h"

/*
这里，就用微分差值和透明计算去绘制一张图片，
绘制GUI库使用基于GDI的封装库EasyX
实现效果：
主对角线使用微分差值，进行绘制一个渐变色
副对角线使用透明计算，进行绘制一个透明混合颜色
*/
#include<iostream>
using namespace std;
template<typename T>
class PrintExecer
{
public:
	virtual void onBegin()
	{
		std::cout << "out: ";
	}
	virtual void onEnd()
	{
		std::cout << std::endl;
	}
	virtual void operator()(T & a)
	{
		std::cout << a << " ";
	}
};
template<typename T>
void printfList(T * list,char * str,int count=0)
{
	if (str != NULL)
		cout << str << ":";
	if (count == 0)
		count=list->size();
	for (int i = 0; i < count; i++)
	{
		cout << list->get(i) << " ";
	}
	cout << endl;
}
template<typename T>
class ExecTreeNode
{
public:
	virtual void onBegin()
	{
		cout << "Tree:";
	}
	virtual void onEnd()
	{
		cout << endl;
	}
	virtual void operator()(T & t)
	{
		cout << t << " ";
	}
};
void testArray()
{
	AlgoArray<int, int> arry(1);
	arry.push(5);
	cout << arry.size() << ":" << arry.capital() << endl;
	for (int i = 0; i < 99999; i++)
	{
		arry[i] = i;
	}
	cout << arry.size() << ":" << arry.capital() << endl;
	arry.shrinkCapital();
	cout << arry.size() << ":" << arry.capital() << endl;
	
	arry[128] = 5;
	cout << arry.size() << ":" << arry.capital() << endl;
	arry[1027] = 10;
	cout << arry.size() << ":" << arry.capital() << endl;

	arry.setSize(0);
	cout << arry.size() << ":" << arry.capital() << endl;
	arry.shrinkCapital();
	cout << arry.size() << ":" << arry.capital() << endl;
}

void TestString()
{
	AlgoString<char, int> spcstrn = "  \n\taadd\v\t  bbcc \t  \n  ggvv \t ";
	AlgoArray<AlgoString<char, int>, int> savarr;
	spcstrn.splitWhen("\n\r\t\v ", savarr, 1);
	for (int i = 0; i < savarr.size(); i++)
	{
		cout << savarr[i].getData() << endl;
	}
	cout << "*******************" << endl;

	AlgoString<char, int> cntstr = "abcd55";
	cntstr *= 20;
	int count = cntstr.countOf("bcd");
	cout << "count:" << count << endl;

	AlgoString<char, int> tmstr = " \n\tabbc\tppo\t\n \r \v";
	AlgoString<char, int> tmstr2 = tmstr;
	cout << "=" << tmstr << "=" << endl;
	tmstr.trimEnd();
	cout << "=" << tmstr << "=" << endl;
	tmstr.trimBegin();
	cout << "=" << tmstr << "=" << endl;
	tmstr2.trim();
	cout << "=" << tmstr2 << "=" << endl;

	tmstr = "\n\t \r\v \n  \t\n\r   ";
	tmstr.trim();
	cout << "=" << tmstr << "=" << endl;

	AlgoString<char, int> cp1 = "aaA";
	AlgoString<char, int> cp2 = "Aaa";
	cout << "ingcaseCmp:"<<cp1.compareIgnoreCase(cp2) << endl;

	AlgoString<char, int> str("123456");

	AlgoString<char, int> strs = str.subString(2, 2);
	cout << strs << endl;
	str[5] = 'a';
	cout << "str[5]=" << str[5] << endl;
	str *= 4;
	cout << str.getData() << endl;
	str.replace("123", "AABBDDCC",-1);
	char * joins[] = {"张三","李四","王五","张柳","刘奇"};
	str.joinString("@ ", (const char **)joins, 5);

	str = str.subString(str.indexOf("@ "), 6);
	cout << str << endl;
	cout << str.getCapital() << endl;
	str.shrinkCapital();
	cout << "shrinked:" << str.getCapital() << endl;

	AlgoArray<AlgoString<char, int>, int> joinArr;
	joinArr.push(AlgoString<char, int>("老虎"));
	joinArr.push(AlgoString<char, int>("狮子"));
	joinArr.push(AlgoString<char, int>("豹子"));
	joinArr.push(AlgoString<char, int>("僵尸"));
	joinArr.push(AlgoString<char, int>(""));
	joinArr.push(AlgoString<char, int>("木马"));
	str.join("# ", joinArr, true);
	cout << str.getData() << endl;
	str.remove("# ", 1);
	cout << str.getData() << endl;

	joinArr = str.split("# ", joinArr, -1,false);
	for (int i = 0; i < joinArr.size(); i++)
	{
		cout << "split:" << joinArr[i] << endl;
	}
	cout << "------------------------------"<<endl;

	AlgoString<char, int> str1 = "hello string";
	str1 = str1 + "滚你妈逼";
	str1 += str;
	cout << "str1:" << str1.getData() << endl; 
	cout << "str1:cap:" << str1.getCapital() << endl;

	cout << "String Equ:"<<(str == str1) << endl;

	char * pstr = (char *)str1;
	cout << pstr << endl;

	cout << "gather" << (str > str1) << endl;
	cout << "nequ" << (str != str1) << endl;
}

void TestWindows()
{
	TCHAR root[] = { TEXT("D:\\") };
	AlgoArray<AlgoString<TCHAR, int>, int> saveArr;
	saveArr=AlgoWinFile::getFileList(root, saveArr);
	AlgoWinDirectory::getAllLogicalDriverPath(saveArr);
	for (int i = 0; i < saveArr.size(); i++)
	{
		cout << AlgoWinString::Unicode2Ascii(saveArr[i]) << endl;

		AlgoArray<AlgoString<TCHAR, int>, int> files;
		AlgoWinFile::getFileList(saveArr[i], files);
		for (int j = 0; j < files.size(); j++)
		{
			cout << "\t" << AlgoWinString::Unicode2Ascii(files[j]) << endl;
		}
	}
	cout << "*********************************" << endl;
	TCHAR reg_run[] = {TEXT("AppX8mn6f6acw2d3hves535dpq0zqnxqkec7\\Application")};
	HKEY hKey = NULL;
	bool ret = AlgoWinRegister::openKey(HKEY_CLASSES_ROOT, reg_run, &hKey);
	AlgoArray<AlgoString<TCHAR, int>, int> saveReg;
	AlgoWinRegister::getKeyList(hKey, saveReg);
	for (int i = 0; i < saveReg.size(); i++)
	{
		cout << AlgoWinString::Unicode2Ascii(saveReg[i]) << endl;
	}
	cout << "__________________" << endl;
	AlgoWinRegister::getValueNameList(hKey, saveReg);
	for (int i = 0; i < saveReg.size(); i++)
	{
		cout << AlgoWinString::Unicode2Ascii(saveReg[i]) << endl;
	}

	AlgoWinProcess::adjustProcessPermission(GetCurrentProcess());
	cout << "__________________" << endl;
	AlgoArray<AlgoRegValueData, int> saveVal;
	AlgoWinRegister::getValueList(hKey, saveVal);
	AlgoString<char, int> buf;
	for (int i = 0; i < saveVal.size(); i++)
	{
		cout << AlgoWinString::Unicode2Ascii(saveVal[i].valName);
		DWORD type = saveVal[i].valType;
		if (type == REG_SZ || type == REG_EXPAND_SZ)
		{
			buf.prepareMemery(AlgoWinString::getRequireSize4Unicode2Ascii((WCHAR *)saveVal[i].valData.getData()));
			AlgoWinString::Unicode2Ascii((WCHAR *)saveVal[i].valData.getData(),buf);
			cout << "\t"<<buf.getData() << endl;
		}
		cout  << endl;
	}
}
#include"AlgoPath.hpp"
void mkdirproc(AlgoString<char, int> path)
{
	cout << "md:" << path << endl;
}
void testPath()
{
	AlgoString<char, int> path = ".txt";
	AlgoString<char, int> parent = AlgoPath::getParent<char>(path, '\\');
	cout << parent << endl;
	AlgoString<char, int> suffix = AlgoPath::getSuffix<char>(path, '.', '\\');
	cout << suffix << endl;
	AlgoString<char, int> name = AlgoPath::getName<char>(path, '\\');
	cout << name << endl;
	AlgoString<char, int> mdpath = "c:\\aaa\\bbb\\ccc\\ddd\\ee.ff\\gg";
	AlgoPath::makeDirs(mdpath, '\\', mkdirproc);
}
void testProcess()
{
	AlgoWinProcess::adjustProcessPermission(GetCurrentProcess());
	AlgoArray<PROCESSENTRY32, int> savePcs;
	AlgoWinProcess::enumerateAllProcessData(savePcs);
	AlgoArray<MODULEENTRY32, int> saveMol;
	AlgoArray<THREADENTRY32, int> saveThd;
	for (int i = 0; i < savePcs.size(); i++)
	{
		cout << "ProcessId:" << savePcs[i].th32ProcessID << "\texecName:" << AlgoWinString::Unicode2Ascii(AlgoString<TCHAR, int>(savePcs[i].szExeFile)) << endl;
		
		AlgoWinProcess::enumerateAllModuleData(savePcs[i].th32ProcessID, saveMol);
		for (int j = 0; j < saveMol.size(); j++)
		{
			cout << "\tModuleId:" << saveMol[j].th32ModuleID << "\texecName:" << AlgoWinString::Unicode2Ascii(AlgoString<TCHAR, int>(saveMol[j].szExePath)) << endl;
		}

		AlgoWinProcess::enumerateAllThreadData(savePcs[i].th32ProcessID, saveThd);

		for (int j = 0; j < saveThd.size(); j++)
		{
			for (int j = 0; j < saveMol.size(); j++)
			{
				cout << "\t\tThreadId:" << saveThd[j].th32ThreadID <<  endl;
			}
		}
	}
}

void testWinWindow()
{
#if 0
	AlgoArray<ALGO_WINDOWD_INFO, int> hwndes;
	AlgoWinWindow::getChilden(hwndes, NULL);

	AlgoArray<ALGO_WINDOWD_INFO, int> childs;

	for (int i = 0; i < hwndes.size(); i++)
	{
		printf("%d:%08x \t size:%d/%d %d/%d %s \t %s\n",i,(unsigned int)hwndes[i].hWnd,
			hwndes[i].title.getLength(),
			hwndes[i].title.getCapital(),
			hwndes[i].className.getLength(),
			hwndes[i].className.getCapital(),
			AlgoWinString::Unicode2Ascii(hwndes[i].title).getData(),
			AlgoWinString::Unicode2Ascii(hwndes[i].className).getData()
			);

		AlgoWinWindow::getChilden(childs, hwndes[i].hWnd);

		for (int j = 0; j < childs.size(); j++)
		{
			printf("\t\t%d:%08x \t size:%d/%d %d/%d %s \t %s\n", j, (unsigned int)childs[j].hWnd,
				childs[j].title.getLength(),
				childs[j].title.getCapital(),
				childs[j].className.getLength(),
				childs[j].className.getCapital(),
				AlgoWinString::Unicode2Ascii(childs[j].title).getData(),
				AlgoWinString::Unicode2Ascii(childs[j].className).getData()
				);

		}
	}
#else 
	AlgoArray<ALGO_WINDOWD_INFO, int> hwndes;
	AlgoWinWindow::enumWindow(hwndes);

	AlgoArray<ALGO_WINDOWD_INFO, int> childs;

	for (int i = 0; i < hwndes.size(); i++)
	{
		printf("%d:%08x \t size:%d/%d %d/%d %s \t %s\n", i, (unsigned int)hwndes[i].hWnd,
			hwndes[i].title.getLength(),
			hwndes[i].title.getCapital(),
			hwndes[i].className.getLength(),
			hwndes[i].className.getCapital(),
			AlgoWinString::Unicode2Ascii(hwndes[i].title).getData(),
			AlgoWinString::Unicode2Ascii(hwndes[i].className).getData()
			);

		AlgoWinWindow::enumChildWindow(childs, hwndes[i].hWnd);

		for (int j = 0; j < childs.size(); j++)
		{
			printf("\t\t%d:%08x \t size:%d/%d %d/%d %s \t %s\n", j, (unsigned int)childs[j].hWnd,
				childs[j].title.getLength(),
				childs[j].title.getCapital(),
				childs[j].className.getLength(),
				childs[j].className.getCapital(),
				AlgoWinString::Unicode2Ascii(childs[j].title).getData(),
				AlgoWinString::Unicode2Ascii(childs[j].className).getData()
				);

		}
	}
#endif
}
void enumWindowChildsDisplay(HWND hwnd, int level)
{
	AlgoArray<ALGO_WINDOWD_INFO, int> childs;
	AlgoWinWindow::enumChildWindow(childs, hwnd);

	for (int j = 0; j < childs.size(); j++)
	{
		for (int k = 0; k < level; k++)
			printf("    ");
		printf("%d:%08x \t size:%d/%d %d/%d %s \t %s\n", j, (unsigned int)childs[j].hWnd,
			childs[j].title.getLength(),
			childs[j].title.getCapital(),
			childs[j].className.getLength(),
			childs[j].className.getCapital(),
			AlgoWinString::Unicode2Ascii(childs[j].title).getData(),
			AlgoWinString::Unicode2Ascii(childs[j].className).getData()
			);
		enumWindowChildsDisplay(childs[j].hWnd,level+1);

	}
}
void testEnumAllControls()
{
	AlgoArray<ALGO_WINDOWD_INFO, int> curths;
	AlgoWinWindow::enumThreadWindow(curths, GetCurrentThreadId());
	for (int i = 0; i < curths.size(); i++)
	{
		printf("%d:%08x \t size:%d/%d %d/%d %s \t %s\n", i, (unsigned int)curths[i].hWnd,
			curths[i].title.getLength(),
			curths[i].title.getCapital(),
			curths[i].className.getLength(),
			curths[i].className.getCapital(),
			AlgoWinString::Unicode2Ascii(curths[i].title).getData(),
			AlgoWinString::Unicode2Ascii(curths[i].className).getData()
			);
	}
	return;
	
	AlgoArray<ALGO_WINDOWD_INFO, int> allwokers;
	AlgoWinWindow::findAllWindow(allwokers, NULL, TEXT("WorkerW"), false);
	for (int i = 0; i < allwokers.size(); i++)
	{
		printf("%d:%08x \t size:%d/%d %d/%d %s \t %s\n", i, (unsigned int)allwokers[i].hWnd,
			allwokers[i].title.getLength(),
			allwokers[i].title.getCapital(),
			allwokers[i].className.getLength(),
			allwokers[i].className.getCapital(),
			AlgoWinString::Unicode2Ascii(allwokers[i].title).getData(),
			AlgoWinString::Unicode2Ascii(allwokers[i].className).getData()
			);
	}
	return;

	/*
	296:0001039a     size:0/64 7/64          WorkerW
    0:00010182   size:0/64 16/64         SHELLDLL_DefView
        0:00010184       size:10/64 13/64 FolderView     SysListView32
	*/
	HWND floder = AlgoWinWindow::superFindWindow(TEXT("FolderView"), TEXT("SysListView32"), (HWND)0x0001039a);
	printf("%08x\n",(unsigned int)floder);
	return;

	AlgoArray<ALGO_WINDOWD_INFO, int> hwndes;
	AlgoWinWindow::enumWindow(hwndes);

	for (int i = 0; i < hwndes.size(); i++)
	{
		printf("%d:%08x \t size:%d/%d %d/%d %s \t %s\n", i, (unsigned int)hwndes[i].hWnd,
			hwndes[i].title.getLength(),
			hwndes[i].title.getCapital(),
			hwndes[i].className.getLength(),
			hwndes[i].className.getCapital(),
			AlgoWinString::Unicode2Ascii(hwndes[i].title).getData(),
			AlgoWinString::Unicode2Ascii(hwndes[i].className).getData()
			);
		enumWindowChildsDisplay(hwndes[i].hWnd,1);
	}
}

#include<graphics.h>
void testGraphics()
{
	int wWid = 1080, wHei = 720;
	HWND hwnd = initgraph(wWid, wHei);
	AlgoWinBatchDraw draw(hwnd);
	HDC hdc = GetImageHDC();
	while (1)
	{
		
		hdc=draw.BeginBatchDraw();
		hdc = draw.getMDC();
		//BeginBatchDraw();
		HBRUSH brush = CreateSolidBrush((COLORREF)0xffffff);
		HGDIOBJ obj = SelectObject(hdc, brush);
		Rectangle(hdc, 0, 0, wWid, wHei);
		DeleteObject(SelectObject(hdc, obj));
		for (int i = 0; i < 300; i++)
		{
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			HGDIOBJ obj= SelectObject(hdc, brush);
			Rectangle(hdc, rand() % wWid, rand() % wHei, rand() % wWid, rand() % wHei);
			DeleteObject(SelectObject(hdc, obj));
			
		}
		//EndBatchDraw();
		//draw.EndBatchDraw();
		draw.FlushBatchDraw();
		//Sleep(5);
	}

}

void testInputText()
{
	AlgoWinControl::KeyMediaNext();
	printf("20S后停止播放");
	Sleep(20*1000);
	AlgoWinControl::KeyMediaPlayPause();
	
}
bool MyFilter(const int & elem)
{
	if (elem <= 3)
		return true;
	return false;
}
void MyRangePlus(int & elem, int index, bool isFirst, bool isEnd)
{
	if (isFirst)
		printf("List:\t");
	printf("%d:%d ",index,elem);
	elem *= 1.5;
	if (isEnd)
		printf("\n");
}
void testContainer()
{
	int arr[] = {1,2,1,3,4,5,1,2,5,3,4,2,5,4,1,2,3,5,4,2,1,5,3,2,4,4};
	AlgoList<int, int> lst;
	lst.addAll(arr, sizeof(arr) / sizeof(int));
	//printfList(&lst, "FE:");
	lst.rangePlus(MyRangePlus); 

	lst.clear();
	lst.addAllFilter(arr, sizeof(arr) / sizeof(int), MyFilter);
	printfList(&lst, "FE:");
	lst.removeAllRepeat(AlgoDefaultCmpFunc<int>);
	printfList(&lst, "FE:");
}
void testImpString()
{
	cout << AlgoString<char,int>("aaa") *3 << endl;
	cout << 3* AlgoString<char, int>("aaa") << endl;
	cout << AlgoString<char, int>(NULL) + "bbb" << endl;
	cout << AlgoString<char, int>(NULL).isNullOrEmpty() << endl;
}
void testHeapSort()
{
	int arr[] = {5,8,3,6,1,7,2,9,-1,4,0,10,11,21,22,23,16,17,26,27,28,18,19,20,29,30,24,25,12,13,14,15,31,32,33};
	//AlgoSortHeap<int,int,int>(arr, sizeof(arr) / sizeof(int), AlgoDefaultCmpFunc<int>, AlgoArraySelectGet<int, int, int>, AlgoArraySelectSwap<int, int, int>, false);
	AlgoForeach<int,int,int>(arr, sizeof(arr) / sizeof(int), PrintExecer<int>(), AlgoArraySelectGet<int, int, int>);

	cout << endl;

	AlgoSortMerge<int, int, int>(arr, sizeof(arr) / sizeof(int), AlgoDefaultCmpFunc<int>, AlgoArraySelectGet<int, int, int>, AlgoArraySelectSet<int, int, int>, false);
	AlgoForeach<int, int, int>(arr, sizeof(arr) / sizeof(int), PrintExecer<int>(), AlgoArraySelectGet<int, int, int>);

	cout << endl;

	bool isIn = AlgoIn("hello", 5, AlgoCharStringCmpFunc, "test", "val", "hello", "world", "你好");
	cout << "isIn:" << isIn << endl;

	cout << "sum:" << AlgoAdd(5, 1, 2, 3, 4, 5) << endl;

	cout << "lessAll:" << AlgoLessAll(0, AlgoDefaultCmpFunc<int>, 5, 1, 2, 3, 4, 4) << endl;


	int fval = 14;

	int index = AlgoSearchInsert(arr, sizeof(arr) / sizeof(int), fval, AlgoDefaultCmpFunc<int>, AlgoArraySelectGet<int, int, int>);
	cout << "f"<<fval<<":" << index << endl;

	index = AlgoSearchHalf(arr, sizeof(arr) / sizeof(int), fval, AlgoDefaultCmpFunc<int>, AlgoArraySelectGet<int, int, int>);
	cout << "f" << fval << ":" << index << endl;

	index = AlgoSearchFibonacci(arr, sizeof(arr) / sizeof(int), fval, AlgoDefaultCmpFunc<int>, AlgoArraySelectGet<int, int, int>);
	cout << "f" << fval << ":" << index << endl;
}
void pTestProveString()
{
	AlgoString<WCHAR, int> str=(WCHAR)'A' ;
	cout << AlgoWinString::Unicode2Ascii(str) << endl;
	str = (WCHAR)'B' + str;
	cout << AlgoWinString::Unicode2Ascii(str )<< endl;
	str += 'C';
	cout << AlgoWinString::Unicode2Ascii(str )<< endl;
	str *= 3;
	cout << AlgoWinString::Unicode2Ascii(str )<< endl;
	cout << AlgoWinString::Unicode2Ascii(str.subLeft(4) )<< endl;
	cout << AlgoWinString::Unicode2Ascii(str.subRight(4) )<< endl;
	cout << AlgoWinString::Unicode2Ascii( str.appendBool(1 == 1)+L"[]") << endl;
	cout << AlgoWinString::Unicode2Ascii(str.appendInteger(-125, 16) + L"[]") << endl;
	cout << AlgoWinString::Unicode2Ascii(str.appendFloat(-0.02) + L"[]") << endl;

	AlgoString<WCHAR, int> fmtstr;
	fmtstr.formatString(L"%你好%%，%d,我是%c星球的%s,浮起来%f,对吗%b，哈哈哈0x%X，开o%o玩笑的b%n，不跟你%p开%g的莞笑", 12, 'R',L"【Ugex%%】", -17.128, true,12,12,12,-15.55,3.141592653549);
	cout << AlgoWinString::Unicode2Ascii(fmtstr) << endl;

	AlgoString<char, int> bparse = "fAlSeaaa";
	bool bpval = false;
	bool retState =bparse.parseBool(bparse.getData(), &bpval);
	cout << retState << ":" << bpval << endl;

	int ipval = 0;
	retState = bparse.parseInteger<int>("+11.125", &ipval, 10);
	cout << retState << ":" << ipval << endl;

	double dpval = 0;
	retState = bparse.parseFloat<double>("-11.125", &dpval);
	cout << retState << ":" << dpval << endl;

	AlgoString<char, int> subut = "C :\\ aa a\\bb\n\t   E b\\c,cc\\d dd.aac";
	AlgoString<char, int> subdot = subut.subUtil(0, 'e',true);
	cout << subut.trimAll() << endl;
	cout << subdot.reverse() << endl;

	cout << subdot.insert(2,"AAAA") << endl;
	cout << subdot.subString(2,4) << endl;

}
bool MyElemAddFilter(const int & elem)
{
	if (elem % 2 == 0)
		return false;
	return true;
}
bool MyElemFilter(const int & elem)
{
	if (elem<=10)
		return true;
	return false;
}
void printfAlgoArrInt(AlgoArray<int, int> & arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}
void testListFilter()
{
	int arr[] = {1,1,1,1,5,6,7,8,1,1,1,1,13,14,15,16,17,18,19};
	AlgoList<int, int> lst;
	lst.addAllFilter(arr, sizeof(arr) / sizeof(int), MyElemAddFilter);

	lst.elementFilter(MyElemFilter);

	lst[0] = 33;

	lst.setCursorToEnd();
	if (lst.hasPrevious())
	{
		do
		{
			int val = lst.getCursorData();
			if (val % 2 == 0)
			{
				lst.deleteCursorToPrevious();
			}
			else
			{
				lst.previousCursor();
				cout << val << " ";
			}

			
		} while (lst.hasPrevious());
	}
	cout << endl;

	AlgoArray<int, int> agarr;
	agarr.addAll(arr, sizeof(arr) / sizeof(int));
	printfAlgoArrInt(agarr);

	agarr.removeFast(0);
	printfAlgoArrInt(agarr);

	agarr.removeFast(1);
	printfAlgoArrInt(agarr);

	agarr.remove(0);
	printfAlgoArrInt(agarr);

	agarr.insert(0, 33);
	printfAlgoArrInt(agarr);

	agarr.removeAll(1,AlgoDefaultCmpFunc<int>);
	printfAlgoArrInt(agarr);


}
void printfVectorInt(AlgoVector<int, int> & vec)
{
	int size = vec.size();
	printf("size:%d capital:%d\t[",size,vec.capital());
	for (int i = 0; i < size; i++)
	{
		printf("%d ",vec[i]);
	}
	printf("]\n");
}
void testVector()
{
	AlgoVector<int, int> vec(8);
	for (int i = 0; i < 100; i++)
	{
		if (vec.isFull())
			break;
		vec.push(i);
	}
	printfVectorInt(vec);

	for (int i = 0; i < 100; i++)
	{
		if (vec.isEmpty())
			break;
		vec.pop();
	}
	printfVectorInt(vec);


	for (int i = 0; i < 100; i++)
	{
		if (vec.isFull())
			break;
		vec.enque(i);
	}
	printfVectorInt(vec);

	for (int i = 0; i < 100; i++)
	{
		if (vec.isEmpty())
			break;
		vec.deque();
	}
	printfVectorInt(vec);

	for (int i = 0; i < 10; i++)
	{
		printf("-------------%d:%d-----------------\n",i,i*10);
		if (rand() % 100 < 50)
		{
			for (int j = i * 10; j < i * 10 + 5; j++)
			{
				if (vec.isFull() == false)
				{
					vec.push(j);
					printf("in:%d\n",vec.tial());
				}
			}
			printf("push:#");
			printfVectorInt(vec);
		}
		else
		{
			for (int j = 0; j <3; j++)
			{
				if (vec.isEmpty() == false)
				{
					printf("ot:%d\n", vec.tial());
					vec.pop();
					
				}
			}
			printf("pop:#");
			printfVectorInt(vec);
		}
	}
	printf("vec:add:0-2\n");
	
	for (int i = 0; i < 3; i++)
	{
		vec.push(i);
	}
	printfVectorInt(vec);
	printf("#----------------------------#\n");
	AlgoVector<int, int> vec2(vec);
	printfVectorInt(vec2);
	vec2 = vec;
	printfVectorInt(vec2);

	
	printfVectorInt(vec2);
	printf("******************************\n");
	bool ret=vec2.setCapital(5);
	printfVectorInt(vec2);
	ret = vec2.setCapital(0);
	printfVectorInt(vec2);
	ret = vec2.setCapital(12);
	printfVectorInt(vec2);

}
void testBaseList()
{
	AlgoBaseList<int> root1(99),root2(49);
	AlgoBaseList<int> elem0(0), elem1(1), elem2(2), elem3(3);

	root1.insertList(&root1, &elem0)->insertList(&root1, &elem1);

	root2.insertList(&root2, &elem2)->insertList(&root2, &elem3);

	AlgoBaseList<int> * root = root1.insertList(&root1, &root2);

	root=root->deleteNode(root);

	bool loop = root->isLoopNextList(root);

}
#include"AlgoAnyList.hpp"
void testAlgoAnyList()
{
	AlgoAnyList * list = ALGO_ANY_LIST_BASE_MAKE_NODE(12, int, ALGO_ANY_LIST_DATA_TYPE_INT);
	for (int i = 0; i < 10; i++)
	{
		AlgoAnyListNode * node = ALGO_ANY_LIST_BASE_MAKE_NODE(i,int, ALGO_ANY_LIST_DATA_TYPE_INT);
		list = AlgoAnyList_appendList(list, node);
	}
	for (int i = 0; i < 10; i++)
	{
		AlgoAnyListNode * node = ALGO_ANY_LIST_BASE_MAKE_NODE(i*0.5, double, ALGO_ANY_LIST_DATA_TYPE_DOUBLE);
		list = AlgoAnyList_appendList(list, node);
	}

	for (int i = 0; i < 10; i++)
	{
		AlgoAnyListNode * node = NULL;
		ALGO_ANY_LIST_MEMORY_MAKE_NODE("hello,哈哈哈", node,15,ALGO_ANY_LIST_DATA_TYPE_LPCHAR);
		list = AlgoAnyList_appendList(list, node);
	}
	
	AlgoAnyList * cur = list;
	while (cur)
	{
		if (cur->data_type == ALGO_ANY_LIST_DATA_TYPE_INT)
		{
			printf("%d ", ALGO_ANY_LIST_GET_DATA(cur->data, int));
			ALGO_ANY_LIST_FREE_DATA(cur->data, int);
		}
		else if (cur->data_type == ALGO_ANY_LIST_DATA_TYPE_DOUBLE)
		{
			printf("%lf ", ALGO_ANY_LIST_GET_DATA(cur->data, double));
			ALGO_ANY_LIST_FREE_DATA(cur->data, double);
		}
		else if (cur->data_type == ALGO_ANY_LIST_DATA_TYPE_LPCHAR)
		{
			printf("%s ", ALGO_ANY_LIST_GET_DATA_MEMORY(cur->data,char *));
			ALGO_ANY_LIST_FREE_DATA_MEMORY(cur->data, char*);
		}
		cur = cur->next;
	}
	cur = list;
}
#include"AlgoTypes32.hpp"
void testTypes32()
{
	
	UINT32_T a = 12;
	a -= 20;
	printf("%08x\n",a);
	AlgoHost2BigEndian(&a, sizeof(a));
	printf("%08x\n", a);
	AlgoBigEndian2Host(&a, sizeof(a));
	printf("%08x\n", a);
}
#include"AlgoConsole.hpp"
int main(int argc, char * argv[])
{
	//AlgoConsole::backColor(AlgoConsole::CCE_BLUE, AlgoConsole::CCE_RED);
	AlgoConsole::textColor(AlgoConsole::CCE_LGREEN, AlgoConsole::CCE_BLACK);
	//testProcess();
	//testPath();
	//TestWindows();
	//testWinWindow();
	//testEnumAllControls();
	//testGraphics();
	//testInputText();
	//testContainer();
	//testImpString();
	//testHeapSort();
	//pTestProveString();
	//testListFilter();
	testVector();
	//testBaseList();
	//testAlgoAnyList();
	testTypes32();
	system("pause");
	return 0;

	char cpc[] = {"test"};
	if (AlgoIn<char *>(cpc, 4, AlgoCharStringCmpFunc, "hello", "world", "this", "is", "test"))
		cout << "test in here" << endl;
	if (AlgoIn<char *>(cpc, 4, AlgoCharStringCmpFunc, "hello", "world", "this", "is", "nothing"))
		cout << "test not in here" << endl;
	cout << "compare in end" << endl;

	int color = RGB(128,85,177);
	int red = AlgoGetBitData(color, 31, 31, false);
	cout << red<<":"<<(red==(color&0xff))<<":"<<(color&0xff) << endl;
	int newcolor = AlgoSetBitData(color, 8, 15, 188, false);
	cout << "newColor:" << "red:" << ((newcolor>>8) & 0xff) << endl;
	color = AlgoSetBitData(color, 1, 5, 7, false);
	cout << color<< endl;
	color = AlgoGetBitData(color, 1, 5, false);
	cout << color << endl;


	cout << "isIn:" << AlgoIn<char *>("112", 4, AlgoCharStringCmpFunc, "1", "7", "12","67", "112") << endl;

	AlgoMap<int, double, ALGO_FUNC_CMP(int)> map(AlgoDefaultCmpFunc<int>);
	map.put(1,10);
	map.put(2,20);
	map.put(2,30);
	map.remove(2);

	unsigned char * pmap = AlgoVaryPointer<AlgoMap<int, double, ALGO_FUNC_CMP(int)>, unsigned char>(&map);
	int ps = sizeof(map);
	for (int i = 0; i < ps; i++)
	{
		printf("%2x ",pmap[i]);
	}
	cout << "\nvary pointer" << endl;
	
	for (int i = 0; i < map.size(); i++)
	{
		cout << "key:" << map.getIndexKey(i) << "\t"
		 << "value:" << map.get(map.getIndexKey(i)) << endl;
	}
	ExecTreeNode<int> exec;
	AlgoSortTree<int,ALGO_FUNC_CMP(int)> tree(AlgoDefaultCmpFunc<int>);
	tree.add(5);
	tree.add(10);
	tree.add(4);
	tree.add(7);
	tree.add(3);
	tree.range(exec,AlgoOnFunc,AlgoOnFunc);
	tree.remove(7);
	tree.range(exec, AlgoOnFunc, AlgoOnFunc);
	tree.remove(0);
	tree.range(exec, AlgoOnFunc, AlgoOnFunc);
	cout << tree.contians(4) << " " << tree.contians(100) << endl;


	tree.clear();
	tree.range(exec, AlgoOnFunc, AlgoOnFunc);




	int arr[] = {5,8,14,2,6,7,1,4,3,9,12,10,11,15,13,0,16,17,18,19,20,21,22,23,24,25,26,27,28,32,29,31,30,25,63,2,6,2,65,5223,25,6,56,6,56,56,5,6,566,5,6,5,6,5656,5,65,65,5,5665,5,5,55,5,5,5,55,65,68,85,5,8,8,878,5,5,5656,85,58,5,8,75,8,8,8,5,98,8,5,85,6};
	AlgoSortQuick<int, int, unsigned int>(arr, sizeof(arr) / sizeof(int), AlgoDefaultCmpFunc<int>,AlgoArraySelectGet<int,int,int>,AlgoArraySelectSet<int,int,int>, true);
	AlgoForeach<int,int,unsigned int>(arr, sizeof(arr)/sizeof(int),PrintExecer<int>(),AlgoArraySelectGet<int,int,int>);
	int index = AlgoSearchHalf(arr, (int)(sizeof(arr) / sizeof(int)), 19, AlgoDefaultCmpFunc<int>, AlgoArraySelectGet<int, int, int>);
	cout << "index:" << index << endl;

	cout << "************" << endl;
	int cont = AlgoCount<int, int, int>(arr, 6, 0, (int)(sizeof(arr) / sizeof(int)) - 1, AlgoDefaultCmpFunc<int>,AlgoArraySelectGet<int, int, int>);
	int sum = AlgoSum<int, int, int>(arr, 0, (int)(sizeof(arr) / sizeof(int)) - 1, AlgoArraySelectGet<int, int, int>);
	double avg = AlgoAvg<int, int, int, double>(arr, 0, (int)(sizeof(arr) / sizeof(int)) - 1, AlgoArraySelectGet<int, int, int>, 1.0);
	int max = AlgoMax<int, int, int>(arr, 0, (int)(sizeof(arr) / sizeof(int)) - 1, AlgoDefaultCmpFunc<int>, AlgoArraySelectGet<int, int, int>, NULL);
	int min = AlgoMin<int, int, int>(arr, 0, (int)(sizeof(arr) / sizeof(int)) - 1, AlgoDefaultCmpFunc<int>, AlgoArraySelectGet<int, int, int>, NULL);
	cout << "count:" << cont << "\tsum:" << sum << "\tavg:" << avg << "\tmax:" << max << "\tmin:" << min << endl;

	AlgoArray<int, int> arry;
	cout << arry.size() << ":" << arry.capital() << endl;
	for (int i = 0; i < 5; i++)
	{
		arry[i] = i;
	}
	arry.memorySet(20);
	cout << arry.size() << ":" << arry.capital() << endl;
	arry.shrinkCapital();
	cout << arry.size() << ":" << arry.capital() << endl;

	AlgoList<int,int> list;
	list.add(1);
	list.add(2);
	list.add(3);
	list.add(4);
	list.add(5);
	list.add(6);
	list.insert(0,4);
	list.insert(0, 7);
	int size = list.size();
	list.replace(1, 9);
	list.remove(0,NULL);

	while (list.size())
	{
		list.remove(0, NULL);
	}
	list.push(1);
	list.push(2);
	cout << list.top() << endl;
	cout << list.pop() << endl;
	printfList(&list, "remove all\n");

	list.addAll<int>(arr, 0, (int)(sizeof(arr) / sizeof(int))-1,AlgoArraySelectGet<int,int,int>);
	list.remove(list.size()-1, NULL);
	list.remove(0, NULL);
	list.remove(list.size() - 1, NULL);
	list.remove(0, NULL);
	list.remove(list.size() - 1, NULL);
	printfList(&list, "remove end\n");

	list.clear();
	for (int i = 0; i < 2000; i++)
	{
		list.add(i);
	}

	cout << "\n\n" << "listSize:" << list.size() << endl;
	long beftime = time(NULL);
	AlgoShuffle<AlgoList<int, int>, int, int>(&list, 0, list.size() - 1, AlgoListSelectSwap<AlgoList<int, int>, int, int>);
	cout << "shuffle time:" << (time(NULL) - beftime) << endl;
	printfList(&list, "shuffled\n", 20);

	beftime = time(NULL);
	AlgoSortQuick<AlgoList<int, int>, int, int>(&list, list.size(), AlgoDefaultCmpFunc<int>,AlgoListSelectGet<AlgoList<int,int>,int,int>,AlgoListSelectSet<AlgoList<int,int>,int,int>,true);
	cout << "sort time:" << (time(NULL) - beftime) << endl;
	printfList(&list, "sorted\n", 20);

	beftime = time(NULL);
	AlgoReverse<AlgoList<int, int>, int, int>(&list, 0, list.size() - 1, AlgoListSelectSwap<AlgoList<int, int>, int, int>);
	cout << "reverse time:" << (time(NULL) - beftime) << endl;
	printfList(&list, "reversed\n", 20);

	system("pause");

	int count;
	int * arrto = list.toArray(&count);
	for (int i = 0; i < count; i++)
	{
		cout << arrto[i] << " ";
	}
	list.freeArray(arrto);
	cout << "arr pd" << endl;

	bool isin = AlgoIsIn<AlgoList<int, int>, int, int> (22, &list, list.size(),AlgoDefaultCmpFunc<int>,AlgoListSelectGet<AlgoList<int,int>,int,int>);
	cout << "algo is in:" << isin << endl;
	
	cout << "direct out" << endl;
	for (int i = 0; i < list.size(); i++)
	{
		if (i == 19)
			int a=list.get(i);
		cout << list.get(i) << " ";
	}
	cout << endl;

	cout << "contians 22:" << list.contains(22, AlgoDefaultCmpFunc<int>)<<endl;
	list.remove(22, NULL, AlgoDefaultCmpFunc<int>);
	cout << "contians 22:" << list.contains(22, AlgoDefaultCmpFunc<int>) << endl;
	printfList(&list, "remove 22 data\n");


	AlgoSortQuick<AlgoList<int, int>, int, int>(&list, list.size(),AlgoDefaultCmpFunc<int>,AlgoListSelectGet<AlgoList<int,int>,int,int>,AlgoListSelectSet<AlgoList<int,int>,int,int>, true);
	AlgoReverse<AlgoList<int, int>, int, int>(&list, 0, list.size() - 1, AlgoListSelectSwap<AlgoList<int, int>, int, int>);
	printfList(&list, "sort reverse\n");

	srand(time(NULL));
	AlgoShuffle<AlgoList<int, int>, int, int>(&list, 0, list.size() - 1, AlgoListSelectSwap<AlgoList<int, int>, int, int>);
	printfList(&list, "shuffle\n");
	

	cout << "cur direct out " << endl;
	list.setCursorPos(0);
	while (list.hasNext())
	{
		cout << list.getCursorData() << " ";
		list.nextCursor();
	}
	cout << endl;

	cout << "get end data" << endl;
	list.setCursorToEnd();
	cout << list.getCursorData() << endl;

	cout << "reverse out" << endl;
	while (list.hasPrevious())
	{
		cout << list.getCursorData() << " ";
		list.previousCursor();
	}
	cout << endl;

	cout << "data:" << list.get(4) << endl;

	system("pause");
	return 0;

}