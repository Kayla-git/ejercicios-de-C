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

    
    if (!encontrado_origen || user_origen.saldo < monto) {
        printf("Usuario no encontrado o saldo insuficiente.\n");
        fclose(archivo);
        return;
    }

    
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
        if (mov) {
            movimiento mov_origen = {2, monto, 0, "2024-10-26", "", ""};
            strcpy(mov_origen.cuit_origen, cuit_origen);
            strcpy(mov_origen.cuit_destino, cuit_destino);
            fwrite(&mov_origen, sizeof(movimiento), 1, mov);
            fclose(mov);
            printf("Transferencia realizada correctamente.\n");
        } else {
            printf("Error al registrar el movimiento.\n");
        }
    } else {
        printf("Receptor no encontrado.\n");//solo dios sabe si esto va a funcionar 
    }
    fclose(archivo);
}
