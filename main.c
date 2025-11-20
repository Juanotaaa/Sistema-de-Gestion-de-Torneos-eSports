#include <stdio.h>
#include <stdlib.h>
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
    char idUsuario[10];
    char nickname[30];
    char contrasenia[20];
    char email[50];
    char pais[30];
    int nivel;
} Usuario;

typedef struct stAdministrador
{
    char usuario[20];
    char contrasenia[20];
    char nombreCompleto[50];
    char rol[20];
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
    char estado[15];
} Torneo;

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

/* Administradores hardcodeados */
const Administrador a[] =
{
    {"EduProfe", "EduElMejor", "Eduardo Mango", "admin"},
    {"Kevito", "kevin123", "Kevin", "admin"}
};
const int totalAdmins = sizeof(a) / sizeof(a[0]);


Usuario usuarioActual;
int hayUsuarioLogueado = 0;


///PROTOTIPADO
void funcionMenu(int menu);
void loginAdministrador();
int validacionUsuarioAdmin(char usuarioAdmin[], int validos, char contraseniaAdmin[]);
int validacionContrasenia(char contrasenia[]);
int validaciondeNickname(char nickname[]);
Usuario crearUsuario();
int guardarUsuario(Usuario, char[]);
void loginUsuario(Usuario *u);
int validacionUsuario(char archivo[], char usuario[], char contraseniaUsuario[]);
void salirDeLaApp();
void mostrarTorneos(Torneo t);
int verListadoTorneos();

//prototipado de torneos
//prototipado de fran
Torneo cargaTorneo(); //Llevar a Main -Fran
int buscarTorneoPorID(char id[], Torneo* T, int* pos);
int validacionIDTorneo(char idTorneo[]); //Llevar a Main -Fran
void crearTorneo(); //Llevar a Main -Fran
Torneo modificarTorneo(Torneo idTorneo); //Llevar a Main -Fran
int fechaUnica(Fecha f);
int fechaAnterior(Fecha a, Fecha b);
void actualizarEstadoTorneo(Torneo* T);
void modificarTorneoAEleccion(char idTorneo[]);
void verTorneosAbiertosYCuposDisponibles();
void mostrarTorneosAbiertos(Torneo T);
//prototipado nuevo de modificaciones de cande
int buscarTorneo(char idTorneo[], Torneo * torneo);
Torneo * torneoArrDinamico(int* dim);
int contarTorneos();
void guardarListaTorneo(Torneo* listaTorneo, int dim);

/// prototipado agregado por mati
int guardarVideojuego(Videojuego juego);
int tieneNumero(char cadena[]);
Videojuego cargaVideojuego();
int validacionIDVideojuego(char idJuego[]);
void modificarVideojuego(char idJuego[]);
void verCatalogoVideojuegos();

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
        scanf("%d", &opcion);
        fflush(stdin);

        if(opcion==1)
        {
            Usuario u;
            loginUsuario(&u);
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
        printf("\n\t[1]-Ver mi perfil\n");
        printf("\n\t[2]-Ver torneos abiertos\n");
        printf("\n\t[3]-Ver catálogo de videojuegos\n");
        printf("\n\t[4]-Registrarme a un torneo\n");
        printf("\n\t[5]-Cerrar sesión\n");
        printf("\n\t[6]-Regresar al MENU PRINCIPAL\n");
        scanf("%d",&opcion);

        if(opcion==1)
        {
            mostrarPerfilUsuario(usuarioActual);
            system("pause");
            funcionMenu(MENU_USUARIO_LOGEADO);
        }
        if(opcion==2)
        {
            verTorneosAbiertosYCuposDisponibles();
                        system("pause");
            funcionMenu(MENU_USUARIO_LOGEADO);
        }
        if(opcion==3)
        {
            verCatalogoVideojuegos();
                        system("pause");
            funcionMenu(MENU_USUARIO_LOGEADO);
        }
        if(opcion==4)
        {
            registrarInscripcion();
            system("pause");
            funcionMenu(MENU_USUARIO_LOGEADO);
        }
        if(opcion==5)
        {
            hayUsuarioLogueado = 0;
            system("pause");
            funcionMenu(MENU_PRINCIPAL);
        }
        if(opcion==6)
        {
            funcionMenu(MENU_PRINCIPAL);
        }
        break;

    case MENU_ADMINISTRADOR_LOGEADO:
        printf("\n\tADMINISTRADOR - Presione la opcion que desea:\n");
        printf("\n\t[1]-Ver torneos\n");
        printf("\n\t[2]-Crear torneo\n");
        printf("\n\t[3]-Modificar torneo\n");
        printf("\n\t[4]-Ver torneos abiertos\n");
        printf("\n\t[5]-Cargar videojuego\n");
        printf("\n\t[6]-Modificar videojuego\n");
        printf("\n\t[7]-Ver catalogo videojuegos\n");
        printf("\n\t[8]-Registrar inscripcion\n");
        printf("\n\t[9]-Ver participantes de un torneo\n");
        printf("\n\t[10]-Torneos sin participantes\n");
        printf("\n\t[11]-Regresar al menu principal\n");
        scanf("%d",&opcion);

        if(opcion==1)
        {
            verListadoTorneos();
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(opcion==2)
        {
            crearTorneo();
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(opcion==3)
        {
            char idTorneo[10];
            printf("Ingrese el ID del torneo a modificar: ");
            scanf("%s", idTorneo);
            modificarTorneoAEleccion(idTorneo);
            system("pause");
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);

        }
        if(opcion==4)
        {
            verTorneosAbiertosYCuposDisponibles();
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(opcion==5)
        {
            Videojuego juego = cargaVideojuego();
            guardarVideojuego(juego);
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(opcion==6)
        {
            char idModificado[10];
            printf("Ingrese ID del videojuego a modificar: ");
            scanf("%s", idModificado);
            modificarVideojuego(idModificado);
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(opcion==7)
        {
            verCatalogoVideojuegos();
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(opcion==8)
        {
            registrarInscripcion();
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(opcion==9)
        {
            verParticipantesTorneo();
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(opcion==10)
        {
            torneosSinParticipantes();
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
        }
        if(opcion==11)
        {
            funcionMenu(MENU_PRINCIPAL);
        }
        break;

    default:
        break;
    }
}


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

void loginUsuario(Usuario *u)
{
    char contraseniaUsuario[20];
    char usuario[20];
    char control='n';
    int valUsuario;

    do
    {
        printf("\n\tIngrese su usuario:\n");
        fflush(stdin);
        scanf("%s", usuario);

        printf("\n\tIngrese su contrasenia\n");
        fflush(stdin);
        scanf("%s", contraseniaUsuario);

        valUsuario = validacionUsuario(ARCHIVO_USUARIO, usuario, contraseniaUsuario);

        if(valUsuario == 1)
        {
            printf("\nUsted se ha logeado correctamente\n");

            strcpy(u->nickname, usuario);
            strcpy(u->contrasenia, contraseniaUsuario);

            FILE *f = fopen(ARCHIVO_USUARIO, "rb");
            Usuario aux;

            while(fread(&aux, sizeof(Usuario), 1, f) > 0)
            {
                if(strcmp(aux.nickname, u->nickname) == 0)
                {
                    *u = aux;
                    usuarioActual = aux;
                    hayUsuarioLogueado = 1;
                    break;
                }
            }

            fclose(f);
            funcionMenu(MENU_USUARIO_LOGEADO);
            return;
        }
        else
        {
            printf("\nError al ingresar datos\n");
            printf("\nDesea intentarlo de nuevo? [s/n]\n");
            fflush(stdin);
            scanf(" %c", &control);
        }

    } while(control == 's' || control == 'S');
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
    char control='n';
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
            return;
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
                return;
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
int buscarTorneoPorID(char id[], Torneo *T, int *pos)
{
    int encontrado = 0;
    FILE* archivo = fopen("torneos.bin", "rb+");
    if (!archivo)
    {
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
            break;
        }
    }

    fclose(archivo);
    return encontrado;
}

Torneo cargaTorneo()
{
    Torneo T;
    char id[10];
    int pos;

    printf("\nIngrese ID del torneo: \n");
    scanf("%9s", id);

    int Existe = buscarTorneoPorID(id, &T, &pos);

    while (Existe == 0)
    {
        printf("ID ya existente. Ingrese otro ID: \n");
        scanf("%9s", id);

        Existe = buscarTorneoPorID(id, &T, &pos);
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

    guardarListaTorneo(&listaTorneo, dim);
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
void guardarListaTorneo(Torneo* listaTorneo, int dim){

    FILE* ArchivoTorneo=fopen("torneo.bin", "wb");

    if(!ArchivoTorneo){
        printf("\nNo se pudo abrir el archivo\n");
        return;
    }

    fwrite(listaTorneo, sizeof(Torneo), dim, ArchivoTorneo);

    fclose(ArchivoTorneo);

return;
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
                gets(aux.email);

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
    gets(u.email);

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
    if (!buscarTorneoPorID(idTorneo, &T, &pos))
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
               u.idUsuario, u.nickname, u.email, u.pais, u.nivel);
    }
    fclose(buffer);
}

void mostrarPerfilUsuario(Usuario u)
{
    printf("\n--- PERFIL USUARIO ---\n");
    printf("ID: %s\n", u.idUsuario);
    printf("Nickname: %s\n", u.nickname);
    printf("Email: %s\n", u.email);
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