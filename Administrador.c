#include "Administrador.h"
#include <stdio.h>
#include <string.h>

const Administrador a[] =
{
    {"EduProfe", "EduElMejor", "Eduardo Mango", "admin"},
    {"Kevito", "kevin123", "Kevin", "admin"},
    {"Aye", "ayecrack", "Ayelen", "admin" }
};
const int totalAdmins = sizeof(a) / sizeof(a[0]);


int loginAdministrador()
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
            //funcionMenu(MENU_ADMINISTRADOR_LOGEADO);
            return 1;
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
                //funcionMenu(MENU_PRINCIPAL);
                return 0;
            }
        }

    }
    while(control=='s' || control=='S');

return 0;
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