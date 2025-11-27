#include "Usuario.h"
#include <stdio.h>
#include <string.h>

const char Paises[100][100]={"Argentina", "Chile", "Uruguay", "Mexico", "Colombia", "Venezuela",
    "Peru", "Estados Unidos", "España", "Japon", "Italia", "Francia", "Portugal", "Otro"};
const int cantPaises=14;

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
        printf("\nEl nombre de Usuario no cumple con la longitud de los requisitos, caracteres ingresados: %d\n", dimension);
        esValido=0;
    }
    return esValido;
}

int crearUsuario(Usuario* u)
{

    printf("\nRecuerde que para registrarse, debe ingresar: un nombre de usuario que no este siendo utilizado y que cumpla con el siguiente requisito:\n");
    printf("-Caracteres minimo: 5\n");
    printf("-Caracteres maximos: 8\n");
    printf("\nAl mismo tiempo la contrasenia debera cumplir con los siguientes requisitos:\n");
    printf("-Caracteres minimo: 5\n");
    printf("-Caracteres maximos: 8\n");
    printf("-Minimo un numero\n");

    char control='s';
    int valNickname;
    int valContra;
    int valRepetido;

    do
    {
        printf("\nIngrese su nombre de Usuario:\n");
        fflush(stdin);
        scanf("%s", u->nickname);

        valNickname=validaciondeNickname(u->nickname);
        if(valNickname!=1)
        {
            printf("\nDesea ingresar otro nombre de Usuario? [s/n]\n");
            scanf(" %c", &control);
            fflush(stdin);
        }else{
            valRepetido=validarUsuarioRepetido(u->nickname);
            if(valRepetido!=1){
                printf("\nDesea ingresar otro nombre de Usuario? [s/n]\n");
                scanf(" %c", &control);
                fflush(stdin);
            }

        }

        if(control=='n' || control=='N'){
            return 0;
        }
    }
    while((control=='s' || control=='S') && (valNickname!=1 || valRepetido!=1));

    do
    {
        printf("\nIngrese una contrasenia:\n");
        fflush(stdin);
        scanf("%s", u->contrasenia);

        valContra=validacionContrasenia(u->contrasenia);
        if(valContra!=1)
        {
            printf("\nDesea ingresar otra contrasenia? [s/n]\n");
            scanf(" %c", &control);
            fflush(stdin);
        }

        if(control=='n' || control=='N'){
            return 0;
        }

    }
    while((control=='s' || control=='S') && valContra!=1);

    int id=idUsuario();

    sprintf(u->idUsuario, "%d", id);

    return 1;
}

int agregarInformacionUsuario(Usuario*info){

    printf("\nPara poder continuar usted debera completar la siguiente informacion\n");
    printf("\nUna vez completado estos datos, sera reenviado al MENU USUARIO\n");

    char control='s';
    int valNumTel;
    int valPais;
    int valNumTelRepetido;

    do
    {
        printf("\nIngrese su pais (La primer letra tiene que ser en Mayuscula) \n");
        fflush(stdin);
        scanf("%s", info->pais);

        valPais=validacionPaises(info->pais);
        if(valPais!=1)
        {
            printf("\nEl pais ingresado no esta permitido en nuestros servidores\n");
            printf("\nDesea ingresar otro Pais? [s/n]\n");
            scanf(" %c", &control);
            fflush(stdin);
        }

        if(control=='n' || control=='N'){
            return 0;
        }

    }
    while((control=='s' || control=='S') && valPais!=1);


    do
    {
        printf("\nIngrese su numero telefonico\n");
        fflush(stdin);
        scanf("%s", info->numTelefonico);

        valNumTel=validarNumTelefonico(info->numTelefonico);
        if(valNumTel!=1)
        {
            printf("\nDesea ingresar otro numero telefonico? [s/n]\n");
            scanf(" %c", &control);
            fflush(stdin);
        }else{
            valNumTelRepetido=validarNumTelefonicoRepetido(info->numTelefonico);
            if(valNumTelRepetido!=1){
                printf("\nDesea ingresar otro numero telefonico? [s/n]\n");
                scanf(" %c", &control);
                fflush(stdin);
            }
        }

        if(control=='n' || control=='N'){
            return 0;
        }

    }
    while((control=='s' || control=='S') && (valNumTel!=1 || valNumTelRepetido!=1));


return 1;
}



int validacionPaises(char Pais[]){

    for(int i=0; i<cantPaises; i++)
    {
        if(strcmp(Pais, Paises[i])==0)
        {
            return 1;
        }
    }
    return 0;
}



int validarNumTelefonico(char numTelefonico[]){


   int dimension=strlen(numTelefonico);
    int esValido=1;
    if(dimension<MIN_TELEFONO || dimension>MAX_TELEFONO)
    {
        printf("\nEl numero telefonico no cumple con la longitud esperada de un numero telefonico, caracteres ingresados: %d\n", dimension);
        esValido=0;
    }
    char caracterActual;
    for(int i=0; i<dimension; i++)
    {
        caracterActual=numTelefonico[i];
        if(caracterActual>='0' && caracterActual<='9')
        {
            continue;
        }
        else
        {
            printf("\nEl numero telefonico es invalido, no olvide que solo puede ingresar numeros\n");
            esValido=0;
        }
    }

    return esValido;
}

int validarNumTelefonicoRepetido(char* numTelefono){

    FILE*ArchivoUsuario=fopen(ARCHIVO_USUARIO, "rb");

    if(!ArchivoUsuario){
        printf("\nNo se pudo abrir el archivo en modo lectura\n");
        return 1;
    }

    Usuario c;
    while(fread(&c, sizeof(Usuario), 1, ArchivoUsuario)){
        if(strcmp(numTelefono, c.numTelefonico)==0){
            return 0;
        }
    }
    fclose(ArchivoUsuario);

return 1;
}


int idUsuario(){

    FILE*ArchivoUsuario=fopen(ARCHIVO_USUARIO, "rb");

    if(!ArchivoUsuario){
        printf("\nNo se pudo abrir el archivo en modo lectura\n");
        return 1;
    }

    Usuario u;
    int id=1;

    while(fread(&u, sizeof(Usuario), 1, ArchivoUsuario)){
        id++;
    }

    fclose(ArchivoUsuario);

return id;
}



int validarUsuarioRepetido(char nickname[]){

    FILE* ArchivoUsuario=fopen(ARCHIVO_USUARIO, "rb");

    if (!ArchivoUsuario){
        printf("\nNo se pudo abrir el archivo en modo lectura\n");
        return 1;
    }

    Usuario u;
    while(fread(&u, sizeof(Usuario), 1, ArchivoUsuario)){
        if(strcmp(u.nickname, nickname)==0){
            printf("\nEste nombre de Usuario ya esta siendo utilizado, por favor escoja otro\n");
            return 0;
        }
    }

    fclose(ArchivoUsuario);

return 1;
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

void mostrarPerfilUsuario(Usuario u)
{
    printf("\n--- PERFIL USUARIO ---\n");
    printf("ID: %s\n", u.idUsuario);
    printf("Nickname: %s\n", u.nickname);
    printf("Numero de Telefono : %s\n", u.numTelefonico);
    printf("Pais: %s\n", u.pais);
    printf("Nivel: %d\n", u.nivel);
}
