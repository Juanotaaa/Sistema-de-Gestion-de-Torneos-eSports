#ifndef USUARIO_H
#define USUARIO_H

#define MIN_NICKNAME 5
#define MAX_NICKNAME 8
#define MIN_CONTRA 5
#define MAX_CONTRA 8
#define ARCHIVO_USUARIO "usuario.bin"
#define MIN_TELEFONO 8
#define MAX_TELEFONO 10

typedef struct stUsuario
{
    char idUsuario[10];
    char nickname[30];
    char contrasenia[20];
    char numTelefonico[50];
    char pais[30];
    int nivel;
} Usuario;

///PROTOTIPADOS
int validacionContrasenia(char contrasenia[]);
int validaciondeNickname(char nickname[]);
int crearUsuario(Usuario*u);
int guardarUsuario(Usuario, char[]);
int loginUsuario(Usuario *u, int * hayUsuarioLogueado);
int validacionUsuario(char archivo[], char usuario[], char contraseniaUsuario[]);
int validarUsuarioRepetido(char nickname[]);
int idUsuario();
int agregarInformacionUsuario(Usuario*info);
int validarNumTelefonico(char numTelefonico[]);
int validacionPaises(char Pais[]);
int validarNumTelefonicoRepetido(char* numTelefono);

#endif