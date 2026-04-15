#include <stdio.h>
#include "menu.h"

int main() {
    cargarTareas(); // carga las tareas al arrancar el programa
    menuPrincipal();
    guardarTareas(); // guarda las tareas al salir del programa
    return 0;
}