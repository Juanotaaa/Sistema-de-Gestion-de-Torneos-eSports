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
typedef struct stVideojuego {
    char idJuego[10]; // C�digo �nico del juego (ej. "LOL", "CS2")
    char nombre[50];
    char genero[30];
    char plataforma[20];
} Videojuego;

typedef struct stUsuario {
    char idUsuario[10]; // ID de jugador �nico
    char nickname[30];
    char contrasenia[20];
    char email[50];
    char pais[30];
    int nivel; // Nivel de experiencia (ej. 1 a 10)
} Usuario;

typedef struct stAdministrador {
    char usuario[20]; // Usuario para el login
    char contrasenia[20];
    char nombreCompleto[50];
    char rol[20]; // Ej: "Organizador", "Staff"
} Administrador;

typedef struct stFecha {
    int dia;
    int mes;
    int anio;
} Fecha;

typedef struct stTorneo {
    char idTorneo[10];
    char nombre[50];
    Videojuego juego;
    int capacidadMaxima;
    int cuposDisponibles;
    Fecha fechaInicio;
    float premioTotal;
    char estado[15]; // "Abierto", "En Curso", "Finalizado"
} Torneo;

typedef struct stInscripcion {
    char idInscripcion[10];
    char idTorneo[10];
    char idUsuario[10];
    Fecha fechaInscripcion;
} Inscripcion;



///Prototipado:
void funcionMenu(int menu);
int validacionContrasenia(char contrasenia[]);
int validacionDeMail(char[]);
Usuario crearUsuario();
int guardarUsuario(Usuario, char[]);
void mostrarUsuario(Usuario usuario);
int leerArchivoUsuario(char archivo[], Usuario* usuarios, int*dimension);
int redimensionarMemoriaUsuario(Usuario *x, int dim);
Usuario* asignarMemoriaUsuario(int dim);

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

void funcionMenu(int menu){

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
        if(opcion==1){
            funcionMenu(MENU_USUARIO);
        }else if(opcion==2){
            funcionMenu(MENU_ADMINISTRADOR);
        }else{
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
        if(opcion==1){
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }if(opcion==2){
            crearUsuario();
            funcionMenu(MENU_USUARIO);
        }if(opcion==3){
            funcionMenu(MENU_PRINCIPAL);
        }

break;
case MENU_ADMINISTRADOR:
    printf("\n\tPresione la opcion que desea:\n");
    printf("\n\t[1]-Ingresar\n");
    printf("\n\t[2]-Regresar al MENU PRINCIPAL\n");
    scanf("%d", &opcion);
    fflush(stdin);
        if(opcion==1){
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }if(opcion==2){
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
        if(opcion==1){
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }if(opcion==2){
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }if (opcion==3){
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }if (opcion==4){
           printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }
        
    
break;
case MENU_ADMINISTRADOR_LOGEADO:
    printf("\n\tPresione la opcion que desea:\n");
    printf("\n\t[1]-Agregar torneo\n");
    printf("\n\t[2]-Modificar torneo\n"); 
    printf("\n\t[3]-Ver ganancias\n");
    printf("\n\t[4]-Ver usuarios\n");
    printf("\n\t[5]-Cerrar sesion\n");
    fflush(stdin);
    scanf("%d", &opcion);
         if(opcion==1){
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }if(opcion==2){
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }if (opcion==3){
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }if (opcion==4){
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }if (opcion==5){
            printf("\nTodavia no hay funcion, REPARTIRSE LA TAREA!!");
        }

break;
default:
    break;
}


}




int validacionContrasenia(char contrasenia[]){

    int dimension=strlen(contrasenia);
    int esValido=1;
    if(dimension<MIN_CONTRA || dimension>MAX_CONTRA){
        printf("\nLa contrasenia no cumple con la longitud de los requisitos, caracteres ingresados: %d\n", dimension);
        esValido=0;
    }
    char caracterActual;
    for(int i=0; i<dimension; i++){
        caracterActual=contrasenia[i];
        if(caracterActual=='1' || caracterActual=='2'|| caracterActual=='3'|| caracterActual=='4'|| caracterActual=='5'
        || caracterActual=='6'|| caracterActual=='7'|| caracterActual=='8'|| caracterActual=='9'|| caracterActual=='0'){
            break;
        }
        if(i==dimension-1){
            printf("\nContrasenia invalida, no olvide que se requiere al menos un numero\n");
            esValido=0;
        }
    }


return esValido;
}



int validacionDeMail(char email[]){

    //Esta es una funcion auxiliar para validar el mail, creamos una variable dimension para que guarde los datos del email
    //cargado, con strlen podemos contar cuantos caracteres tiene. Luego se crea una variable "esValido" que la igualamos a 1.
    //Hacemos un if donde validamos el tamaño, usamos || porque no pide que sean las dos condiciones al mismo tiempo.

    int dimension=strlen(email);
    int esValido=1;
    if(dimension<MIN_EMAIL || dimension>MAX_EMAIL){
        printf("\nEl email no cumple con la longitud de los requisitos, caracteres ingresados: %d\n", dimension);
        esValido=0;
    }

return esValido;
}


 
Usuario crearUsuario(){

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

    do{
        printf("\nIngrese su mail:\n");
        fflush(stdin);
        scanf("%s", usuario.email);

            valMail=validacionDeMail(usuario.email);
            if(valMail!=1){
                printf("\nDesea ingresar otro mail? [s/n]\n");
                scanf(" %c", &control);
                fflush(stdin);

            }
    } while((control=='s' || control=='S') && valMail!=1);
    

    do{
        printf("\nIngrese una contrasenia:\n");
        fflush(stdin);
        scanf("%s", usuario.contrasenia);

            valContra=validacionContrasenia(usuario.contrasenia);
            if(valContra!=1){
                printf("\nDesea ingresar otra contrasenia? [s/n]\n");
                scanf(" %c", &control);
                fflush(stdin);

            }
    } while((control=='s' || control=='S') && valContra!=1);
    

return usuario;
}



int guardarUsuario(Usuario x, char archivo[]){

    printf("\nGuardando en archivo\n");
    FILE* usuarioArchivo=fopen(archivo, "ab");

    if(!usuarioArchivo){
        printf("\nEl archivo no pudo abrirse\n");
        return 0;
    }

    fwrite(&x, sizeof(Usuario), 1, usuarioArchivo);

    fclose(usuarioArchivo);

return 1;
}

int leerArchivoUsuario(char archivo[], Usuario* usuarios, int*dimension){

    printf("\nLeyendo el archivo\n");
    FILE* usuarioArchivo=fopen(archivo, "rb");

    if(!usuarioArchivo){
        printf("\nEl archivo no pudo abrirse\n");
        return 0;
    }

    Usuario x;
    int i=0;
    (*dimension)=i+1;

    while(fread(&x, sizeof(Usuario), 1, usuarioArchivo)>0){
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

Usuario* asignarMemoriaUsuario(int dim){ //no es necesario la dimension con puntero porque el usuario te va a decir la dimension

    Usuario* x_calloc=NULL;

    x_calloc=(Usuario*)calloc(dim, sizeof(Usuario));

return x_calloc;
}


int redimensionarMemoriaUsuario(Usuario *x, int dim){

    int nuevaDim=dim;

    Usuario* aux=(Usuario*)realloc(x, nuevaDim* sizeof(Usuario));
    
    if(aux!=NULL){
        x=aux;
        dim=nuevaDim;
        return 1;
    }else{
        printf("\nError al redimensionar el arreglo\n");
        return 0;
    }

}

void mostrarUsuario(Usuario usuario){

    //Estoy mostrando todos los datos momentaneamente, solo para verificar que cargan bien
    printf("Usuario: %s\n", usuario.nickname);
    printf("ID: %s\n", usuario.idUsuario);
    printf("Email: %s\n", usuario.email);
    printf("Pais: %s\n", usuario.pais);
    printf("Contrasenia: %s\n", usuario.contrasenia);
    printf("Nivel: %d\n", usuario.nivel);

}