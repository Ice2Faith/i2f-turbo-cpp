寄存器模板的创建 和 项目模板的创建
	0.首先先搭建项目框架，也就是文件夹节后
		0.1.新建一个文件夹，作为项目根文件夹，需要中文，这里就叫做:Template
		0.2.在Template文件夹下创建文件夹：User，Obj
		0.3.在Obj文件夹下创建文件夹：Listing,Objects
		0.4.复制模板文件到User目录下：main.c,startup_stm32f10x_hd.s,stm32f10x.h
		形成文件树如下：
			Template
				User
					main.c
					startup_stm32f10x_hd.s
					stm32f10x.h
				Obj
					Listing
					Objects
				
	1.打开Keil软件（Keil5）
	2.菜单-Project-New uVersion Project-选择我们刚建立的文件夹Template-填写文件名称：template-保存
		-展开Stmicroelectronics-展开STM32F1 Series-展开STM32F103-选中STM32F103ZE-OK-关闭弹出的窗口
		-这时候软件显示项目树-展开Target 1-双击Source Group 1-可以看到我们的User和Obj文件夹-进入User文件夹
		-选择文件类型为所有类型-选择所有文件-也就是我们User下的三个文件-添加添加-关闭选框-展开Source Group 1
		-可以看到我们的三个文件已经添加
	3.配置魔术棒设置-点击菜单下方的三个积木旁边的魔术棒-选择Target菜单-勾选Use MicroLib
		-选择菜单Output-勾选Create HEX File-点击Select Folder for Objects-选中我们的Obj/Objects文件夹
		-选择Listing菜单-点击Select Folder for Listings-选中我们的Obj/Listing文件夹
		-选择Debug菜单-下拉选框选择调试器CMSIS-DAP Debugger-点击旁边的Setting-选择SW-勾选SWJ
		-选择Connect为Normal-选择Reset为SYSRESETREQ-选择Flash Download菜单-勾选Reset and Run
		-如果列表没有显示-点击Add-选择STM32F10x High-density Flash 512k-点击Add-一路OK即可
	4.编写main.c，代码如下，其中SYstemInit函数时必须的，此函数在main函数之前被调用，一般用来做为系统时钟和IO端口的初始化
		#include"stm32f10x.h"

		//boot function first run before main function on system on
		//usually to init sysclock or io port etc.
		void SystemInit()
		{
			
		}

		int main()
		{
			
			return 0;
		}
		
	5.编译项目-点击菜单栏下方的左边图标，一个向下箭头下方有一些省略号的哪一个，类似的图标中的第二个，
		看到如下信息，就成功了：
		FromELF: creating hex file...
		".\Obj\template.axf" - 0 Error(s), 0 Warning(s).
	