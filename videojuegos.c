<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "videojuegos.h"

// VALIDAR QUE NO HAYA Nï¿½MEROS
int tieneNumero(char cadena[])
{
    int i = 0;
    while (cadena[i] != '\0')
    {
        if (cadena[i] >= '0' && cadena[i] <= '9')
            return 1;
        i++;
    }
    return 0;
}

// GENERAR ID AUTOMï¿½TICO PARA VIDEOJUEGO
int generarIDVideojuego()
{
    FILE* archivo = fopen("videojuegos.bin", "rb");
    int maxID = 0;

    if (archivo != NULL)
    {
        Videojuego aux;
        while (fread(&aux, sizeof(Videojuego), 1, archivo) == 1)
        {
            if (aux.idJuego > maxID)
                maxID = aux.idJuego;
        }
        fclose(archivo);
    }

    return maxID + 1;
}

// VALIDAR PLATAFORMA
int validarPlataforma(char *p)
{
    if (strcmpi(p, "PC") == 0)  return 1;
    if (strcmpi(p, "XBOX") == 0) return 1;
    if (strcmpi(p, "PS4") == 0) return 1;
    if (strcmpi(p, "PS5") == 0) return 1;
    return 0;
}

// CARGAR VIDEOJUEGO
Videojuego cargaVideojuego()
{
    Videojuego juego;
    juego.idJuego = generarIDVideojuego();
    printf("ID asignado automï¿½ticamente: %d\n", juego.idJuego);

    // Nombre
    do
    {
        printf("Ingrese nombre: ");
        scanf("%49s", juego.nombre);
        if (tieneNumero(juego.nombre))
            printf("ERROR: El nombre no puede contener nï¿½meros.\n");
    }
    while (tieneNumero(juego.nombre) || strlen(juego.nombre) == 0);

    // Gï¿½nero
    do
    {
        printf("Ingrese genero: ");
        scanf("%29s", juego.genero);
        if (tieneNumero(juego.genero))
            printf("ERROR: El genero no puede contener numeros.\n");
    }
    while (tieneNumero(juego.genero) || strlen(juego.genero) == 0);

    // Plataforma
    do
    {
        printf("Ingrese plataforma (PC | XBOX | PS4 | PS5): ");
        scanf("%19s", juego.plataforma);
        if (!validarPlataforma(juego.plataforma))
            printf("ERROR: Plataforma invalida.\n");
    }
    while (!validarPlataforma(juego.plataforma));

    return juego;
}

// GUARDAR VIDEOJUEGO
int guardarVideojuego(Videojuego juego)
{
    FILE* archivo = fopen("videojuegos.bin", "ab");
    if (archivo == NULL)
    {
        printf("Error al abrir archivo.\n");
        return 0;
    }

    fwrite(&juego, sizeof(Videojuego), 1, archivo);
    fclose(archivo);

    printf("Videojuego guardado correctamente.\n");
    return 1;
}

// MODIFICAR VIDEOJUEGO
void modificarVideojuego(int idJuego)
{
    FILE* archivo = fopen("videojuegos.bin", "rb+");
    if (!archivo)
    {
        printf("No existe archivo videojuegos.bin\n");
        return;
    }

    Videojuego aux;
    int encontrado = 0;

    while (fread(&aux, sizeof(Videojuego), 1, archivo) == 1)
    {
        if (aux.idJuego == idJuego)
        {
            encontrado = 1;

            // Nuevo nombre
            do
            {
                printf("Nuevo nombre: ");
                scanf("%49s", aux.nombre);
                if (tieneNumero(aux.nombre))
                    printf("ERROR: El nombre no puede contener nï¿½meros.\n");
            }
            while (tieneNumero(aux.nombre) || strlen(aux.nombre) == 0);

            // Nuevo gï¿½nero
            do
            {
                printf("Nuevo genero: ");
                scanf("%29s", aux.genero);
                if (tieneNumero(aux.genero))
                    printf("ERROR: El gï¿½nero no puede contener nï¿½meros.\n");
            }
            while (tieneNumero(aux.genero) || strlen(aux.genero) == 0);

            // Nueva plataforma
            do
            {
                printf("Nueva plataforma (PC | XBOX | PS4 | PS5): ");
                scanf("%19s", aux.plataforma);
                if (!validarPlataforma(aux.plataforma))
                    printf("ERROR: Plataforma invï¿½lida.\n");
            }
            while (!validarPlataforma(aux.plataforma));

            fseek(archivo, -sizeof(Videojuego), SEEK_CUR);
            fwrite(&aux, sizeof(Videojuego), 1, archivo);

            printf("Videojuego modificado correctamente.\n");
            fclose(archivo);
            return;
        }
    }

    if (!encontrado)
        printf("No se encontrï¿½ videojuego con ese ID.\n");

    fclose(archivo);
}

// VER CATALOGO DE VIDEOJUEGOS
void verCatalogoVideojuegos()
{
    FILE* archivo = fopen("videojuegos.bin", "rb");
    if (!archivo)
    {
        printf("No hay videojuegos cargados.\n");
        return;
    }

    Videojuego aux;
    printf("\n=== CATALOGO DE VIDEOJUEGOS ===\n");
    while (fread(&aux, sizeof(Videojuego), 1, archivo) == 1)
    {
        printf("ID: %d | Nombre: %s | Plataforma: %s\n", aux.idJuego, aux.nombre, aux.plataforma);
    }

    fclose(archivo);
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "videojuegos.h"

// VALIDAR QUE NO HAYA NÚMEROS
int tieneNumero(char cadena[])
{
    int i = 0;
    while (cadena[i] != '\0')
    {
        if (cadena[i] >= '0' && cadena[i] <= '9')
            return 1;
        i++;
    }
    return 0;
}

// VALIDAR QUE SOLO HAYA LETRAS (sin símbolos ni números)
int soloLetras(char *cadena)
{
    for (int i = 0; cadena[i] != '\0'; i++)
    {
        if (!((cadena[i] >= 'A' && cadena[i] <= 'Z') ||
              (cadena[i] >= 'a' && cadena[i] <= 'z')))
        {
            return 0; // símbolo inválido
        }
    }
    return 1;
}

// GENERAR ID AUTOMÁTICO PARA VIDEOJUEGO
int generarIDVideojuego()
{
    FILE* archivo = fopen("videojuegos.bin", "rb");
    int maxID = 0;

    if (archivo != NULL)
    {
        Videojuego aux;
        while (fread(&aux, sizeof(Videojuego), 1, archivo) == 1)
        {
            if (aux.idJuego > maxID)
                maxID = aux.idJuego;
        }
        fclose(archivo);
    }

    return maxID + 1;
}

// VALIDAR PLATAFORMA
int validarPlataforma(char *p)
{
    if (strcmpi(p, "PC") == 0)  return 1;
    if (strcmpi(p, "XBOX") == 0) return 1;
    if (strcmpi(p, "PS4") == 0) return 1;
    if (strcmpi(p, "PS5") == 0) return 1;
    return 0;
}

// CARGAR VIDEOJUEGO
Videojuego cargaVideojuego()
{
    Videojuego juego;
    juego.idJuego = generarIDVideojuego();
    printf("ID asignado automáticamente: %d\n", juego.idJuego);

    // Nombre
    do
    {
        printf("Ingrese nombre: ");
        scanf("%49s", juego.nombre);
        if (tieneNumero(juego.nombre) || !soloLetras(juego.nombre))
            printf("ERROR: El nombre no puede contener números ni símbolos.\n");
    }
    while (tieneNumero(juego.nombre) || !soloLetras(juego.nombre));

    // Género
    do
    {
        printf("Ingrese género: ");
        scanf("%29s", juego.genero);
        if (tieneNumero(juego.genero) || !soloLetras(juego.genero))
            printf("ERROR: El género no puede contener números ni símbolos.\n");
    }
    while (tieneNumero(juego.genero) || !soloLetras(juego.genero));

    // Plataforma
    do
    {
        printf("Ingrese plataforma (PC | XBOX | PS4 | PS5): ");
        scanf("%19s", juego.plataforma);
        if (!validarPlataforma(juego.plataforma))
            printf("ERROR: Plataforma inválida.\n");
    }
    while (!validarPlataforma(juego.plataforma));

    return juego;
}

// GUARDAR VIDEOJUEGO
int guardarVideojuego(Videojuego juego)
{
    FILE* archivo = fopen("videojuegos.bin", "ab");
    if (archivo == NULL)
    {
        printf("Error al abrir archivo.\n");
        return 0;
    }

    fwrite(&juego, sizeof(Videojuego), 1, archivo);
    fclose(archivo);

    printf("Videojuego guardado correctamente.\n");
    return 1;
}

// MODIFICAR VIDEOJUEGO
void modificarVideojuego(int idJuego)
{
    FILE* archivo = fopen("videojuegos.bin", "rb+");
    if (!archivo)
    {
        printf("No existe archivo videojuegos.bin\n");
        return;
    }

    Videojuego aux;
    int encontrado = 0;

    while (fread(&aux, sizeof(Videojuego), 1, archivo) == 1)
    {
        if (aux.idJuego == idJuego)
        {
            encontrado = 1;

            // Nuevo nombre
            do
            {
                printf("Nuevo nombre: ");
                scanf("%49s", aux.nombre);
                if (tieneNumero(aux.nombre) || !soloLetras(aux.nombre))
                    printf("ERROR: El nombre no puede contener números ni símbolos.\n");
            }
            while (tieneNumero(aux.nombre) || !soloLetras(aux.nombre));

            // Nuevo género
            do
            {
                printf("Nuevo género: ");
                scanf("%29s", aux.genero);
                if (tieneNumero(aux.genero) || !soloLetras(aux.genero))
                    printf("ERROR: El género no puede contener números ni símbolos.\n");
            }
            while (tieneNumero(aux.genero) || !soloLetras(aux.genero));

            // Nueva plataforma
            do
            {
                printf("Nueva plataforma (PC | XBOX | PS4 | PS5): ");
                scanf("%19s", aux.plataforma);
                if (!validarPlataforma(aux.plataforma))
                    printf("ERROR: Plataforma inválida.\n");
            }
            while (!validarPlataforma(aux.plataforma));

            fseek(archivo, -sizeof(Videojuego), SEEK_CUR);
            fwrite(&aux, sizeof(Videojuego), 1, archivo);

            printf("Videojuego modificado correctamente.\n");
            fclose(archivo);
            return;
        }
    }

    if (!encontrado)
        printf("No se encontró videojuego con ese ID.\n");

    fclose(archivo);
}

// VER CATALOGO DE VIDEOJUEGOS
void verCatalogoVideojuegos()
{
    FILE* archivo = fopen("videojuegos.bin", "rb");
    if (!archivo)
    {
        printf("No hay videojuegos cargados.\n");
        return;
    }

    Videojuego aux;
    printf("\n=== CATALOGO DE VIDEOJUEGOS ===\n");
    while (fread(&aux, sizeof(Videojuego), 1, archivo) == 1)
    {
        printf("ID: %d | Nombre: %s | Plataforma: %s\n", aux.idJuego, aux.nombre, aux.plataforma);
    }

    fclose(archivo);
}



>>>>>>> 9f87bdde27f413650bb2a625a122775c76434952
