#include<stdio.h>
#include<Windows.h>
int main(int argc, char * argv[])
{
    rename(argv[0],"resizewnd.exe");
    if(argc<5 || argv[1][0]=='?')
    {
        printf("? : get help\n");
        printf("mode windowTarget width height : resize this windowTarget to width*height\n");
        printf("mode:\n");
        printf("\tH:HWND\n");
        printf("\tC:ClassName\n");
        printf("\tT:Title\n");
    }
    else
    {
        HWND hwnd=NULL;
        if(argv[1][0]=='h' || argv[1][0]=='H')
            sscanf(argv[2],"%x",&hwnd);
        else if(argv[1][0]=='c' || argv[1][0]=='C')
            hwnd=FindWindowA(argv[2],NULL);
        else if(argv[1][0]=='t' || argv[1][0]=='T')
            hwnd=FindWindowA(NULL,argv[2]);
        else
        {
            printf("not legal command format.");
            return 0;
        }
        int mx=0,my=0;
        sscanf(argv[3],"%d",&mx);
        sscanf(argv[4],"%d",&my);
        if(hwnd!=NULL)
            SetWindowPos(hwnd,NULL,0,0,mx,my,SWP_NOMOVE|SWP_NOZORDER);

    }
	return 0;
}
