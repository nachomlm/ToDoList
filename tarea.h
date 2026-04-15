#ifndef TAREA_H
#define TAREA_H
#define TAM 200

typedef enum {
    PENDIENTE,
    EN_CURSO,
    TERMINADA,
    CANCELADA
} EstadoTarea;

typedef enum {
    FACIL,
    MEDIO,
    DIFICIL
} NivelDificultad;

typedef struct {
    char titulo[TAM];
    char descripcion[500];
    EstadoTarea estado;
    NivelDificultad dificultad;
    char fechaCreacion[TAM];
    char fechaVencimiento[TAM];
} Tarea;

void mostrarTareaDetalle(Tarea tarea);
const char* estadoToString(EstadoTarea estado);

#endif