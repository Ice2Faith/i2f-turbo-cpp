#include<stdio.h>
#include<time.h>
#include<Windows.h>
int main(int argc, char * argv[])
{
    rename(argv[0],"mousedrag.exe");
    if(argc<4 || argv[1][0]=='?')
    {
        printf("? : get help\n");
        printf("mode leftDistance topDistance: mouse drag to (leftDistance,topDistance) form of mode\n");
        printf("mode:\n");
        printf("\tR:relatively present cursor position\n");
        printf("\tA:absolute screen position\n");
    }
    else
    {
        int mx=0,my=0;
        sscanf(argv[2],"%d",&mx);
        sscanf(argv[3],"%d",&my);
        if(argv[1][0]=='r' || argv[1][0]=='R')
        {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            int imx=mx>=0?1:-1;
            int imy=my>=0?1:-1;
            POINT point;
            GetCursorPos(&point);
            int px=point.x,py=point.y;
            while(1)
            {
                int changed=0;
                if(px!=point.x+mx)
                {
                    px+=imx;
                    changed=1;
                }
                if(py!=point.y+mx)
                {
                    py+=imy;
                    changed=1;
                }
                if(changed==0)
                    break;
                SetCursorPos(px,py);
                Sleep(5);
            }
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
        else if(argv[1][0]=='a' || argv[1][0]=='A')
        {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            POINT point;
            GetCursorPos(&point);
            int imx=(mx-point.x)>=0?1:-1;
            int imy=(my-point.y)>=0?1:-1;
            int px=point.x,py=point.y;
            while(1)
            {
                int changed=0;
                if(px!=mx)
                {
                    px+=imx;
                    changed=1;
                }
                if(py!=mx)
                {
                    py+=imy;
                    changed=1;
                }
                if(changed==0)
                    break;
                SetCursorPos(px,py);
                Sleep(5);
            }
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
        else
        {
            printf("not legal command format.");
        }
    }
	return 0;
}
