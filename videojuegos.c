#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "videojuegos.h"

// VALIDAR QUE SOLO HAYA LETRAS Y NUMEROS (sin s�mbolos)
int letrasYNumeros(char *cadena)
{
    for (int i = 0; cadena[i] != '\0'; i++)
    {
        if (!((cadena[i] >= 'A' && cadena[i] <= 'Z') ||
              (cadena[i] >= 'a' && cadena[i] <= 'z') ||
              (cadena[i] >= '0' && cadena[i] <= '9')))
        {
            return 0; // s�mbolo invalido
        }
    }
    return 1;
}

// VALIDAR QUE SOLO HAYA LETRAS (sin s�mbolos ni n�meros)
int soloLetras(char *cadena)
{
    for (int i = 0; cadena[i] != '\0'; i++)
    {
        if (!((cadena[i] >= 'A' && cadena[i] <= 'Z') ||
              (cadena[i] >= 'a' && cadena[i] <= 'z')))
        {
            return 0; // simbolo invalido
        }
    }
    return 1;
}

// VERIFICAR SI UN VIDEOJUEGO YA EXISTE POR NOMBRE
int existeVideojuego(char nombre[])
{
    FILE *archivo = fopen("videojuegos.bin", "rb");
    if (!archivo)
        return 0;

    Videojuego aux;
    while (fread(&aux, sizeof(Videojuego), 1, archivo) == 1)
    {
        if (strcmpi(aux.nombre, nombre) == 0)
        {
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}

// GENERAR ID AUTOMATICO PARA VIDEOJUEGO
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
    char nombreJuego[50];
    nombreJuego = generarIDVideojuego();
    sprintf(juego.idJuego, "%d", nombreJuego)
    printf("ID asignado automaticamente: %d\n", juego.idJuego);

    // Nombre
    do
    {
        printf("Ingrese nombre (solo letras y numeros): ");
        scanf("%49s", juego.nombre);

        if (!letrasYNumeros(juego.nombre))
            printf("ERROR: El nombre solo puede contener letras y numeros.\n");
        else if (existeVideojuego(juego.nombre))
            printf("ERROR: Ya existe un videojuego con ese nombre.\n");

    } while (!letrasYNumeros(juego.nombre) || existeVideojuego(juego.nombre));

    // Genero
    do
    {
        printf("Ingrese genero: ");
        scanf("%29s", juego.genero);
        if (!soloLetras(juego.genero))
            printf("ERROR: El genero no puede contener numeros ni simbolos.\n");
    }
    while (!soloLetras(juego.genero));

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
void modificarVideojuego(char idJuego[])
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
        if (strcmpi(aux.idJuego, idJuego) == 0)
        {
            encontrado = 1;

            Videojuego original = aux; // Guardamos copia del original

            // Nuevo nombre
            do
            {
                printf("Nuevo nombre (solo letras y numeros): ");
                scanf("%49s", aux.nombre);

                if (!letrasYNumeros(aux.nombre))
                {
                    printf("ERROR: El nombre solo puede contener letras y numeros.\n");
                }
                else if (strcmpi(aux.nombre, original.nombre) != 0 && existeVideojuego(aux.nombre))
                {
                    // Evita conflicto si escribe el mismo nombre que ya tenia
                    printf("ERROR: Ya existe un videojuego con ese nombre.\n");
                }

            } while (!letrasYNumeros(aux.nombre) ||
                    (strcmpi(aux.nombre, original.nombre) != 0 && existeVideojuego(aux.nombre)));

            // Nuevo genero
            do
            {
                printf("Nuevo genero: ");
                scanf("%29s", aux.genero);

                if (!soloLetras(aux.genero))
                    printf("ERROR: El genero no puede contener numeros ni simbolos.\n");

            } while (!soloLetras(aux.genero));

            // Nueva plataforma
            do
            {
                printf("Nueva plataforma (PC | XBOX | PS4 | PS5): ");
                scanf("%19s", aux.plataforma);

                if (!validarPlataforma(aux.plataforma))
                    printf("ERROR: Plataforma invalida.\n");

            } while (!validarPlataforma(aux.plataforma));

            // Guardar cambios
            fseek(archivo, -sizeof(Videojuego), SEEK_CUR);
            fwrite(&aux, sizeof(Videojuego), 1, archivo);

            printf("Videojuego modificado correctamente.\n");
            fclose(archivo);
            return;
        }
    }

    if (!encontrado)
        printf("No se encontro videojuego con ese ID.\n");

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



