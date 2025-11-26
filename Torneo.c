#include "Torneo.h"
#include "videojuegos.h"
#include "videojuegos.c"
#include <stdio.h>
#include <string.h>

int verListadoTorneos()
{
    FILE* archivoTorneo=fopen("torneos.bin", "rb");

    if(!archivoTorneo)
    {
        printf("\nNo se pudo ingresar al archivo en modo lectura\n");
        system("pause");
        funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        return 0;
    }

    Torneo t;

    while(fread(&t, sizeof(Torneo), 1, archivoTorneo))
    {
        mostrarTorneos(t);
    }

    fclose(archivoTorneo);
    return 1;
}

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

int obtenerProximoIDTorneo()
{
    FILE *arch = fopen("ultimoIDTorneo.dat", "rb");
    int ultimoID = 0;

    if (arch)
    {
        fread(&ultimoID, sizeof(int), 1, arch);
        fclose(arch);
    }

    ultimoID++;

    arch = fopen("ultimoIDTorneo.dat", "wb");
    fwrite(&ultimoID, sizeof(int), 1, arch);
    fclose(arch);

    return ultimoID;
}


int buscarTorneoPorID(int id[])
{
    FILE* archivo = fopen("torneos.bin", "rb");
    if (!archivo)
        return 0;

    Torneo aux;

    while (fread(&aux, sizeof(Torneo), 1, archivo) == 1)
    {
        if (aux.idTorneo == id)
        {
            fclose(archivo);
            return 1; // Encontrado
        }
    }

    fclose(archivo);
    return 0;
}

void guardarTorneo(Torneo t)
{
    FILE *arch = fopen("torneos.dat", "ab");
    fwrite(&t, sizeof(Torneo), 1, arch);
    fclose(arch);
}

Torneo cargaTorneo()
{
    Torneo T;
    int id[10];


   Torneo t;

    printf("\n=== CREAR NUEVO TORNEO ===\n");

    t.idTorneo = obtenerProximoIDTorneo();
    if (t.idTorneo == -1)
    {
        printf("Error al obtener el ID del torneo.\n");
        return t;
    }
    printf("ID asignado automaticamente: %d\n", t.idTorneo);


    printf("Ingrese nombre del torneo: \n");
    scanf("%49s", T.nombre);

    printf("Ingrese nombre del juego: (INGRESE NOMBRES SIN ESPACIOS) \n");
    fflush(stdin);
    scanf("%49s", T.juego.nombre);

    printf("Ingrese genero del juego: PVP, FPS, Battle Royale, Extract Shooter... \n");
    scanf("%29s", T.juego.genero);
    do
            {
                printf("Nuevo genero: ");
                scanf("%29s", aux.genero);
                if (tieneNumero(aux.genero))
                    printf("ERROR: El genero no puede contener numeros.\n");
            }
            while (tieneNumero(aux.genero) || strlen(aux.genero) == 0);
    
    if(strcmp(T.juego.genero, "PVP")!=0 && strcmp(T.juego.genero, "FPS")!=0 && strcmp(T.juego.genero, "Battle Royale")!=0 && strcmp(T.juego.genero, "Extract Shooter")!=0)
    {
        do {
        printf("Ingrese un genero valido: PVP, FPS, Battle Royale, Extract Shooter \n");
        scanf("%29s", T.juego.genero);
        } while (strcmp(T.juego.genero, "PVP")!=0 && strcmp(T.juego.genero, "FPS")!=0 && strcmp(T.juego.genero, "Battle Royale")!=0 && strcmp(T.juego.genero, "Extract Shooter")!=0);
    }

    printf("Ingrese plataforma del juego: PC | Xbox | Playstation4(PS4) | Playstation5(PS5) \n");
    scanf("%19s", T.juego.plataforma);
     do
            {
                printf("Nueva plataforma (PC | XBOX | PS4 | PS5): ");
                scanf("%19s", aux.plataforma);
                if (!validarPlataforma(aux.plataforma))
                    printf("ERROR: Plataforma inv�lida.\n");
            }
            while (!validarPlataforma(aux.plataforma));

    printf("Ingrese capacidad maxima del torneo: \n");
    scanf("%d", &T.capacidadMaxima);

    T.cuposDisponibles = T.capacidadMaxima;

    printf("\nIngrese fecha de inicio (dd mm aaaa): \n");
    printf("\nIngrese el año: ");
    scanf("%d", &T.fechaInicio.anio);
    if(T.fechaInicio.anio<2025)
    {
        do {
        printf("\n Ingrese una fecha valida, si no su torneo figurara como cerrado \n");
        printf("Ingrese el año: ");
        scanf("%d", &T.fechaInicio.anio);
        } while (T.fechaInicio.anio<2025);
    }

    printf("\nIngrese el mes: ");
    scanf("%d", &T.fechaInicio.mes);
     if( (T.fechaInicio.anio<1) && (T.fechaInicio.anio>12) )
    {
        do {
        printf("\n porfavor ingrese una fecha valida, si no su torneo figurara como cerrado \n");
        printf("Ingrese el mes: ");
        scanf("%d", &T.fechaInicio.mes);
        } while ( (T.fechaInicio.anio<1) && (T.fechaInicio.anio>12) );
    }
    printf("Ingrese el dia: ");
    scanf("%d", &T.fechaInicio.dia);
     if(T.fechaInicio.dia<1 && T.fechaInicio.dia>31)
    {
        do {
        printf("\n Porfavor ingrese una fecha valida. \n");
        printf("Ingrese el dia: ");
        scanf("%d", &T.fechaInicio.dia);
        } while ( (T.fechaInicio.dia>1) && (T.fechaInicio.dia>31) );
    }
    

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
    printf("\n=== ID Torneo: %d ======\n", T.idTorneo);
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

void modificarTorneoAEleccion(int idTorneo) //funcion intervenida por Cande
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

        if(listaTorneo[i].idTorneo == idTorneo)
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
            do
    {
        printf("Ingrese nombre: ");
        scanf("%49s", juego.nombre);
        if (tieneNumero(juego.nombre))
            printf("ERROR: El nombre no puede contener n�meros.\n");
    }
    while (tieneNumero(juego.nombre) || strlen(juego.nombre) == 0);
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
            do
    {
        printf("Ingrese genero: ");
        scanf("%29s", juego.genero);
        if (tieneNumero(juego.genero))
            printf("ERROR: El genero no puede contener numeros.\n");
    }
    while (tieneNumero(juego.genero) || strlen(juego.genero) == 0);
        }
        printf("Desea modificar la plataforma del juego? S/N \n");
    fflush(stdin);
    scanf(" %c", &respuesta);
    if (respuesta == 's' || respuesta == 'S')
        {
            printf("Ingrese la nueva plataforma del juego \n");
            scanf("%19s", T.juego.plataforma);
            do
    {
        printf("Ingrese plataforma (PC | XBOX | PS4 | PS5): ");
        scanf("%19s", juego.plataforma);
        if (!validarPlataforma(juego.plataforma))
            printf("ERROR: Plataforma invalida.\n");
    }
    while (!validarPlataforma(juego.plataforma));

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
     printf("\nIngrese el año: ");
    scanf("%d", &T.fechaInicio.anio);
    if(T.fechaInicio.anio<2025)
    {
        do {
        printf("\n Ingrese una fecha valida, si no su torneo figurara como cerrado \n");
        printf("Ingrese el año: ");
        scanf("%d", &T.fechaInicio.anio);
        } while (T.fechaInicio.anio<2025);
    }

    printf("\nIngrese el mes: ");
    scanf("%d", &T.fechaInicio.mes);
     if( (T.fechaInicio.anio<1) && (T.fechaInicio.anio>12) )
    {
        do {
        printf("\n porfavor ingrese una fecha valida, si no su torneo figurara como cerrado \n");
        printf("Ingrese el mes: ");
        scanf("%d", &T.fechaInicio.mes);
        } while ( (T.fechaInicio.anio<0) && (T.fechaInicio.anio>12) );
    }
    printf("Ingrese el dia: ");
    scanf("%d", &T.fechaInicio.dia);
     if(T.fechaInicio.dia<1 && T.fechaInicio.dia>31)
    {
        do {
        printf("\n Porfavor ingrese una fecha valida. \n");
        printf("Ingrese el dia: ");
        scanf("%d", &T.fechaInicio.dia);
        } while ( (T.fechaInicio.dia>1) && (T.fechaInicio.dia>31) );
    }
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

void verTorneosAbiertosYCuposDisponibles()
{
    FILE *ArchivoTorneo = fopen("torneos.bin", "rb");

    if(ArchivoTorneo == NULL)
    {
        printf("No se pudo abrir el archivo de torneos.\n");
        return;
    }
    Torneo T;

    printf("\n=== TORNEOS ABIERTOS DISPONIBLES ===\n");
    while((fread(&T, sizeof(Torneo), 1, ArchivoTorneo) > 0) && (T.cuposDisponibles > 0))
    {
        mostrarTorneosAbiertos(T);
    }
    fclose(ArchivoTorneo);
    return;
}

void mostrarTorneosAbiertos(Torneo T)
{
        if (strcmp(T.estado, "Abierto") == 0)
        {
            printf("ID: %d | Nombre: %s | Juego: %s | Cupos Disponibles: %d\n", T.idTorneo, T.nombre, T.juego.nombre, T.cuposDisponibles);
        }else{
            printf("No hay torneos abiertos disponibles en este momento.\n");
        }
}

Torneo * torneoArrDinamico(int* dim){ //Funcion hecha por cande

    int cant = contarTorneos();

    Torneo* torneoArray = (Torneo*)calloc(cant, sizeof(Torneo));

    *dim = cant;

    FILE * ArchivoTorneo=fopen("torneos.bin", "r+b");

    if(!ArchivoTorneo){
        printf("\nNo se pudo abrir el archivo en modo lectura\n");
        return 0;
    }

    Torneo T;
    int i=0;

    while(fread(&T, sizeof(Torneo), 1, ArchivoTorneo)){
        torneoArray[i]=T;
    }
    fclose(ArchivoTorneo);

return torneoArray;
}

int contarTorneos(){

    FILE*ArchivoTorneo=fopen("torneos.bin", "rb");

    if(!ArchivoTorneo){
        printf("\nNo se pudo abrir el torneo en modo lectura\n");
        return 0;
    }

    Torneo T;
    int cant=0;

    while(fread(&T, sizeof(Torneo), 1, ArchivoTorneo)){
        cant++;
    }
    fclose(ArchivoTorneo);

return cant;
}

int buscarTorneo(int idTorneo, Torneo* torneo){

    FILE * ArchivoTorneo = fopen("torneos.bin", "rb");

    if(ArchivoTorneo == NULL)
    {
        printf("No se pudo abrir el archivo de torneos.\n");
        return 0;
    }


    while(fread(torneo, sizeof(Torneo), 1, ArchivoTorneo)){

        if(idTorneo == torneo->idTorneo){

            return 1;
        }

    }

    fclose(ArchivoTorneo);

return 0;
}

void guardarListaTorneo(Torneo* listaTorneo, int dim)
{
    FILE* ArchivoTorneo = fopen("torneos.bin", "wb");

    if(!ArchivoTorneo){
        printf("\nNo se pudo abrir el archivo\n");
        return;
    }

    fwrite(listaTorneo, sizeof(Torneo), dim, ArchivoTorneo);

    fclose(ArchivoTorneo);
}

void torneosSinParticipantes()
{
    FILE * archTorneos = fopen("torneos.bin", "rb");
    if (!archTorneos)
    {
        printf("No se pudieron abrir los torneos.\n");
        return;
    }

    Torneo T;
    Inscripcion I;
    int tieneParticipantes;

    printf("\n=== Torneos abiertos sin participantes ===\n");

    while (fread(&T, sizeof(Torneo), 1, archTorneos) == 1)
    {
        if (strcmp(T.estado, "Abierto") == 0)
        {
            tieneParticipantes = 0;

            FILE * archIns = fopen("inscripciones.bin", "rb");
            if (archIns)
            {
                while (fread(&I, sizeof(Inscripcion), 1, archIns) == 1)
                {
                    if (I.idTorneo == T.idTorneo)
                    {
                        tieneParticipantes = 1;
                        break; // hay participante salimos
                    }
                }
                fclose(archIns);
            }

            if (!tieneParticipantes)
            {
                printf("ID: %d | Nombre: %s | Juego: %s | Plataforma: %s | Cupos: %d\n",T.idTorneo, T.nombre, T.juego.nombre, T.juego.plataforma, T.cuposDisponibles);
            }
        }
    }

    fclose(archTorneos);
}