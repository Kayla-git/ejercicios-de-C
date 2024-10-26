#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estructuras
typedef struct {
    char cuit[23];
    char nombre[52];
    char num[14];
    char email[50];
    char CVU[23];
    char alias[5];
    char IVA[50];
    int saldo;
} usuario;

typedef struct {
    int tipo;  // 1: caja de ahorro, 2: cuenta corriente
    char CBU[22];
    char cuitl[23];
} cuentabanco;

typedef struct {
    int tipo1;  // 1: ingreso, 2: transferencia, 3: pago
    int monto;
    int iibb;
    char fecha[11];
    char cuit_origen[23];
    char cuit_destino[23];
} movimiento;

// Función para crear un nuevo usuario
void crear_usuario() {
    usuario nuevo_usuario;

    printf("Ingrese el CUIT del usuario: ");
    scanf("%s", nuevo_usuario.cuit);
    printf("Ingrese el nombre completo del usuario: ");
    scanf(" %[^\n]", nuevo_usuario.nombre);
    printf("Ingrese el número de celular del usuario: ");
    scanf("%s", nuevo_usuario.num);
    printf("Ingrese el email del usuario: ");
    scanf("%s", nuevo_usuario.email);
    printf("Ingrese el CVU del usuario: ");
    scanf("%s", nuevo_usuario.CVU);
    printf("Ingrese el alias del usuario: ");
    scanf("%s", nuevo_usuario.alias);
    printf("Ingrese la condición ante el IVA del usuario: ");
    scanf(" %[^\n]", nuevo_usuario.IVA);
    printf("Ingrese el saldo inicial del usuario: ");
    scanf("%d", &nuevo_usuario.saldo);

    FILE *archivo = fopen("usuarios.dat", "ab");
    if (!archivo) {
        printf("Error al abrir el archivo de usuarios.\n");
        return;
    }
    fwrite(&nuevo_usuario, sizeof(usuario), 1, archivo);
    fclose(archivo);

    printf("Usuario creado correctamente.\n");
}

// Función para ingresar dinero
void ingresar_dinero(char *cuit) {
    FILE *archivo = fopen("usuarios.dat", "rb+");
    if (!archivo) {
        printf("Error al abrir el archivo de usuarios.\n");
        return;
    }
    usuario user;
    int encontrado = 0, monto;

    while (fread(&user, sizeof(usuario), 1, archivo) == 1) {
        if (strcmp(user.cuit, cuit) == 0) {
            printf("Ingrese el monto a ingresar: ");
            scanf("%d", &monto);
            user.saldo += monto;

            fseek(archivo, -sizeof(usuario), SEEK_CUR);
            fwrite(&user, sizeof(usuario), 1, archivo);
            encontrado = 1;

            FILE *mov = fopen("movimientos.dat", "ab");
            movimiento nuevo_mov = {1, monto, 0, "2024-10-26", "", ""};
            strcpy(nuevo_mov.cuit_origen, cuit);
            fwrite(&nuevo_mov, sizeof(movimiento), 1, mov);
            fclose(mov);
            printf("Dinero ingresado correctamente.\n");
            break;
        }
    }
    fclose(archivo);
    if (!encontrado) printf("Usuario no encontrado.\n");
}

// Función para transferir dinero
void transferir_dinero(char *cuit_origen) {
    FILE *archivo = fopen("usuarios.dat", "rb+");
    if (!archivo) {
        printf("Error al abrir el archivo de usuarios.\n");
        return;
    }
    usuario user_origen, user_destino;
    int encontrado_origen = 0, encontrado_destino = 0, monto;
    char cuit_destino[23];

    printf("Ingrese el CUIT del receptor: ");
    scanf("%s", cuit_destino);
    printf("Ingrese el monto a transferir: ");
    scanf("%d", &monto);

    while (fread(&user_origen, sizeof(usuario), 1, archivo) == 1) {
        if (strcmp(user_origen.cuit, cuit_origen) == 0) {
            encontrado_origen = 1;
            break;
        }
    }

    if (encontrado_origen && user_origen.saldo >= monto) {
        rewind(archivo);
        while (fread(&user_destino, sizeof(usuario), 1, archivo) == 1) {
            if (strcmp(user_destino.cuit, cuit_destino) == 0) {
                encontrado_destino = 1;
                break;
            }
        }

        if (encontrado_destino) {
            user_origen.saldo -= monto;
            fseek(archivo, -sizeof(usuario), SEEK_CUR);
            fwrite(&user_origen, sizeof(usuario), 1, archivo);

            user_destino.saldo += monto;
            fseek(archivo, -sizeof(usuario), SEEK_CUR);
            fwrite(&user_destino, sizeof(usuario), 1, archivo);

            FILE *mov = fopen("movimientos.dat", "ab");
            movimiento mov_origen = {2, monto, 0, "2024-10-26", "", ""};
            strcpy(mov_origen.cuit_origen, cuit_origen);
            strcpy(mov_origen.cuit_destino, cuit_destino);
            fwrite(&mov_origen, sizeof(movimiento), 1, mov);
            fclose(mov);
            printf("Transferencia realizada correctamente.\n");
        } else {
            printf("Receptor no encontrado.\n");
        }
    } else {
        printf("Saldo insuficiente o usuario no encontrado.\n");
    }
    fclose(archivo);
}

// Función para listar movimientos
void listar_movimientos(char *cuit) {
    FILE *mov = fopen("movimientos.dat", "rb");
    if (!mov) {
        printf("Error al abrir el archivo de movimientos.\n");
        return;
    }
    movimiento mov_act;
    printf("Movimientos para CUIT %s:\n", cuit);
    while (fread(&mov_act, sizeof(movimiento), 1, mov) == 1) {
        if (strcmp(mov_act.cuit_origen, cuit) == 0 || strcmp(mov_act.cuit_destino, cuit) == 0) {
            printf("Tipo: %d | Monto: %d | Fecha: %s\n", mov_act.tipo1, mov_act.monto, mov_act.fecha);
        }
    }
    fclose(mov);
}

// Menú principal
int main() {
    int opcion;
    char cuit[23];

    do {
        printf("\n--- Menu Principal ---\n");
        printf("1. Crear usuario\n");
        printf("2. Ingresar dinero\n");
        printf("3. Transferir dinero\n");
        printf("4. Listar movimientos\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                crear_usuario();
                break;
            case 2:
                printf("Ingrese su CUIT: ");
                scanf("%s", cuit);
                ingresar_dinero(cuit);
                break;
            case 3:
                printf("Ingrese su CUIT: ");
                scanf("%s", cuit);
                transferir_dinero(cuit);
                break;
            case 4:
                printf("Ingrese su CUIT: ");
                scanf("%s", cuit);
                listar_movimientos(cuit);
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while(opcion != 0);

    return 0;
}

