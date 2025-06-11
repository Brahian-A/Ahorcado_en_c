#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void mostrar_barra_vida(int errores, int max_errores)
{
    int llenos = max_errores - errores;
    printf("                   %s Vida: [", errores >= max_errores  ? "💀" : "❤️");
    for (int i = 0; i < llenos; i++) printf("█");
    for (int i = 0; i < errores; i++) printf("░");
    printf("]\n");
}

void actualizar_matriz(char matriz[5][6], int errores)
{
    switch (errores)
    {
        case 1:
            strcpy(matriz[2], " O   ");
            strcpy(matriz[3], " |   ");
            break;
        case 2:
            strcpy(matriz[3], "/|\\  ");
            break;
        case 3:
            strcpy(matriz[4], "/ \\  ");
            break;
        case 4:
            strcpy(matriz[1], " |   ");
            break;
        case 5:
            strcpy(matriz[0], " |   ");
            break;
    }
}

int main(void)
{
    int victorias = 0;
    FILE *archivo_victorias = fopen("victorias.txt", "r");
    if (archivo_victorias != NULL) {
        fscanf(archivo_victorias, "%d", &victorias);
        fclose(archivo_victorias);
    }

    char respuesta[10];

    while (69)
    {
        char *line = NULL;
        size_t len = 0;
        int len_word = 0;
        int errores = 0;
        const int max_errores = 6;
        char solucion[50];
        const char *words[] = {
            "programacion", "computadora", "teclado", "raton", "pantalla",
            "lenguaje", "desarrollador", "variable", "funcion", "compilador",
            "algoritmo", "memoria", "procesador", "software", "hardware",
            "internet", "servidor", "base", "datos", "codigo"
        };
        char matriz[5][6] = {
            "     ",
            "     ",
            "     ",
            "     ",
            "     "
        };

        srand(time(NULL));
        int index = rand() % 20;
        char palabra_oculta[50];
        strcpy(palabra_oculta, words[index]);
        len_word = strlen(palabra_oculta);

        for (int i = 0; i < len_word; i++)
            solucion[i] = '_';
        solucion[len_word] = '\0';

        while (69)
        {
            if (isatty(STDIN_FILENO))
            {
                system("clear");
                for (int i = 0; i < 5; i++)
                    printf("%s\n", matriz[i]);
                mostrar_barra_vida(errores, max_errores);
                printf("Palabra: %s %d\n", solucion, len_word);
                printf("Ingresa una letra: ");
                printf("%s", palabra_oculta); 
            }

            if (getline(&line, &len, stdin) == -1)
            {
                free(line);
                return 1;
            }

            char letra = line[0];
            int acierto = 0;

            for (int i = 0; i < len_word; i++)
            {
                if (palabra_oculta[i] == letra && solucion[i] == '_')
                {
                    solucion[i] = letra;
                    acierto = 1;
                }
            }

            if (!acierto)
            {
                errores++;
                actualizar_matriz(matriz, errores);
            }

            if (strcmp(solucion, palabra_oculta) == 0)
            {
                printf("¡Ganaste! La palabra era: %s\n", palabra_oculta);
                victorias++;
                if (victorias == 1)
                    printf("%d Victoria \n", victorias);
                else
                    printf("%d Victorias \n", victorias);
                break;
            }

            if (errores >= max_errores)
            {
                printf("¡Perdiste! La palabra era: %s\n", palabra_oculta);
            }

            if (errores == max_errores + 1)
                break;
        }

        free(line);
        printf("¿Querés jugar otra vez? (s/n): ");
        fgets(respuesta, sizeof(respuesta), stdin);
        if (respuesta[0] != 's' && respuesta[0] != 'S')
            break;
    }


    archivo_victorias = fopen("victorias.txt", "w");
    if (archivo_victorias != NULL) {
        fprintf(archivo_victorias, "%d\n", victorias);
        fclose(archivo_victorias);
    }

    return 0;
}
