/*----------- Librerías -------------------*/

#include <stdlib.h>
#include<string.h>
#include<windows.h>
#include<stdio.h>
#include<ctype.h>
#include<dos.h>
#include<time.h>
#include<conio.h>
#define RETURNTIME 15
#define ENTER 13
#define TAB 9
#define BCKSPC 8


/*******************************************************************************************************************************************/
/* Estructuras  */

struct fecha
{
	int dd;
	int mm;
	int aaaa;	
};


struct RegistroEntrenador
{
	char ApellidoNombre[60];
	int  Legajo;
	char ClaveIngreso[32];
	int  Horas;
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


/*******************************************************************************************************************************************/
/*----------- Prototipos de Funciones -------------------*/

int Menu();
bool IniciarSesion(FILE *AuxE, int leg, char pass[32]);
void takepassword(char pwd[50]);
void registrarRutinas();
void ListarSocios();


/*******************************************************************************************************************************************/
/* Funcion Principal  */ 

main()
{
	int opc = 0;
	char pass[32];
	int leg = 0;
	bool login = false;
	
	system("color 1F");	
	
	FILE *archivo = fopen("Entrenadores.dat", "rb");
	
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
                        printf("   \xcd\xcd\xcd\xcd INICIAR SESI%cN ENTRENADORES \xcd\xcd\n", 224);
                        printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	 
	                    printf("\n- Ingrese legajo: ");
	                    _flushall(); scanf("%d", &leg);	                   
	                    printf("\n- Ingrese Contrase%ca: ",164);
						_flushall(); takepassword(pass); 
	
					    login = IniciarSesion(archivo, leg, pass);

				   	   	break;
				    }
			

			case 2: {	if(login == true)
						{
							ListarSocios();
											   		  					
					    }
						else printf("\n- Primero debe Iniciar Sesi%cn!\n\n", 162);
				    	
						break;
				    }


			case 3: {	if(login == true)
						{
 
						registrarRutinas();
												  																																				
	   	                }
						  																																												   	 
						else
							{
							  printf("\n- Primero debe Iniciar sesion!\n\n");																									
					        }																																												
					   	  	break;	
				    }
		    
			case 0: {
							printf("\n- Fin del programa...");
				   	   		 break;
				    }

			default: {
						printf("Error. Opci%cn incorrecta...", 162);
				   	    break;
				     }
				    
		};	
		
		
		printf("\n\n");
		system("pause");
		
	} while ( opc != 0);
	
	
	fclose(archivo);
	
}


/*DESCRIPCION DE FUNCIONES*/


/*******************************************************************************************************************************************
Nombre: Menu()
Descripcion: Nos sirve para visualizar el Menu Principal 
Funcion con tipo de Retorno Entero (int). Retorna la opcion para ingresar en el switch del main.
No recibe Parametros.

*******************************************************************************************************************************************/


int Menu()
{
	int opcion = 0;
	
	printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
    printf("      \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd M%cDULO GYM \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n",224,224);
    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	printf("\n1- Iniciar Sesi%cn",162);
	printf("\n2- Visualizar Listado de Socios y Actividad que Desarrolla. ");
	printf("\n3- Registrar Rutinas");
	printf("\n0- Cerrar la Aplicaci%cn.",162);
	printf("\n\nOpci%cn: ", 162);scanf("%d", &opcion);
	

	return opcion;
}


/*******************************************************************************************************************************************
Nombre: IniciarSesion(FILE *AuxE, int leg, char pass[32])
Descripcion: Verifica si el Usuario y Contraseña existen.
Funcion con tipo de Retorno Booleano (bool).
Recibe 3 Parametros: Primero el puntero al archivo que queremos leer, segundo el legajo a validar y tercero la contraseña a validar.

*******************************************************************************************************************************************/


bool IniciarSesion(FILE *AuxE, int leg, char pass[32])
{
	
	RegistroEntrenador log;
	bool iniciado = false;
	int valor;

	
	rewind(AuxE);
    fread(&log, sizeof(RegistroEntrenador), 1, AuxE);
    
	
	while(!feof(AuxE))
    {
        valor = strcmp(pass, log.ClaveIngreso);
        
        if(leg == log.Legajo)
		{
			if(valor == 0)
			{	
		        Beep(800,200);
				printf("\n\n- Accediste al Sistema como %c%s%c.\n\n", 34, log.ApellidoNombre, 34);
				iniciado = true;
			}

		}
        fread(&log, sizeof(RegistroEntrenador), 1, AuxE);
    }
    
    if(iniciado == false) printf("\n\nEl nombre de usuario y/o contrasena no coinciden\n\n");
    return iniciado;
    
}


/*******************************************************************************************************************************************
Nombre: takepassword(char pwd[50])
Descripcion: Recibe la cadena ingresada en main la cual es reflejada en el parametro formal pwd[50] para convertir los caracteres en asteriscos 
Funcion sin tipo de Retorno (void).
Con un Parametros de tipo vector de caracteres o string.

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
Nombre: registrarRutinas()
Descripcion : Registra las Rutinas para Cada Cliente.
Funcion sin tipo de Retorno (void).
Sin Parametros.

*******************************************************************************************************************************************/


void registrarRutinas()
{
	FILE *rutinas = fopen("Rutinas.txt", "a+");
	char cadena[380];
	
	if(rutinas == NULL)
	{
		printf("Error. No se pudo abrir el archivo.\n\n");
        exit(EXIT_FAILURE);
	}
	
	system("cls");
	
	printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
    printf("        \xcd\xcd\xcd\xcd\xcd\xcd\xcd  RUTINAS \xcd\xcd\xcd\xcd\xcd\xcd\xcd\n", 224);
    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	
	
	printf("\n- Ingresar 'fin' para finalizar la carga de la Rutina\n\n");
    
	do
	{
		_flushall();
		gets(cadena);
		
		if ( strcmp(strlwr(cadena), "fin") != 0 )
		{
			fputs(strcat(cadena, "\n"), rutinas);
		}
		
	} while ( strcmp(strlwr(cadena), "fin") != 0 );
	

	printf("\n- Rutina Registrada\n");

    fclose(rutinas);
    
}



/*****************************************************************************************************************************************
Nombre: ListarSocios()
Descripcion : Realiza un Listado de Socios y las actividades que realizan, con su respectivo entrenador y horario.
Funcion sin tipo de Retorno (void).
Sin Parametros.

*****************************************************************************************************************************************/


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


// FIN DEL MODULO GYM