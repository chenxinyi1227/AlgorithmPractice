#include <stdio.h>

int main()
{
    char choice;
    
    while((choice = getchar()) == '\n');
    while((getchar()) != '\n');
    printf("choice %c\n", choice);
    switch(choice)
    {
        case 'a': printf("a\n");break;
        case 'b': printf("b\n");break;
        case 'c': printf("ac\n");break;
        default:break;
    }
    return 0;
}