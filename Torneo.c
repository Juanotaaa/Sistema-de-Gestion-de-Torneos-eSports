
#include "Torneo.h"
#include <stdio.h>
#include <string.h>


void crearTorneo()
{
    FILE *ArchivoTorneo = fopen("torneos.bin", "ab");
    if(ArchivoTorneo == NULL)
    {
        printf("No se pudo abrir el archivo de torneos.\n");
        return;
    }

    Torneo T;
    T = cargaTorneo();
    fwrite(&T, sizeof(Torneo), 1, ArchivoTorneo);
    fclose(ArchivoTorneo);
}
int buscarTorneoPorID(char id[])
{
    FILE* archivo = fopen("torneos.bin", "rb");
    if (!archivo)
        return 0;

    Torneo aux;

    while (fread(&aux, sizeof(Torneo), 1, archivo) == 1)
    {
        if (strcmp(aux.idTorneo, id) == 0)
        {
            fclose(archivo);
            return 1; // Encontrado
        }
    }

    fclose(archivo);
    return 0;
}

Torneo cargaTorneo()
{
    Torneo T;
    char id[10];

    // --- CONTROL DE ID ÚNICO ---
    printf("\nIngrese ID del torneo: \n");
    scanf("%9s", id);

    while (buscarTorneoPorID(id) == 1)
    {
        printf("ID ya existente. Ingrese otro ID: \n");
        scanf("%9s", id);
    }

    strcpy(T.idTorneo, id);

    printf("Ingrese nombre del torneo: \n");
    scanf("%49s", T.nombre);

    printf("Ingrese ID del juego: \n");
    scanf("%9s", T.juego.idJuego);

    printf("Ingrese nombre del juego: (INGRESE NOMBRES SIN ESPACIOS) \n");
    fflush(stdin);
    scanf("%49s", T.juego.nombre);

    printf("Ingrese genero del juego: PVP, FPS, Battle Royale, Extract Shooter... \n");
    scanf("%29s", T.juego.genero);

    printf("Ingrese plataforma del juego: PC/Xbox/Playstation (PS) \n");
    scanf("%19s", T.juego.plataforma);

    printf("Ingrese capacidad maxima del torneo: \n");
    scanf("%d", &T.capacidadMaxima);

    T.cuposDisponibles = T.capacidadMaxima;

    printf("Ingrese fecha de inicio (dd mm aaaa): \n");
    scanf("%d %d %d", &T.fechaInicio.dia, &T.fechaInicio.mes, &T.fechaInicio.anio);

    actualizarEstadoTorneo(&T);

    do
    {
        printf("Ingrese premio total del torneo: \n");
        scanf("%f", &T.premioTotal);
        if (T.premioTotal < 1)
        {
            printf("El premio total no puede ser menor a una unidad unica de puntos. Por favor, ingrese un valor valido.\n");
        }
    }
    while (T.premioTotal < 1);

    strcpy(T.estado, "Abierto");

    return T;
}

int fechaUnica(Fecha f)
{
    return f.anio * 10000 + f.mes * 100 + f.dia;
}

int fechaAnterior(Fecha a, Fecha b)
{
    return fechaUnica(a) < fechaUnica(b);
}

void actualizarEstadoTorneo(Torneo *T)
{
    Fecha corte = {2025, 11, 20};

    if (fechaAnterior(T->fechaInicio, corte))
    {
        printf("\nInicializo un Torneo que ya terminó\n");
        strcpy(T->estado, "Finalizado");
    }
    else
    {
        printf("\nEl estado del Torneo está Abierto\n");
        strcpy(T->estado, "Abierto");
    }
}

void mostrarTorneo(Torneo T)
{
    printf("\n=== ID Torneo: %s ======\n", T.idTorneo);
    printf("\n=== Nombre: %s ===\n", T.nombre);
    printf("\n=== Juego: %s ===\n", T.juego.nombre);
    printf("\n=== Capacidad Maxima: %d ===\n", T.capacidadMaxima);
    printf("\n=== Cupos Disponibles: %d ===\n", T.cuposDisponibles);
    printf("\n=== Fecha de Inicio: %02d/%02d/%04d ===\n", T.fechaInicio.dia, T.fechaInicio.mes, T.fechaInicio.anio);
    printf("\n=== Premio Total: %.2f ===\n", T.premioTotal);
    printf("\n=== Estado: %s ===\n", T.estado);
}

void mostrarTorneos(Torneo t)
{
    mostrarTorneo(t);
}

void modificarTorneoAEleccion(char idTorneo[]) //funcion intervenida por Cande
{
    int dim;
    Torneo * listaTorneo=torneoArrDinamico(&dim);

    if(dim==0){
        printf("\nNo existen torneos\n");
        return;
    }

    Torneo T;
    int encontrado = 0;

    for(int i=0; i<dim; i++){

        if(strcmp(listaTorneo[i].idTorneo, idTorneo) == 0)
            {
                encontrado = 1;
                T = modificarTorneo(listaTorneo[i]);
                listaTorneo[i]=T;
                printf("Torneo modificado correctamente.\n");
                break;
            }

    }

    if(encontrado==0){
        printf("\nNo se encontro el torneo especificado\n");
        return;
    }

    guardarListaTorneo(listaTorneo, dim);
}

Torneo modificarTorneo(Torneo T)
{
    printf("\nEstos son los datos actuales del torneo:\n");
    mostrarTorneo(T);
    system("pause");

   char respuesta = 's';
   printf ("Desea modificiar el nombre del torneo? S/N \n");
   fflush(stdin);
    scanf(" %c", &respuesta);
        if (respuesta == 's' || respuesta == 'S')
        {
            printf("Ingrese nuevo nombre del torneo: \n");
            scanf("%49s", T.nombre);
        }
    printf("Desea modificar el nombre del juego? S/N \n");
    fflush(stdin);
    scanf(" %c", &respuesta);
    if (respuesta == 's' || respuesta == 'S')
        {
            printf("Ingrese el nuevo nombre del juego: \n");
            scanf("%49s", T.juego.nombre);
        }
        printf("Desea modificar el genero del juego? S/N \n");
    fflush(stdin);
    scanf(" %c", &respuesta);
    if (respuesta == 's' || respuesta == 'S')
        {
            printf("Ingrese el nuevo genero del juego \n");
            scanf("%29s", T.juego.genero);
        }
        printf("Desea modificar la plataforma del juego? S/N \n");
    fflush(stdin);
    scanf(" %c", &respuesta);
    if (respuesta == 's' || respuesta == 'S')
        {
            printf("Ingrese la nueva plataforma del juego \n");
            scanf("%19s", T.juego.plataforma);
        }
    printf("Desea modificar la capacidad maxima del torneo? S/N \n");
    fflush(stdin);
    scanf(" %c", &respuesta);
    if (respuesta == 's' || respuesta == 'S')
        {
            printf("Ingrese nueva capacidad maxima del torneo: \n");
            scanf("%d", &T.capacidadMaxima);
        }
        T.cuposDisponibles = T.capacidadMaxima; // Actualizar cupos disponibles

        printf("Desea modificar la fecha de inicio del torneo? S/N \n");
        fflush(stdin);
        scanf(" %c", &respuesta);
        if (respuesta == 's' || respuesta == 'S')
        {
            printf("Ingrese nueva fecha de inicio (dd mm aaaa): \n");
             scanf("%d %d %d", &T.fechaInicio.dia, &T.fechaInicio.mes, &T.fechaInicio.anio);
             actualizarEstadoTorneo(&T);
        }
        printf("Desea modificar el premio total del torneo? S/N \n");
        fflush(stdin);
        scanf(" %c", &respuesta);
        if (respuesta == 's' || respuesta == 'S')
        {
            printf("Ingrese nuevo premio total del torneo: \n");
            scanf("%f", &T.premioTotal);
        }

    printf("\nAsi quedo el torneo modificado:\n");
    mostrarTorneo(T);
    system("pause");
    return T;

}