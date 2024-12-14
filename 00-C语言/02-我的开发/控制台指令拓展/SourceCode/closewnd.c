#include<stdio.h>
#include<Windows.h>
int main(int argc, char * argv[])
{
    rename(argv[0],"closewnd.exe");
    if(argc<=2 || argv[1][0]=='?')
    {
        printf("? : get help\n");
        printf("mode windowTarget windowTarget ...: close this windowTarget\n");
        printf("mode:\n");
        printf("\tH:HWND\n");
        printf("\tC:ClassName\n");
        printf("\tT:Title\n");
    }
    else
    {
        for(int i=2;i<argc;i++)
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
            if(hwnd!=NULL)
                PostMessageA(hwnd, WM_CLOSE, 0, 0);
        }
    }
	return 0;
}
