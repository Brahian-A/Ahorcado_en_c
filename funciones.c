void mostrar_barra_vida(int errores, int max_errores)
{
    int bloques_llenos = max_errores - errores;
    int bloques_totales = max_errores;

    if (errores < max_errores)
        printf("                                                   ❤️ Vida: [");
    else
        printf("💀 Vida: [");

    for (int i = 0; i < bloques_totales; i++)
    {
        if (i < bloques_llenos)
            printf("█");
        else
            printf("░");
    }

    printf("]\n");
}