#include "Snack.c"
int main()
{
    do
    {
        system("cls");
       SnackEattingGmme();
       system("cls");
       printf("\n\tClick \'*\' exit,else continue:\n\t>/ ");
    }while(getch()!='*');

    return 0;
}
