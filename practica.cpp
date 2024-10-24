#include <string.h>
#include <stdio.h>
#include <time.h>

void uno();
void dos();
void tres();

struct empleados{
	int idempleado;
	char nomyapelli[30];
	char domicilio[30];
	char idespe[30];
}empleados1;

struct RegistroAsistencia{
	int idempleado;
	int fecha;
	int hentrada;
	int hsalida;
}RegistroAsistencia1;

struct PrecioEspecialidad{
	int idespec;
	char descripcion[30];
	float preciohs;
}especialidad1;

struct Liquidacion{
	int idempleado;
	int fecdesde;
	int fechasta;
	int canth;
	int pagado;
}liquidacion1;

int main(){
		
}



