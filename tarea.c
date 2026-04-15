#include <stdio.h>
#include <string.h>
#include "tarea.h"

// funcion reutilizable
const char* estadoToString(EstadoTarea estado) {
    switch(estado) {
        case PENDIENTE: return "Pendiente";
        case EN_CURSO: return "En curso";
        case TERMINADA: return "Terminada";
        case CANCELADA: return "Cancelada";
        default: return "Desconocido";
    }
}

// funcion mostrar detalle de la tarea
void mostrarTareaDetalle(Tarea tarea) {
    printf("Titulo: %s\n", tarea.titulo);
    printf("Descripcion: %s\n", tarea.descripcion);

    // usar la función
    printf("Estado: %s\n", estadoToString(tarea.estado));

    const char* dificultadTexto;
    switch(tarea.dificultad) {
        case FACIL: dificultadTexto = "Facil"; break;
        case MEDIO: dificultadTexto = "Medio"; break;
        case DIFICIL: dificultadTexto = "Dificil"; break;
        default: dificultadTexto = "Desconocido"; break;
    }
    printf("Dificultad: %s\n", dificultadTexto);

    printf("Fecha de creacion: %s\n", tarea.fechaCreacion);
    printf("Fecha de vencimiento: %s\n", tarea.fechaVencimiento);
}