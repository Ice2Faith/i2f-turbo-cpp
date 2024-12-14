#include<stdio.h>
#include<Windows.h>
int main(int argc, char * argv[])
{
	rename(argv[0],"mousewheel.exe");
    if(argc<3 || argv[1][0]=='?')
    {
        printf("? : get help\n");
        printf("mode times: mouse wheel times form of mode\n");
        printf("mode:\n");
        printf("\tU:up mouse wheel\n");
        printf("\tD:down mouse wheel\n");
    }
    else
    {
        int times=1;
        sscanf(argv[2],"%d",&times);
        if(argv[1][0]=='u' || argv[1][0]=='U')
        {
            for(int i=0;i<times;i++)
                mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 120, 0);
        }else if(argv[1][0]=='d' || argv[1][0]=='D')
        {
            for(int i=0;i<times;i++)
                mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -120, 0);
        }
        else
        {
            printf("not legal command format.");
        }
    }
	return 0;
}
