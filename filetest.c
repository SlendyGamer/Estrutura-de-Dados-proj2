#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int main()
{
    setlocale(LC_ALL,"portuguese");
    FILE *file, *newFile;
    char line[80];

    file = fopen("Dados.txt", "r");
    newFile = fopen("novosDados.txt", "w");

    if (file == NULL)
    {
        printf("arquivo antigo nao encontrado");
        return 2;
    }
    else if (newFile == NULL)
    {
        printf("arquivo novo nao criado");
        return 2;
    }
    else
    {
        int int1, int2, num;
        char string1[39], string2[24];
        float float1;

        if (fgets(line,sizeof(line), file) != NULL)
        {
        sscanf(line, "%d", &num);
        }
        while (fgets(line,sizeof(line), file) != NULL)
        {
            sscanf(line, "%d %38[^\n] %d %23[^\n] %f", &int1, string1, &int2, string2, &float1);
            printf("escaneado: %d  %s  %d  %s %.2f\n", int1, string1, int2, string2, float1); //sucesso
            fprintf(newFile, "%d %s %d %s %.2f\n", int1, string1, int2, string2, float1);

        }
        printf("%d\n", num);
        fclose(file);
        fclose(newFile);
        printf("sucesso");
    }
}
