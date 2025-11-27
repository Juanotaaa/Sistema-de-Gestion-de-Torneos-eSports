#include "Administrador.h"
#include "Usuario.h"
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


