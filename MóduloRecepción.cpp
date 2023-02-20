/*------------ Librerías -----------------------*/
#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include<dos.h>
#include<time.h>
#define RETURNTIME 15
#define ENTER 13
#define TAB 9
#define BCKSPC 8

//************* ESTRUCTURAS DE DATOS **************

struct fecha
{
	int dd;
	int mm;
	int aaaa;	
};

struct RegistroSocio
{
	int dni;
	char apellidoNombre[60];
	char patologia[60];
	char domicilio[60];
	int edad;
	float altura;
	float peso;
	char nrocelular[50];
	int nrosocio;
	fecha fechaIngreso;
	bool borrado;
};

struct RegistroTurno
{
	int   LegajoEntrenador;
	char  Entrenador[50];
	char  Socio[50];
	char  Actividad[50];
	int   NroSocio;
	float Horario;
	int   Clientes;
	int   Honorarios;
	bool  Borrado;

};


struct RegistroEntrenador
{
	char ApellidoNombre[60];
	int  Legajo;
	char ClaveIngreso[32];
	int  Horas;
	bool borrado; 
};


struct RegistroActividad
{
	char  Actividad[60];
	char  Entrenador[60];
	float Horario;
	int   Dia;
	int   Atendidos;
	bool  Borrado;

};

struct RegistroUsuario
{
	// Usuario de Recepción
	char Username[10];
	char Password[32];
	char ApellidoyNombre[60];
	bool Borrado;
};


//************* FUNCIONES PROTOTIPO **************

bool IniciarSesion(FILE *RECEP, char usu[10], char pass[32]);
void takepassword(char pwd[50]);
void RegistrarSocio();
void ListarSocios();
void RegistrarTurnos();
int  Menu();
void ListarFechasPago();


//************* FUNCIÓN PRINCIPAL **************

main(void)
{
	
	FILE *usuarios = fopen("Usuarios.dat", "rb");
	
	bool login = false;
	char user[10], pass[32];
	int opc = 0;
	
	system("color 1F");
	
	do 
	{
		system("cls");	
		opc = Menu();
		system("cls");	
		
		switch ( opc )
		{
			case 1: {
					    system("cls");
	                    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
                        printf("      \xcd\xcd\xcd\xcd\xcd\xcd  INICIAR SESI%cN \xcd\xcd\xcd\xcd\xcd\xcd\n", 224);
                        printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	 
	                    printf("\n- Ingrese Nombre de Usuario: ");
	                    _flushall(); gets(user);	                   
	                    printf("\n- Ingrese Contrase%ca: ",164); takepassword(pass); 
	
					    login = IniciarSesion(usuarios, user, pass);
				        
						if (login == false)
						{
							printf("\n\n- Datos Incorrectos, usuario no encontrado.");
									  			 			   					 
						}

				        break;
					}
		
			case 2: {
			            if(login == true) RegistrarSocio();
						else printf("\nPrimero debe Iniciar Sesi%cn!\n\n", 162);		 	            
						break;
					}

			case 3: {
					    if(login == true) RegistrarTurnos();
						else printf("\nPrimero debe Iniciar Sesi%cn!\n\n", 162);		 		  					    
						break;
					}

			case 4: {
	                    if(login == true) ListarSocios();
						else printf("\nPrimero debe Iniciar Sesi%cn!\n\n", 162);                   
						break;
					}

			case 5: {
						if(login == true) ListarFechasPago();
						else printf("\nPrimero debe Iniciar Sesi%cn!\n\n", 162);
						break;
					}
            
			case 0: {
						printf("Fin del programa...");
						break;
					}

			default: {
						printf("Error. Opci%cn incorrecta...",162);
						break;
					}
			
		};
		
		printf("\n\n");
		system("pause");
	} while (opc != 0);
	
fclose(usuarios);
	
}


/*DESCRIPCION DE FUNCIONES*/


/************************************************************************************************************************************************
Nombre: IniciarSesion(FILE *AuxE, int leg, char pass[32])
Descripcion: Verifica si el Usuario y Contraseña existen.
Funcion con tipo de Retorno Booleano (bool).
Recibe 3 Parametros: Primero el puntero al archivo que queremos leer, segundo el nombre de usuario a validar y tercero la contraseña a validar.

************************************************************************************************************************************************/


bool IniciarSesion(FILE *RECEP, char usu[10], char pass[32])
{
	RegistroUsuario check;
	bool bandera = false;
	
	// Paso 1 - Rebobinar el archivo, ubicar el puntero al principio del archivo
	rewind(RECEP);
	

	// Paso 2 - Intentar extraer el siguiente registro
	fread(&check, sizeof(RegistroUsuario), 1, RECEP);

	
	// Paso 3 - Se ejecutarán las instrucciones del WHILE, mientras no sea fin de archivo (y &&) no se haya encontrado el registro
	while( (!feof(RECEP)) && (bandera == false))
	{
		if( (strcmp(usu, check.Username) == 0) && (strcmp(pass, check.Password) == 0) ) // string compare con retorno de tipo int, retorna un 0 cuando las cadenas son iguales
			{	 	 	
				Beep(800,200);
		 	    printf("\n\n- Accediste al Sistema como %c%s%c.\n\n", 34, check.ApellidoyNombre, 34);
	            // Indicar que se encontró el registro
			    bandera = true;	
			}
	 	else
		 	{
			  	// Paso 5 - Intentar extraer el siguiente registro
				   		  	
   		        fread(&check, sizeof(RegistroUsuario), 1, RECEP);
						
			}

	}		  	  
		
	return bandera;

}


/*******************************************************************************************************************************************
Nombre: takepassword(char pwd[50])
Descripcion: Recibe la cadena ingresada en main la cual es reflejada en el parametro formal pwd[50] para convertir los caracteres en asteriscos 
Funcion sin tipo de Retorno (void).
Recibe un Parametro de tipo vector de caracteres o string.

*******************************************************************************************************************************************/


void takepassword(char pwd[50])
{
	int i;
	char ch;
	
	while(1)
	{
		ch = getch();
		if(ch == ENTER || ch == TAB){
			pwd[i] = '\0';
			break;
		}else if(ch == BCKSPC){
			if(i>0){
				i--;
				printf("\b \b");
			}
		}else{
			pwd[i++] = ch;
			printf("* \b");
		}
	}
}


/*******************************************************************************************************************************************
Nombre: int Menu()
Descripcion: Nos sirve para visualizar el Menu Principal 
Funcion con tipo de Retorno Entero (int). Retorna la opcion para ingresar en el switch del main.
No recibe Parametros.

*******************************************************************************************************************************************/


int Menu()
{
	int opcion = 0;
	
    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
    printf("     \xcd\xcd\xcd\xcd\xcd\xcd M%cDULO RECEPCI%cN \xcd\xcd\xcd\xcd\xcd\xcd\n",224,224);
    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	printf("\n1- Iniciar Sesi%cn",162);
	printf("\n2- Registrar Socio");
	printf("\n3- Registrar Actividades de Socios");
	printf("\n4- Listar Socios");
	printf("\n5- Listar Fechas de Pago");
	printf("\n0- Cerrar la Aplicaci%cn",162);
	printf("\n\nOpcion: ");
	scanf("%d", &opcion);
	
	return opcion;
}


/**********************************************************************************************************************************************
Nombre: RegistrarSocio()
Descripcion : Registra los Socios del Gimnasio.
Funcion sin tipo de Retorno (void).
No recibe Parametros.

**********************************************************************************************************************************************/


void RegistrarSocio()
{
	FILE *archi = fopen("Socios.dat", "a+b");
	RegistroSocio regi;
	
	int nroReg=0; //Variable contador del nro de registros almacenado.
    char continua='N';
 
 
 do{
 	
    system("CLS");
    printf("\t****************************\n");
    printf("\t     ** REGISTRO %d **\n", ++nroReg);
    printf("\t****************************\n"); 
	
	do{
	_flushall();
	printf("\n- N%cmero de Socio(m%cx. 4 d%cgitos): ", 163,160,161);
	scanf("%d", &regi.nrosocio);
	} while(regi.nrosocio > 9999);
	
	_flushall();
	printf("\n- DNI: "); 
	scanf("%d", &regi.dni);
	
	printf("\n- Nombre y Apellido: "); 
	_flushall(); 
	gets(regi.apellidoNombre);
	
	printf("\n- Ingresar Patolog%ca, si es que presenta alguna: ",161);
	gets(regi.patologia);
	
	printf("\n- Edad: ");
	_flushall();
	scanf("%d", &regi.edad);
	
	printf("\n- Altura(m): ");
	scanf("%f", &regi.altura);
	
	printf("\n- Peso(kg): ");
	scanf("%f", &regi.peso);
	
	printf("\n- Domicilio: ");
	_flushall();
	gets(regi.domicilio);
	
	printf("\n- N%cmero de Tel%cfono: ",163,130);
	gets(regi.nrocelular);
	
	_flushall();
	printf("\n- Fecha de Ingreso\n");
	printf("\n- D%ca: ",161);
	scanf("%d", &regi.fechaIngreso.dd);
	
	printf("\n- Mes: ");
	scanf("%d", &regi.fechaIngreso.mm);
	
	printf("\n- A%co: ",164);
	scanf("%d", &regi.fechaIngreso.aaaa);

	
	regi.borrado = false;
	
	// Ubicar el puntero al final del archivo
	fseek(archi, 0, SEEK_END);
	
	// Escribir el registro en el archivo
	fwrite(&regi, sizeof(regi), 1, archi);
	
	printf("\n\n- El socio se agreg%c exitosamente...",162);
	
    _flushall();
    printf("\n\n- Desea registrar otro Socio? (S/N): ");
    scanf("%c", &continua);
 
    } while(continua == 'S' || continua == 's');
	
	fclose(archi);
	
}

/**********************************************************************************************************************************************
Nombre: ListarFechasPago()
Descripcion : Realiza un listado de las fechas de pago de cada socio.
Funcion sin tipo de Retorno (void).
No recibe Parametros.

**********************************************************************************************************************************************/


void ListarFechasPago()
{
	FILE *AuxS = fopen("Socios.dat", "rb");
	
	RegistroSocio S;
	
	printf("\n");
	printf("%-30s%-30s%-30s\n","   SOCIO", " FECHA DE PAGO", " NRO SOCIO");
	printf("%-30s%-30s%-30s\n\n", "  \xcd\xcd\xcd\xcd\xcd\xcd\xcd", "\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd", "\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
	
	//fseek(AuxT, 0, SEEK_SET);
	fread(&S, sizeof(RegistroSocio), 1, AuxS);
	
	while(!feof(AuxS))
	{
      printf("%-30s%5d/%d/%d%25d", S.apellidoNombre, S.fechaIngreso.dd,S.fechaIngreso.mm+1,S.fechaIngreso.aaaa, S.nrosocio);
      printf("\n\n");
      fread(&S, sizeof(RegistroSocio), 1, AuxS);
      
	}
	
	printf("\n\n");
	fclose(AuxS);
	
}

/**********************************************************************************************************************************************
Nombre: ListarSocios()
Descripcion : Realiza un listado de los Socios y las actividades que realizan, con su respectivo entrenador y horario.
Funcion sin tipo de Retorno (void).
No recibe Parametros.

**********************************************************************************************************************************************/


void ListarSocios()
{
	FILE *AuxT = fopen("Turnos.dat", "rb");
	
	RegistroTurno T;
	int contador = 0;
	

	printf("\n");
	printf("%-30s%-30s%-30s%-30s\n","  SOCIO", "ACTIVIDAD"," ENTRENADOR", "HORARIO");
	printf("%-30s%-30s%-30s%-30s\n\n", "  \xcd\xcd\xcd\xcd\xcd\xcd", "\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd","\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd", "\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
	
	rewind(AuxT);
	fread(&T, sizeof(RegistroTurno), 1, AuxT);
	
	while(!feof(AuxT))
	{
      printf("%-30s%-30s%-30s%6.2f", T.Socio, T.Actividad, T.Entrenador, T.Horario);
      printf("\n\n");
      fread(&T, sizeof(RegistroTurno), 1, AuxT);
      
	}
	
	printf("\n\n");
	fclose(AuxT);
	
}

/**********************************************************************************************************************************************
Nombre: RegistrarTurnos()
Descripcion : Los socios registran un turno para determinada actividad y con un entrenador a eleccion.
Funcion sin tipo de Retorno (void).
No recibe Parametros.

**********************************************************************************************************************************************/



void RegistrarTurnos() 
{
	
	FILE *AuxS = fopen("Socios.dat", "rb");
	FILE *AuxT = fopen("Turnos.dat", "a+b");
	FILE *AuxE = fopen("Entrenadores.dat", "rb");

	RegistroEntrenador E;
	RegistroTurno T;
	RegistroSocio S;

	
	bool flag = false;
	int leg=0, nroS=0, clientes = 0, pago = 0;
	char actividad[50];
	int continua = -1;
	
	
	do
	{
	
	system("cls");
	printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
    printf("      \xcd\xcd\xcd REGISTRO DE ACTIVIDAD \xcd\xcd\xcd\n");
    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");

	printf("\n- Nro de Socio: ");
	_flushall();
	scanf("%d", &nroS);
	
	rewind(AuxS);
	fread(&S, sizeof(RegistroSocio), 1, AuxS);
	
	while(!feof(AuxS))
	{
		if(nroS == S.nrosocio)
		{
		   printf("\n- Hola %s, ingres%c el Legajo del entrenador que buscas.\n", S.apellidoNombre, 160);
		   nroS = T.NroSocio;
		   strcpy(T.Socio,S.apellidoNombre);		
           printf("\n- Legajo del Entrenador: ");
	       _flushall();
           scanf("%d", &leg);
		   
		}
		 
        else
        {
        	fread(&S, sizeof(RegistroSocio), 1, AuxS);
		}
	}
	
	rewind(AuxE);
	fread(&E, sizeof(RegistroEntrenador), 1, AuxE);
	
	while(!feof(AuxE))
	{
		if(leg == E.Legajo)
        {
        	T.LegajoEntrenador = leg;
			printf("\n- Elegiste a %s.", E.ApellidoNombre);
        	strcpy(T.Entrenador,E.ApellidoNombre);
        	printf("\n\n- Qu%c actividad quer%cs entrenar?: ", 130, 130);
        	_flushall();
        	gets(T.Actividad);
        	printf("\n- En qu%c horario te gustar%ca venir?: ", 130, 161);
        	_flushall();
        	scanf("%f", &T.Horario);
        	flag = true;
        	break;
		}
		 
		// Leer el siguiente registro del archivo AuxE											 
	    else
		{
		 	fread(&E, sizeof(RegistroEntrenador), 1, AuxE);
		}				   
	}
	
	if(flag == true)
	{
	    printf("\n- Perfecto. Se registr%c exitosamente.",162);
		T.Borrado = false;    
      	fwrite(&T, sizeof(RegistroTurno), 1, AuxT);
	}

    _flushall();
    printf("\n\n- Desea registrar otra Actividad? (SI = 1/NO = 0): ");
    scanf("%c", &continua);
 
    } while(continua == 1);
    
    
fclose(AuxE);
fclose(AuxT);
fclose(AuxS);

}



// FIN DEL PROGRAMA
/*****************************************************************************************************************************************/

