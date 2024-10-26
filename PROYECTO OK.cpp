#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
void crear_usuario();
void ingresar();
int user_registry(const void *field, char tipo);

typedef struct{
	char cuit[23];
	char nombre[52];
	char num[14];
	char email[50];
	char CVU[23];
	char alias[5];
	char IVA[50];
	char contra[50];
	int saldo;
}usuario;

void menu_ing(const usuario *usser);

typedef struct{
	int type;
	char CBU[22];
	char cuitl[23];
}cuentabanco;

typedef struct{
	int tipo1;
	int monto;
	int iibb;
	int fech;
	char cuilt[50];
}movimientos;


int main(){
	char opc;
	FILE *archivo=fopen("user.dat","rb" );
	if(archivo==NULL){
		archivo=fopen("user.dat", "wb");
		if (archivo==NULL){
		printf("Error al abrir el archivo de registros.\n");
		exit(0);
		}else{
			usuario user;
			strcpy(user.nombre, "Administrador");
			strcpy(user.num, "0000000000000");
			strcpy(user.email, "admin0@gmail");
			strcpy(user.cuit, "00000000000");
			if (fwrite(&user, sizeof(usuario), 1, archivo) != 1) {
    			printf("Error al escribir los datos en el archivo\n");
			}
		}
	}
	fclose(archivo);
	repeat: 
	printf("\t\t\tBienvenido a Kamaba Pay!\n\n\t\t\tEscoja que desea hacer:\n\n\t\t\t1. Crear Usuario.\n\t\t\t2. Ingresar.\n\t\t\t3. Salir.\n");
	scanf("%s", &opc);
	switch (opc){
		case '1':
			crear_usuario();
			goto repeat;
			break;
		case '2':
			ingresar();
			goto repeat;
			break;
		case '3':
			printf("Usted ha salido.");
			break;
		default:
			system("cls");
			printf("\nOpcion invalida. Escoja de las siguientes:\n\n");
			goto repeat;
		}
}
	
	void crear_usuario(){
		int band=1;
		int i=1;
		int pos;
		int gm=0;
		char tipo;
		char CODVER[23];
		int DIGVERI;
		char cvu1[23];
		int errorcvu=0;
		int contnomb=0;
		int punto=0;
		int pos1;
		char gmail[50];
		char alias[51];
		usuario user;
		system("cls");
		printf("\n\t --- Panel de Registro de Nuevo Usuario ---\n");
		printf("\nHola, nuevo usuario! Por favor siga las instrucciones para crear una cuenta.\n");
		printf("\nIngrese su nombre completo: ");
		while(band!=0){
			fflush(stdin);
			fgets(user.nombre, sizeof(user.nombre), stdin);
			band=1;
			i=0;
			size_t len=strlen(user.nombre);
			if(len>0&&user.nombre[len-1]=='\n') {
    			user.nombre[len-1]='\0';
    		}
			while(user.nombre[i] != '\0' && band != 2){
				 if(!((user.nombre[i] >= 'A' && user.nombre[i] <= 'Z') || (user.nombre[i] >= 'a' && user.nombre[i] <= 'z') || user.nombre[i] == ' ')){
					band=2;
				}
				i++;
			}
			if((user.nombre[0]!=' ')&&(user.nombre[1]!=' ')&&(((user.nombre[0]>= 'A'))&&((user.nombre[0]<='Z')))){
				if(band!=2){
					if (strlen(user.nombre)>=2){
						if (strlen(user.nombre)<=50){
            	 		tipo='n';
							if ((contnomb=(user_registry(user.nombre, tipo)))==1){
							band=0;
							}else
								band=0;
						}else
								printf("\nEl nombre es muy largo.\n");
            		}else
            				printf("\nEl nombre es muy corto.\n");
        		}else
        			printf("\nIngrese un nombre valido. (Solo letras)\n");
			}else
				printf("\nNombre invalido, el primer caracter debe ser una letra mayuscula seguido de un caracter\n");
			}
		band=1;
		printf("\nIngrese su numero completo de celular. Agregando el codigo de area: ");
		while (band!=0){                   
			fflush(stdin);
			gets(user.num);
			fflush(stdin);
			band=1;
			i=0;
			while(user.num[i] != '\0' && band != 2){
				 if(!((user.num[i] >= '0' && user.num[i] <= '9'))){
					band=2;
				}
				i++;
			}
			if(band!=2){
				if (strlen(user.num)==13){
					if ((user.num[0]=='5')&&(user.num[1]=='4')&&(user.num[2]=='9')){
						tipo='c';
						if (user_registry(user.num, tipo)==1){
							band=0;
						}else
							printf("\nNumero ya existente.\n");
					}else              
						printf("\nIngrese un codigo de area valido.(549)\n");
				}else
					printf("\nIngrese un numero valido. (De 13 numeros).\n");
			}else
			printf("\nIngrese un numero valido (Sin letras).\n");
		}
		band=1;
		printf("\nIngrese su correo electronico: ");
		while(band!=0){
			fflush(stdin);
			gets(user.email);
			fflush(stdin);
			band=1;
			i=0;
			gm=0;
			punto=0;
			while(user.email[i] != '\0' && band != 2){
				if(!((user.email[i] >= 'A' && user.email[i] <= 'Z') || (user.email[i] >= 'a' && user.email[i] <= 'z') || (user.email[i] >= '0' && user.email[i] <= '9')||(user.email[i] == '@')||(user.email[i]=='.'))){
					band=2;
				}
				if(user.email[i]=='@'){
					gm++;
					pos=i;
				}
				if((user.email[i]=='.')&&(user.email[i]>pos)){
					if(user.email[i]=='.'){
						punto++;
						pos1=i;
					}
				}
				i++;	
				}
			if (punto==1){
				i=0;
				pos=pos+1;
				fflush(stdin);
				strcpy(gmail, " ");
				fflush(stdin);
				while(user.email[pos+i]!='.'&&user.email[pos+i]!='@'){
					fflush(stdin);
					gmail[i]=user.email[pos+i];
					fflush(stdin);
					i++;
				}
			}else
				punto=0;
			if(user.email[0]!='@'){
				if (band!=2){
					if(gm==1){
						if (punto!=0){
							if (strlen(user.email)<=49){
								if((strcmp(gmail, "gmail") == 0)||(strcmp(gmail, "hotmail") == 0)||(strcmp(gmail, "yahoo") == 0)||(strcmp(gmail, "outlook") == 0)){
									tipo='e';
									if((user.email[pos1+1]=='c')&&(user.email[pos1+2]=='o')&&(user.email[pos1+3]=='m')&&(user.email[pos1+4]=='\0')){
										if (user_registry(user.email, tipo)==1){
											band=0;
										}else{
											printf("\nEmail ya existente.\n");
										}
									}else{
										band=1;
										printf("\nDireccion invalida. Asegurarse que los puntos y dominio esten correctos.\n");
										}
								}else
									printf("\nDireccion inivalida. Solo gmail, yahoo, outlook y hotmail.\n");	
							}else
								printf("\nDireccion inivalida. Excede la longitud permitida.\n");
						}else
							printf("\nDireccion inivalida. Revisar los puntos\n");
					}else
						printf("\nDireccion inivalida. Revise la cantidad de arrobas.\n");
				}else
					printf("\nDireccion inivalida. Solo letras y numeros.\n");
			}else
				printf("\nDireccion inivalida. El primer caracter debe ser una letra\n");
		}
		band=1;
		printf("\nIngrese su cuit: ");
		while (band!=0){
			fflush(stdin);
			gets(user.cuit);
			fflush(stdin);
			band=1;
			i=0;
			while(user.cuit[i] != '\0' && band != 2){
				if(!((user.cuit[i] >= '0' && user.cuit[i] <= '9'))){
					band=2;
				}
				i++;
			}
			if(band!=2){
				if (strlen(user.cuit)==11){
					if (((user.cuit[0]=='2')&&(user.cuit[1]=='7'))||((user.cuit[0]=='2')&&(user.cuit[1]=='0'))||((user.cuit[0]=='3')&&(user.cuit[1]=='0'))){
						if((11-((((user.cuit[0]-'0')*5)+((user.cuit[1]-'0')*4)+((user.cuit[2]-'0')*3)+((user.cuit[3]-'0')*2)+((user.cuit[4]-'0')*7)+((user.cuit[5]-'0')*6)+((user.cuit[6]-'0')*5)+((user.cuit[7]-'0')*4)+((user.cuit[8]-'0')*3)+((user.cuit[9]-'0')*2))%11))==(user.cuit[10]-'0')){
							tipo='t';
							if (user_registry(user.cuit, tipo)==1){
								band=0;
							}else
								printf("\nCUIT/L ya existente.\n");
						}else
							printf("\nCUIT/L invalido. No verifica.\n");
					}else
						printf("\nPrimeros digitos de CUIT/L invalidos.\n");
				}else
					printf("\nLa longitud del CUIT/L es invalida.\n");	
			}else
			printf("\nIngrese un cuit valido. (Solo numeros)\n");
		}
		band=1;
		while(band!=0){
			for(int i=0; i<=5; i++){
				user.CVU[i]='0';
			}
			user.CVU[6]='3';
			user.CVU[7]='1';
			srand(time(NULL));
			for(i=8; i<=20; i++){
				user.CVU[i]='0'+rand()%10;
				}
			for (i=0; i<=20; i++){
				CODVER[i]='1';
				CODVER[i+1]='3';
				CODVER[i+2]='7';
				i=i+2;				
				}
			for (i=0; i<=20; i++){
				DIGVERI=(CODVER[i]+((user.CVU[i]-'0')*(CODVER[i]-'0')));
				}
				DIGVERI=DIGVERI%10;
			if(DIGVERI==0){
				user.CVU[21]='0';
			}else
				user.CVU[21]=DIGVERI+'0';
			user.CVU[22] = '\0';
			FILE *archiv=fopen("user.dat","rb" );
			if(archiv==NULL){
				printf("Error al abrir los registros para validacion. Cerrando el programa.");
				exit(0);
				}
			usuario usi;
			while (fread(&usi, sizeof(usuario), 1, archiv)){
				if (strcmp(usi.CVU, user.CVU) == 0){
					fclose(archiv);
					errorcvu=1;
				}
			}
			if (errorcvu!=1){
				band=0;
			}
		}
		user.alias[0]=user.nombre[0];
		user.alias[1]=user.nombre[1];
		user.alias[2]=user.cuit[4];
		user.alias[3]=user.cuit[5];
		user.alias[4]=contnomb + '0';
		user.alias[5] = '\0';
		tipo='a';
		fflush(stdin);
		band=1;
		printf("\nCree una contrasena (Solo letras y numeros, al menos 8 caracteres de longitud.):\n");
		fflush(stdin);
		while (band!=0){
			i=0;
			fflush(stdin);
			fgets(user.contra, sizeof(user.contra), stdin);
			fflush(stdin);
			size_t len=strlen(user.contra);
			if(len>0&&user.contra[len-1]=='\n') {
    			user.contra[len-1]='\0';
    		}
			while(user.contra[i] !='\0' && band != 2){
				if(!((user.contra[i] >= 'A' && user.contra[i] <= 'Z') || (user.contra[i] >= 'a' && user.contra[i] <= 'z') || (user.contra[i] >= '0' && user.contra[i] <= '9'))){
					band=2;
				}else
				i++;
			}
			if(band!=2){
				if(strlen(user.contra)<=49){
					if(strlen(user.contra)>=8){
						band=0;
					}else
						printf("\nContrasena invalida. Demasiado corta.\n");
				}else
					printf("\nContrasena invalida. Demasiado larga.\n");
			}else
				printf("\nContrasena invalida. Solo se permite el uso de numeros y letras.\n");
		}
		if (user_registry(user.alias, tipo)==1){
			printf("\nSu alias es %s y su CVU es %s\n", user.alias, user.CVU);
		}else{
			alias[5]=user_registry(user.alias, tipo);
			printf("\nSu alias es %s y su CVU es %s\n", user.alias, user.CVU);
		}
		FILE *arc=fopen("user.dat", "a+b");
		if(arc==NULL){
			printf("Error al abrir el archivo de usuarios para registar los datos.\n");
			exit (0);
		}
		if (fwrite(&user, sizeof(usuario), 1, arc) != 1) {
    		printf("Error al escribir los datos en el archivo\n");
    		exit(0);
		}
		fclose(arc);
		FILE *arcuit=fopen("ADMINvalidar_IVA.txt", "a+b");
		if(arcuit==NULL){
			printf("Error al abrir archivo IVA. Cerrando el programa.");
			exit(0);
		}else
		fprintf(arcuit, "! Nuevo CUIT a verificar: %s\n", user.cuit);
		fclose(arcuit);
		printf("\nCuenta creada con exito!\n\n Te bienvenimos, %s.\nIngrese 0 para volver al menu principal, y cualquier otro numero para salir del programa.\n", user.nombre);
		scanf("%d", &band);
		if (band==0){
			system("cls");
		}else{
		printf("Saliendo del programa... Usted ha salido.");
		exit(0);
		}
}


	 int user_registry(const void *field, char tipo){
		int contnom=1;
		int contalias=1;
		FILE *archivo=fopen("user.dat","rb" );
			if(archivo==NULL){
				printf("Error al abrir los registros para validacion. Cerrando el programa.");
				exit(0);
				}
		usuario usu;
		while (fread(&usu, sizeof(usuario), 1, archivo)){
		switch (tipo){
			case 'n':{
				char *nombre=(char *)field;
				if (strcmp(usu.nombre, nombre) == 0){
					contnom++;
				}
				break;
				}
			case 'c':{
				char *num=(char *)field;
				if (strcmp(usu.num, num) == 0){
					fclose(archivo);
					return 0;
				}
				break;
			}
			case 'e':{
				char *email=(char *)field;
				if (strcmp(usu.email, email) == 0){
					fclose(archivo);
					return 0;
				}
				break;
			}
			case 't':{
				char *cuit=(char *)field;
				if (strcmp(usu.cuit, cuit) == 0){
					fclose(archivo);
					return 0;
				}
				break;
			}
			case 'a':{
				char *alias=(char *)field;
				if (strcmp(usu.alias, alias) == 0){
					fclose(archivo);
					contalias++;
				}
				break;
			}
			case 'o':{
				char *contr=(char *)field;
				if (strcmp(usu.contra, contr) == 0){
					fclose(archivo);
					return 0;
				}
				break;
			}
			}
		}
		if(contalias>0){
			fclose (archivo);
			return contalias;
		}
		if (contnom>0){
			fclose(archivo);
			return contnom;
		}else
		return 1;
	}
	
	void ingresar(){
        char opci;
        usuario uso;
        usuario usr;
		char tip;
		FILE *arci = fopen("user.dat", "rb");
    		if (arci==NULL) {
        		printf("Error al abrir el archivo.\n");
        		exit(0);
        	}
		system("cls");
		printf("\t\t\n---Panel de Ingreso de Usuario---\t\t\n\n");
        printf("\t\t\t¿Como desea ingresar?!\n\n\t\t\t 1. Utilizando email. \n\t\t\t2. Utilizando numero de celular.\n\t\t\t3. Utilizando CUIT/L.\n");
        scanf("%s", &opci);
		switch (opci){
        	case '1':
                printf("\nIngrese su email.\n");
                fflush(stdin);
                gets(uso.email);
                fflush(stdin);
                tip='e';
                if(user_registry(uso.email, tip)!=1){
                    printf("\nIngrese su contraseña\n");
					gets(uso.contra);
					tip='o';
					if(user_registry(uso.contra, tip)!=1){
						while (fread(&usr, sizeof(usuario), 1, arci)){
							if (strcmp(usr.email, uso.email) == 0){
								uso=usr;
								printf("\nIngresando...Espere.\n");
								sleep(1);
								menu_ing(&uso);
							}
						}
						fclose(arci);
                    }else
                    printf("\nContrasena incorrecta.\n");
                }else
                	printf("\nCorreo no vinculado a una cuenta.\n");
            		break;
        	case '2':
            	printf("\nIngrese su numero.\n");
            	fflush(stdin);
				gets(uso.num);
				fflush(stdin);
                tip='c';
                if(user_registry(uso.num, tip)!=1){
                    printf("\nIngrese su contrasena\n");
                    gets(uso.contra);
                    tip='o';
                    if(user_registry(uso.contra, tip)!=1){
                    	while (fread(&usr, sizeof(usuario), 1, arci)){
							if (strcmp(usr.num, uso.num) == 0){
								uso=usr;
								printf("\nIngresando...Espere.\n");
								sleep(1);
								menu_ing(&uso);
							}
						}
						fclose(arci);
                    }else
                    printf("\nContrasena incorrecta.\n");
                }else
                	printf("\nNumero no vinculado a una cuenta.\n");
            		break;
        	case '3':
            	printf("\nIngrese su CUIT/L.\n");
            	fflush(stdin);
                gets(uso.cuit);
                fflush(stdin);
                tip='t';
                if(user_registry(uso.cuit, tip)!=1){
                    printf("\nIngrese su contrasena\n");
                    gets(uso.contra);
                    tip='o';
                    if(user_registry(uso.contra, tip)!=1){
                    	while (fread(&usr, sizeof(usuario), 1, arci)){
							if (strcmp(usr.cuit, uso.cuit) == 0){
								uso=usr;
								printf("\nIngresando...Espere.\n");
								sleep(1);
								menu_ing(&uso);
							}
						}
						fclose(arci);
                    }else
                    printf("\nContrasena incorrecta.\n");
                }else
                	printf("\nCUIT/L no vinculado a una cuenta.\n");
           			break;
        }        
    }
    
    void menu_ing(const usuario *usser){
    	printf("\nHola, %s!\n", usser->nombre);
	}