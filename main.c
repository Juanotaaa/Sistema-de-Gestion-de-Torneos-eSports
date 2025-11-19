#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define MIN_EMAIL 5
#define MAX_EMAIL 50
#define MIN_CONTRA 5
#define MAX_CONTRA 20
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
    char idJuego[10]; // C�digo �nico del juego (ej. "LOL", "CS2")
    char nombre[50];
    char genero[30];
    char plataforma[20];
} Videojuego;

typedef struct stUsuario
{
    char idUsuario[10]; // ID de jugador �nico
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
    char idInscripcion[10];
    char idTorneo[10];
    char idUsuario[10];
    Fecha fechaInscripcion;
} Inscripcion;



///PROTOTIPADO
void funcionMenu(int menu);
int validacionContrasenia(char contrasenia[]);
int validacionDeMail(char[]);
Usuario crearUsuario();
int guardarUsuario(Usuario, char[]);
void mostrarUsuario(Usuario usuario);
int leerArchivoUsuario(char archivo[], Usuario* usuarios, int*dimension);
int redimensionarMemoriaUsuario(Usuario *x, int dim);
Usuario* asignarMemoriaUsuario(int dim);
Torneo cargaTorneo(); //Llevar a Main -Fran
int validacionIDTorneo(char idTorneo[]); //Llevar a Main -Fran
void crearTorneo(Torneo torneo); //Llevar a Main -Fran
void modificarTorneo(char idTorneo[]); //Llevar a Main -Fran

/// prototipado agregado por mati
int guardarVideojuego(Videojuego juego);
Videojuego cargaVideojuego();
int validacionIDVideojuego(char idJuego[]);
void modificarVideojuego(char idJuego[]);
void verCatalogoVideojuegos();

///prototipados juani
void verInfoDetalladaUsuario();
void verListadoUsuarios();
void agregarModificarUsuario();



int main()
{
    funcionMenu(MENU_PRINCIPAL);
    /*Usuario usuario=crearUsuario();
    mostrarUsuario(usuario);
    guardarUsuario(usuario, ARCHIVO_USUARIO);
    int dimension=0; //Este esta bien que no sea puntero porque en la funcion solamente se manejara un puntero a un solo elemento (no es un arreglo)
    Usuario* listaUsuarios=NULL; //Debe ser un puntero porque en la funcion ese puntero va a contener varios valores (sera un arreglo)
    leerArchivoUsuario(ARCHIVO_USUARIO, listaUsuarios, &dimension);
    printf("\ndimension actual es: %d\n", dimension);*/





    //free(listaUsuarios);
    //listaUsuarios=NULL;
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
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }
        if(opcion==2)
        {
            crearUsuario();
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
            funcionMenu(MENU_ADMINISTRADOR_LOGEADO);/// lo llevo a mi parte
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
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }


        break;
    case MENU_ADMINISTRADOR_LOGEADO:
        printf("\n\tPresione la opcion que desea:\n");
        printf("\n\t[1]-Agregar torneo\n");
        printf("\n\t[2]-Modificar torneo\n");
        printf("\n\t[3]-Modificar/Agregar Usuarios\n");
        printf("\n\t[4]-Ver usuarios\n");
        printf("\n\t[5]-Ver usuario por ID\n");
        printf("\n\t[6]-Agregar Videojuego\n");
        printf("\n\t[7]-Modificar Videojuego\n");
        printf("\n\t[8]-ver catalogo de Videojuegos\n");
        printf("\n\t[9]-Cerrar sesion\n");
        fflush(stdin);
        scanf("%d", &opcion);
        if(opcion==1)
        {
            crearTorneo(cargaTorneo());
        }
        if(opcion==2)
        {
            char idTorneo[10];
            printf("Ingrese el ID del torneo a modificar: ");
            scanf("%s", idTorneo);
            modificarTorneo(idTorneo);
        }
        if (opcion==3)
        {
           agregarModificarUsuario();

        }
        if (opcion==4)
        {
            verListadoUsuarios();

        }
         if (opcion==5)
        {
            verInfoDetalladaUsuario();

        }
        /// parte echa por mi para mostrar a los chicos
        if(opcion==6)
        {
            Videojuego juego = cargaVideojuego();
            guardarVideojuego(juego);
        }
        if (opcion==7)
        {
            char idModificado[10];
            printf("ingrese ID del Videojuego a modificar: ");
            scanf("%s",idModificado);
            modificarVideojuego(idModificado);
        }
        if (opcion==8)
        {
            verCatalogoVideojuegos();
        }
        if (opcion==9)
        {
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
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
        if(caracterActual=='1' || caracterActual=='2'|| caracterActual=='3'|| caracterActual=='4'|| caracterActual=='5'
                || caracterActual=='6'|| caracterActual=='7'|| caracterActual=='8'|| caracterActual=='9'|| caracterActual=='0')
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

    //Esta es una funcion auxiliar para validar el mail, creamos una variable dimension para que guarde los datos del email
    //cargado, con strlen podemos contar cuantos caracteres tiene. Luego se crea una variable "esValido" que la igualamos a 1.
    //Hacemos un if donde validamos el tamaño, usamos || porque no pide que sean las dos condiciones al mismo tiempo.

    int dimension=strlen(email);
    int esValido=1;
    if(dimension<MIN_EMAIL || dimension>MAX_EMAIL)
    {
        printf("\nEl email no cumple con la longitud de los requisitos, caracteres ingresados: %d\n", dimension);
        esValido=0;
    }

    return esValido;
}



Usuario crearUsuario()
{

    //Funcion donde creamos el usuario, al comienzo hace un recordatorio de todas las condiciones para validar
    //Creamos 3 variables, un char (para usar como condicion de corte en el do while) y dos variables de entero
    //para igualar despues las funciones auxiliares. Realizo un do while porque mi intencion es que al menos
    //el ciclo se haga una vez, hago un bucle tanto para el email como para la contraseña. Retorno el usuario.

    Usuario usuario;
    printf("\nRecuerde que para registrarse, debe ingresar un email valido y una contrasenia que cumpla con los siguientes requisitos:\n");
    printf("-Caracteres minimo: 5\n");
    printf("-Minimo una mayuscula\n");
    printf("-Minimo un numero\n");

    char control='s';
    int valMail;
    int valContra;

    do
    {
        printf("\nIngrese su mail:\n");
        fflush(stdin);
        scanf("%s", usuario.email);

        valMail=validacionDeMail(usuario.email);
        if(valMail!=1)
        {
            printf("\nDesea ingresar otro mail? [s/n]\n");
            scanf(" %c", &control);
            fflush(stdin);

        }
    }
    while((control=='s' || control=='S') && valMail!=1);


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

int leerArchivoUsuario(char archivo[], Usuario* usuarios, int*dimension)
{

    printf("\nLeyendo el archivo\n");
    FILE* usuarioArchivo=fopen(archivo, "rb");

    if(!usuarioArchivo)
    {
        printf("\nEl archivo no pudo abrirse\n");
        return 0;
    }

    Usuario x;
    int i=0;
    (*dimension)=i+1;

    while(fread(&x, sizeof(Usuario), 1, usuarioArchivo)>0)
    {
        printf("\nLeyendo linea %d\n", *dimension); //para que me lo tome como valor hay que agregarle *
        mostrarUsuario(x);
        /*if(redimensionarMemoriaUsuario(usuarios, (int)(*dimension))){
            printf("\nLinea leida %d", *dimension);
            usuarios[i]=x;
            i++;
            (*dimension)=i+1;
        }*/

    }

    fclose(usuarioArchivo);
    return 1;
}

Usuario* asignarMemoriaUsuario(int dim)  //no es necesario la dimension con puntero porque el usuario te va a decir la dimension
{

    Usuario* x_calloc=NULL;

    x_calloc=(Usuario*)calloc(dim, sizeof(Usuario));

    return x_calloc;
}


int redimensionarMemoriaUsuario(Usuario *x, int dim)
{

    int nuevaDim=dim;

    Usuario* aux=(Usuario*)realloc(x, nuevaDim* sizeof(Usuario));

    if(aux!=NULL)
    {
        x=aux;
        dim=nuevaDim;
        return 1;
    }
    else
    {
        printf("\nError al redimensionar el arreglo\n");
        return 0;
    }

}

void mostrarUsuario(Usuario usuario)
{

    //Estoy mostrando todos los datos momentaneamente, solo para verificar que cargan bien
    printf("Usuario: %s\n", usuario.nickname);
    printf("ID: %s\n", usuario.idUsuario);
    printf("Email: %s\n", usuario.email);
    printf("Pais: %s\n", usuario.pais);
    printf("Contrasenia: %s\n", usuario.contrasenia);
    printf("Nivel: %d\n", usuario.nivel);

}


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
    //Funcion para cargar los datos de un torneo nuevo
    Torneo T;

    printf("\nIngrese ID del torneo: \n");
    scanf("%s", T.idTorneo);

    int Existe = validacionIDTorneo(T.idTorneo); //Validacion si ya existe el Torneo
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

    printf("Ingrese nombre del juego: \n");
    scanf("%s", T.juego.nombre);

    printf("Ingrese genero del juego: PVP, FPS, Battle Royale, Extract Shooter... \n");
    scanf("%s", T.juego.genero);

    printf("Ingrese plataforma del juego: PC/Xbox/Playstation (PS) \n");
    scanf("%s", T.juego.plataforma);

    printf("Ingrese capacidad maxima del torneo: \n");
    scanf("%d", &T.capacidadMaxima);

    T.cuposDisponibles = T.capacidadMaxima; //Todos los cupos estan disponibles al inicio

    printf("Ingrese fecha de inicio (dd mm aaaa): \n");
    scanf("%d %d %d", &T.fechaInicio.dia, &T.fechaInicio.mes, &T.fechaInicio.anio);

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

    strcpy(T.estado, "Abierto"); //Todos los torneos comienzan en estado "Abierto"

    return T;
}

int validacionIDTorneo(char idTorneo[])  //Chequea que el ID no exista desde antes -Fran
{
    FILE *ArchivoTorneo = fopen("torneos.bin", "rb");
    if(ArchivoTorneo == NULL)
    {
        printf("No se pudo abrir el archivo de torneos.\n");
        return 1; // Si no se puede abrir el archivo, asumimos que el ID es válido
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

void modificarTorneo(char idTorneo[])  //MODULARIZAR O MEJORAR CON SWITCH PARA CADA CAMPO -F
{
    FILE *ArchivoTorneo = fopen("torneos.bin", "r+b");
    if(ArchivoTorneo == NULL)
    {
        printf("No se pudo abrir el archivo de torneos.\n");
        return;
    }

    Torneo T;
    int encontrado = 0;
    char respuesta = 's';

    while(fread(&T, sizeof(Torneo), 1, ArchivoTorneo) > 0)
    {
        if(strcmp(T.idTorneo, idTorneo) == 0)
        {
            encontrado = 1;
            printf("Torneo encontrado. Ingrese los nuevos datos:\n");

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
            }

            printf("Desea modificar el premio total del torneo? S/N \n");
            fflush(stdin);
            scanf(" %c", &respuesta);
            if (respuesta == 's' || respuesta == 'S')
            {
                printf("Ingrese nuevo premio total del torneo: \n");
                scanf("%f", &T.premioTotal);
            }

            printf("Desea modificar el estado del torneo? S/N \n");
            fflush(stdin);
            scanf(" %c", &respuesta);
            if (respuesta == 's' || respuesta == 'S')   //Se asegura que los profes no se pasen de vivos (<3) -Fran
            {
                int estadoValido = 0;
                do
                {
                    printf("Ingrese nuevo estado del torneo (Abierto, EnCurso, Finalizado): \n");
                    scanf("%s", T.estado);
                    if (strcmp(T.estado, "Abierto") == 0 || strcmp(T.estado, "EnCurso") == 0 || strcmp(T.estado, "Finalizado") == 0)
                    {
                        estadoValido = 1;
                    }
                    else
                    {
                        printf("Estado inválido. Los valores válidos son: Abierto, EnCurso, Finalizado.\n");
                    }
                }
                while (!estadoValido);
            }

            fseek(ArchivoTorneo, -sizeof(Torneo), SEEK_CUR); // Mover el puntero al inicio del registro encontrado
            fwrite(&T, sizeof(Torneo), 1, ArchivoTorneo); //Sobrescribir el registro con los nuevos datos
            printf("Torneo modificado exitosamente.\n");
            break;
        }
    }

    if(!encontrado)
    {
        printf("No se encontro un torneo con el ID proporcionado.\n");
    }
    fclose(ArchivoTorneo);
}
/// aca funciones nuevas mati
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
/*
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

    printf("Ingrese genero: ");
    scanf("%s", juego.genero);

    printf("Ingrese plataforma: ");
    scanf("%s", juego.plataforma);

    return juego;
}
*/
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
    int id;
    int control;

do {
    printf("Ingrese el ID: ");
    control = scanf("%d", &id);

    if (control == 0)
        {
        printf("Error: debe ingresar un numero\n");
        fflush(stdin);
        getchar();
        }

} while (control == 0);

    while (validacionIDVideojuego(juego.idJuego))
    {
        printf("ID existente. Ingrese otro: ");
        scanf("%s", juego.idJuego);
    }

    printf("Ingrese nombre: ");
    scanf("%s", juego.nombre);/// en el nombre no le pongo validacion ya que pueden aparecer juegos como minecraft 2


    do
    {
        printf("Nuevo genero: ");
        scanf("%s", juego.genero);

        if (tieneNumero(juego.genero))
            printf("El genero no puede contener numeros.\n");

    }
    while (tieneNumero(juego.genero));


    do
    {
        printf("Nueva plataforma: ");
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

//////////////////////////////////////////////////////////////////////////////////////////////////////
void agregarModificarUsuario()
{
    Usuario u;
    Usuario aux;
    int encontrado = 0;

    printf("Ingrese ID del Usuario: ");
    fflush(stdin);
    scanf("%s", u.idUsuario);
    
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
                scanf("%s", u.nickname);

                printf("Ingrese nueva contrasenia: ");
                fflush(stdin);
                scanf("%s", u.contrasenia);

                printf("Ingrese nuevo email: ");
                fflush(stdin);
                scanf("%s", u.email);

                printf("Ingrese nuevo pais: ");
                fflush(stdin);
                scanf("%s", u.pais);

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

    // Si no existe → agregar nuevo
    printf("\nUsuario no encontrado. Se procedera a agregarlo.\n");

    printf("Ingrese nickname: ");
    fflush(stdin);
    scanf("%s", u.nickname);

    printf("Ingrese contrasenia: ");
    fflush(stdin);
    scanf("%s", u.contrasenia);

    printf("Ingrese email: ");
    fflush(stdin);
    scanf("%s", u.email);

    printf("Ingrese pais: ");
    fflush(stdin);
    scanf("%s", u.pais);

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
    scanf("%s", idBuscado);

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
