#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

char bienvenida[] = "Bienvenido al sistema gestor de bibliotecas, seleccione la opcion deseada\n";

struct Cliente {
	int ID; //Unico
	char nombre[30], apellido[30];
	char correo[30];
	char telefono[10];
	struct Direccion {
		char calle[20];
		char numero[4];
		char colonia[20];
		char codigo_postal[6];
	};
	char notas[100];
};

struct Libro {
	int ID; //Unico
	char titulo[30];
	char autor[30];
	char anno[4];
	char editorial[20];
	char isbn[15];
	char tipo[20];
	char notas[100];
	int precio;
};

int Menu_Clientes(){
	int op;
	system("cls");
	printf(bienvenida);
	printf("Se entro al menu de clientes\n");
	printf("1.-Nuevo Cliente\n");
	printf("2.-Editar Cliente\n");
	printf("3.-Eliminar Cliente\n");
	printf("4.-Regresar al menu principal\n");
	printf("9.-Salir del programa\n");
	printf("Op: ");
	scanf("%d", &op);
	switch(op){
		case 1:
		//	Nuevo_Cliente();
			break;
		case 2:
		//	Editar_Cliente();
			break;
		case 3:
		//	Eliminar_Cliente();
			break;
		case 4:
			Menu_Principal();
			break;
		case 9:
			printf("Gracias por usar nuestro programa, vuelva pronto\n");
			getche();
			return 0;
		default:
			system("cls");
			printf("Opcion no encontrada, favor de seleccionar una opcion valida\n");
			getche();
			Menu_Clientes();
	}
	
}

int Menu_Libros(){
	int op;
	system("cls");
	printf(bienvenida);
	printf("Se entro al menu de libros\n");
	printf("1.-Nuevo Libro\n");
	printf("2.-Editar Libro\n");
	printf("3.-Eliminar Libro\n");
	printf("4.-Regresar al menu principal");
	printf("9.-Salir del programa\n");
	scanf("%d", &op);
	
	switch(op){
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			printf("Gracias por usar nuestro programa, vuelva pronto\n");
			getche();
			Menu_Principal();
			break;
		case 9:
			return 0;
		default:
			system("cls");
			printf("Opcion no encontrada, favor de seleccionar una opcion valida\n");
			getche();
			Menu_Libros();
	}
	return 0;
}

int Menu_Biblioteca(){
	int op;
	system("cls");
	printf(bienvenida);
	printf("Se entro al menu de Biblioteca\n");
	printf("1.-Comprar Libro\n");
	printf("2.-Rentar Libro\n");
	printf("3.-Leer en sala\n");
	printf("4.-Regresar Libro\n");
	printf("5.-Regresar al menu principal\n");
	printf("9.-Salir del programa\n");
	printf("Op: ");
	scanf("%d", &op);
	
	switch(op){
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			Menu_Principal();
			break;
		case 9:
			printf("Gracias por usar nuestro programa, vuelva pronto\n");
			getche();
			return 0;
		default:
			system("cls");
			printf("Opcion no encontrada, favor de seleccionar una opcion valida\n");
			getche();
			Menu_Biblioteca();
	}
	return 0;
}

int Menu_Inventario(){
	int op;
	system("cls");
	printf(bienvenida);
	printf("Se entro al menu de Inventario\n");
}

int Menu_Principal(){
	int op;
	system("cls");
	printf(bienvenida);
	printf("1.- Clientes\n");
	printf("2.- Libros\n");
	printf("3.- Biblioteca\n");
	printf("4.- Inventario\n");
	printf("5.- Salir\n");
	printf("Op: ");
	scanf("%d", &op);
	fflush(stdin);
	switch(op)
	{
		case 1:
			Menu_Clientes();
			break;
		case 2:
			Menu_Libros();
			break;
		case 3:
			Menu_Biblioteca();
			break;
		case 4:
			Menu_Inventario();
			break;
		case 5:
			printf("Gracias por usar nuestro programa, vuelva pronto\n");
			getche();
			return 0;
		default:
			system("cls");
			printf("Opcion no encontrada, favor de seleccionar una opcion valida\n");
			getche();
			Menu_Principal();		
	}
}

main(){
	Menu_Principal();
	return 0;
	
}
