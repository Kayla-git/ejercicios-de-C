#include <stdio.h>
#include <time.h>

int main() {
    time_t tiempo_actual;
    struct tm *info_tiempo;
    char buffer[80];

    // Obtener la hora actual en segundos desde 1970
    time(&tiempo_actual);

    // Convertir a tiempo local (struct tm)
    info_tiempo = localtime(&tiempo_actual);

    // Formatear la hora en una cadena legible
    strftime(buffer, 80, "Fecha y hora: %Y-%m-%d %H:%M:%S", info_tiempo);

    // Mostrar la hora
    printf("%s\n", buffer);

    return 0;
}

