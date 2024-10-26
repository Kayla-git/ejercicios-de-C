

void ingresar_dinero_por_cvu(char *cvu) {
    // Declarar el puntero de archivo
    FILE *archivo = fopen("usuarios.dat", "rb+");
    if (!archivo) {
        printf("Error al abrir el archivo de usuarios.\n");
        return;
    }
    usuario usr;
    int encontrado = 0, monto;
    char cvu[23];
    
    printf("Ingrese el CVU del usuario: ");
    scanf("%s", cvu);

    

    // Buscar el usuario por CVU
    while (fread(&usr, sizeof(usuario), 1, archivo) == 1) {
        if (strcmp(usr.CVU, cvu) == 0) { // Comparar el CVU
            printf("Hola %s, tu saldo actual es de: %d\n", usr.nombre, usr.saldo);
            printf("¿Cuánto deseas ingresar? ");
            scanf("%d", &monto);

            if (monto > 0) {
                usr.saldo = usr.saldo + monto; 

                fseek(archivo, -sizeof(usuario), SEEK_CUR); 
                fwrite(&usr, sizeof(usuario), 1, archivo); 
                printf("Dinero ingresado correctamente. Tu nuevo saldo es: %d\n", usr.saldo);
            } else {
                printf("El monto debe ser positivo.\n");
            }
            encontrado = 1; 
            break;
        }
    }

    fclose(archivo); // Cerrar el archivo
    if (!encontrado) {
        printf("Usuario no encontrado.\n");
    }
}


