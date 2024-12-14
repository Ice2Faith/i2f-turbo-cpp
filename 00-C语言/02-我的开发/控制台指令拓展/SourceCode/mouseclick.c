#include<stdio.h>
#include<Windows.h>
int main(int argc, char * argv[])
{
    rename(argv[0],"mouseclick.exe");
    if(argc<3 || argv[1][0]=='?')
    {
        printf("? : get help\n");
        printf("mode times: mouse click times form of mode\n");
        printf("mode:\n");
        printf("\tL:left mouse button\n");
        printf("\tR:right mouse button\n");
        printf("\tM:middle mouse button\n");
    }
    else
    {
        int times=1;
        sscanf(argv[2],"%d",&times);
        if(argv[1][0]=='l' || argv[1][0]=='L')
        {
            for(int i=0;i<times;i++)
            mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }else if(argv[1][0]=='r' || argv[1][0]=='R')
        {
            for(int i=0;i<times;i++)
            mouse_event(MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }
        else if(argv[1][0]=='m' || argv[1][0]=='M')
        {
            for(int i=0;i<times;i++)
            mouse_event(MOUSEEVENTF_MIDDLEDOWN|MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
        }
        else
        {
            printf("not legal command format.");
        }
    }
	return 0;
}
