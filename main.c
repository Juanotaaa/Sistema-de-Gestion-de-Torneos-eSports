#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define MIN_EMAIL 5
#define MAX_EMAIL 50
#define MIN_CONTRA 5
#define MAX_CONTRA 20
#define ARCHIVO_USUARIO "usuario.bin"

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
int validacionContrasenia(char contrasenia[]);
int validacionDeMail(char[]);
Usuario crearUsuario();
int guardarUsuario(Usuario, char[]);
void mostrarUsuario(Usuario usuario);
int leerArchivoUsuario(char archivo[]);


int main()
{
    Usuario usuario=crearUsuario();
    mostrarUsuario(usuario);
    guardarUsuario(usuario, ARCHIVO_USUARIO);
    leerArchivoUsuario(ARCHIVO_USUARIO);
   

    return 0;
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

    int dimension=strlen(email);
    int esValido=1;
    if(dimension<MIN_EMAIL || dimension>MAX_EMAIL){
        printf("\nEl email no cumple con la longitud de los requisitos, caracteres ingresados: %d\n", dimension);
        esValido=0;
    }

return esValido;
}



Usuario crearUsuario(){

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
    FILE* usuarioArchivo=fopen(archivo, "wb");

    if(!usuarioArchivo){
        printf("\nEl archivo no pudo abrirse\n");
        return 0;
    }

    fwrite(&x, sizeof(Usuario), 1, usuarioArchivo);

    fclose(usuarioArchivo);

return 1;
}

int leerArchivoUsuario(char archivo[]){

    printf("\nLeyendo el archivo\n");
    FILE* usuarioArchivo=fopen(archivo, "rb");

    if(!usuarioArchivo){
        printf("\nEl archivo no pudo abrirse\n");
        return 0;
    }

    Usuario x;

    while(!feof(usuarioArchivo)){
    
        fread(&x, sizeof(Usuario), 1, usuarioArchivo);
        if(!feof(usuarioArchivo)){
           mostrarUsuario(x);
        }
    }

    fclose(usuarioArchivo);
    return 1;
}

Usuario* asignarMemoriaUsuario(int dim){ //no es necesario la dimension con puntero porque el usuario te va a decir la dimension

    Usuario* x_calloc=NULL;

    x_calloc=(Usuario*)calloc(dim, sizeof(Usuario));

return x_calloc;
}


int redimensionarMemoriaUsuario(Usuario **x, int dim){

    int nuevaDim= dim;

    


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