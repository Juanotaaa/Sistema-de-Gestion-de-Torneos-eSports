#include <stdio.h>
#include <stdlib.h>


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


int main()
{
    printf("Hola Mundo");

    return 0;
}



