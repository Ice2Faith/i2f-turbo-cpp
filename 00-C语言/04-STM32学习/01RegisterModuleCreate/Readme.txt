�Ĵ���ģ��Ĵ��� �� ��Ŀģ��Ĵ���
	0.�����ȴ��Ŀ��ܣ�Ҳ�����ļ��нں�
		0.1.�½�һ���ļ��У���Ϊ��Ŀ���ļ��У���Ҫ���ģ�����ͽ���:Template
		0.2.��Template�ļ����´����ļ��У�User��Obj
		0.3.��Obj�ļ����´����ļ��У�Listing,Objects
		0.4.����ģ���ļ���UserĿ¼�£�main.c,startup_stm32f10x_hd.s,stm32f10x.h
		�γ��ļ������£�
			Template
				User
					main.c
					startup_stm32f10x_hd.s
					stm32f10x.h
				Obj
					Listing
					Objects
				
	1.��Keil�����Keil5��
	2.�˵�-Project-New uVersion Project-ѡ�����Ǹս������ļ���Template-��д�ļ����ƣ�template-����
		-չ��Stmicroelectronics-չ��STM32F1 Series-չ��STM32F103-ѡ��STM32F103ZE-OK-�رյ����Ĵ���
		-��ʱ�������ʾ��Ŀ��-չ��Target 1-˫��Source Group 1-���Կ������ǵ�User��Obj�ļ���-����User�ļ���
		-ѡ���ļ�����Ϊ��������-ѡ�������ļ�-Ҳ��������User�µ������ļ�-������-�ر�ѡ��-չ��Source Group 1
		-���Կ������ǵ������ļ��Ѿ����
	3.����ħ��������-����˵��·���������ľ�Աߵ�ħ����-ѡ��Target�˵�-��ѡUse MicroLib
		-ѡ��˵�Output-��ѡCreate HEX File-���Select Folder for Objects-ѡ�����ǵ�Obj/Objects�ļ���
		-ѡ��Listing�˵�-���Select Folder for Listings-ѡ�����ǵ�Obj/Listing�ļ���
		-ѡ��Debug�˵�-����ѡ��ѡ�������CMSIS-DAP Debugger-����Աߵ�Setting-ѡ��SW-��ѡSWJ
		-ѡ��ConnectΪNormal-ѡ��ResetΪSYSRESETREQ-ѡ��Flash Download�˵�-��ѡReset and Run
		-����б�û����ʾ-���Add-ѡ��STM32F10x High-density Flash 512k-���Add-һ·OK����
	4.��дmain.c���������£�����SYstemInit����ʱ����ģ��˺�����main����֮ǰ�����ã�һ��������Ϊϵͳʱ�Ӻ�IO�˿ڵĳ�ʼ��
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
		
	5.������Ŀ-����˵����·������ͼ�꣬һ�����¼�ͷ�·���һЩʡ�Ժŵ���һ�������Ƶ�ͼ���еĵڶ�����
		����������Ϣ���ͳɹ��ˣ�
		FromELF: creating hex file...
		".\Obj\template.axf" - 0 Error(s), 0 Warning(s).
	