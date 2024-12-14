#include<stdio.h>
#include<Windows.h>
int main(int argc, char * argv[])
{
    rename(argv[0],"mousegoto.exe");
    if(argc<4 || argv[1][0]=='?')
    {
        printf("? : get help\n");
        printf("mode leftDistance topDistance : move cursor to (leftDistance,topDistance)\n");
        printf("mode:\n");
        printf("\tR:relatively present point move cursor\n");
        printf("\tA:absolute present point move cursor\n");
    }
    else
    {
        int mx=0,my=0;
        sscanf(argv[2],"%d",&mx);
        sscanf(argv[3],"%d",&my);
        if(argv[1][0]=='r' || argv[1][0]=='R')
        {
            POINT point;
            GetCursorPos(&point);
            SetCursorPos(point.x+mx,point.y+my);
        }else if(argv[1][0]=='a' || argv[1][0]=='A')
        {
            SetCursorPos(mx,my);
        }
        else
        {
            printf("not legal command format.");
        }
    }
	return 0;
}
