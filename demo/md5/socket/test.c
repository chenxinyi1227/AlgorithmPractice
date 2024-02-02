#include <stdio.h>
#include <unistd.h>

int main() 
{
    FILE *file = fopen("demo.txt", "w");
    if (file == NULL) 
    {
        printf("Failed to open file.\n");
        return 1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) 
    {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}
