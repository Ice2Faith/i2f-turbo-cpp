#include<stdio.h>
#include<Windows.h>
#include<string.h>
int main(int argc, char * argv[])
{
    rename(argv[0],"wndlist.exe");
    HWND hwnd = NULL;
	char title[256];
	char clsname[256];
	printf("HWND      CLASS");
	for(int i=0;i<43;i++)
        printf(" ");
	printf("  TITLE\n");
	int showall=1;
	if(argc>1)
    {
        if(argv[1][0]=='T')
            showall=0;
        else if(argv[1][0]=='?')
        {
            printf("[T]:show window list,if have T only show have title window.\n");
        }
    }
	do
	{
		hwnd = FindWindowEx(NULL, hwnd, NULL, NULL);
		GetWindowTextA(hwnd,title,255);
		GetClassNameA(hwnd, clsname, 255);
        if (showall==0 && strlen(title)==0)
                continue;
        else
        {
            printf("%08x  ",hwnd);
            int clen=strlen(clsname);
            if(clen<48)
            {
                printf("%s",clsname);
                for(int i=clen;i<48;i++)
                    printf(" ");
            }
            else
            {
                for(int i=0;i<45;i++)
                    printf("%c",clsname[i]);
                printf("...");
            }
            printf("  %s\n",title);
        }

	} while (hwnd!=NULL);
	return 0;
}
