#ifndef VIDEOJUEGOS_H_INCLUDED
#define VIDEOJUEGOS_H_INCLUDED

typedef struct {
    int idJuego;
    char nombre[50];
    char genero[30];
    char plataforma[20];
} Videojuego;

// Funciones
int generarIDVideojuego();
int validarPlataforma(char *p);
Videojuego cargaVideojuego();
int guardarVideojuego(Videojuego juego);
void modificarVideojuego(int idJuego);
void verCatalogoVideojuegos();
int tieneNumero(char cadena[]);
int soloLetras(char *cadena);

#endif // VIDEOJUEGOS_H_INCLUDED
