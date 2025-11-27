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


/// prototipado agregado por mati
int guardarVideojuego(Videojuego juego);
int tieneNumero(char cadena[]);
Videojuego cargaVideojuego();
int validacionIDVideojuego(char idJuego[]);
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
        {
            char opcion[10];
            printf("\n\tADMINISTRADOR - Presione la opcion que desea:\n");
            printf("\n\t[1]-Cargar videojuego\n");
            printf("\n\t[2]-Modificar videojuego\n");
            printf("\n\t[3]-Ver catalogo videojuegos\n");
            printf("\n\t[4]-Regresar al MENU ADMINISTRADOR\n");
            scanf("%s", opcion);
            fflush(stdin);

            if(strcmp(opcion, "1") == 0)
            {
                Videojuego juego = cargaVideojuego();
                if(guardarVideojuego(juego))
                    printf("\nVideojuego cargado correctamente.\n");
                else
                    printf("\nError al guardar el videojuego.\n");
                system("pause");
                funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
            }
            else if(strcmp(opcion, "2") == 0)
            {
                verCatalogoVideojuegos();
                int idModificado;
                printf("\nIngrese ID del videojuego a modificar: ");
                scanf("%d", &idModificado);
                fflush(stdin);
                modificarVideojuego(idModificado);
                system("pause");
                funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
            }
            else if(strcmp(opcion, "3") == 0)
            {
                verCatalogoVideojuegos();
                system("pause");
                funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
            }
            else if(strcmp(opcion, "4") == 0)
            {
                funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
            }
            else
            {
                printf("\n\tOpcion invalida\n");
                system("pause");
                funcionMenu(MENU_ADMINISTRADOR_VIDEOJUEGOS);
            }
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

//INSCRIPCION
int validarTorneoAbierto(Torneo T)
{
    int validos = 0;

    if (strcmp(T.estado, "Abierto") == 0)
    {
        validos = 1;
    }

    return validos;
}

//INSCRIPCION
int validarCupos(Torneo T)
{
    int validos = 0;

    if (T.cuposDisponibles > 0)
    {
        validos = 1;
    }

    return validos;
}

//INSCRIPCION
void registrarInscripcion()
{
    int continuar = 1;

    char idTorneo[10];
    char idUsuario[10];

    Torneo T;
    int posT;

    printf("Ingrese ID del torneo: ");
    scanf("%s", idTorneo);

    if (!buscarTorneoPorID(idTorneo))
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
