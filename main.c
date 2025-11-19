#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <string.h>

#define MIN_NICKNAME 5
#define MAX_NICKNAME 50
#define MIN_CONTRA 5
#define MAX_CONTRA 20
#define MIN_EMAIL 5
#define MAX_EMAIL 50
#define ARCHIVO_USUARIO "usuario.bin"
//MENUS
#define MENU_PRINCIPAL 1
#define MENU_USUARIO 2
#define MENU_ADMINISTRADOR 3
#define MENU_USUARIO_LOGEADO 4
#define MENU_ADMINISTRADOR_LOGEADO 5


// Estructuras de Juegos, Usuarios, Administradores, Fechas y Torneos
typedef struct stVideojuego
{
    char idJuego[10];
    char nombre[50];
    char genero[30];
    char plataforma[20];
} Videojuego;

typedef struct stUsuario
{
    char idUsuario[10]; // ID de jugador único
    char nickname[30];
    char contrasenia[20];
    char email[50];
    char pais[30];
    int nivel; // Nivel de experiencia (ej. 1 a 10)
} Usuario;

typedef struct stAdministrador
{
    char usuario[20]; // Usuario para el login
    char contrasenia[20];
    char nombreCompleto[50];
    char rol[20]; // Ej: "Organizador", "Staff"
} Administrador;

typedef struct stFecha
{
    int dia;
    int mes;
    int anio;
} Fecha;

typedef struct stTorneo
{
    char idTorneo[10];
    char nombre[50];
    Videojuego juego;
    int capacidadMaxima;
    int cuposDisponibles;
    Fecha fechaInicio;
    float premioTotal;
    char estado[15]; // "Abierto", "En Curso", "Finalizado"
} Torneo;

typedef struct stInscripcion
{
    char idInscripcion[30];
    char idTorneo[10];
    char idUsuario[10];
    Fecha fechaInscripcion;
} Inscripcion;

/* Administradores hardcodeados (los dos) */
const Administrador a[] =
{
    {"EduProfe", "EduElMejor", "Eduardo Mango", "admin"},
    {"Kevito", "kevin123", "Kevin", "admin"}
};
const int totalAdmins = sizeof(a) / sizeof(a[0]);

/// struct para promocion

typedef struct
{
    char idUsuario[20];
    int cantidadTorneos;
} Ranking;


///PROTOTIPADO
//prototipado de cande
void funcionMenu(int menu);
void loginAdministrador();
int validacionUsuarioAdmin(char usuarioAdmin[], int validos, char contraseniaAdmin[]);
int validacionContrasenia(char contrasenia[]);
int validacionDeMail(char[]);
int validaciondeNickname(char[]);
Usuario crearUsuario();
int guardarUsuario(Usuario, char[]);
void loginUsuario();
int validacionUsuario(char archivo[], char usuario[], char contraseniaUsuario[]);
void salirDeLaApp();
void mostrarTorneos(Torneo t);
int verListadoTorneos();

//prototipado de fran
Torneo cargaTorneo(); //Llevar a Main -Fran
int validacionIDTorneo(char idTorneo[]); //Llevar a Main -Fran
void crearTorneo(); //Llevar a Main -Fran
void modificarTorneo(char idTorneo[]); //Llevar a Main -Fran

/// prototipado agregado por mati
int guardarVideojuego(Videojuego juego);
int tieneNumero(char cadena[]);
Videojuego cargaVideojuego();
int validacionIDVideojuego(char idJuego[]);
void modificarVideojuego(char idJuego[]);
void verCatalogoVideojuegos();
int buscarTorneoPorID(char id[], Torneo *T, int *pos);
int validarTorneoAbierto(Torneo T);
int validarCupos(Torneo T);
void registrarInscripcion();
int buscarUsuarioPorID(char id[], Usuario *U);
void verParticipantesTorneo();
void rankingTorneo();

/// prototipado juani
void verInfoDetalladaUsuario();
void verListadoUsuarios();
void agregarModificarUsuario();


int main()
{
    funcionMenu(MENU_PRINCIPAL);
    return 0;
}

void funcionMenu(int menu)
{
    system("cls"); // en sistemas *nix puede usarse "clear"

    int opcion=0;

    switch (menu)
    {
    case MENU_PRINCIPAL:
        printf("\n\tBIENVENIDO A NEXUS\n");
        printf("\n\tPresione la opcion que desea:\n");
        printf("\n\t[1]-Ingresar como usuario\n");
        printf("\n\t[2]-Ingresar como administrador\n");
        printf("\n\t[3]-Salir\n");
        fflush(stdin);
        scanf("%d", &opcion);
        if(opcion==1)
        {
            funcionMenu(MENU_USUARIO);
        }
        else if(opcion==2)
        {
            funcionMenu(MENU_ADMINISTRADOR);
        }
        else if(opcion==3)
        {
            salirDeLaApp();

        }
        else
        {
            printf("\n\tOpcion invalida, por favor ingrese una opcion correcta\n");
            system("pause");
            funcionMenu(MENU_PRINCIPAL);
        }

        break;

    case MENU_USUARIO:
        printf("\n\tPresione la opcion que desea:\n");
        printf("\n\t[1]-Ingresar\n");
        printf("\n\t[2]-No tiene cuenta? Registrese aqui!\n");
        printf("\n\t[3]-Regresar al MENU PRINCIPAL\n");
        scanf("%d", &opcion);
        fflush(stdin);
        if(opcion==1)
        {
            loginUsuario();
        }
        if(opcion==2)
        {
            Usuario u = crearUsuario();
            guardarUsuario(u, ARCHIVO_USUARIO);
            funcionMenu(MENU_USUARIO);
        }
        if(opcion==3)
        {
            funcionMenu(MENU_PRINCIPAL);
        }
        break;

    case MENU_ADMINISTRADOR:
        printf("\n\tPresione la opcion que desea:\n");
        printf("\n\t[1]-Ingresar\n");
        printf("\n\t[2]-Regresar al MENU PRINCIPAL\n");
        scanf("%d", &opcion);
        fflush(stdin);
        if(opcion==1)
        {
            loginAdministrador();
        }
        if(opcion==2)
        {
            funcionMenu(MENU_PRINCIPAL);
        }
        break;

    case MENU_USUARIO_LOGEADO:
        printf("\n\tPresione la opcion que desea:\n");
        printf("\n\t[1]-Ver perfil\n");
        printf("\n\t[2]-Ver torneos disponibles\n");
        printf("\n\t[3]-Inscripcion a torneos\n");
        printf("\n\t[4]-Cerrar sesion\n");

        fflush(stdin);
        scanf("%d", &opcion);
        if(opcion==1)
        {
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }
        if(opcion==2)
        {
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }
        if (opcion==3)
        {
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }
        if (opcion==4)
        {
            funcionMenu(MENU_PRINCIPAL);
        }
        break;

    case MENU_ADMINISTRADOR_LOGEADO:
        printf("\n\tPresione la opcion que desea:\n");
        printf("\n\t[1]-Ver torneos\n");
        printf("\n\t[2]-Agregar torneo\n");
        printf("\n\t[3]-Modificar torneo\n");
        printf("\n\t[4]-Ver ganancias\n");
        printf("\n\t[5]-Agregar Videojuego\n");
        printf("\n\t[6]-Modificar Videojuego\n");
        printf("\n\t[7]-ver catalogo de Videojuegos\n");
        printf("\n\t[8]-Registrar inscripcion\n");
        printf("\n\t[9]-Ver participantes de un torneo\n");
        printf("\n\t[10]-Ver ranking de jugadores\n");
        printf("\n\t[11]-Cerrar sesion\n");
        fflush(stdin);
        scanf("%d", &opcion);
        if (opcion==1)
        {
            verListadoTorneos();

        }
        if(opcion==2)
        {
            crearTorneo();
        }
        if(opcion==3)
        {
            char idTorneo[10];
            printf("Ingrese el ID del torneo a modificar: ");
            scanf("%s", idTorneo);
            modificarTorneo(idTorneo);
        }
        if (opcion==4)
        {
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }
        if(opcion==5)
        {
            Videojuego juego = cargaVideojuego();
            guardarVideojuego(juego);
        }
        if (opcion==6)
        {
            char idModificado[10];
            printf("ingrese ID del Videojuego a modificar: ");
            scanf("%s",idModificado);
            modificarVideojuego(idModificado);
        }
        if (opcion==7)
        {
            verCatalogoVideojuegos();
        }
        if (opcion==8)
        {
            registrarInscripcion();
        }
        if(opcion == 9)
        {
            verParticipantesTorneo();
        }
        if(opcion == 10)
        {

            rankingTorneo();
        }
        if(opcion == 11)
        {

            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }


        break;
    default:
        break;
    }


}

//funciones de Cande
int validacionContrasenia(char contrasenia[])
{
    int dimension=strlen(contrasenia);
    int esValido=1;
    if(dimension<MIN_CONTRA || dimension>MAX_CONTRA)
    {
        printf("\nLa contrasenia no cumple con la longitud de los requisitos, caracteres ingresados: %d\n", dimension);
        esValido=0;
    }
    char caracterActual;
    for(int i=0; i<dimension; i++)
    {
        caracterActual=contrasenia[i];
        if(caracterActual>='0' && caracterActual<='9')
        {
            break;
        }
        if(i==dimension-1)
        {
            printf("\nContrasenia invalida, no olvide que se requiere al menos un numero\n");
            esValido=0;
        }
    }
    return esValido;
}

int validacionDeMail(char email[])
{
    int dimension=strlen(email);
    int esValido=1;
    if(dimension<MIN_EMAIL || dimension>MAX_EMAIL)
    {
        printf("\nEl email no cumple con la longitud de los requisitos, caracteres ingresados: %d\n", dimension);
        esValido=0;
    }
    return esValido;
}

int validaciondeNickname(char nickname[])
{
    int dimension=strlen(nickname);
    int esValido=1;
    if(dimension<MIN_NICKNAME || dimension>MAX_NICKNAME)
    {
        printf("\nEl nickname no cumple con la longitud de los requisitos, caracteres ingresados: %d\n", dimension);
        esValido=0;
    }
    return esValido;
}

Usuario crearUsuario()
{
    Usuario usuario;
    printf("\nRecuerde que para registrarse, debe ingresar un nickname valido y una contrasenia que cumpla con los siguientes requisitos:\n");
    printf("-Caracteres minimo: 5\n");
    printf("-Minimo un numero\n");

    char control='s';
    int valNickname;
    int valContra;

    do
    {
        printf("\nIngrese su nickname:\n");
        fflush(stdin);
        scanf("%s", usuario.nickname);

        valNickname=validaciondeNickname(usuario.nickname);
        if(valNickname!=1)
        {
            printf("\nDesea ingresar otro nickname? [s/n]\n");
            scanf(" %c", &control);
            fflush(stdin);
        }
    }
    while((control=='s' || control=='S') && valNickname!=1);

    do
    {
        printf("\nIngrese una contrasenia:\n");
        fflush(stdin);
        scanf("%s", usuario.contrasenia);

        valContra=validacionContrasenia(usuario.contrasenia);
        if(valContra!=1)
        {
            printf("\nDesea ingresar otra contrasenia? [s/n]\n");
            scanf(" %c", &control);
            fflush(stdin);
        }
    }
    while((control=='s' || control=='S') && valContra!=1);

    return usuario;
}

int guardarUsuario(Usuario x, char archivo[])
{
    printf("\nGuardando en archivo\n");
    FILE* usuarioArchivo=fopen(archivo, "ab");

    if(!usuarioArchivo)
    {
        printf("\nEl archivo no pudo abrirse\n");
        return 0;
    }

    fwrite(&x, sizeof(Usuario), 1, usuarioArchivo);

    fclose(usuarioArchivo);
    return 1;
}




void loginUsuario()
{
    char contraseniaUsuario[20];
    char usuario[20];
    char control;
    int valUsuario;

    do
    {
        printf("\n\tIngrese su usuario:\n");
        fflush(stdin);
        scanf("%s", usuario);

        printf("\n\tIngrese su contrasenia\n");
        fflush(stdin);
        scanf("%s", contraseniaUsuario);

        valUsuario=validacionUsuario(ARCHIVO_USUARIO, usuario, contraseniaUsuario);

        if(valUsuario==1)
        {
            printf("\nUsted se ha logeado correctamente\n");
        }
        else
        {
            printf("\nError al ingresar datos\n");
            printf("\nDesea intentarlo de nuevo? [s/n]\n");
            fflush(stdin);
            scanf(" %c", &control);
        }

    }
    while(control=='s' || control=='S');
}

int validacionUsuario(char archivo[], char usuario[], char contraseniaUsuario[])
{
    FILE * usuarioArchivo=fopen(archivo, "rb");

    if(!usuarioArchivo)
    {
        printf("\nNo se pudo abrir el archivo en modo lectura\n");
        return 0;
    }

    Usuario u;

    while(fread(&u, sizeof(Usuario), 1, usuarioArchivo))
    {
        if(strcmp(usuario, u.nickname)==0)
        {
            if(strcmp(contraseniaUsuario, u.contrasenia)==0)
            {
                fclose(usuarioArchivo);
                return 1;
            }
        }
    }
    fclose(usuarioArchivo);
    return 0;
}

void loginAdministrador()
{
    char contraseniaAdmin[20];
    char usuarioAdmin[20];
    char control;
    int valAdmin;
    int validos = totalAdmins;
    do
    {
        printf("\n\tIngrese su usuario:\n");
        fflush(stdin);
        scanf("%s", usuarioAdmin);

        printf("\n\tIngrese su contrasenia\n");
        fflush(stdin);
        scanf("%s", contraseniaAdmin);

        valAdmin=validacionUsuarioAdmin(usuarioAdmin, validos, contraseniaAdmin);

        if(valAdmin==1)
        {
            printf("\nUsted se ha logeado correctamente\n");
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        else
        {
            printf("\nError al ingresar datos\n");
            printf("\nDesea intentarlo de nuevo? [s/n]\n");
            printf("\nSi presiona n será dirigido al menu principal\n");
            fflush(stdin);
            scanf(" %c", &control);
            if(control=='n' || control=='N')
            {
                funcionMenu(MENU_PRINCIPAL);
            }
        }

    }
    while(control=='s' || control=='S');
}


int validacionUsuarioAdmin(char usuarioAdmin[], int validos, char contraseniaAdmin[])
{
    for(int i=0; i<validos; i++)
    {
        if(strcmp(usuarioAdmin, a[i].usuario)==0)
        {
            if(strcmp(contraseniaAdmin, a[i].contrasenia)==0)
            {
                return 1;
            }
        }
    }
    return 0;
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

}
//Funciones de Fran (Torneos)
void crearTorneo(Torneo torneo)
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

Torneo cargaTorneo()
{
    Torneo T;
    printf("\nIngrese ID del torneo: \n");
    scanf("%s", T.idTorneo);

    int Existe = validacionIDTorneo(T.idTorneo);
    while(Existe == 0)
    {
        printf("Ingrese un ID de torneo valido: ");
        scanf("%s", T.idTorneo);
        Existe = validacionIDTorneo(T.idTorneo);
    }

    printf("Ingrese nombre del torneo: \n");
    scanf("%s", T.nombre);

    printf("Ingrese ID del juego: \n");
    scanf("%s", T.juego.idJuego);

    printf("Ingrese nombre del juego: (INGRESE NOMBRES SIN ESPACIOS) \n");
    scanf("%c", T.juego.nombre);

    printf("Ingrese genero del juego: PVP, FPS, Battle Royale, Extract Shooter... \n");
    scanf("%s", T.juego.genero);

    printf("Ingrese plataforma del juego: PC/Xbox/Playstation (PS) \n");
    scanf("%s", T.juego.plataforma);

    printf("Ingrese capacidad maxima del torneo: \n");
    scanf("%d", &T.capacidadMaxima);

    T.cuposDisponibles = T.capacidadMaxima; //Todos los cupos estan disponibles al inicio

    printf("Ingrese fecha de inicio (dd mm aaaa): \n");
    scanf("%d %d %d", &T.fechaInicio.dia, &T.fechaInicio.mes, &T.fechaInicio.anio);

    actualizarEstadoTorneo(T);

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

// Módulo de torneos:

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

int validacionIDTorneo(char idTorneo[])
{
    FILE *ArchivoTorneo = fopen("torneos.bin", "rb");
    if(ArchivoTorneo == NULL)
    {
        return 1; // Si no se puede abrir el archivo, asumimos que el ID es válido (no existen torneos)
    }

    Torneo T;
    int esValido = 1;

    while(fread(&T, sizeof(Torneo), 1, ArchivoTorneo) > 0)
    {
        if(strcmp(T.idTorneo, idTorneo) == 0)
        {
            printf("El ID del torneo ya existe. Ingrese un ID diferente.\n");
            esValido = 0;
            break;
        }
    }

    fclose(ArchivoTorneo);
    return esValido;
}

void modificarTorneoAEleccion(char idTorneo[])
{
    FILE *archivoTorneo = fopen("torneos.bin", "r+b");

    if(archivoTorneo!=NULL)
    {
        Torneo T;
        int encontrado = 0;

        while(fread(&T, sizeof(Torneo), 1, archivoTorneo) > 0)
        {
            if(strcmp(T.idTorneo, idTorneo) == 0)
            {
                encontrado = 1;
                T = modificarTorneo(T);

                fseek(archivoTorneo, -sizeof(Torneo), SEEK_CUR);
                fwrite(&T, sizeof(Torneo), 1, archivoTorneo);

                printf("Torneo modificado correctamente.\n");
                break;
            }
        }

        if(!encontrado)
        {
            printf("No se encontro un torneo con ese ID.\n");
        }
        fclose(archivoTorneo);
    }
    else
    {
        printf("No existe el archivo de torneos.\n");
    }
}

Torneo modificarTorneo(Torneo T)
{
    printf("\nEstos son los datos actuales del torneo:\n");
    mostrarTorneo(T);

   char respuesta = 's';
   printf ("Desea modificiar el nombre del torneo? S/N \n");
   fflush(stdin);
    scanf(" %c", &respuesta);
        if (respuesta == 's' || respuesta == 'S')
        {
            printf("Ingrese nuevo nombre del torneo: \n");
            scanf("%s", T.nombre);
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
            printf("ID: %s | Nombre: %s | Juego: %s | Cupos Disponibles: %d\n", T.idTorneo, T.nombre, T.juego.nombre, T.cuposDisponibles);
        }else{
            printf("No hay torneos abiertos disponibles en este momento.\n");
        }
}


/// funciones de videojuegos (mati)
int guardarVideojuego(Videojuego juego)
{
    FILE* archivo = fopen("videojuegos.bin", "ab");
    if (archivo == NULL)
    {
        printf("Error al abrir archivo.\n");
        return -1;
    }

    fwrite(&juego, sizeof(Videojuego), 1, archivo);
    fclose(archivo);

    printf("Videojuego guardado correctamente.\n");
    return 0;
}

int tieneNumero(char cadena[])
{
    int i = 0;

    while (cadena[i] != '\0')  // mientras no termine la palabra
    {
        if (cadena[i] >= '0' && cadena[i] <= '9')
            return 1; // tiene un número
        i++;
    }

    return 0;
}

Videojuego cargaVideojuego()
{
    Videojuego juego;


    printf("Ingrese ID del videojuego: ");
    scanf("%s", juego.idJuego);


    while (validacionIDVideojuego(juego.idJuego) == 1)
    {
        printf("ID existente. Ingrese otro: ");
        scanf("%s", juego.idJuego);
    }

    printf("Ingrese nombre: ");
    scanf("%s", juego.nombre);


    do
    {
        printf("Ingrese genero: ");
        scanf("%s", juego.genero);

        if (tieneNumero(juego.genero))
            printf("El genero no puede contener numeros.\n");

    }
    while (tieneNumero(juego.genero));


    do
    {
        printf("Ingrese plataforma: ");
        scanf("%s", juego.plataforma);

        if (tieneNumero(juego.plataforma))
            printf("La plataforma no puede contener numeros.\n");

    }
    while (tieneNumero(juego.plataforma));

    return juego;
}


int validacionIDVideojuego(char idJuego[])
{
    FILE* archivo = fopen("videojuegos.bin", "rb");
    if (archivo == NULL)
    {
        return 0; // basicamente el juego no esta repetido
    }

    Videojuego aux;
    while (fread(&aux, sizeof(Videojuego), 1, archivo) == 1)
    {
        if (strcmp(aux.idJuego,idJuego) == 0)
        {
            fclose(archivo);
            return 1; // si el juego ya existe osea esta repetido
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

            }
            while (tieneNumero(aux.genero));

            do
            {
                printf("Nueva plataforma: ");
                scanf("%s", aux.plataforma);

                if (tieneNumero(aux.plataforma))
                    printf("La plataforma no puede contener numeros.\n");

            }
            while (tieneNumero(aux.plataforma));

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
    if (archivo == NULL)
    {
        printf("No hay videojuegos cargados.\n");
        return;
    }

    Videojuego aux;

    printf("\n=== CATALOGO DE VIDEOJUEGOS ===\n");
    while (fread(&aux, sizeof(Videojuego), 1, archivo) == 1)
    {
        printf("ID: %s | Nombre: %s | Plataforma: %s\n",aux.idJuego, aux.nombre, aux.plataforma);
    }

    fclose(archivo);
}
int buscarTorneoPorID(char id[], Torneo *T, int *pos)
{
    int encontrado = 0;
    FILE* archivo = fopen("torneos.bin", "rb+");
    if (!archivo)
    {
        printf("el archivo no se abrio correctamente \n");
        return 0;
    }

    Torneo aux;
    while (fread(&aux, sizeof(Torneo), 1, archivo) == 1)
    {
        if (strcmp(aux.idTorneo, id) == 0)
        {
            *T = aux;
            *pos = ftell(archivo) - sizeof(Torneo);
            encontrado = 1;

        }
    }

    fclose(archivo);
    return encontrado;
}
int buscarUsuarioPorID(char id[], Usuario *U)
{
    int encontrado=0;
    FILE* archivo = fopen("usuario.bin", "rb");
    if (!archivo)
    {
        printf("el archivo no se abrio correctamente \n");
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
void registrarInscripcion()
{
    int continuar = 1;

    char idTorneo[10];
    char idUsuario[10];

    Torneo T;
    int posT;

    printf("Ingrese ID del torneo: ");
    scanf("%s", idTorneo);

    if (!buscarTorneoPorID(idTorneo, &T, &posT))
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
void verParticipantesTorneo()
{
    char idTorneo[10];
    printf("Ingrese ID del torneo: ");
    scanf("%s", idTorneo);

    Torneo T;
    int pos;
    if (!buscarTorneoPorID(idTorneo, &T, &pos))
    {
        printf("No existe un torneo con ese ID.\n");
        return;
    }

    FILE* archivo = fopen("inscripciones.bin", "rb");
    if (!archivo)
    {
        printf("No se pudo abrir inscripciones.\n");
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








//////////////////////////////////////////////////////////////////////////////////////////////////////
/// Funciones agregadas por Juani: ver/listar/agregar/modificar
void agregarModificarUsuario()
{
    Usuario u;
    Usuario aux;
    int encontrado = 0;

    printf("Ingrese ID del Usuario: ");
    fflush(stdin);
    fgets(u.idUsuario, sizeof(u.idUsuario), stdin);
    // quitar salto final si lo tiene
    u.idUsuario[strcspn(u.idUsuario, "\n")] = '\0';

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
                fgets(aux.nickname, sizeof(aux.nickname), stdin);
                aux.nickname[strcspn(aux.nickname, "\n")] = '\0';

                printf("Ingrese nueva contrasenia: ");
                fflush(stdin);
                fgets(aux.contrasenia, sizeof(aux.contrasenia), stdin);
                aux.contrasenia[strcspn(aux.contrasenia, "\n")] = '\0';

                printf("Ingrese nuevo email: ");
                fflush(stdin);
                fgets(aux.email, sizeof(aux.email), stdin);
                aux.email[strcspn(aux.email, "\n")] = '\0';

                printf("Ingrese nuevo pais: ");
                fflush(stdin);
                fgets(aux.pais, sizeof(aux.pais), stdin);
                aux.pais[strcspn(aux.pais, "\n")] = '\0';

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
    fgets(u.nickname, sizeof(u.nickname), stdin);
    u.nickname[strcspn(u.nickname, "\n")] = '\0';

    printf("Ingrese contrasenia: ");
    fflush(stdin);
    fgets(u.contrasenia, sizeof(u.contrasenia), stdin);
    u.contrasenia[strcspn(u.contrasenia, "\n")] = '\0';

    printf("Ingrese email: ");
    fflush(stdin);
    fgets(u.email, sizeof(u.email), stdin);
    u.email[strcspn(u.email, "\n")] = '\0';

    printf("Ingrese pais: ");
    fflush(stdin);
    fgets(u.pais, sizeof(u.pais), stdin);
    u.pais[strcspn(u.pais, "\n")] = '\0';

    printf("Ingrese nivel: ");
    scanf("%d", &u.nivel);

    buffer = fopen("usuario.bin", "ab");
    fwrite(&u, sizeof(Usuario), 1, buffer);
    fclose(buffer);

    printf("\nUsuario agregado correctamente.\n");
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

    while(fread(&u, sizeof(Usuario), 1, buffer) > 0)
    {
        printf("ID: %s | Nickname: %s\n", u.idUsuario, u.nickname);
    }

    fclose(buffer);
}

void verInfoDetalladaUsuario()
{
    char idBuscado[10];
    Usuario u;
    int encontrado = 0;

    printf("Ingrese el ID del usuario a buscar: ");
    fflush(stdin);
    fgets(idBuscado, sizeof(idBuscado), stdin);
    idBuscado[strcspn(idBuscado, "\n")] = '\0';

    FILE *buffer = fopen("usuario.bin", "rb");
    if(buffer == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    while(fread(&u, sizeof(Usuario), 1, buffer) > 0)
    {
        if(strcmp(u.idUsuario, idBuscado) == 0)
        {
            encontrado = 1;
            printf("\n--- INFORMACION DEL USUARIO ---\n");
            printf("ID: %s\n", u.idUsuario);
            printf("Nickname: %s\n", u.nickname);
            printf("Contrasenia: %s\n", u.contrasenia);
            printf("Email: %s\n", u.email);
            printf("Pais: %s\n", u.pais);
            printf("Nivel: %d\n", u.nivel);
            break;
        }
    }

    fclose(buffer);

    if(!encontrado)
        printf("\nNo se encontro el usuario.\n");
}


/// adicional



void rankingTorneo()
{
    char idTorneo[10];
    printf("Ingrese ID del torneo: ");
    scanf("%s", idTorneo);

    Torneo T;
    int pos;
    if (!buscarTorneoPorID(idTorneo, &T, &pos))
    {
        printf("No existe un torneo con ese ID.\n");
        return;
    }

    FILE* archi = fopen("inscripciones.bin", "rb");
    if (!archi)
    {
        printf("No se pudo abrir inscripciones.\n");
        return;
    }

    Inscripcion I;
    Ranking lista[200];
    int cant = 0;

    // Guardamos solo los usuarios  participan de este torneo
    while (fread(&I, sizeof(Inscripcion), 1, archi) == 1)
    {
        if (strcmp(I.idTorneo, idTorneo) == 0)
        {
            /// evitamos los duplicados
            int encontrado = 0;
            for (int i = 0; i < cant; i++)
            {
                if (strcmp(lista[i].idUsuario, I.idUsuario) == 0)
                {
                    encontrado = 1;

                }
            }


            if (!encontrado && cant < 200) // si no fue encontrado lo agregamos
            {
                strcpy(lista[cant].idUsuario, I.idUsuario);
                lista[cant].cantidadTorneos = 0;
                cant++;
            }
        }
    }

    fclose(archi);

    if (cant == 0)
    {
        printf("No hay participantes inscritos en este torneo.\n");
        return;
    }


    for (int i = 0; i < cant; i++)
    {
        FILE* archivo = fopen("inscripciones.bin", "rb");
        if (!archivo)
        {
            printf("Error al reabrir inscripciones.\n");
            return;
        }

        Inscripcion aux;

        while (fread(&aux, sizeof(Inscripcion), 1, archivo) == 1)
        {
            if (strcmp(aux.idUsuario, lista[i].idUsuario) == 0)
                lista[i].cantidadTorneos++;
        }

        fclose(archivo);
    }


    for (int i = 0; i < cant - 1; i++)
    {
        for (int j = 0; j < cant - i - 1; j++)
        {
            if (lista[j].cantidadTorneos < lista[j + 1].cantidadTorneos)
            {
                Ranking aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }

    /// Mostramos ranking
    printf("\n Ranking de participantes del torneo %s (por torneos jugados totales) \n", T.nombre);

    for (int i = 0; i < cant; i++)
    {
        Usuario U;
        if (buscarUsuarioPorID(lista[i].idUsuario, &U))
        {
            printf("%d) %s (ID: %s) - %d torneos jugados\n",i + 1,U.nickname,lista[i].idUsuario,lista[i].cantidadTorneos);
        }
        else
        {

            printf("%d) ID: %s - %d torneos jugados (usuario no encontrado)\n", i + 1, lista[i].idUsuario, lista[i].cantidadTorneos);
        }
    }

    printf("\n");
}

