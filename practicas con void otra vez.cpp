#include <iostream>
#include <cstring>

using namespace std;

struct Usuario {
    char cuit[12];
    float saldo;
};


void ingresar_dinero(Usuario &usuario);

int main() {
    Usuario usuario;

    strcpy(usuario.cuit, "20-12345678-9"); // Ejemplo de CUIT
    usuario.saldo = 1000.0; // Saldo inicial
    
    printf("saldo actual: %2.f \n", usuario.saldo);

    ingresar_dinero(usuario);

    printf("el saldo actualizado: %2.f", usuario.saldo);

    return 0;
}


void ingresar_dinero(Usuario &usuario) {
    float monto;
    cout << "Ingrese el monto a ingresar: ";
    cin >> monto;

    // Validar que el monto sea positivo
    if (monto > 0) {
        usuario.saldo += monto; // Actualizar saldo
        cout << "Monto ingresado correctamente." << endl;
    } else {
        cout << "Monto inválido. Debe ser mayor a 0." << endl;
    }
}

