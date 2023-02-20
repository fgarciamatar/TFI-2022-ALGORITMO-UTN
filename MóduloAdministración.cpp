/************************************* LIBRERIAS ***********************************************/
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

/************************************* VARIABLES GLOBALES **************************************/

const int TAMANO = 50;


/************************************* ESTRUCTURAS DE DATOS *************************************/

struct fecha
{
	int dd;
	int mm;
	int aaaa;	
};

struct RegistroUsuario
{
	// Usuario de Recepción o Administración
	char Username[10];
	char Password[32];
	char ApellidoyNombre[60];
	bool Borrado;
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
	bool  Borrado;

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

/************************************* PROTOTIPOS DE FUNCIONES *************************************/

int  Menu();
bool IniciarSesion(FILE *RECEP, char usu[10], char pass[32]);
int  RegistrarUsuarios(FILE *RECEP);
void takepassword(char pwd[50]);
int  CheckUser(FILE *archi, char user[10]);
void Condiciones();
void RegistrarEntrenador(); 
void RegistrarActividad();
int  CalcularPago();
void OrdenarMayorCargaHoraria(RegistroEntrenador vec[TAMANO], int &N);


/************************************* FUNCION PRINCIPAL ******************************************/

main(void)
{

	int opc = 0, pago = 0, saldo = 0, N = 0;
	char user[10], pass[32];
	bool login = false;
	
	RegistroEntrenador vector[TAMANO];
	
	system("color 1F");
	
	FILE *archivo;
	archivo = fopen("Usuarios.dat", "a+b");
	
	if (archivo == NULL)
	{
		// Intento crear el archivo nuevamente
		archivo = fopen("Usuarios.dat", "a+b");
		
		if (archivo == NULL)
		{
			printf("\n- Error. No se pudo crear el archivo");
			exit(1);
		}
	}

	
	do 
	{
		system("cls");	
		opc = Menu();
		system("cls");	
		
		switch (opc)
		{
			case 1: {
					    system("cls");
	                    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
                        printf("      \xcd\xcd\xcd\xcd\xcd\xcd  INICIAR SESI%cN \xcd\xcd\xcd\xcd\xcd\xcd\n", 224);
                        printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	 
	                    printf("\n- Ingrese Nombre de Usuario: ");
	                    _flushall(); gets(user);	                   
	                    printf("\n- Ingrese Contrase%ca: ",164); takepassword(pass); 
	
					    login = IniciarSesion(archivo, user, pass);
				        
						if (login == false)
						{
							printf("\n\n- Datos Incorrectos, usuario no encontrado.");
										  			 			   					 																								
						}

				        break;
					}
		
			case 2: {
						RegistrarUsuarios(archivo);				  					 
				        break;
					}

			case 3: {
			            if (login == true) RegistrarEntrenador();
						else printf("\n- Inicie Sesi%cn, por favor.",162);				  					 
				        
						break;
					}
		   
		   case 4: {
			            if (login == true) RegistrarActividad();
						else printf("\n- Inicie Sesi%cn, por favor.",162);				  					 
						break;
					}

			case 5: { 
			            if (login == true)
						{
						pago = CalcularPago();								  
						printf("\n\n- Su Pago Total es: %c%d\n", 36, pago);				 	  	 																  
						}
						 			  	 	  		
						else printf("\n- Inicie Sesi%cn, por favor.",162);

						break;
					}

			case 6: {
						if (login == true) OrdenarMayorCargaHoraria(vector, N);				   	   		 	   			   
						else printf("\n- Inicie Sesi%cn, por favor.",162);
						break;
					}
            
            case 7: {
						Condiciones();
						break;
					}
			
			case 0: {
						printf("Fin del programa...");
						break;
					}

			default: {
						printf("Error. Opcion incorrecta...");
						break;
					}
			
		};
		
		printf("\n\n");
		system("pause");
	} while (opc != 0);

	fclose(archivo);


}


/*DESCRIPCION DE FUNCIONES*/


/************************************************************************************************************************************************
Nombre: RegistrarEntrenador()
Descripcion: Registra a los Entrenadores en el sistema.
Funcion sin tipo de Retorno (void).
No recibe Parametros.

************************************************************************************************************************************************/


void RegistrarEntrenador()
{
	
	FILE *AUX = fopen("Entrenadores.dat", "a+b");
	int c,n=0, p=0, mayus=0, digitos=0, minus=0, mayus2=0, digitos2=0, simb=0, b=0, c1=0, x, horas = 0;
	bool digitoscons = false;
	
	RegistroEntrenador regi;

    system("cls");
    
	printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
    printf("         \xcd\xcd\xcd\xcd\xcd\xcd  REGISTRAR ENTRENADOR \xcd\xcd\xcd\xcd\xcd\xcd\n");
    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	 
	
	printf("\n- Nombre y Apellido: ");
    _flushall();
    gets(regi.ApellidoNombre);
    
	do{
	printf("\n- Ingrese Legajo(max. 4 digitos): ");
	_flushall();
	scanf("%d", &regi.Legajo);
    } while(regi.Legajo > 9999);
    
	
	printf("\n- Contrase%ca: ", 164);
	_flushall();
	gets(regi.ClaveIngreso);
    p = strlen(regi.ClaveIngreso);
          
          if((p >= 6)&&(p <= 32))
          {
          	
		    for(int i = 0; i < p; i++)
	        {
	            if((regi.ClaveIngreso[i] >= 97) && (regi.ClaveIngreso[0] <= 122)) {minus++;}
	            
				if ((regi.ClaveIngreso[i] >=65) && (regi.ClaveIngreso[i] <=90)) {mayus2++;}
	            
				if(isdigit(regi.ClaveIngreso[i])){ digitos2++;} 
                
				if( (regi.ClaveIngreso[i]>=32 && regi.ClaveIngreso[i]<=47 ) || (regi.ClaveIngreso[i]>=58 && regi.ClaveIngreso[i]<=64) || (regi.ClaveIngreso[i] > 122) )  {simb++;}	
                
				if (regi.ClaveIngreso[i]>=48 && regi.ClaveIngreso[i]<=57)
                    {
                        b = regi.ClaveIngreso[i] + 1;
                        c1= regi.ClaveIngreso[i] + 1;

                        if ((regi.ClaveIngreso[i+1] == b) && (regi.ClaveIngreso[i+2] == c1))
                        {
                            digitoscons = true;
 
                        }                    
                    } 
                    
			}
            
            if((minus>=1) && (mayus2>=1) && (digitos2>=1))
            {
            	if(simb==0)
            	{
            		if(digitoscons == false)
		            {
             	      printf("\n- Horas Diarias de Atenci%cn: ", 162);
             		  _flushall();
					  scanf("%d", &horas);      
      	              horas = (horas * 6) * 4;
			          regi.Horas = horas;
				      // Igualar el campo borrado a false, para indicar que cada registro que se guarde está activo para determinada operacion
					  regi.borrado = false;
	                  // Ubicar el puntero al final del archivo
	                  fseek(AUX, 0, SEEK_END);
	                  // Escribir el registro en el archivo
	                  fwrite(&regi, sizeof(RegistroEntrenador), 1, AUX);
	                  printf("\n- El Entrenador se agreg%c exitosamente.",162);	
					  getch(); 
				      
                       do{
                       printf("\n\n- Desea agregar otro entrenador? (SI:1 , NO:0): ");
                       scanf("%d" ,&x);
                       }while (x!=0 && x!=1);		   	        
             	       
          		       if (x==1) RegistrarEntrenador();
					}
					  	  
    	            else{
         	              printf("\n- No debe tener m%cs de 3 caracteres num%cricos consecutivos",160,130);
   		                  getch();
                            
					    }
            	
	
				}
				 			
            	else
            	{
            		printf("\n- La Contrase%ca no debe tener caracteres de puntuaci%cn, ni acentos, ni espacios, solo alfanum%cricos.",164,162,130);
            		getch();
                    
				}
            	
			}
			else
			{
 		        printf("\n- La Contrase%ca debe tener al menos una may%cscula, una min%cscula y un d%cgito en la misma palabra.",164,163,163,161);
 				getch();
                
			}			  
	  
          	
		  }
          else
          {
          printf("\n- La Contrase%ca ingresada debe contener entre 6 y 32 caracteres estrictamente.",164);
          getch();
          
          }  


fclose(AUX);

}


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
    printf("   \xcd\xcd\xcd\xcd\xcd\xcd M%cDULO ADMINISTRACI%cN \xcd\xcd\xcd\xcd\xcd\xcd\n",224,224);
    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	printf("\n1- Iniciar Sesi%cn",162);
	printf("\n2- Registrar Usuario de Recepci%cn",162);
	printf("\n3- Registrar Entrenador");
	printf("\n4- Registrar Actividades del Gym");
	printf("\n5- Calcular Pago al Entrenador");
	printf("\n6- Entrenador con mayor carga horaria");
	printf("\n7- Ver Condiciones de Registro");
	printf("\n0- Salir");
	printf("\n\nOpci%cn: ", 162);
	scanf("%d", &opcion);
	
	return opcion;
}

/************************************************************************************************************************************************
Nombre: CheckUser(FILE *archi, char user[10])
Descripcion: Valida si el nombre de usuario ya existe.
Funcion con tipo de Retorno Entero (int).
Recibe dos Parametros, el primero de tipo puntero al archivo Usuarios.dat y segundo la cadena ingresada para el nombre de usuario.

************************************************************************************************************************************************/


int CheckUser(FILE *archi, char user[10])
{
	RegistroUsuario regi;
	int check = 1;
	
	// Paso 1 - Rebobinar el archivo
	rewind(archi);
	//fseek(archi, 0, SEEK_SET);
	
	
	// Paso 2 - Intentar extraer el siguiente "dato" (variable simple o registro) del archivo
	fread(&regi, sizeof(regi), 1, archi);
	
	
	// Paso 3 - Mientras no sea FIN DE ARCHIVO (EOF)
	while (!feof(archi))
	{
		// Paso 4 - Procesar el dato actual
		
		if (regi.Borrado == false)
		{
		 	check = strcmp(regi.Username,user);
		}
	
	// Paso 5 - Intentar extraer el siguiente dato o registro
		fread(&regi, sizeof(regi), 1, archi);
		
	} // while
	
	return check;
	
}


/************************************************************************************************************************************************
Nombre: RegistrarUsuarios(FILE *RECEP)
Descripcion: Registra a los Administradores del sistema.
Funcion con tipo de Retorno Entero (int).
Recibe un Parametro de tipo puntero al archivo Usuarios.dat, se lo envia en modo lectura/escritura.

************************************************************************************************************************************************/


int RegistrarUsuarios(FILE *RECEP)
{
	
	system("cls");
	RegistroUsuario a;
    int c,n=0, p=0, mayus=0, digitos=0, minus=0, mayus2=0, digitos2=0, simb=0, b=0, c1=0;
	bool dcons = false;
	
	printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
    printf("        \xcd\xcd\xcd\xcd\xcd\xcd  REGISTRO \xcd\xcd\xcd\xcd\xcd\xcd\n");
    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
		
    printf("\n- UserName: ");
    _flushall();
    gets(a.Username);
    c = CheckUser(RECEP,a.Username);
    
    do
    {
	
	if(c == 0)
    {
    	printf("\n- El Usuario ya existe.\n\n- ");
    	system("pause");
    	RegistrarUsuarios(RECEP);
	} 
    
	} while (c == 0);
	
    
    n = strlen(a.Username);    
	
	
	
    if((n >= 6)&&(n <= 10)){

    if((a.Username[0] >= 97) && (a.Username[0] <= 122))
    {
    	
	for(int i = 0; i < n; i++)
	{
    
	 if(isupper(a.Username[i])){ mayus++;}  //Si es mayuscula aumenta el contador
	 //if ((a.Username[i] >=65) && (a.Username[i]) <=90) {mayus++;}
	 if(isdigit(a.Username[i])){ digitos++;} //Si es un digito aumenta el contador
                        
    }
    
    if(mayus>=2)
    {
    	if(digitos>=1 && digitos<=3)
    	{
		      
		  printf("\n- Contrase%ca: ", 164);
          gets(a.Password);
          p = strlen(a.Password);
          
          if((p >= 6)&&(p <= 32))
          {
          	
		    for(int i = 0; i < p; i++)
	        {
	            if((a.Password[i] >= 97) && (a.Password[0] <= 122)) {minus++;}
	            
				if ((a.Password[i] >=65) && (a.Password[i] <=90)) {mayus2++;}
	            
				if(isdigit(a.Password[i])){ digitos2++;} 
                
				if( (a.Password[i]>=32 && a.Password[i]<=47 ) || (a.Password[i]>=58 && a.Password[i]<=64) || (a.Password[i] > 122) )  {simb++;}	
                
				if (a.Password[i]>=48 && a.Password[i]<=57)
                    {
                        b = a.Password[i] + 1;
                        c1= a.Password[i] + 1;

                        if ((a.Password[i+1] == b) && (a.Password[i+2] == c1))
                        {
                            dcons = true;
 
                        }                    
                    } 
                    
			}
            
            if((minus>=1) && (mayus2>=1) && (digitos2>=1))
            {
            	if(simb==0)
            	{
            		if(dcons == false)
		            {
             	      printf("\n- Nombre y Apellido: ");
                      _flushall();
                      gets(a.ApellidoyNombre);
				      a.Borrado = false;
	                  // Ubicar el puntero al final del archivo
	                  fseek(RECEP, 0, SEEK_END);
	                  // Escribir el registro en el archivo
	                  fwrite(&a, sizeof(RegistroUsuario), 1, RECEP);
	                  printf("\n- El Usuario se agreg%c exitosamente.",162);	
					  getch(); 
				      return 1;
             	      
					}
					  	  
    	            else{
         	              printf("\n- No debe tener m%cs de 3 caracteres num%cricos consecutivos",160,130);
   		                  getch();
                          return 0;  
					    }
            	
	
				}
				 			
            	else
            	{
            		printf("\n- La Contrase%ca no debe tener caracteres de puntuaci%cn, ni acentos, ni espacios, solo alfanum%cricos.",164,162,130);
            		getch();
                    return 0;
				}
            	
			}
			else
			{
 		        printf("\n- La Contrase%ca debe tener al menos una may%cscula, una min%cscula y un d%cgito en la misma palabra.",164,163,163,161);
 				getch();
                return 0; 
			}			  
	  
          	
		  }
          else
          {
          printf("\n- La Contrase%ca ingresada debe contener entre 6 y 32 caracteres estrictamente.",164);
          getch();
          return 0;
          }  
    		
        }
       	
	    else
        {      
        printf("\n- El UserName ingresado debe tener como m%cximo 3 d%cgitos.", 160, 161);
        getch();
        return 0;
        }

	}
	
	else
    {
       
        printf("\n- El UserName ingresado debe tener al menos dos may%csculas.", 163);
        getch();
        return 0;

    }

}

    else
{

      printf("\n- El UserName ingresado debe comenzar con una min%cscula.", 163);
      getch();
      return 0;

}



}

else
{

printf("\n- El UserName ingresado debe contener entre 6 y 10 caracteres estrictamente.");
getch();
return 0;

}



}

/************************************************************************************************************************************************
Nombre: RegistrarActividad()
Descripcion: Registra las Actividades del Gimnasio.
Funcion sin tipo de Retorno (void).
No recibe Parametros.

************************************************************************************************************************************************/


void RegistrarActividad()
{
	FILE *AuxA = fopen("Actividades.dat", "a+b");
	FILE *AuxE = fopen("Entrenadores.dat", "rb");

	
	RegistroActividad m;
	RegistroEntrenador t;
	
	int Leg=0, x;
	bool bandera = false;
	float hora;
	char actividad[50];
	
	system("cls");
	
	printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
    printf("     \xcd\xcd\xcd  REGISTRO DE ACTIVIDAD \xcd\xcd\xcd\n");
    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");

	
	printf("\n\n- Actividad: ");
    _flushall();
    gets(m.Actividad);
    
    printf("\n- Horario: ");
    _flushall();
    scanf("%f", &m.Horario);
    
    do
    {
    	
    printf("\n- Legajo del Entrenador: ");
	_flushall();
    scanf("%d", &Leg);
	
	rewind(AuxE);
	fread(&t, sizeof(RegistroEntrenador), 1, AuxE);
	

	
	while( (!feof(AuxE)) && (bandera == false) )
	{

      if(Leg == t.Legajo)
       {
      	
      	printf("\n- Entrenador a cargo: %s", t.ApellidoNombre);
      	strcpy(m.Entrenador,t.ApellidoNombre);  // Copiar lo del segundo parametro al primero
        m.Borrado = false; // Registro Activo
        fseek(AuxA, 0, SEEK_END); // Ubicar puntero al final del archivo
        fwrite(&m, sizeof(RegistroActividad), 1, AuxA); // Grabar los datos en el archivo
        bandera = true; // se encontro el entrenador con ese legajo ingresado
        
        
	   }
	    
	  else
	  {
  	    //printf("\n- No se encontr%c un entrenador con el Legajo ingresado.", 162);
	    fread(&t, sizeof(RegistroEntrenador), 1, AuxE);	
	  }
     
	}
	
	if(bandera == true)
	{
		printf("\n\n- Actividad registrada con %cxito.", 130);
	}
	
	else
	{
		printf("\n- No se encontr%c al Entrenador.", 162);
	}
    
    
    } while(bandera == false);
    
    
    fclose(AuxA);
    fclose(AuxE);
    
}


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
Nombre: CalcularPago()
Descripcion: Calcula el pago mensual y pago extra de determinado entrenador. 
Funcion con tipo de Retorno Entero (int). 
No recibe Parametros.

*******************************************************************************************************************************************/


int CalcularPago()
{
	FILE *AuxT = fopen("Entrenadores.dat", "rb");
	RegistroEntrenador T;
	char continua = 'N';
	int leg = 0, clientes = 0, saldo = 0, extra = 0;
	bool flag = false;
	
	rewind(AuxT);
	fread(&T, sizeof(RegistroEntrenador), 1, AuxT);
		
	system("cls");
	printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
    printf("        \xcd\xcd\xcd  CALCULAR PAGO  \xcd\xcd\xcd\n");
    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	
	printf("\n- Legajo del Entrenador: ");
	_flushall();
	scanf("%d", &leg);

	
	while(!feof(AuxT))
	{
		if(leg == T.Legajo)
        {
        	flag = true;
        	break;
		}
	    
		fread(&T, sizeof(RegistroEntrenador), 1, AuxT);
	}
	
	
	if(flag == true)
	{
	printf("\n- Hola %s.", T.ApellidoNombre);
	printf("\n\n- Ingrese la cantidad de clientes que tiene a cargo: ");
	scanf("%d", &clientes);
	extra = clientes * 3500;
	printf("\n- Su Pago por Clientes es: %d", extra);
	saldo = extra + 25000;
	}
	
	else
	{
		printf("\n- El legajo ingresado no est%c registrado.\n", 160);
	}
	

    return saldo;
    fclose(AuxT);
	
}


/*******************************************************************************************************************************************
Nombre: OrdenarMayorCargaHoraria(RegistroEntrenador vec[TAMANO], int &N)
Descripcion: Nos sirve para visualizar el Menu Principal 
Funcion con tipo de Retorno Entero (int). Retorna la opcion para ingresar en el switch del main.
Recibe dos Parametros: El primero es un vector de tipo RegistroEntrenador en el cual se van a volcar los datos del archivo Entrenadores.dat
y el segundo es una variable por referencia para manejar un limite de repeticiones en los bucles.

*******************************************************************************************************************************************/


void OrdenarMayorCargaHoraria(RegistroEntrenador vec[TAMANO], int &N)
{
	RegistroEntrenador regi, aux;
	int i = 0, L = 0; 
	bool bandera = false;
	
	FILE *archi = fopen("Entrenadores.dat", "a+b");
	
	rewind(archi);
	fread(&regi, sizeof(RegistroEntrenador), 1, archi);
	
	while (!feof(archi))
	{
		vec[i] = regi;
		i++;
		
		fread(&regi, sizeof(RegistroEntrenador), 1, archi);
	}
	
	N = i;
	
	L = N - 1;
	
	do
	{
		bandera = false;
		for(int i=0; i<L; i++)
		{
			if (vec[i].Horas < vec[i+1].Horas)
			{
				aux = vec[i];
				vec[i] = vec[i+1];
				vec[i+1] = aux;
				
				bandera = true;
			}
		}
		
		L = L - 1;
		
	} while (bandera == true);
		
	system("cls");
	printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
    printf("    \xcd\xcd\xcd CARGA HORARIA DE ENTRENADORES \xcd\xcd\xcd\n");
    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
	
	for (int i=0; i<N; i++)
	{
		regi = vec[i];
			 
		if ( regi.borrado == false )
		{
			
			printf("\n\n- Entrenador: %s", regi.ApellidoNombre);
			printf("\n- Carga Horaria: %d horas mensuales", regi.Horas);
	        printf("\n- Legajo: %d", regi.Legajo);
			        
			if (regi.borrado == false)
			{
				printf("\n- Estado: ACTIVO");
			}
			else
			{
				printf("\n- Estado: BORRADO");
			}	
			
		}
	}	
	
	printf("\n\n");
	fclose(archi);
	
}

/*******************************************************************************************************************************************
Nombre: Condiciones()
Descripcion: Visualiza las condiciones que se deben cumplir para registrar un nombre de usuario y una clave de ingreso.
Funcion sin tipo de Retorno (void). 
No recibe Parametros.

*******************************************************************************************************************************************/

void Condiciones()
{
	system("cls");
	printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
    printf("        \xcd\xcd\xcd\xcd\xcd\xcd  USERNAME \xcd\xcd\xcd\xcd\xcd\xcd\n");
    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n\n");
    
    printf("a) Ser %cnico para cada usuario registrado.\n", 163);
    printf("b) Comenzar con una letra min%cscula.\n", 163);
    printf("c) Tener al menos 2 letras may%csculas.\n", 163);
    printf("d) Tener como m%cximo 3 d%cgitos.\n", 160,161);
    printf("e) Deber%c tener entre 6 y 10 caracteres.\n", 160);
    printf("\n\n");
    
   	printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
    printf("        \xcd\xcd\xcd\xcd\xcd\xcd  CONTRASE%cA \xcd\xcd\xcd\xcd\xcd\xcd\n", 165);
    printf("   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n\n");
    
    printf("a) Deber%c contener al menos una letra may%cscula, una letra min%cscula y un n%cmero.\n", 160,163,163,163);
    printf("b) No podr%c contener ning%cn caracter de puntuaci%cn, ni acentos, ni espacios. S%clo caracteres alfanum%cricos.\n", 160,163,162,162,130);
    printf("c) Deber%c tener entre 6 y 32 caracteres.\n", 160);
    printf("d) No debe tener m%cs de 3 caracteres num%cricos consecutivos.\n", 160,163);
    printf("e) No debe tener 2 letras alfab%cticamente consecutivas (ascendentemente A-Z).\n", 130);
	printf("\n\n");
    
    
    
}



// FIN DEL MODULO ADMINISTRACION
/********************************************************************************************************************************************/