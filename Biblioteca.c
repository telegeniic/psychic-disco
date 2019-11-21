#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

char bienvenida[] = "Bienvenido al sistema gestor de bibliotecas, seleccione la opcion deseada\n";

struct Cliente {
	int ID; //Unico
	char nombre[30], apellido[30];
	char correo[30];
	char telefono[10];
	char direccion[30];
	char notas[100];
};

struct Libro {
	int ID; //Unico
	char titulo[30];
	char autor[30];
	char anno[4]; //año, se usa doble nn para evitar usar la letra ñ en el codigo
	char editorial[20];
	char isbn[15];
	int tipo;
	char notas[100];
	int precio;
	int inventario; //cantidad de piezas en inventario
};

typedef struct fecha{
	int dia;
	int mes;
	int anno;
}Fecha;

struct Ventas {
	int idCliente;
	int idLibro;
	int dias;
	Fecha fecha;
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
			Nuevo_Cliente();
			break;
		case 2:
			Editar_Cliente();
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
			getch();
			Menu_Clientes();
	}
	
}

int Nuevo_Cliente(){
	struct Cliente cliente;
	char temp[100];
	int exit = 0, ultID, op;
	FILE *lectura;
	lectura = fopen("Clientes.txt","r");
	if(lectura==NULL || feof(lectura)) ultID = 1 ;
	else{
		while(!feof(lectura)){
			fscanf(lectura, "%d %s %s %s %s %s %s\n", &ultID,temp,temp,temp,temp,temp,temp);
		}
		ultID++;
	}
	fclose(lectura);
	FILE *archivo;
	archivo = fopen("Clientes.txt","a");
	do{
		system("cls");
		
		cliente.ID = ultID;
		
		printf("Cual es el nombre del nuevo cliente?\n");
		scanf("%s", cliente.nombre);
		
		printf("Cual es el apellido del cliente?\n");
		scanf("%s", cliente.apellido);
		
		printf("Cual es su correo electronico?\n");
		scanf("%s", cliente.correo);
		
		printf("Cual es su numero de telefono?\n");
		scanf("%s", cliente.telefono);
		
		printf("Cual es su direccion?\n");
		scanf("%s", cliente.direccion);
		
		strcpy(cliente.notas,"vacio");
		
		Imprimir_Cliente(cliente);
		
		printf("Desea guardar la info?\n");
		printf("1.-Si\n2.-No\n");
		scanf("%d", &op);
		
		if(op==1){
			ultID++;
			system("cls");
			printf("Datos guardados con exito\n");
			fprintf(archivo, "%d %s %s %s %s %s %s\n", cliente.ID, cliente.nombre, cliente.apellido, cliente.correo, cliente.telefono, cliente.direccion, cliente.notas);
		}
		else {
			system("cls");
			printf("Los datos no se han guardado\n");
		}
		printf("Desea registrar otro cliente?\n");
		printf("1.-Si\n");
		printf("2.-No\n");
		scanf("%d", &exit);
	}while(exit==1);
	
	fclose(archivo);
	
	Menu_Principal();
	
	return 0;
}

int Editar_Cliente(){
	int i,j, op, max, busquedaID, error, tempID;
	char temp[100];
	struct Cliente *cliente;
	FILE *lectura;
	FILE *escritura;
	cliente = (struct Cliente *)malloc(sizeof(struct Cliente));
	lectura = fopen("Clientes.txt","r");
	rewind(lectura);
	if(lectura==NULL || feof(lectura)){
		printf("No hay clientes para editar\n");
	} 
	else {
		
		for(i=1;!feof(lectura);i++){
			cliente = realloc(cliente, i*sizeof(struct Cliente));
			fscanf(lectura, "%d %s %s %s %s %s %s\n", &tempID, temp,temp,temp,temp,temp,temp);
		}
		
		max = i;
		rewind(lectura);
		
		for(j=0;!feof(lectura);j++){
			fscanf(lectura, "%d %s %s %s %s %s %s\n", &cliente[j].ID, cliente[j].nombre, cliente[j].apellido, cliente[j].correo, cliente[j].telefono, cliente[j].direccion, cliente[j].notas);
		}
		
		fclose(lectura);
		
		do{
			printf("Cual seria el id del cliente a modificar?\n");
			scanf("%d", &busquedaID);
			
			for(i=0;i<max;i++){
				printf("id: %d\n", cliente[i].ID);
				if(busquedaID == cliente[i].ID) {
					error=0;
					break;
				}
				else error = 1;	
			} 
			if(error != 1){
				system("cls");
				Imprimir_Cliente(cliente[i]);
				printf("Modificar Valores:\n");
				printf("Nombre: ");
				scanf("%s", cliente[i].nombre);
				fflush(stdin);
				printf("Apellido: ");
				scanf("%s", cliente[i].apellido);
				fflush(stdin);
				printf("Correo: ");
				scanf("%s", cliente[i].correo);
				fflush(stdin);
				printf("Telefono: ");
				scanf("%s", cliente[i].telefono);
				fflush(stdin);
				printf("Direccion: ");
				scanf("%s", cliente[i].direccion);
				fflush(stdin);
				printf("Notas: ");
				scanf("%s", cliente[i].notas);
				fflush(stdin);
				
				system("cls");
				printf("Valores Modificados\n");
				Imprimir_Cliente(cliente[i]);
				
				printf("Desea Guardar los cambios?\n");
				printf("1.-Si\n2.-No\n");
				scanf("%d", &op);
				fflush(stdin);
				if(op == 1){
					escritura = fopen("Clientes.txt","w");
					for(j=0;j<max-1;j++){
						fprintf(escritura, "%d %s %s %s %s %s %s\n",cliente[j].ID, cliente[j].nombre, cliente[j].apellido, cliente[j].correo, cliente[j].telefono, cliente[j].direccion, cliente[j].notas);
					}
					fclose(escritura);
					printf("Cambios Guardados\n");
				}
				else printf("No se Guardaron los cambios\n");
			}
			else printf("Id No encontrado\n");
			
			printf("Desea buscar otro cliente para modificarlo?\n");
			printf("1.-Si\n2.-No\n");
			scanf("%d", &op);
			fflush(stdin);
		} while(op==1);
	}
	free(cliente);
	Menu_Principal();
	return 0;
}

int Imprimir_Cliente(struct Cliente cliente){
	printf("Datos del cliente\n");
	printf("Id: %d\n", cliente.ID);
	printf("nombre: %s\n", cliente.nombre);
	printf("apellido: %s\n", cliente.apellido);
	printf("telefono: %s\n", cliente.telefono);
	printf("correo electronico: %s\n", cliente.correo);
	printf("Direccion: %s\n", cliente.direccion);
	printf("Notas: %s\n", cliente.notas);
	return 0;
}

int Menu_Libros(){
	int op;
	system("cls");
	printf(bienvenida);
	printf("Se entro al menu de libros\n");
	printf("1.-Nuevo Libro\n");
	printf("2.-Editar Libro\n");
	printf("3.-Eliminar Libro\n");
	printf("4.-Regresar al menu principal\n");
	printf("9.-Salir del programa\n");
	scanf("%d", &op);
	
	switch(op){
		case 1:
			Nuevo_Libro();
			break;
		case 2:
			Editar_Libro();
			break;
		case 3:
		//	Eliminar_Libro();
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
}

int Nuevo_Libro(){
	int tempID, tempInt;
	struct Libro libro;
	char temp[100];
	int exit = 0, ultID, op;
	FILE *lectura;
	lectura = fopen("Libros.txt","r");
	rewind(lectura);
	if(lectura==NULL || feof(lectura)) ultID = 1 ;
	else{
		while(!feof(lectura)){
			printf("Buscando ultimo id\n");
			fscanf(lectura, "%d %s %s %s %s %s %d %s %d %d\n", &ultID, temp,temp,temp,temp,temp,&tempInt,temp,&tempInt,&tempInt);
		}
		ultID++;
	}
	fclose(lectura);
	FILE *archivo;
	archivo = fopen("Libros.txt","a");
	do{
		system("cls");
		
		libro.ID = ultID;
		
		printf("Cual es el titulo del libro?\n");
		scanf("%s", libro.titulo);
		
		printf("Quien es el autor?\n");
		scanf("%s", libro.autor);
		
		printf("Cual fue el a%co de publicacion?\n",164);
		scanf("%s", libro.anno);
		
		printf("Cual es la editorial?\n");
		scanf("%s", libro.editorial);
		
		printf("Cual es el ISBN?\n");
		scanf("%s", libro.isbn);
		
		do{
			printf("Cual es el tipo de libro?\n");
			printf("1.-Renta\n2.-Venta\n3.-Solo Lectura\n");
			scanf("%d", &libro.tipo);
			if(libro.tipo < 0 || libro.tipo > 4) printf("Opcion no valida\n");
		}while(libro.tipo < 0 || libro.tipo > 4);
		
		strcpy(libro.notas,"vacio");
		
		printf("Cual es el precio del libro?\n");
		scanf("%d", &libro.precio);
		
		printf("Con cuantas piezas se van a agregar al inventario?\n");
		scanf("%d", &libro.inventario);
		
		Imprimir_Libro(libro);
		
		printf("Desea guardar la info?\n");
		printf("1.-Si\n2.-No\n");
		scanf("%d", &op);
		
		if(op==1){
			ultID++;
			system("cls");
			printf("Datos guardados con exito\n");
			fprintf(archivo, "%d %s %s %s %s %s %d %s %d %d\n", 
					libro.ID, libro.titulo, libro.autor, libro.anno, libro.editorial, libro.isbn, libro.tipo, libro.notas, libro.precio, libro.inventario);
		}
		else {
			system("cls");
			printf("Los datos no se han guardado\n");
		}
		printf("Desea registrar otro cliente?\n");
		printf("1.-Si\n");
		printf("2.-No\n");
		scanf("%d", &exit);
	}while(exit==1);
	
	fclose(archivo);
	
	Menu_Principal();
	
	return 0;
}

int Editar_Libro(){
	int i,j, op, max, busquedaID, error, tempID, tempInt;
	char temp[100];
	struct Libro *libro;
	FILE *lectura;
	FILE *escritura;
	libro = (struct Libro *)malloc(sizeof(struct Libro));
	lectura = fopen("Libros.txt","r");
	rewind(lectura);
	if(lectura==NULL || feof(lectura)){
		printf("No hay libros para editar\n");
	} 
	else {
		
		for(i=1;!feof(lectura);i++){
			libro = realloc(libro, i*sizeof(struct Libro));
			fscanf(lectura, "%d %s %s %s %s %s %d %s %d %d\n", &tempID, temp,temp,temp,temp,temp,&tempInt,temp,&tempInt,&tempInt);
		}
		
		max = i;
		rewind(lectura);
		
		for(j=0;!feof(lectura);j++){
			fscanf(lectura, "%d %s %s %s %s %s %d %s %d %d\n", 
					&libro[j].ID, libro[j].titulo, libro[j].autor, libro[j].anno, libro[j].editorial, libro[j].isbn,
					&libro[j].tipo, libro[j].notas, &libro[j].precio, &libro[j].inventario);
		}
		
		fclose(lectura);
		
		do{
			system("cls");
			printf("Cual seria el id del libro a modificar?\n");
			scanf("%d", &busquedaID);
			
			for(i=0;i<max;i++){
				printf("id: %d\n", libro[i].ID);
				if(busquedaID == libro[i].ID) {
					error=0;
					break;
				}
				else error = 1;	
			} 
			if(error != 1){
				system("cls");
				Imprimir_Libro(libro[i]);
				printf("Modificar Valores:\n");
				printf("Titulo: ");
				scanf("%s", libro[i].titulo);
				fflush(stdin);
				printf("Autor: ");
				scanf("%s", libro[i].autor);
				fflush(stdin);
				printf("A%co: ",164);
				scanf("%s", libro[i].anno);
				fflush(stdin);
				printf("Editorial: ");
				scanf("%s", libro[i].editorial);
				fflush(stdin);
				printf("ISBN: ");
				scanf("%s", libro[i].isbn);
				fflush(stdin);
				do{
					printf("Cual es el tipo de libro?\n");
					printf("1.-Renta\n2.-Venta\n3.-Solo Lectura\n");
					scanf("%d", &libro[i].tipo);
					if(libro[i].tipo < 0 || libro[i].tipo > 4) printf("Opcion no valida\n");
				}while(libro[i].tipo < 0 || libro[i].tipo > 4);
				fflush(stdin);
				printf("Notas: ");
				scanf("%s", libro[i].notas);
				fflush(stdin);
				printf("Precio: ");
				scanf("%d", &libro[i].precio);
				fflush(stdin);
				
				system("cls");
				printf("Valores Modificados\n");
				Imprimir_Libro(libro[i]);
				
				printf("Desea Guardar los cambios?\n");
				printf("1.-Si\n2.-No\n");
				scanf("%d", &op);
				fflush(stdin);
				if(op == 1){
					escritura = fopen("Libros.txt","w");
					for(j=0;j<max-1;j++){
						fprintf(escritura, "%d %s %s %s %s %s %d %s %d %d\n", 
						libro[j].ID, libro[j].titulo, libro[j].autor, libro[j].anno, libro[j].editorial, libro[j].isbn, libro[j].tipo, libro[j].notas, libro[j].precio, libro[j].inventario);
					}
					fclose(escritura);
					system("cls");
					printf("Cambios Guardados\n");
				}	
				else {
					system("cls");
					printf("No se Guardaron los cambios\n");
				}
			}
			else{
				system("cls");
				printf("Id No encontrado\n");
			}
			printf("Desea buscar otro libro para modificarlo?\n");
			printf("1.-Si\n2.-No\n");
			scanf("%d", &op);
			fflush(stdin);
		} while(op==1);
	}
	free(libro);
	Menu_Principal();
	return 0;
}

int Imprimir_Libro(struct Libro libro){
	printf("Los datos del libro:\n");
	printf("ID: %d\n", libro.ID);
	printf("Titulo: %s\n", libro.titulo);
	printf("Autor: %s\n", libro.autor);
	printf("A%co: %s\n", 164, libro.anno);
	printf("Editorial: %s\n", libro.editorial);
	printf("ISBN: %s\n", libro.isbn);
	switch(libro.tipo){
		case 1:
			printf("Tipo: Renta\n");
			break;
		case 2:
			printf("Tipo: Venta\n");
			break;
		case 3:
			printf("Tipo: Solo Lectura\n");
			break;
	}
	printf("Notas: %s\n", libro.notas);
	printf("Precio $%d\n", libro.precio);
	printf("Inventario: %d\n", libro.inventario);
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
			Comprar_Libro();
			break;
		case 2:
			Rentar_Libro();
			break;
		case 3:
		//	Leer_Sala();
			break;
		case 4:
		//	Regresar_Libro();
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
}

int Imprimir_Ticket(struct Libro libro, int cantidad, float total){
	printf("Ticket generado por software de gestion de biblioteca\n");
	printf("Biblioteca FCFM\n");
	printf("Titulo del libro: %s\n", libro.titulo);
	printf("Precio unitario del libro $%d\n", libro.precio);
	printf("Cantidades compradas: %d\n", cantidad);
	printf("Total (iva incluido) $%.2f\n", total);
	return 0;
}

int Comprar_Libro(){
	int i,j, op, max, busquedaID, error, tempID, tempInt, encontrado, indice, cantidad;
	float total;
	char temp[100], buscar[100];
	struct Libro *libro;
	FILE *lectura;
	FILE *escritura;
	libro = (struct Libro *)malloc(sizeof(struct Libro));
	lectura = fopen("Libros.txt","r");
	rewind(lectura);
	if(lectura==NULL || feof(lectura)){
		printf("No hay libros para buscar\n");
	} 
	else {
		
		for(i=1;!feof(lectura);i++){
			libro = realloc(libro, i*sizeof(struct Libro));
			fscanf(lectura, "%d %s %s %s %s %s %d %s %d %d\n", &tempID, temp,temp,temp,temp,temp,&tempInt,temp,&tempInt,&tempInt);
		}
		
		max = i;
		rewind(lectura);
		
		for(j=0;!feof(lectura);j++){
			fscanf(lectura, "%d %s %s %s %s %s %d %s %d %d\n", 
					&libro[j].ID, libro[j].titulo, libro[j].autor, libro[j].anno, libro[j].editorial, libro[j].isbn,
					&libro[j].tipo, libro[j].notas, &libro[j].precio, &libro[j].inventario);
		}
		
		printf("Buscar por titulo o por ISBN?\n");
		printf("1.-Titulo\n2.-ISBN\n");
		scanf("%d", &op);
		switch(op){
			case 1:
				printf("Escriba el titulo del libro\n");
				scanf(" %s", buscar);
				for(i=0;i<max;i++){
					if(strcmp(libro[i].titulo,buscar) == 0) {
						encontrado = 1;
						indice = i;
					}
				}
				break;
			case 2:
				printf("Escriba el ISBN del libro\n");
				scanf(" %s", buscar);
				for(i=0;i<max;i++){
					if(strcmp(libro[i].isbn,buscar) == 0){
						encontrado = 1;
						indice = i;
					}
				}
				break;
			default:
				printf("Opcion no encontrada\nRegresando");
				Comprar_Libro();
				return 0;
		}
		
		if(encontrado == 1){
			i = indice;
			Imprimir_Libro(libro[i]);
			if(libro[i].tipo == 2){
				do{
					printf("Cuantos Libros desea comprar?\n");
					scanf("%d", &cantidad);
					if(cantidad > libro[i].inventario) printf("No hay tantas unidades en inventario\n");
				}while(cantidad > libro[i].inventario);
				total = cantidad * libro[i].precio * 1.16;
				printf("Total: %.2f\n", total);
				printf("Desea realizar la compra?\n");
				printf("1.-Si\n2.-No\n");
				fflush(stdin);
				scanf(" %d", &op);
				if(op == 1) {
					Imprimir_Ticket(libro[i], cantidad, total);
					libro[i].inventario = libro[i].inventario - cantidad;
					escritura = fopen("Libros.txt","w");
					for(j=0;j<max-1;j++){
						fprintf(escritura, "%d %s %s %s %s %s %d %s %d %d\n", 
						libro[j].ID, libro[j].titulo, libro[j].autor, libro[j].anno, libro[j].editorial, libro[j].isbn, libro[j].tipo, libro[j].notas, libro[j].precio, libro[j].inventario);
					}
					fclose(escritura);
				}
				else printf("La compra no se realizo\n");
			}
			else{
				printf("El libro no se encuentra disponible para la venta\n");
			}
		}
		else{
			printf("No se ah encontrado el libro\n");
		}
		
	}
}

int Rentar_Libro(){
	int i,j, op, max, busquedaID, error, tempID, tempInt, encontrado, indice, cantidad;
	int idCliente, clienteEncontrado, dias, maxLib;
	float total;
	char temp[100], buscar[100];
	struct Ventas venta;
	struct Cliente *cliente;
	struct Libro *libro;
	FILE *lectura;
	FILE *escritura;
	FILE *fcliente;
	FILE *renta;
	cliente = (struct Cliente *)malloc(sizeof(struct Cliente));
	libro = (struct Libro *)malloc(sizeof(struct Libro));
	fcliente = fopen("Clientes.txt", "r");
	lectura = fopen("Libros.txt","r");
	if(lectura==NULL || feof(lectura)){
		printf("No hay libros para buscar\n");
	} 
	else if(fcliente==NULL || feof(fcliente)){
		printf("No hay clientes registrados");
	}
	else {
		
		rewind(fcliente);
		rewind(lectura);
		
		for(i=1;!feof(fcliente);i++){
			cliente = realloc(cliente, i*sizeof(struct Cliente));
			fscanf(fcliente, "%d %s %s %s %s %s %s\n", &tempID, temp,temp,temp,temp,temp,temp);
		}
		
		for(i=1;!feof(lectura);i++){
			libro = realloc(libro, i*sizeof(struct Libro));
			fscanf(lectura, "%d %s %s %s %s %s %d %s %d %d\n", &tempID, temp,temp,temp,temp,temp,&tempInt,temp,&tempInt,&tempInt);
		}
		
		rewind(fcliente);
		rewind(lectura);
		
		for(j=0;!feof(fcliente);j++){
			fscanf(fcliente, "%d %s %s %s %s %s %s\n", &cliente[j].ID, cliente[j].nombre, cliente[j].apellido, cliente[j].correo, cliente[j].telefono, cliente[j].direccion, cliente[j].notas);
		}
		max = j;
		
		for(j=0;!feof(lectura);j++){
			fscanf(lectura, "%d %s %s %s %s %s %d %s %d %d\n", 
					&libro[j].ID, libro[j].titulo, libro[j].autor, libro[j].anno, libro[j].editorial, libro[j].isbn,
					&libro[j].tipo, libro[j].notas, &libro[j].precio, &libro[j].inventario);
		}
		maxLib = j;
		
		printf("Buscar por titulo o por ISBN?\n");
		printf("1.-Titulo\n2.-ISBN\n");
		scanf("%d", &op);
		switch(op){
			case 1:
				printf("Escriba el titulo del libro\n");
				scanf(" %s", buscar);
				for(i=0;i<max;i++){
					if(strcmp(libro[i].titulo,buscar) == 0) {
						encontrado = 1;
						indice = i;
					}
				}
				break;
			case 2:
				printf("Escriba el ISBN del libro\n");
				scanf(" %s", buscar);
				for(i=0;i<max;i++){
					if(strcmp(libro[i].isbn,buscar) == 0){
						encontrado = 1;
						indice = i;
					}
				}
				break;
			default:
				printf("Opcion no encontrada\nRegresando");
				Comprar_Libro();
				return 0;
		}
		
		if(encontrado == 1){
			i = indice;
			Imprimir_Libro(libro[i]);
			if(libro[i].tipo == 1){
				do{
					printf("Cuantos Libros desea rentar?\n");
					scanf("%d", &cantidad);
					if(cantidad > libro[i].inventario) printf("No hay tantas unidades en inventario\n");
				}while(cantidad > libro[i].inventario);
				total = cantidad * libro[i].precio;
				printf("Total: %.2f\n", total);
				do{
					printf("Ingrese el ID del cliente\n");
					scanf("%d", &idCliente);
					for(j=0;j<max;j++){
						if(cliente[j].ID==idCliente) {
							encontrado = 1;
							clienteEncontrado = cliente[j].ID;
							Imprimir_Cliente(cliente[j]);
						}
					}
				}while(encontrado != 1);
				printf("Cuantos dias va a rentar el libro?\n");
				scanf("%d", &dias);
				
				time_t tiempo = time(0); //Bloque que consigue la fecha de hoy
		        struct tm *tlocal = localtime(&tiempo);
		        char dia[3];
		        strftime(dia,3,"%d",tlocal);
		        char mes[3];
		        strftime(mes,3,"%m",tlocal);
		        char anno[3];
		        strftime(anno,3,"%y",tlocal);
		        venta.idCliente = clienteEncontrado;
		        venta.idLibro = libro[i].ID;
		        venta.dias = dias;
				
				printf("Desea realizar la renta?\n");
				printf("1.-Si\n2.-No\n");
				fflush(stdin);
				scanf(" %d", &op);
				if(op == 1) {
					libro[i].inventario = libro[i].inventario - cantidad;
					escritura = fopen("Rentas.txt","a");
					fprintf(escritura, "%d %d %d %s %s %s\n", venta.idCliente, venta.idLibro, venta.dias, dia, mes, anno);
					fclose(escritura);
					
					escritura = fopen("Libros.txt","w");
					for(j=0;j<maxLib;j++){
						fprintf(escritura, "%d %s %s %s %s %s %d %s %d %d\n", 
						libro[j].ID, libro[j].titulo, libro[j].autor, libro[j].anno, libro[j].editorial, libro[j].isbn, libro[j].tipo, libro[j].notas, libro[j].precio, libro[j].inventario);
					}
					fclose(escritura);
				}
				else printf("La renta no se realizo\n");
			}
			else{
				printf("El libro no se encuentra disponible para la renta\n");
			}
		}
		else{
			printf("No se ah encontrado el libro\n");
		}
	}
	fclose(lectura);
	fclose(fcliente);
	Menu_Biblioteca();
	return 0;
}

//int Leer_Sala()

int Menu_Inventario(){
	int op;
	system("cls");
	printf(bienvenida);
	printf("Se entro al menu de Inventario\n");
	printf("1.-Buscar por cliente\n");
	printf("2.-Buscar por libro\n");
	printf("3.-Regresar al menu principal\n");
	printf("9.-Salir del programa\n");
	scanf("%d", &op);
	fflush(stdin);
	
	switch(op){
		case 1:
			Busqueda_Cliente();
			break;
		case 2:
			Menu_Busqueda_Libro();
			break;
		case 3:
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
			Menu_Inventario();
			
	}
}

int Busqueda_Cliente(){
	int i,j,k, op, max, busquedaID, error, tempID, noVentas, tempInt;
	int maxVenta, maxLibros;
	char temp[100];
	
	struct Libro *libro;
	struct Cliente *cliente;
	struct Ventas *venta;
	
	FILE *lectura;
	FILE *ventas;
	FILE *libros;
	
	libro = (struct Libro *)malloc(sizeof(struct Libro));
	venta = (struct Ventas *)malloc(sizeof(struct Ventas));
	cliente = (struct Cliente *)malloc(sizeof(struct Cliente));
	
	libros = fopen("Libros.txt", "r");
	ventas = fopen("Rentas.txt", "r");
	lectura = fopen("Clientes.txt","r");
	
	if(ventas==NULL || feof(ventas)){
		printf("No hay ventas registradas");
		noVentas = 1;
	}
	if(lectura==NULL || feof(lectura)){
		printf("No hay clientes registrados\n");
	} 
	else if(libros==NULL || feof(libros)){
		printf("No hay libros registrados\n");
	}
	else {
		
		for(i=1;!feof(libros);i++){
			libro = realloc(libro, i*sizeof(struct Libro));
			fscanf(libros, "%d %s %s %s %s %s %d %s %d %d\n", &tempID, temp,temp,temp,temp,temp,&tempInt,temp,&tempInt,&tempInt);
		}
		maxLibros = i;
		
		for(i=1;!feof(ventas);i++){
			venta = realloc(venta, i*sizeof(struct Ventas));
			fscanf(ventas, "%d %d %d %d %d %d\n", &tempID, &tempID,&tempID,&tempID,&tempID,&tempID);
		}
		maxVenta = i;
		
		for(i=1;!feof(lectura);i++){
			cliente = realloc(cliente, i*sizeof(struct Cliente));
			fscanf(lectura, "%d %s %s %s %s %s %s\n", &tempID, temp,temp,temp,temp,temp,temp);
		}
		max = i;
		
		rewind(libros);
		rewind(ventas);
		rewind(lectura);
		
		for(j=0;!feof(libros);j++){
			fscanf(libros, "%d %s %s %s %s %s %d %s %d %d\n", 
					&libro[j].ID, libro[j].titulo, libro[j].autor, libro[j].anno, libro[j].editorial, libro[j].isbn,
					&libro[j].tipo, libro[j].notas, &libro[j].precio, &libro[j].inventario);
		}
		for(j=0;!feof(lectura);j++){
			fscanf(lectura, "%d %s %s %s %s %s %s\n", &cliente[j].ID, cliente[j].nombre, cliente[j].apellido, cliente[j].correo, cliente[j].telefono, cliente[j].direccion, cliente[j].notas);
		}
		for(j=0;!feof(ventas);j++){
			fscanf(ventas, "%d %d %d %d %d %d\n", &venta[j].idCliente, &venta[j].idLibro ,&venta[j].dias,&venta[j].fecha.dia, &venta[j].fecha.mes, &venta[j].fecha.anno);
		}
		
		fclose(libros);
		fclose(ventas);
		fclose(lectura);
		
		do{
			printf("Cual seria el id del cliente a buscar?\n");
			scanf("%d", &busquedaID);
			
			for(i=0;i<max;i++){
				printf("id: %d\n", cliente[i].ID);
				if(busquedaID == cliente[i].ID) {
					error=0;
					break;
				}
				else error = 1;	
			} 
			if(error != 1){
				system("cls");
				Imprimir_Cliente(cliente[i]);
				for(j=0;i<maxVenta;i++){
					if(venta[j].idCliente == cliente[i].ID){
						error = 0;
						break;
					}
					else error = 1;
				}
				if(error != 1){
					for(k=0;k<maxLibros;k++){
						if(venta[j].idLibro == libro[k].ID){
							error = 0;
							break;
						}
						else error = 1;
					}
					if(error != 1){
						printf("El cliente rento el siguiente libro\n");
						Imprimir_Libro(libro[k]);
					}
				}
				else printf("El cliente no ah rentado libros\n");
			}
			else printf("Id No encontrado\n");
			
			printf("Desea buscar otro cliente?\n");
			printf("1.-Si\n2.-No\n");
			scanf("%d", &op);
			fflush(stdin);
		} while(op==1);
	}
	free(libro);
	free(venta);
	free(cliente);
	Menu_Principal();
	return 0;
}

int Menu_Busqueda_Libro(){
	int op;
	system("cls");
	printf(bienvenida);
	printf("Busqueda por Libro\n");
	printf("1.-Buscar por titulo\n");
	printf("2.-Buscar por Autor\n");
	printf("3.-Buscar por ISBN\n");
	printf("4.-Regresar al menu de inventario\n");
	printf("5.-Regresar al menu principal\n");
	printf("9.-Salir del programa\n");
	printf("Op: ");
	scanf("%d", &op);
	
	switch(op){
		case 1:
			Busqueda_Titulo();
			break;
		case 2:
			Busqueda_Autor();
			break;
		case 3:
			Busqueda_ISBN();
			break;
		case 4:
			Menu_Inventario();
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
			Menu_Busqueda_Libro();
	}
}

int Busqueda_Titulo(){
		int i,j, op, max, busquedaID, error, tempID, tempInt, encontrado, indice, cantidad;
	float total;
	char temp[100], buscar[100];
	struct Libro *libro;
	FILE *lectura;
	FILE *escritura;
	libro = (struct Libro *)malloc(sizeof(struct Libro));
	lectura = fopen("Libros.txt","r");
	rewind(lectura);
	if(lectura==NULL || feof(lectura)){
		printf("No hay libros para buscar\n");
	} 
	else {
		
		for(i=1;!feof(lectura);i++){
			libro = realloc(libro, i*sizeof(struct Libro));
			fscanf(lectura, "%d %s %s %s %s %s %d %s %d %d\n", &tempID, temp,temp,temp,temp,temp,&tempInt,temp,&tempInt,&tempInt);
		}
		
		max = i;
		rewind(lectura);
		
		for(j=0;!feof(lectura);j++){
			fscanf(lectura, "%d %s %s %s %s %s %d %s %d %d\n", 
					&libro[j].ID, libro[j].titulo, libro[j].autor, libro[j].anno, libro[j].editorial, libro[j].isbn,
					&libro[j].tipo, libro[j].notas, &libro[j].precio, &libro[j].inventario);
		}
		

			printf("Escriba el titulo del libro\n");
			scanf(" %s", buscar);
			for(i=0;i<max;i++){
				if(strcmp(libro[i].titulo,buscar) == 0) {
					encontrado = 1;
					break;
				}
			}
		
		if(encontrado == 1){
			Imprimir_Libro(libro[i]);
		}
		else{
			printf("No se ah encontrado el libro\n");
		}
		
	}
}

int Busqueda_ISBN(){
	int i,j, op, max, busquedaID, error, tempID, tempInt, encontrado, indice, cantidad;
	float total;
	char temp[100], buscar[100];
	struct Libro *libro;
	FILE *lectura;
	FILE *escritura;
	libro = (struct Libro *)malloc(sizeof(struct Libro));
	lectura = fopen("Libros.txt","r");
	rewind(lectura);
	if(lectura==NULL || feof(lectura)){
		printf("No hay libros para buscar\n");
	} 
	else {
		
		for(i=1;!feof(lectura);i++){
			libro = realloc(libro, i*sizeof(struct Libro));
			fscanf(lectura, "%d %s %s %s %s %s %d %s %d %d\n", &tempID, temp,temp,temp,temp,temp,&tempInt,temp,&tempInt,&tempInt);
		}
		
		max = i;
		rewind(lectura);
		
		for(j=0;!feof(lectura);j++){
			fscanf(lectura, "%d %s %s %s %s %s %d %s %d %d\n", 
					&libro[j].ID, libro[j].titulo, libro[j].autor, libro[j].anno, libro[j].editorial, libro[j].isbn,
					&libro[j].tipo, libro[j].notas, &libro[j].precio, &libro[j].inventario);
		}
		
		printf("Escriba el ISBN del libro\n");
		scanf(" %s", buscar);
		for(i=0;i<max;i++){
			if(strcmp(libro[i].isbn,buscar) == 0){
				encontrado = 1;
				break;
			}
		}
		
		if(encontrado == 1){
			Imprimir_Libro(libro[i]);
		}
		else{
			printf("No se ah encontrado el libro\n");
		}
		
	}
}

int Busqueda_Autor(){
	int i,j, op, max, busquedaID, error, tempID, tempInt, encontrado, indice, cantidad;
	float total;
	char temp[100], buscar[100];
	struct Libro *libro;
	FILE *lectura;
	FILE *escritura;
	libro = (struct Libro *)malloc(sizeof(struct Libro));
	lectura = fopen("Libros.txt","r");
	rewind(lectura);
	if(lectura==NULL || feof(lectura)){
		printf("No hay libros para buscar\n");
	} 
	else {
		
		for(i=1;!feof(lectura);i++){
			libro = realloc(libro, i*sizeof(struct Libro));
			fscanf(lectura, "%d %s %s %s %s %s %d %s %d %d\n", &tempID, temp,temp,temp,temp,temp,&tempInt,temp,&tempInt,&tempInt);
		}
		
		max = i;
		rewind(lectura);
		
		for(j=0;!feof(lectura);j++){
			fscanf(lectura, "%d %s %s %s %s %s %d %s %d %d\n", 
					&libro[j].ID, libro[j].titulo, libro[j].autor, libro[j].anno, libro[j].editorial, libro[j].isbn,
					&libro[j].tipo, libro[j].notas, &libro[j].precio, &libro[j].inventario);
		}
		
		printf("Escriba el autor del libro\n");
		scanf(" %s", buscar);
		for(i=0;i<max;i++){
			if(strcmp(libro[i].autor,buscar) == 0){
				encontrado = 1;
				break;
			}
		}
		
		if(encontrado == 1){
			Imprimir_Libro(libro[i]);
		}
		else{
			printf("No se ah encontrado el libro\n");
		}
		
	}
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
			fflush(stdin);
			Menu_Principal();		
	}
}

main(){
	Menu_Principal();
	return 0;
	
}
