//
//  Mini-Proyecto 2 - Programación Avanzada
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *ptrFile;
FILE *ptrFile2;
char line[300];

struct _empleado
{
	int id;
	char nombre[50];
	char apellidos[100];
	int idDept;
	char fechaNacim[11];
	char fechaContrat[11];
	char ciudad[50];
	int proyActuales;
	double salario;
};

struct _departamento
{
	int idDept;
	char nombre[80];
	char descripcion[150];
	int piso;
	double presupuesto;
};

struct _usuario
{
	char usuario[50];
	char password[50];
};

int lecturaTabla1(struct _empleado *empleados)
{
	int contEmp = 0;
	
	ptrFile = fopen("table_1.txt", "r");
	
	if (ptrFile != NULL)
	{
		//printf("table_1.txt open\n");
		
		while(!feof(ptrFile))
		{
			while (fgets(line, sizeof(line), ptrFile))
			{
				int state = 0;
				int finished = 0;
				
				// Que no sea la primera línea y que no haya terminado de leer la línea
				while (contEmp != 0 && state < 5)
				{
					char elem[150] = {NULL};
					
					// Obtener primera palabra antes del ;
					char *token = strtok(line, ";");
					strcpy(elem, token);
					
					while (token != NULL && finished == 0)
					{
						switch (state)
						{
							case 0:
								empleados[contEmp - 1].id = atoi(elem);
								break;
							case 1:
								strcpy(empleados[contEmp - 1].nombre, elem);
								break;
							case 2:
								strcpy(empleados[contEmp - 1].apellidos, elem);
								break;
							case 3:
								empleados[contEmp - 1].idDept = atoi(elem);
								break;
							case 4:
								strcpy(empleados[contEmp - 1].fechaNacim, elem);
								break;
							case 5:
								strcpy(empleados[contEmp - 1].fechaContrat, elem);
								break;
							case 6:
								strcpy(empleados[contEmp - 1].ciudad, elem);
								break;
							case 7:
								empleados[contEmp - 1].proyActuales = atoi(elem);
								break;
							case 8:
								empleados[contEmp - 1].salario = atof(elem);
								finished = 1;
								break;
							default:
								printf("done");
						}
						state++;
						
						if (finished != 1)
						{
							// Obtener palabra antes del ;
							token = strtok(NULL, ";");
							strcpy(elem, token);
						}
					}
				}
				
				// Cambiar de línea de registros
				contEmp++;
			}
		}
		
		if (fclose(ptrFile) == 0)
		{
			//printf("table_1.txt closed\n");
		}
		else
		{
			printf("Error in fclose for table_1.txt\n");
		}
	}
	else
	{
		printf("Error in fopen for table_1.txt\n");
	}
	
	return contEmp;
};

int lecturaTabla2(struct _departamento *departamentos)
{
	int contDept = 0;
	
	ptrFile = fopen("table_2.txt", "r");
	
	if (ptrFile != NULL)
	{
		//printf("table_2.txt open\n");
		
		while(!feof(ptrFile))
		{
			while (fgets(line, sizeof(line), ptrFile))
			{
				int state = 0;
				int finished = 0;
				
				// Que no sea la primera línea y que no haya terminado de leer la línea
				while (contDept != 0 && state < 5)
				{
					char elem[150] = {NULL};
					
					// Obtener primera palabra antes del ;
					char *token = strtok(line, ";");
					strcpy(elem, token);
					
					while (token != NULL && finished == 0)
					{
						switch (state)
						{
							case 0:
								departamentos[contDept - 1].idDept = atoi(elem);
								break;
							case 1:
								strcpy(departamentos[contDept - 1].nombre, elem);
								break;
							case 2:
								strcpy(departamentos[contDept - 1].descripcion, elem);
								break;
							case 3:
								departamentos[contDept - 1].piso = atoi(elem);
								break;
							case 4:
								departamentos[contDept - 1].presupuesto = atof(elem);
								finished = 1;
								break;
							default:
								printf("done");
						}
						state++;
						
						if (finished != 1)
						{
							// Obtener palabra antes del ;
							token = strtok(NULL, ";");
							strcpy(elem, token);
						}
					}
				}
				
				// Cambiar de línea de registros
				contDept++;
			}
		}
		
		if (fclose(ptrFile) == 0)
		{
			//printf("table_2.txtclosed\n");
		}
		else
		{
			printf("Error in fclose for table_2.txt\n");
		}
	}
	else
	{
		printf("Error in fopen for table_2.txt\n");
	}
	
	return contDept;
};

void impresionTabla1(struct _empleado *empleados, int contEmp)
{
	for (int i = 0; i < contEmp; i++)
	{
		printf("%d; %s; %s; %d; %s; %s; %s; %d; %0.f;\n", empleados[i].id, empleados[i].nombre, empleados[i].apellidos, empleados[i].idDept, empleados[i].fechaNacim, empleados[i].fechaContrat, empleados[i].ciudad, empleados[i].proyActuales, empleados[i].salario);
	}
};

void impresionTabla2(struct _departamento *departamentos, int contDept)
{
	for (int i = 0; i < contDept; i++)
	{
		printf("%d; %s; %s; %d; %.0f;\n", departamentos[i].idDept, departamentos[i].nombre, departamentos[i].descripcion, departamentos[i].piso, departamentos[i].presupuesto);
	}
	
};

int main(int argc, const char * argv[])
{
	struct _empleado empleados[50] = {NULL, "", "", NULL, "", "", " ", NULL, 0};
	struct _departamento departamentos[20] = {NULL, "", "", NULL, 0};
	int opcion = 0;
	
	// Cantidad de registros
	int contEmp = lecturaTabla1(empleados) - 1;
	int contDept = lecturaTabla2(departamentos) - 1;

	// Menú
	printf("Base de Datos de Empleados y Departamentos\n");
	printf("Opciones:\n");
	printf("1. Ver tabla 1 - Empleados.\n");
	printf("2. Ver tabla 2 - Departamentos.\n");
	printf("3. Hacer query SELECT.\n");
	printf("4. Hacer query JOIN.\n");
	printf("5. Hacer query INSERT.\n");
	printf("0. Salir.\n");
	printf("Teclee la opción deseada: ");
	scanf("%d", &opcion);
	do
	{
		switch (opcion) {
			case 0:
				printf("Proceso terminado. Vuelva pronto.\n");
				break;
			case 1:
				printf("Tabla 1\n");
				impresionTabla1(empleados, contEmp);
				break;
			case 2:
				printf("Tabla 2\n");
				impresionTabla2(departamentos, contDept);
				break;
			case 3:
				printf("Query SELECT\n");
				break;
			case 4:
				printf("Query JOIN\n");
				break;
			case 5:
				printf("\nQuery INSERT\n");
				printf("1. INSERT a Tabla 1 - Empleados\n");
				printf("2. INSERT a Tabla 2 - Departamentos\n");
				printf("0. Regresar al menú\n");
				printf("Teclee la opción deseada: ");
				int insertOpcion = 0;
				scanf("%d", &insertOpcion);
				if (insertOpcion == 1)
				{
					ptrFile2 = fopen("table_1.txt","a");
					if (ptrFile2 != NULL)
					{
						//printf("table_1.txt open\n");
						int id, idDept, proyActuales;
						double salario;
						char temp, nombre[50], apellidos[100], fechaNacim[11], fechaContrat[11], ciudad[50];
						printf("Id (entero): ");
						scanf("%d", &id);
						empleados[contEmp].id = id;
						printf("Nombre (string): ");
						scanf("%c",&temp); // Limpiar buffer
						scanf("%[^\n]", nombre);
						strcpy(empleados[contEmp].nombre, nombre);
						printf("Apellidos (string): ");
						scanf("%c",&temp);
						scanf("%[^\n]", apellidos);
						strcpy(empleados[contEmp].apellidos, apellidos);
						printf("Id de Departamento (entero): ");
						scanf("%d", &idDept);
						empleados[contEmp].idDept = idDept;
						printf("Fecha de Nacimiento (Día/Mes/Año): ");
						scanf("%c",&temp);
						scanf("%s", fechaNacim);
						strcpy(empleados[contEmp].fechaNacim, fechaNacim);
						printf("Fecha de Contratación (Día/Mes/Año): ");
						scanf("%s", fechaContrat);
						strcpy(empleados[contEmp].fechaContrat, fechaContrat);
						printf("Ciudad (string): ");
						scanf("%c",&temp);
						scanf("%[^\n]", ciudad);
						strcpy(empleados[contEmp].ciudad, ciudad);
						printf("Proyectos Actuales (entero): ");
						scanf("%d", &proyActuales);
						empleados[contEmp].proyActuales = proyActuales;
						printf("Salario (double): ");
						scanf("%lf", &salario);
						empleados[contEmp].salario = salario;
						fprintf(ptrFile, "\n%d;%s;%s;%d;%s;%s;%s;%d;%.0f;", id, nombre, apellidos, idDept, fechaNacim, fechaContrat, ciudad, proyActuales, salario);
						contEmp++;
						
						if (fclose(ptrFile2) == 0)
						{
							printf("table_1.txt closed\n");
						}
						else
						{
							printf("Error in fclose for table_1.txt\n");
						}
					}
					else
					{
						printf("Error in fopen for table_1.txt\n");
					}
				}
				else if (insertOpcion == 2)
				{
					ptrFile2 = fopen("table_2.txt","a");
					if (ptrFile2 != NULL)
					{
						//printf("table_2.txt open\n");
						int idDept, piso;
						char temp, nombre[80], descripcion[150];
						double presupuesto;
						printf("Id (entero): ");
						scanf("%d", &idDept);
						departamentos[contDept].idDept = idDept;
						printf("Nombre (string): ");
						scanf("%c",&temp); // Limpiar buffer
						scanf("%[^\n]", nombre);
						strcpy(departamentos[contDept].nombre, nombre);
						printf("Descripción (string): ");
						scanf("%c",&temp);
						scanf("%[^\n]", descripcion);
						strcpy(departamentos[contDept].descripcion, descripcion);
						printf("Piso (entero): ");
						scanf("%d", &piso);
						departamentos[contDept].piso = piso;
						printf("Presupuesto (double): ");
						scanf("%lf", &presupuesto);
						departamentos[contDept].presupuesto = presupuesto;
						fprintf(ptrFile, "\n%d;%s;%s;%d;%.0f;", idDept, nombre, descripcion, piso, presupuesto);
						contDept++;
						
						if (fclose(ptrFile2) == 0)
						{
							printf("File closed\n");
						}
						else
						{
							printf("Error in fclose for table_2.txt\n");
						}
					}
					else
					{
						printf("Error in fopen for table_2.txt\n");
					}
				}
				break;
			default:
				printf("Opción inválida, intente de nuevo.\n");
		}
		printf("\nBase de Datos de Empleados y Departamentos\n");
		printf("Opciones:\n");
		printf("1. Ver tabla 1 - Empleados.\n");
		printf("2. Ver tabla 2 - Departamentos.\n");
		printf("3. Hacer query SELECT.\n");
		printf("4. Hacer query JOIN.\n");
		printf("5. Hacer query INSERT.\n");
		printf("0. Salir.\n");
		printf("Teclee la opción deseada: ");
		scanf("%d", &opcion);
	} while (opcion != 0);
	
	return 0;
}
