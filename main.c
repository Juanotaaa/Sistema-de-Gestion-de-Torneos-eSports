#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Administrador.h"
#include "Usuario.h"
#include "Torneo.h"

//MENUS
#define MENU_PRINCIPAL 1
#define MENU_USUARIO 2
#define MENU_ADMINISTRADOR 3
#define MENU_USUARIO_LOGEADO 4
#define MENU_ADMINISTRADOR_LOGEADO 5
#define MENU_ADMINISTRADOR_TORNEOS 6
#define MENU_ADMINISTRADOR_VIDEOJUEGOS 7
#define MENU_ADMINISTRADOR_USUARIOS 8


// Estructuras de Juegos, Usuarios, Administradores, Fechas y Torneos
typedef struct stVideojuego
{
    char idJuego[10];
    char nombre[50];
    char genero[30];
    char plataforma[20];
} Videojuego;

typedef struct stInscripcion
{
    char idInscripcion[30];
    char idTorneo[10];
    char idUsuario[10];
    Fecha fechaInscripcion;
} Inscripcion;

typedef struct
{
    char idUsuario[20];
    int cantidadTorneos;
} Ranking;

/* Administradores hardcodeados 
const Administrador a[] =
{
    {"EduProfe", "EduElMejor", "Eduardo Mango", "admin"},
    {"Kevito", "kevin123", "Kevin", "admin"},
    {"Aye", "ayecrack", "Ayelen", "admin" }
};
const int totalAdmins = sizeof(a) / sizeof(a[0]);
*/

Usuario usuarioActual;
int hayUsuarioLogueado = 0;


///PROTOTIPADO
void funcionMenu(int menu);
void salirDeLaApp();
void mostrarTorneos(Torneo t);
int verListadoTorneos();


/// prototipado agregado por mati
int guardarVideojuego(Videojuego juego);
int tieneNumero(char cadena[]);
Videojuego cargaVideojuego();
int validacionIDVideojuego(char idJuego[]);
void modificarVideojuego(char idJuego[]);
void verCatalogoVideojuegos();

int buscarTorneoPorIDParaMati(char id[], Torneo *T, int *pos);
int validarTorneoAbierto(Torneo T);
int validarCupos(Torneo T);
void registrarInscripcion();
int buscarUsuarioPorID(char id[], Usuario *U);
void verParticipantesTorneo();
void torneosSinParticipantes();

// funciones juani
void verInfoDetalladaUsuario();
void verListadoUsuarios();
void agregarModificarUsuario();
void mostrarPerfilUsuario(Usuario u);

int main()
{
    funcionMenu(MENU_PRINCIPAL);
    return 0;
}

void funcionMenu(int menu)
{
    system("cls");

    char opcion[100];

    switch (menu)
    {
    case MENU_PRINCIPAL:
        printf("\n\tBIENVENIDO A NEXUS\n");
        printf("\n\tPresione la opcion que desea:\n");
        printf("\n\t[1]-Ingresar como usuario\n");
        printf("\n\t[2]-Ingresar como administrador\n");
        printf("\n\t[3]-Salir\n");
        fflush(stdin);
        scanf("%s", opcion);

        if(strcmp(opcion, "1")==0)
        {
            funcionMenu(MENU_USUARIO);
        }
        else if(strcmp(opcion, "2")==0)
        {
            funcionMenu(MENU_ADMINISTRADOR);
        }
        else if(strcmp(opcion, "3")==0)
        {
            salirDeLaApp();
        }
        else
        {
            printf("\n\tOpcion invalida\n");
            system("pause");
            funcionMenu(MENU_PRINCIPAL);
        }
        break;

    case MENU_USUARIO:
        printf("\n\tPresione la opcion que desea:\n");
        printf("\n\t[1]-Ingresar\n");
        printf("\n\t[2]-No tiene cuenta? Registrese aqui!\n");
        printf("\n\t[3]-Regresar al MENU PRINCIPAL\n");
        scanf("%s", opcion);
        fflush(stdin);

        if(strcmp(opcion, "1")==0)
        {
           int loginExitoso=loginUsuario(&usuarioActual, &hayUsuarioLogueado);
           if(loginExitoso==1){
            funcionMenu(MENU_USUARIO_LOGEADO);
           }else{
            funcionMenu(MENU_PRINCIPAL);
           }
        }
        if(strcmp(opcion, "2")==0)
        {
            Usuario u;
            int creacionExitosa=crearUsuario(&u); 
            if(creacionExitosa==1){
                int infoExtra=agregarInformacionUsuario(&u);
                if(infoExtra==1){
                printf("\nUsted se ha registrado correctamente\n");
                guardarUsuario(u, ARCHIVO_USUARIO);
                }else{
                    printf("\nUsted sera redirigido al MENU USUARIO\n");
                    system("pause");
                }
            }
            funcionMenu(MENU_USUARIO);
            
        }
        if(strcmp(opcion, "3")==0)
        {
            funcionMenu(MENU_PRINCIPAL);
        }
        else
        {
            printf("\n\tOpcion invalida\n");
            system("pause");
            funcionMenu(MENU_USUARIO);
        }
        break;

    case MENU_ADMINISTRADOR:
        printf("\n\tPresione la opcion que desea:\n");
        printf("\n\t[1]-Ingresar\n");
        printf("\n\t[2]-Regresar al MENU PRINCIPAL\n");
        scanf("%s", opcion);
        fflush(stdin);

        if(strcmp(opcion, "1")==0)
        {
            int loginExitoso=loginAdministrador();
            if(loginExitoso==1){
               funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
            }else{
                funcionMenu(MENU_PRINCIPAL);
            }
        }
        if(strcmp(opcion, "2")==0)
        {
            funcionMenu(MENU_PRINCIPAL);
        }
        else
        {
            printf("\n\tOpcion invalida\n");
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR);
        }
        break;

    case MENU_USUARIO_LOGEADO:
        printf("\n\tPresione la opcion que desea:\n");
        printf("\n\t[1]-Ver mi perfil\n");
        printf("\n\t[2]-Ver torneos abiertos\n");
        printf("\n\t[3]-Ver catálogo de videojuegos\n");
        printf("\n\t[4]-Registrarme a un torneo\n");
        printf("\n\t[5]-Cerrar sesion\n");
        printf("\n\t[6]-Regresar al MENU PRINCIPAL\n");
        scanf("%s", opcion);

        if(strcmp(opcion, "1")==0)
        {
            mostrarPerfilUsuario(usuarioActual);
            system("pause");
            funcionMenu(MENU_USUARIO_LOGEADO);
        }
        if(strcmp(opcion, "2")==0)
        {
            verTorneosAbiertosYCuposDisponibles();
                        system("pause");
            funcionMenu(MENU_USUARIO_LOGEADO);
        }
        if(strcmp(opcion, "3")==0)
        {
            verCatalogoVideojuegos();
                        system("pause");
            funcionMenu(MENU_USUARIO_LOGEADO);
        }
        if(strcmp(opcion, "4")==0)
        {
            registrarInscripcion();
            system("pause");
            funcionMenu(MENU_USUARIO_LOGEADO);
        }
        if(strcmp(opcion, "5")==0)
        {
            hayUsuarioLogueado = 0;
            system("pause");
            funcionMenu(MENU_PRINCIPAL);
        }
        if(strcmp(opcion, "6")==0)
        {
            funcionMenu(MENU_PRINCIPAL);
        }
        else
        {
            printf("\n\tOpcion invalida\n");
            system("pause");
            funcionMenu(MENU_USUARIO_LOGEADO);
        }
        break;

    case MENU_ADMINISTRADOR_LOGEADO:
        printf("\n\tADMINISTRADOR - Presione la opcion que desea:\n");
        printf("\n\t[1]-MENU TORNEOS\n");
        printf("\n\t[2]-MENU VIDEOJUEGOS\n");
        printf("\n\t[3]-MENU USUARIOS\n");
        printf("\n\t[4]-Regresar al menu principal\n");
        scanf("%s", opcion);

        if(strcmp(opcion, "1")==0)
        {
            funcionMenu(MENU_ADMINISTRADOR_TORNEOS);
        }
        if(strcmp(opcion, "2")==0)
        {
            funcionMenu(MENU_ADMINISTRADOR_VIDEOJUEGOS);
        }
        if(strcmp(opcion, "3")==0)
        {
            funcionMenu(MENU_ADMINISTRADOR_USUARIOS);
        }
        if(strcmp(opcion, "4")==0)
        {
            funcionMenu(MENU_PRINCIPAL);
        }
        else
        {
            printf("\n\tOpcion invalida\n");
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        break;
    
    case MENU_ADMINISTRADOR_TORNEOS:
        printf("\n\tADMINISTRADOR - Presione la opcion que desea:\n");
        printf("\n\t[1]-Ver torneos\n");
        printf("\n\t[2]-Crear torneo\n");
        printf("\n\t[3]-Modificar torneo\n");
        printf("\n\t[4]-Ver torneos abiertos\n");
        printf("\n\t[5]-Torneos sin participantes\n");
        printf("\n\t[6]-Regresar al MENU ADMINISTRADOR\n");
        scanf("%s", opcion);
        if(strcmp(opcion, "1")==0)
        {
            verListadoTorneos();
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(strcmp(opcion, "2")==0)
        {
            crearTorneo();
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(strcmp(opcion, "3")==0)
        {
            char idTorneo[10];
            printf("Ingrese el ID del torneo a modificar: ");
            scanf("%s", idTorneo);
            modificarTorneoAEleccion(idTorneo);
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);

        }
        if(strcmp(opcion, "4")==0)
        {
            verTorneosAbiertosYCuposDisponibles();
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(strcmp(opcion, "5")==0)
        {
            torneosSinParticipantes();
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(strcmp(opcion, "6")==0)
        {
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        else
        {
            printf("\n\tOpcion invalida\n");
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_TORNEOS);
        }
        break;

    case MENU_ADMINISTRADOR_VIDEOJUEGOS:
        printf("\n\tADMINISTRADOR - Presione la opcion que desea:\n");
        printf("\n\t[1]-Cargar videojuego\n");
        printf("\n\t[2]-Modificar videojuego\n");
        printf("\n\t[3]-Ver catalogo videojuegos\n");
        printf("\n\t[4]-Regresar al MENU ADMINISTRADOR\n");
        scanf("%s", opcion);
        if(strcmp(opcion, "1")==0)
        {
            Videojuego juego = cargaVideojuego();
            guardarVideojuego(juego);
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(strcmp(opcion, "2")==0)
        {
            char idModificado[10];
            printf("Ingrese ID del videojuego a modificar: ");
            scanf("%s", idModificado);
            modificarVideojuego(idModificado);
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(strcmp(opcion, "3")==0)
        {
            verCatalogoVideojuegos();
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(strcmp(opcion, "4")==0)
        {
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        else
        {
            printf("\n\tOpcion invalida\n");
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_VIDEOJUEGOS);
        }
    break;

    case MENU_ADMINISTRADOR_USUARIOS:
        printf("\n\tADMINISTRADOR - Presione la opcion que desea:\n");
        printf("\n\t[1]-Registrar inscripcion\n");
        printf("\n\t[2]-Ver participantes de un torneo\n");
        printf("\n\t[3]-Regresar al MENU ADMINISTRADOR\n");
        scanf("%s", opcion);
         if(strcmp(opcion, "1")==0)
        {
            registrarInscripcion();
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(strcmp(opcion, "2")==0)
        {
            verParticipantesTorneo();
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(strcmp(opcion, "3")==0)
        {
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        else
        {
            printf("\n\tOpcion invalida\n");
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_USUARIOS);
        }
    break;

    default:
        break;
    }
}




void salirDeLaApp()
{
    printf("\nGracias por su visita a Nexus Arena, esperamos volver a verlo\n");
}

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
            printf("ID: %s | Nombre: %s | Juego: %s | Cupos Disponibles: %d\n", T.idTorneo, T.nombre, T.juego.nombre, T.cuposDisponibles);
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

int buscarTorneo(char idTorneo[], Torneo* torneo){

    FILE * ArchivoTorneo = fopen("torneos.bin", "rb");

    if(ArchivoTorneo == NULL)
    {
        printf("No se pudo abrir el archivo de torneos.\n");
        return 0;
    }


    while(fread(torneo, sizeof(Torneo), 1, ArchivoTorneo)){

        if(strcmp(idTorneo, torneo->idTorneo)==0){

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


/// funciones de videojuegos (mati)
int guardarVideojuego(Videojuego juego)
{
    FILE* archivo = fopen("videojuegos.bin", "ab");
    if(!archivo)
    {
        printf("Error al abrir archivo\n");
        return 0;
    }
    fwrite(&juego, sizeof(Videojuego), 1, archivo);
    fclose(archivo);
    printf("Videojuego guardado correctamente\n");
    return 1;
}

int tieneNumero(char cadena[])
{
    int i = 0;
    while(cadena[i] != '\0') /// mientras no termine la palabra
    {
        if(cadena[i] >= '0' && cadena[i] <= '9') /// busca si tiene un numero
            return 1;
        i++;
    }
    return 0;
}

Videojuego cargaVideojuego()
{
    Videojuego juego;
    do {
        printf("Ingrese ID del videojuego: ");
        scanf("%s", juego.idJuego);
        if(validacionIDVideojuego(juego.idJuego))
            printf("ID existente. Ingrese otro\n");
    } while(validacionIDVideojuego(juego.idJuego) || strlen(juego.idJuego) >= 9);

    do {
        printf("Ingrese nombre: ");
        scanf("%s", juego.nombre);
    } while(strlen(juego.nombre) == 0 || strlen(juego.nombre) >= 49);

    do {
        printf("Ingrese genero: ");
        scanf("%s", juego.genero);
    } while(tieneNumero(juego.genero) || strlen(juego.genero) == 0 || strlen(juego.genero) >= 29);

    do {
        printf("Ingrese plataforma: ");
        scanf("%s", juego.plataforma);
    } while(tieneNumero(juego.plataforma) || strlen(juego.plataforma) == 0 || strlen(juego.plataforma) >= 19);

    return juego;
}


int validacionIDVideojuego(char idJuego[])
{
    FILE* archivo = fopen("videojuegos.bin", "rb");
      if(!archivo)
    {
        return 0;
    }

    Videojuego aux;
    while(fread(&aux, sizeof(Videojuego), 1, archivo) == 1)
    {
        if(strcmp(aux.idJuego, idJuego) == 0)
        {
            fclose(archivo); /// juego repetido
            return 1;
        }
    }
    fclose(archivo);
    return 0;
}
void modificarVideojuego(char idJuego[])
{

    FILE* archivo = fopen("videojuegos.bin", "rb+");
    if (archivo == NULL)
    {
        printf("No existe archivo videojuegos.bin\n");
        return;
    }

    Videojuego aux;
    int encontrado = 0;

    while (fread(&aux, sizeof(Videojuego), 1, archivo) == 1)
    {
        if (strcmp(aux.idJuego,idJuego) == 0)
        {
            encontrado = 1;

            printf("Nuevo nombre: ");
            scanf("%s", aux.nombre);

            do
            {
                printf("Nuevo genero: ");
                scanf("%s", aux.genero);

                if (tieneNumero(aux.genero))
                    printf("El genero no puede contener numeros.\n");

                if (strlen(aux.genero) >= 29)
                    printf("El genero es demasiado largo.\n");

            }while(tieneNumero(aux.genero) || strlen(aux.genero) >= 29);


            do
            {
                printf("Nueva plataforma: ");
                scanf("%s", aux.plataforma);

                if (tieneNumero(aux.plataforma))
                    printf("La plataforma no puede contener numeros.\n");

                if (strlen(aux.plataforma) >= 19)
                    printf("La plataforma es demasiado larga.\n");

            }while(tieneNumero(aux.plataforma) || strlen(aux.plataforma) >= 19);


            fseek(archivo, -sizeof(Videojuego), SEEK_CUR);
            fwrite(&aux, sizeof(Videojuego), 1, archivo);

            printf("Videojuego modificado correctamente.\n");
            break;
        }
    }

    if (!encontrado)
        printf("No se encontro videojuego con ese ID.\n");

    fclose(archivo);
}

void verCatalogoVideojuegos()
{
    FILE* archivo = fopen("videojuegos.bin", "rb");
    if(!archivo)
        {
             printf("No hay videojuegos cargados\n");
    return;
    }

    Videojuego aux;
    printf("=== CATALOGO DE VIDEOJUEGOS ===\n");
    while(fread(&aux, sizeof(Videojuego), 1, archivo) == 1)
    {
        printf("ID: %s Nombre: %s Plataforma: %s\n", aux.idJuego, aux.nombre, aux.plataforma);
    }
    fclose(archivo);
}

int buscarUsuarioPorID(char id[], Usuario *U)
{
    int encontrado=0;
    FILE* archivo = fopen("usuario.bin", "rb");
    if (!archivo)
    {
        return 0;
    }

    Usuario aux;
    while (fread(&aux, sizeof(Usuario), 1, archivo) == 1)
    {
        if (strcmp(aux.idUsuario, id) == 0)
        {
            *U = aux;
            encontrado = 1;
        }
    }

    fclose(archivo);
    return encontrado;
}

int validarTorneoAbierto(Torneo T)
{
    int validos = 0;

    if (strcmp(T.estado, "Abierto") == 0)
    {
        validos = 1;
    }

    return validos;
}
int validarCupos(Torneo T)
{
    int validos = 0;

    if (T.cuposDisponibles > 0)
    {
        validos = 1;
    }

    return validos;
}

int buscarTorneoPorIDParaMati(char id[], Torneo *T, int *pos)
{
    FILE* archivo = fopen("torneos.bin", "rb");
    if(!archivo)
        return 0;

    Torneo aux;
    int index = 0;   // número de registro dentro del archivo
    long bytePos = 0;

    while (fread(&aux, sizeof(Torneo), 1, archivo) == 1)
    {
        if (strcmp(aux.idTorneo, id) == 0)
        {
            *T = aux;
            *pos = bytePos;          // POSICIÓN EN BYTES REAL
            fclose(archivo);
            return 1;
        }

        index++;
        bytePos = index * sizeof(Torneo);
    }

    fclose(archivo);
    return 0;
}

void registrarInscripcion()
{
    int continuar = 1;

    char idTorneo[10];
    char idUsuario[10];

    Torneo T;
    int posT;

    printf("Ingrese ID del torneo: ");
    scanf("%s", idTorneo);

    if (!buscarTorneoPorIDParaMati(idTorneo, &T, &posT))
    {
        printf("No existe un torneo con ese ID.\n");
        continuar = 0;
    }

    if (continuar && !validarTorneoAbierto(T))
    {
        printf("El torneo no está abierto.\n");
        continuar = 0;
    }

    if (continuar && !validarCupos(T))
    {
        printf("No quedan cupos disponibles.\n");
        continuar = 0;
    }

    if (continuar)
    {
        printf("Ingrese ID del usuario: ");
        scanf("%s", idUsuario);

        Usuario U;
        if (!buscarUsuarioPorID(idUsuario, &U))
        {
            printf("No existe un usuario con ese ID.\n");
            return;
        }
    }
    if (continuar)
    {

        Inscripcion I;


        strcpy(I.idInscripcion, idTorneo);
        strcat(I.idInscripcion, "_");
        strcat(I.idInscripcion, idUsuario);

        strcpy(I.idTorneo, idTorneo);
        strcpy(I.idUsuario, idUsuario);
        // Verificamos si ya está inscrito
        FILE* archIns = fopen("inscripciones.bin", "rb");
        if (archIns)
        {
            Inscripcion aux;
            while (fread(&aux, sizeof(Inscripcion), 1, archIns) == 1)
            {
                if (strcmp(aux.idTorneo, idTorneo) == 0 && strcmp(aux.idUsuario, idUsuario) == 0)
                {
                    printf("El usuario ya está inscrito en este torneo.\n");
                    fclose(archIns);
                    return; // Salimos sin registrar de nuevo
                }
            }
            fclose(archIns);
        }




        /// Guardarmos la inscripción en archivo
        FILE* archivo = fopen("inscripciones.bin", "ab");
        if (!archivo)
        {
            printf("Error al abrir archivo de inscripciones.\n");
            return;
        }
        fwrite(&I, sizeof(Inscripcion), 1, archivo);
        fclose(archivo);

        /// Actualizamos
        FILE* archi = fopen("torneos.bin", "rb+");
        if (!archi)
        {
            printf("Error al abrir archivo de torneos.\n");
            return;
        }

        fseek(archi, posT, SEEK_SET); /// volver a la posición del torneo encontrado
        T.cuposDisponibles--;         /// restar cupo
        fwrite(&T, sizeof(Torneo), 1, archi);
        fclose(archi);

        printf("Inscripción realizada correctamente.\n");
    }



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
                    if (strcmp(I.idTorneo, T.idTorneo) == 0)
                    {
                        tieneParticipantes = 1;
                        break; // hay participante salimos
                    }
                }
                fclose(archIns);
            }

            if (!tieneParticipantes)
            {
                printf("ID: %s | Nombre: %s | Juego: %s | Plataforma: %s | Cupos: %d\n",T.idTorneo, T.nombre, T.juego.nombre, T.juego.plataforma, T.cuposDisponibles);
            }
        }
    }

    fclose(archTorneos);
}


//FUNCIONES DE JUANI
void agregarModificarUsuario()
{
    Usuario u;
    Usuario aux;
    int encontrado = 0;

    printf("Ingrese ID del Usuario: ");
    fflush(stdin);
    gets(u.idUsuario);

    FILE *buffer = fopen("usuario.bin", "r+b");

    if(buffer != NULL)
    {
        while(fread(&aux, sizeof(Usuario), 1, buffer) > 0)
        {
            if(strcmp(aux.idUsuario, u.idUsuario) == 0)
            {
                encontrado = 1;
                printf("\nUsuario encontrado. Modificando datos...\n");

                printf("Ingrese nuevo nickname: ");
                fflush(stdin);
                gets(aux.nickname);

                printf("Ingrese nueva contrasenia: ");
                fflush(stdin);
                gets(aux.contrasenia);

                printf("Ingrese nuevo email: ");
                fflush(stdin);
                gets(aux.numTelefonico);

                printf("Ingrese nuevo pais: ");
                fflush(stdin);
                gets(aux.pais);

                printf("Ingrese nuevo nivel: ");
                scanf("%d", &aux.nivel);

                fseek(buffer, -sizeof(Usuario), SEEK_CUR);
                fwrite(&aux, sizeof(Usuario), 1, buffer);

                fclose(buffer);
                printf("\nUsuario modificado correctamente.\n");
                return;
            }
        }
        fclose(buffer);
    }

    printf("\nUsuario no encontrado. Se procedera a agregarlo.\n");

    printf("Ingrese nickname: ");
    fflush(stdin);
    gets(u.nickname);

    printf("Ingrese contrasenia: ");
    fflush(stdin);
    gets(u.contrasenia);

    printf("Ingrese email: ");
    fflush(stdin);
    gets(u.numTelefonico);

    printf("Ingrese pais: ");
    fflush(stdin);
    gets(u.pais);

    printf("Ingrese nivel: ");
    scanf("%d", &u.nivel);

    buffer = fopen("usuario.bin", "ab");
    fwrite(&u, sizeof(Usuario), 1, buffer);
    fclose(buffer);

    printf("\nUsuario agregado correctamente.\n");
}


void verParticipantesTorneo()
{
    char idTorneo[10];
    printf("Ingrese ID del torneo: ");
    scanf("%s", idTorneo);

    Torneo T;
    int pos;
    if (!buscarTorneoPorIDParaMati(idTorneo, &T, &pos))
    {
        printf("No existe un torneo con ese ID.\n");
        return;
    }

    FILE* archivo = fopen("inscripciones.bin", "rb");
    if (!archivo)
    {
        printf("No hay participantes inscritos.\n");
        return;
    }

    Inscripcion I;
    int encontrados = 0;

    printf("\nParticipantes del torneo %s:\n", idTorneo);

    while (fread(&I, sizeof(Inscripcion), 1, archivo) == 1)
    {
        if (strcmp(I.idTorneo, idTorneo) == 0)
        {
            Usuario U;
            if (buscarUsuarioPorID(I.idUsuario, &U))
            {
                printf(" %s %s \n",U.nickname, U.idUsuario);
                encontrados++;
            }
        }
    }

    fclose(archivo);

    if (encontrados == 0)
        printf("No hay participantes inscritos.\n");
}

void verListadoUsuarios()
{
    FILE *buffer = fopen("usuario.bin", "rb");
    if(buffer == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    Usuario u;

    printf("\n--- LISTADO DE USUARIOS ---\n");
    while(fread(&u, sizeof(Usuario), 1, buffer) == 1)
    {
        printf("ID: %s | Nick: %s | Email: %s | Pais: %s | Nivel: %d\n",
               u.idUsuario, u.nickname, u.numTelefonico, u.pais, u.nivel);
    }
    fclose(buffer);
}

void mostrarPerfilUsuario(Usuario u)
{
    printf("\n--- PERFIL USUARIO ---\n");
    printf("ID: %s\n", u.idUsuario);
    printf("Nickname: %s\n", u.nickname);
    printf("Email: %s\n", u.numTelefonico);
    printf("Pais: %s\n", u.pais);
    printf("Nivel: %d\n", u.nivel);
}

void verInfoDetalladaUsuario()
{
    char idUsuario[10];
    printf("Ingrese ID del Usuario: ");
    scanf("%s", idUsuario);

    Usuario U;
    if (buscarUsuarioPorID(idUsuario, &U))
    {
        mostrarPerfilUsuario(U);
    }
    else
    {
        printf("Usuario no encontrado.\n");
    }
}