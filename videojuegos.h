#ifndef VIDEOJUEGOS_H_INCLUDED
#define VIDEOJUEGOS_H_INCLUDED

typedef struct {
    char idJuego[10];
    char nombre[50];
    char genero[30];
    char plataforma[20];
} Videojuego;

// Funciones
int generarIDVideojuego();
int validarPlataforma(char *p);
Videojuego cargaVideojuego();
int guardarVideojuego(Videojuego juego);
void modificarVideojuego(char idJuego[]);
void verCatalogoVideojuegos();
int letrasYNumeros(char *cadena);
int soloLetras(char *cadena);
int existeVideojuego(char nombre[]);

#endif // VIDEOJUEGOS_H_INCLUDED



