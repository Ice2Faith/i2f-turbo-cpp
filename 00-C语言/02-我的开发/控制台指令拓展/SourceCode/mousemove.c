#include<stdio.h>
#include<Windows.h>
#include<conio.h>
int main(int argc, char * argv[])
{
    rename(argv[0],"mousemove.exe");
    if(argc>2 || (argc==2 && argv[1][0]=='?)'))
    {
        printf("? : get help\n");
        printf("keyboard press WASD to move mouse,press 468 to click mouse left right middle\n");
        printf("press space quit move.\n");

    }
    else
    {
        printf("press space to quit move.");
        while(1)
        {
            if(GetAsyncKeyState(VK_SPACE)&0x8000)
                break;
            POINT point;
            GetCursorPos(&point);
            if(GetAsyncKeyState('W')&0x8000)
               --point.y;
            if(GetAsyncKeyState('S')&0x8000)
                ++point.y;
            if(GetAsyncKeyState('A')&0x8000)
                --point.x;
            if(GetAsyncKeyState('D')&0x8000)
                ++point.x;
            SetCursorPos(point.x,point.y);
            if(GetAsyncKeyState('4')&0x8000 || GetAsyncKeyState(VK_NUMPAD4)&0x8000)
            {
               mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
               Sleep(90);
            }

            if(GetAsyncKeyState('6')&0x8000 || GetAsyncKeyState(VK_NUMPAD6)&0x8000)
            {
                 mouse_event(MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                 Sleep(90);
            }

            if(GetAsyncKeyState('8')&0x8000 || GetAsyncKeyState(VK_NUMPAD8)&0x8000)
            {
                 mouse_event(MOUSEEVENTF_MIDDLEDOWN|MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
                 Sleep(90);
            }
            Sleep(5);
        }
    }
	return 0;
}
