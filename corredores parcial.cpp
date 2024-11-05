#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Corredor {
    int id_corredor;
    char nombre[50];
    char apellido[50];
    int cant_carreras;
    float tiempo_promedio;
    float mejor_tiempo;
};

void agregarCorredor(FILE *file);
void actualizarCorredor(FILE *file);
void generarArchivoFiltrado(FILE *file, float tiempo_maximo);
void mostrarCorredores(FILE *file);
int buscarCorredor(FILE *file, int id_corredor);

int main() {
    FILE *file;
    int opcion;
    float tiempo_maximo;

    file = fopen("corredores.bin", "rb+");
    if (file == NULL) {
        file = fopen("corredores.bin", "wb+");
        if (file == NULL) {
            perror("Error al abrir el archivo");
            return 1;
        }
    }

    do {
        printf("1. Agregar corredor\n");
        printf("2. Actualizar corredor\n");
        printf("3. Generar archivo filtrado\n");
        printf("4. Mostrar corredores\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarCorredor(file);
                break;
            case 2:
                actualizarCorredor(file);
                break;
            case 3:
                printf("Ingrese el tiempo máximo: ");
                scanf("%f", &tiempo_maximo);
                generarArchivoFiltrado(file, tiempo_maximo);
                break;
            case 4:
                mostrarCorredores(file);
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 0);

    fclose(file);
    return 0;
}

void agregarCorredor(FILE *file) {
    struct Corredor nuevo_corredor;
    printf("Ingrese ID del corredor: ");
    scanf("%d", &nuevo_corredor.id_corredor);
    
    if (buscarCorredor(file, nuevo_corredor.id_corredor) != -1) {
        printf("El corredor con ID %d ya existe.\n", nuevo_corredor.id_corredor);
        return;
    }

    printf("Ingrese nombre: ");
    scanf("%s", nuevo_corredor.nombre);
    printf("Ingrese apellido: ");
    scanf("%s", nuevo_corredor.apellido);
    printf("Ingrese cantidad de carreras: ");
    scanf("%d", &nuevo_corredor.cant_carreras);
    printf("Ingrese tiempo promedio: ");
    scanf("%f", &nuevo_corredor.tiempo_promedio);
    printf("Ingrese mejor tiempo: ");
    scanf("%f", &nuevo_corredor.mejor_tiempo);

    fseek(file, 0, SEEK_END);
    fwrite(&nuevo_corredor, sizeof(struct Corredor), 1, file);
    printf("Corredor agregado correctamente.\n");
}


void actualizarCorredor(FILE *file) {
    struct Corredor corredor;
    int id_corredor;

    printf("Ingrese ID del corredor a actualizar: ");
    scanf("%d", &id_corredor);
    
    int posicion = buscarCorredor(file, id_corredor);
    if (posicion == -1) {
        printf("Corredor con ID %d no encontrado.\n", id_corredor);
        return;
    }

    fseek(file, posicion * sizeof(struct Corredor), SEEK_SET);
    fread(&corredor, sizeof(struct Corredor), 1, file);

    printf("Ingrese nueva cantidad de carreras: ");
    scanf("%d", &corredor.cant_carreras);
    printf("Ingrese nuevo tiempo promedio: ");
    scanf("%f", &corredor.tiempo_promedio);
    printf("Ingrese nuevo mejor tiempo: ");
    scanf("%f", &corredor.mejor_tiempo);

    fseek(file, posicion * sizeof(struct Corredor), SEEK_SET);
    fwrite(&corredor, sizeof(struct Corredor), 1, file);
    printf("Corredor actualizado correctamente.\n");
}


void generarArchivoFiltrado(FILE *file, float tiempo_maximo) {
    struct Corredor corredor;
    FILE *file_filtrado = fopen("corredores_filtrados.bin", "wb");
    if (file_filtrado == NULL) {
        perror("Error al crear el archivo filtrado");
        return;
    }

    rewind(file);
    while (fread(&corredor, sizeof(struct Corredor), 1, file) == 1) {
        if (corredor.mejor_tiempo < tiempo_maximo) {
            fwrite(&corredor, sizeof(struct Corredor), 1, file_filtrado);
        }
    }

    fclose(file_filtrado);
    printf("Archivo filtrado generado correctamente.\n");
}


void mostrarCorredores(FILE *file) {
    struct Corredor corredor;

    rewind(file);
    printf("Lista de Corredores:\n");
    while (fread(&corredor, sizeof(struct Corredor), 1, file) == 1) {
        printf("ID: %d, Nombre: %s, Apellido: %s, Cant. Carreras: %d, Tiempo Promedio: %.2f, Mejor Tiempo: %.2f\n",
               corredor.id_corredor, corredor.nombre, corredor.apellido,
               corredor.cant_carreras, corredor.tiempo_promedio, corredor.mejor_tiempo);
    }
}


int buscarCorredor(FILE *file, int id_corredor) {
    struct Corredor corredor;
    int posicion = 0;

    rewind(file);
    while (fread(&corredor, sizeof(struct Corredor), 1, file) == 1) {
        if (corredor.id_corredor == id_corredor) {
            return posicion;
        }
        posicion++;
    }
    return -1; // Corredor no encontrado
}



