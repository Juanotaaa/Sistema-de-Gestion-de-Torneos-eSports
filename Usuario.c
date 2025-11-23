#include "Usuario.h"
#include <stdio.h>
#include <string.h>

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
int loginUsuario(Usuario *u, int* hayUsuarioLogueado)
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
                    *hayUsuarioLogueado = 1;
                    break;
                }
            }

            fclose(f);
            //funcionMenu(MENU_USUARIO_LOGEADO);
            return 1;
        }
        else
        {
            printf("\nError al ingresar datos\n");
            printf("\nDesea intentarlo de nuevo? [s/n]\n");
            fflush(stdin);
            scanf(" %c", &control);
            if(control=='n' || control=='N')
            {
                //funcionMenu(MENU_PRINCIPAL);
                return 0;
            }
        }

    } while(control == 's' || control == 'S');

return 0;
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