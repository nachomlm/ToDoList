#include <stdio.h>
#include <string.h>
#include "menu.h"

Tarea tareas[MAX_TAREAS];
int cantidadTareas = 0;
const char* archivoDatos = "tareas.dat";

void guardarTareas(void);

void menuPrincipal() {
    int opcion;
    do {

        printf("\n==== Menu ====\n");
        printf("1. Ver tareas\n");
        printf("2. Agregar tarea\n");
        printf("3. Editar tarea\n");
        printf("4. Eliminar tarea\n");
        printf("5. Buscar tarea\n");
        printf("0. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: menuVerTareas(); break;
            case 2: menuAgregarTarea(); break;
            case 3: menuEditarTarea(); break;
            case 4: menuEliminarTarea(); break;
            case 5: menuBuscarTarea(); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida\n"); break;
        }
    } while (opcion != 0);
}

void menuAgregarTarea() {
    Tarea nueva;

    printf("\n-- Agregar Tarea --\n");

    while(getchar() != '\n'); // descarta el \n que deja el scanf en el buffer

    // Agrega el titulo
    printf("Titulo: ");
    fgets(nueva.titulo, TAM, stdin);
    nueva.titulo[strcspn(nueva.titulo, "\n")] = 0;

    // Agrega la descripcion a la tarea
    printf("Descripcion: ");
    fgets(nueva.descripcion, 500, stdin);
    nueva.descripcion[strcspn(nueva.descripcion, "\n")] = 0;

    // Elije el estado de la tarea(Pendiente, En curso, Terminada, Cancelada)
    printf("Estado (1 = Pendiente, 2 = En curso, 3 = Terminada, 4 = Cancelada): ");
    int estado;
    scanf("%d", &estado);
    while(getchar() != '\n');
    switch(estado) {
        case 1: nueva.estado = PENDIENTE; break;
        case 2: nueva.estado = EN_CURSO; break;
        case 3: nueva.estado = TERMINADA; break;
        case 4: nueva.estado = CANCELADA; break;
        default: nueva.estado = PENDIENTE; break;
    }

    // Indica el nivel de dificultad
    printf("Dificultad (1 = Facil, 2 = Medio, 3 = Dificil): ");
    int dificultadIngresada;
    scanf("%d", &dificultadIngresada);
    while(getchar() != '\n');
    if (dificultadIngresada >= 1 && dificultadIngresada <= 3) {
        nueva.dificultad = (NivelDificultad)(dificultadIngresada - 1);
    } else {
        nueva.dificultad = FACIL;
    }

    // Ingresa la fecha de creacion
    printf("Fecha de creacion (dd/mm/yyyy): ");
    fgets(nueva.fechaCreacion, TAM, stdin);
    nueva.fechaCreacion[strcspn(nueva.fechaCreacion, "\n")] = 0;

    // Ingresa la fecha de vencimiento
    printf("Fecha de vencimiento (dd/mm/yyyy): ");
    fgets(nueva.fechaVencimiento, TAM, stdin);
    nueva.fechaVencimiento[strcspn(nueva.fechaVencimiento, "\n")] = 0;

    // Guarda la tarea en el arreglo y aumenta el contador.
    tareas[cantidadTareas++] = nueva;

    guardarTareas();
    printf("Tarea agregada con exito! \n");
}

void menuVerTareas() {
    // si no hay ninguna tarea cargada
    if(cantidadTareas == 0) {
        printf("No hay ninguna tarea cargada.\n");
        return;
    }

    // se muestra cada tarea con su numero
    printf("\n-- Lista de Tareas --\n");
    for(int i = 0; i < cantidadTareas; i++) {
        printf("%d. %s [%s] - Dificultad: %d\n",
            i + 1,
            tareas[i].titulo,
            estadoToString(tareas[i].estado),
            tareas[i].dificultad);
    }

    // el usuario elige una para ver el detalle
    printf("\nSeleccione una para ver el detalle (0 para volver): ");
    int seleccion;
    scanf("%d", &seleccion);
    while(getchar() != '\n');

    // se valida la seleccion del usuario
    if(seleccion < 1 || seleccion > cantidadTareas) {
        printf("Volviendo...\n");
        return;
    }

    // se muestra el detalle de la tarea
    printf("\n");
    mostrarTareaDetalle(tareas[seleccion - 1]);
}

void menuBuscarTarea() {
    if(cantidadTareas == 0) {
        printf("No hay tareas para buscar.\n");
        return;
    }

    printf("\n-- Buscar Tarea --\n");

    char busqueda[TAM];
    printf("Ingrese titulo a buscar: ");
    while(getchar() != '\n');
    fgets(busqueda, TAM, stdin);
    busqueda[strcspn(busqueda, "\n")] = 0;

    int encontrada = 0;

    for (int i = 0; i < cantidadTareas; i++) {
        if (strstr(tareas[i].titulo, busqueda) != NULL) {
            printf("\nResultado %d:\n", i + 1);
            mostrarTareaDetalle(tareas[i]);
            encontrada = 1;
        }
    }

    if (!encontrada) {
        printf("No se encontraron tareas con ese titulo.\n");
    }
}

void menuEditarTarea() {
    // si no hay ninguna tarea avisa y sale
    if (cantidadTareas == 0) {
        printf("No hay tareas para editar.\n");
        return;
    }

    // se muestran las tarea para que el usuario elija
    printf("\n Editar Tarea \n");
    for (int i = 0; i < cantidadTareas; i++) {
        printf("%d. %s\n", i + 1, tareas[i].titulo);
    }

    printf("Seleccione una tarea para editar(0 para volver): ");
    int seleccion;
    scanf("%d", &seleccion);
    while(getchar() != '\n');

    if (seleccion < 1 || seleccion > cantidadTareas) {
        printf("Volviendo...\n");
        return;
    }


    // se apunta a la tarea seleccionada con un puntero
    Tarea* t = &tareas[seleccion - 1];

    // se edita cada campo , se deja vacio no se modifica
    printf("Titulo actual: %s\nNuevo titulo (Enter para no cambiar): ", t->titulo);
    char title[TAM];
    fgets(title, TAM, stdin);
    title[strcspn(title, "\n")] = 0;
    if(title[0] != '\0') strcpy(t->titulo, title);

    printf("Descripcion actual: %s\nNueva descripcion (Enter para no cambiar): ", t->descripcion);
    char description[500];
    fgets(description, 500, stdin);
    description[strcspn(description, "\n")] = 0;
    if(description[0] != '\0') strcpy(t->descripcion, description);

    printf("Estado actual: %s\nNuevo estado [1 = Pendiente, 2 = En curso, 3 = Terminada, 4 = Cancelada]: ", estadoToString(t->estado));
    int estado;
    scanf("%d", &estado);
    while(getchar() != '\n');
    switch(estado) {
        case 1: t->estado = PENDIENTE; break;
        case 2: t->estado = EN_CURSO; break;
        case 3: t->estado = TERMINADA; break;
        case 4: t->estado = CANCELADA; break;
    }

    printf("Dificultad actual: %d\nNueva dificultad [1 = Facil, 2 = Medio, 3 = Dificil]: ", t->dificultad + 1);
    int dificultad;
    scanf("%d", &dificultad);
    while(getchar() != '\n');
    if (dificultad >= 1 && dificultad <= 3) t->dificultad = (NivelDificultad)(dificultad - 1);

    guardarTareas();
    printf("Tarea editada\n");
}

void menuEliminarTarea() {
    if (cantidadTareas == 0) {
        printf("No hay tareas para eliminar.\n");
        return;
    }

    // recorre y muestra las tareas
    printf("\n-- Eliminar Tarea --\n");
    for(int i = 0; i < cantidadTareas; i++) {
        printf("%d. %s\n", i + 1, tareas[i].titulo);
    }

    printf("Seleccione una tarea para eliminar (0 para volver): ");
    int seleccion;
    scanf("%d", &seleccion);
    while(getchar() != '\n');

    if(seleccion < 1 || seleccion > cantidadTareas) {
        printf("Volviendo...\n");
        return;
    }

    // Desplazamiento hacia la izquierda
    for (int i = seleccion - 1; i < cantidadTareas - 1; i++) {
        tareas[i] = tareas[i + 1];
    }

    cantidadTareas--;

    guardarTareas();
    printf("Tarea eliminada con exito.\n");
}

void guardarTareas(void) {
    // abre el archivo en modo escritura binaria
    FILE* archivo = fopen(archivoDatos, "wb");
    if(archivo == NULL) {
        printf("Error al guardar las tareas.\n");
        return;
    }

    // escribe todas las tareas de una sola vez
    fwrite(tareas, sizeof(Tarea), cantidadTareas, archivo);
    fclose(archivo);
}

void cargarTareas() {
    // abre el archivo en modo lectura binaria
    FILE* archivo = fopen(archivoDatos, "rb");
    if (archivo == NULL) {
        // si no existe el archivo todavia no es un error
        return;
    }

    // lee las tareas y guarda cuantas se leyeron
    cantidadTareas = fread(tareas, sizeof(Tarea), MAX_TAREAS, archivo);
    fclose(archivo);
}
