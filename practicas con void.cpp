#include <iostream>
#include <cstdio>

using namespace std;

struct Usuario {
    char cuit[13];
    float saldo;
};


void transferir_dinero(Usuario &usuario);
void pagar_servicio(Usuario &usuario);

int main() {
    Usuario usuario;

    strcpy(usuario.cuit, "20-12345678-9"); 
    usuario.saldo = 1000.0; 

    printf("Saldo actual: %.2f\n", usuario.saldo); 

    
    transferir_dinero(usuario);

    printf("Nuevo saldo tras la transferencia: %.2f\n", usuario.saldo); 

    pagar_servicio(usuario);

    printf("Saldo final tras pagar servicio: %.2f\n", usuario.saldo); 

    return 0;
}

void transferir_dinero(Usuario &usuario) {
    char cuit_receptor[13];
    float monto;
    bool valido = false;

    
    while (!valido) {
        printf("Ingrese el CUIT del receptor (formato xx-xxxxxxxx-x): ");
        scanf("%s", cuit_receptor);

        
        if (strlen(cuit_receptor) == 13 && cuit_receptor[2] == '-' && cuit_receptor[11] == '-') {
            valido = true;
            for (int i = 0; i < 13; i++) {
                if (i != 2 && i != 11) { 
                    if (!isdigit(cuit_receptor[i])) {
                        valido = false;
                        break;
                    }
                }
            }
        }

        if (!valido) {
            printf("CUIT inválido. Asegúrese de usar el formato correcto.\n");
        }
    }

    
    printf("Ingrese el monto a transferir: ");
    scanf("%f", &monto);

    
    if (monto > 0 && monto <= usuario.saldo) {
        usuario.saldo -= monto; 
        printf("Transferencia realizada a %s por un monto de %.2f.\n", cuit_receptor, monto);
    } else {
        printf("Monto inválido. Debe ser mayor a 0 y no superar el saldo disponible.\n");
    }
}


void pagar_servicio(Usuario &usuario) {
    float monto;
    char tipo_servicio[50];

    
    printf("Ingrese el tipo de servicio a pagar: ");
    scanf("%s", tipo_servicio);

    
    printf("Ingrese el monto a pagar: ");
    scanf("%f", &monto);

    
    if (monto > 0 && monto <= usuario.saldo) {
        usuario.saldo -= monto; 
        printf("Pago de servicio '%s' realizado por un monto de %.2f.\n", tipo_servicio, monto);
    } else {
        printf("Monto inválido. Debe ser mayor a 0 y no superar el saldo disponible.\n");
    }
}

