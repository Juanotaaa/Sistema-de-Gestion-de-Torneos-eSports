#ifndef TORNEO_H
#define TORNEO_H
#include "videojuegos.h"

typedef struct stFecha
{
    int dia;
    int mes;
    int anio;
} Fecha;

typedef struct stTorneo
{
    char idTorneo[10];
    char nombre[50];
    Videojuego juego;
    int capacidadMaxima;
    int cuposDisponibles;
    Fecha fechaInicio;
    float premioTotal;
    char estado[15];
} Torneo;

//prototipado de torneos
//prototipado de fran
Torneo cargaTorneo(); 
int verListadoTorneos();
int buscarTorneoPorID(int idTorneo);
int validacionIDTorneo(int idTorneo);    
void crearTorneo(); 
void MostrarTorneo(Torneo T);
Torneo modificarTorneo(int idTorneo); 
int fechaUnica(Fecha f);
int fechaAnterior(Fecha a, Fecha b);
void actualizarEstadoTorneo(Torneo* T);
void modificarTorneoAEleccion(char idTorneo[]);
void verTorneosAbiertosYCuposDisponibles();
void mostrarTorneosAbiertos(Torneo T);
void verParticipantesTorneo();
void torneosSinParticipantes();
//prototipado nuevo de modificaciones de cande
int buscarTorneo(int idTorneo, Torneo * torneo);
Torneo * torneoArrDinamico(int* dim);
int contarTorneos();
void guardarListaTorneo(Torneo* listaTorneo, int dim);
void torneosSinParticipantes();
int validarTorneoAbierto(Torneo T);

#endif