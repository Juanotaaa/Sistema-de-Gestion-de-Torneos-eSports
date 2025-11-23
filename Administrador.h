#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H



typedef struct stAdministrador
{
    char usuario[20];
    char contrasenia[20];
    char nombreCompleto[50];
    char rol[20];
} Administrador;

/// PROTIPADOS
int loginAdministrador();
int validacionUsuarioAdmin(char usuarioAdmin[], int validos, char contraseniaAdmin[]);

#endif