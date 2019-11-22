#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

char bienvenida[] = "\tBienvenido al sistema gestor de bibliotecas, seleccione la opcion deseada\n";

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
	printf("\tSe entro al menu de clientes\n");
	printf("\t1.-Nuevo Cliente\n");
	printf("\t2.-Editar Cliente\n");
	printf("\t3.-Eliminar Cliente\n");
	printf("\t4.-Regresar al menu principal\n");
	printf("\t9.-Salir del programa\n");
	printf("\tOp: ");
	scanf("%d", &op);
	switch(op){
		case 1:
			Nuevo_Cliente();
			break;
		case 2:
			Editar_Cliente();
			break;
		case 3:
			Eliminar_Cliente();
			break;
		case 4:
			Menu_Principal();
			break;
		case 9:
			printf("\tGracias por usar nuestro programa, vuelva pronto\n");
			getche();
			return 0;
		default:
			system("cls");
			printf("\tOpcion no encontrada, favor de seleccionar una opcion valida\n");
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
		
		printf("\tCual es el nombre del nuevo cliente%c\n", 63);
		scanf("%s", cliente.nombre);
		
		printf("\tCual es el apellido del cliente%c\n", 63);
		scanf("%s", cliente.apellido);
		
		printf("\tCual es su correo electronico%c\n", 63);
		scanf("%s", cliente.correo);
		
		printf("\tCual es su numero de telefono%c\n", 63);
		scanf("%s", cliente.telefono);
		
		printf("\tCual es su direccion%c\n", 63);
		scanf("%s", cliente.direccion);
		
		strcpy(cliente.notas,"vacio");
		
		Imprimir_Cliente(cliente);
		
		printf("\tDesea guardar la info%c\n", 63);
		printf("1.-Si\n2.-No\n");
		scanf("%d", &op);
		
		if(op==1){
			ultID++;
			system("cls");
			printf("\tDatos guardados con exito\n");
			fprintf(archivo, "%d %s %s %s %s %s %s\n", cliente.ID, cliente.nombre, cliente.apellido, cliente.correo, cliente.telefono, cliente.direccion, cliente.notas);
		}
		else {
			system("cls");
			printf("\tLos datos no se han guardado\n");
		}
		printf("\tDesea registrar otro cliente%c\n", 63);
		printf("\t1.-Si\n");
		printf("\t2.-No\n");
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
		printf("\tNo hay clientes para editar\n");
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
			printf("\tCual seria el id del cliente a modificar%c\n", 63);
			scanf("%d", &busquedaID);
			
			for(i=0;i<max;i++){
				printf("\tid: %d\n", cliente[i].ID);
				if(busquedaID == cliente[i].ID) {
					error=0;
					break;
				}
				else error = 1;	
			} 
			if(error != 1){
				system("cls");
				Imprimir_Cliente(cliente[i]);
				printf("\tModificar Valores:\n");
				printf("\tNombre: ");
				scanf("%s", cliente[i].nombre);
				fflush(stdin);
				printf("\tApellido: ");
				scanf("%s", cliente[i].apellido);
				fflush(stdin);
				printf("\tCorreo: ");
				scanf("%s", cliente[i].correo);
				fflush(stdin);
				printf("\tTelefono: ");
				scanf("%s", cliente[i].telefono);
				fflush(stdin);
				printf("\tDireccion: ");
				scanf("%s", cliente[i].direccion);
				fflush(stdin);
				printf("\tNotas: ");
				scanf("%s", cliente[i].notas);
				fflush(stdin);
				
				system("cls");
				printf("\tValores Modificados\n");
				Imprimir_Cliente(cliente[i]);
				
				printf("\tDesea Guardar los cambios%c\n", 63);
				printf("\t1.-Si\n\t2.-No\n");
				scanf("%d", &op);
				fflush(stdin);
				if(op == 1){
					escritura = fopen("Clientes.txt","w");
					for(j=0;j<max-1;j++){
						fprintf(escritura, "%d %s %s %s %s %s %s\n",cliente[j].ID, cliente[j].nombre, cliente[j].apellido, cliente[j].correo, cliente[j].telefono, cliente[j].direccion, cliente[j].notas);
					}
					fclose(escritura);
					printf("\tCambios Guardados\n");
				}
				else printf("\tNo se Guardaron los cambios\n");
			}
			else printf("\tId No encontrado\n");
			
			printf("\tDesea buscar otro cliente para modificarlo%c\n", 63);
			printf("\t1.-Si\n\t2.-No\n");
			scanf("%d", &op);
			fflush(stdin);
		} while(op==1);
	}
	free(cliente);
	Menu_Principal();
	return 0;
}

int Eliminar_Cliente(){
	int i,j, op, max, busquedaID, error, tempID;
	char temp[100];
	struct Cliente *cliente;
	FILE *lectura;
	FILE *escritura;
	cliente = (struct Cliente *)malloc(sizeof(struct Cliente));
	lectura = fopen("Clientes.txt","r");
	rewind(lectura);
	if(lectura==NULL || feof(lectura)){
		printf("\tNo hay clientes para editar\n");
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
			printf("\tCual seria el id del cliente a Eliminar%c\n", 63);
			scanf("%d", &busquedaID);
			
			for(i=0;i<max;i++){
				printf("\tid: %d\n", cliente[i].ID);
				if(busquedaID == cliente[i].ID) {
					error=0;
					break;
				}
				else error = 1;	
			} 
			if(error != 1){
				system("cls");
				Imprimir_Cliente(cliente[i]);
				
				printf("\tDesea Eliminar el cliente%c\n", 63);
				printf("\t1.-Si\n\t2.-No\n");
				scanf("%d", &op);
				fflush(stdin);
				if(op == 1){
					escritura = fopen("Clientes.txt","w");
					for(j=0;j<max-1;j++){
						if(j!=i) fprintf(escritura, "%d %s %s %s %s %s %s\n",cliente[j].ID, cliente[j].nombre, cliente[j].apellido, cliente[j].correo, cliente[j].telefono, cliente[j].direccion, cliente[j].notas);
					}
					fclose(escritura);
					printf("\tCambios Guardados\n");
				}
				else printf("\tNo se Guardaron los cambios\n");
			}
			else printf("\tId No encontrado\n");
			
			printf("\tDesea buscar otro cliente para Eliminarlo%c\n", 63);
			printf("\t1.-Si\n\t2.-No\n");
			scanf("%d", &op);
			fflush(stdin);
		} while(op==1);
	}
	free(cliente);
	Menu_Principal();
	return 0;
}

int Imprimir_Cliente(struct Cliente cliente){
	printf("\tDatos del cliente\n");
	printf("\tId: %d\n", cliente.ID);
	printf("\tnombre: %s\n", cliente.nombre);
	printf("\tapellido: %s\n", cliente.apellido);
	printf("\ttelefono: %s\n", cliente.telefono);
	printf("\tcorreo electronico: %s\n", cliente.correo);
	printf("\tDireccion: %s\n", cliente.direccion);
	printf("\tNotas: %s\n", cliente.notas);
	return 0;
}

int Menu_Libros(){
	int op;
	system("cls");
	printf(bienvenida);
	printf("\tSe entro al menu de libros\n");
	printf("\t1.-Nuevo Libro\n");
	printf("\t2.-Editar Libro\n");
	printf("\t3.-Eliminar Libro\n");
	printf("\t4.-Regresar al menu principal\n");
	printf("\t9.-Salir del programa\n");
	scanf("%d", &op);
	
	switch(op){
		case 1:
			Nuevo_Libro();
			break;
		case 2:
			Editar_Libro();
			break;
		case 3:
			Eliminar_Libro();
			break;
		case 4:
			printf("\tGracias por usar nuestro programa, vuelva pronto\n");
			getche();
			Menu_Principal();
			break;
		case 9:
			return 0;
		default:
			system("cls");
			printf("\tOpcion no encontrada, favor de seleccionar una opcion valida\n");
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
		
		printf("\tCual es el titulo del libro%C\n", 63);
		scanf("%s", libro.titulo);
		
		printf("\tQuien es el autor%c\n", 63);
		scanf("%s", libro.autor);
		
		printf("\tCual fue el a%co de publicacion%c\n",164, 63);
		scanf("%s", libro.anno);
		
		printf("\tCual es la editorial%c\n", 63);
		scanf("%s", libro.editorial);
		
		printf("\tCual es el ISBN%c\n", 63);
		scanf("%s", libro.isbn);
		
		do{
			printf("\tCual es el tipo de libro%c\n", 63);
			printf("\t1.-Renta\n\t2.-Venta\n\t3.-Solo Lectura\n");
			scanf("%d", &libro.tipo);
			if(libro.tipo < 0 || libro.tipo > 4) printf("\tOpcion no valida\n");
		}while(libro.tipo < 0 || libro.tipo > 4);
		
		strcpy(libro.notas,"vacio");
		
		printf("\tCual es el precio del libro%c\n", 63);
		scanf("%d", &libro.precio);
		
		printf("\tCon cuantas piezas se van a agregar al inventario%c\n", 63);
		scanf("%d", &libro.inventario);
		
		Imprimir_Libro(libro);
		
		printf("\tDesea guardar la info%c\n", 63);
		printf("\t1.-Si\n\t2.-No\n");
		scanf("%d", &op);
		
		if(op==1){
			ultID++;
			system("cls");
			printf("\tDatos guardados con exito\n");
			fprintf(archivo, "%d %s %s %s %s %s %d %s %d %d\n", 
					libro.ID, libro.titulo, libro.autor, libro.anno, libro.editorial, libro.isbn, libro.tipo, libro.notas, libro.precio, libro.inventario);
		}
		else {
			system("cls");
			printf("\tLos datos no se han guardado\n");
		}
		printf("\tDesea registrar otro cliente%c\n", 63);
		printf("\t1.-Si\n");
		printf("\t2.-No\n");
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
		printf("\tNo hay libros para editar\n");
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
			printf("\tCual seria el id del libro a modificar%c\n", 63);
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
				printf("\tModificar Valores:\n");
				printf("\tTitulo: ");
				scanf("%s", libro[i].titulo);
				fflush(stdin);
				printf("\tAutor: ");
				scanf("%s", libro[i].autor);
				fflush(stdin);
				printf("\tA%co: ",164);
				scanf("%s", libro[i].anno);
				fflush(stdin);
				printf("\tEditorial: ");
				scanf("%s", libro[i].editorial);
				fflush(stdin);
				printf("\tISBN: ");
				scanf("%s", libro[i].isbn);
				fflush(stdin);
				do{
					printf("\tCual es el tipo de libro%c\n", 63);
					printf("\t1.-Renta\n\t2.-Venta\n\t3.-Solo Lectura\n");
					scanf("%d", &libro[i].tipo);
					if(libro[i].tipo < 0 || libro[i].tipo > 4) printf("\tOpcion no valida\n");
				}while(libro[i].tipo < 0 || libro[i].tipo > 4);
				fflush(stdin);
				printf("\tNotas: ");
				scanf("%s", libro[i].notas);
				fflush(stdin);
				printf("\tPrecio: ");
				scanf("%d", &libro[i].precio);
				fflush(stdin);
				
				system("cls");
				printf("\tValores Modificados\n");
				Imprimir_Libro(libro[i]);
				
				printf("\tDesea Guardar los cambios%c\n", 63);
				printf("\t1.-Si\n\t2.-No\n");
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
					printf("\tCambios Guardados\n");
				}	
				else {
					system("cls");
					printf("\tNo se Guardaron los cambios\n");
				}
			}
			else{
				system("cls");
				printf("\tId No encontrado\n");
			}
			printf("\tDesea buscar otro libro para modificarlo%c\n", 63);
			printf("\t1.-Si\n\t2.-No\n");
			scanf("%d", &op);
			fflush(stdin);
		} while(op==1);
	}
	free(libro);
	Menu_Principal();
	return 0;
}

int Eliminar_Libro(){
	int i,j, op, max, busquedaID, error, tempID, tempInt;
	char temp[100];
	struct Libro *libro;
	FILE *lectura;
	FILE *escritura;
	libro = (struct Libro *)malloc(sizeof(struct Libro));
	lectura = fopen("Libros.txt","r");
	rewind(lectura);
	if(lectura==NULL || feof(lectura)){
		printf("\tNo hay libros para editar\n");
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
			printf("\tCual seria el id del libro a Eliminar%c\n", 63);
			scanf("%d", &busquedaID);
			
			for(i=0;i<max;i++){
				printf("\tid: %d\n", libro[i].ID);
				if(busquedaID == libro[i].ID) {
					error=0;
					break;
				}
				else error = 1;	
			} 
			if(error != 1){
				system("cls");
				Imprimir_Libro(libro[i]);
				
				printf("\tDesea Eliminar el libro%c\n", 63);
				printf("\t1.-Si\n\t2.-No\n");
				scanf("%d", &op);
				fflush(stdin);
				if(op == 1){
					escritura = fopen("Libros.txt","w");
					for(j=0;j<max-1;j++){
						if(j!=i) fprintf(escritura, "%d %s %s %s %s %s %d %s %d %d\n", 
						libro[j].ID, libro[j].titulo, libro[j].autor, libro[j].anno, libro[j].editorial, libro[j].isbn, libro[j].tipo, libro[j].notas, libro[j].precio, libro[j].inventario);
					}
					fclose(escritura);
					system("cls");
					printf("\tCambios Guardados\n");
				}	
				else {
					system("cls");
					printf("\tNo se Guardaron los cambios\n");
				}
			}
			else{
				system("cls");
				printf("\tId No encontrado\n");
			}
			printf("\tDesea buscar otro libro para modificarlo%c\n", 63);
			printf("\t1.-Si\n\t2.-No\n");
			scanf("%d", &op);
			fflush(stdin);
		} while(op==1);
	}
	free(libro);
	Menu_Principal();
	return 0;
}

int Imprimir_Libro(struct Libro libro){
	printf("\tLos datos del libro:\n");
	printf("\tID: %d\n", libro.ID);
	printf("\tTitulo: %s\n", libro.titulo);
	printf("\tAutor: %s\n", libro.autor);
	printf("\tA%co: %s\n", 164, libro.anno);
	printf("\tEditorial: %s\n", libro.editorial);
	printf("\tISBN: %s\n", libro.isbn);
	switch(libro.tipo){
		case 1:
			printf("\tTipo: Renta\n");
			break;
		case 2:
			printf("\tTipo: Venta\n");
			break;
		case 3:
			printf("\tTipo: Solo Lectura\n");
			break;
	}
	printf("\tNotas: %s\n", libro.notas);
	printf("\tPrecio $%d\n", libro.precio);
	printf("\tInventario: %d\n", libro.inventario);
	return 0;
}

int Menu_Biblioteca(){
	int op;
	system("cls");
	printf(bienvenida);
	printf("\tSe entro al menu de Biblioteca\n");
	printf("\t1.-Comprar Libro\n");
	printf("\t2.-Rentar Libro\n");
	printf("\t3.-Leer en sala\n");
	printf("\t4.-Regresar Libro\n");
	printf("\t5.-Regresar al menu principal\n");
	printf("\t9.-Salir del programa\n");
	printf("\tOp: ");
	scanf("%d", &op);
	
	switch(op){
		case 1:
			Comprar_Libro();
			break;
		case 2:
			Rentar_Libro();
			break;
		case 3:
			Leer_Sala();
			break;
		case 4:
			Regresar_Libro();
			break;
		case 5:
			Menu_Principal();
			break;
		case 9:
			printf("\tGracias por usar nuestro programa, vuelva pronto\n");
			getche();
			return 0;
		default:
			system("cls");
			printf("\tOpcion no encontrada, favor de seleccionar una opcion valida\n");
			getche();
			Menu_Biblioteca();
	}
}

int Imprimir_Ticket(struct Libro libro, int cantidad, float total){
	printf("\tTicket generado por software de gestion de biblioteca\n");
	printf("\tBiblioteca FCFM\n");
	printf("\tTitulo del libro: %s\n", libro.titulo);
	printf("\tPrecio unitario del libro $%d\n", libro.precio);
	printf("\tCantidades compradas: %d\n", cantidad);
	printf("\tTotal (iva incluido) $%.2f\n", total);
	return 0;
}

int Regresar_Libro(){
	int i,j, op, max, busquedaID, error, tempID, tempInt, encontrado, indice, cantidad;
	int idCliente, clienteEncontrado, dias, maxLib, maxRenta;
	float total;
	char temp[100], buscar[100];
	
	struct Ventas *venta;
	struct Cliente *cliente;
	struct Libro *libro;
	
	FILE *lectura;
	FILE *escritura;
	FILE *fcliente;
	FILE *renta;
	
	venta = (struct Ventas *)malloc(sizeof(struct Ventas));
	cliente = (struct Cliente *)malloc(sizeof(struct Cliente));
	libro = (struct Libro *)malloc(sizeof(struct Libro));
	
	renta = fopen("Rentas.txt", "r")''
	fcliente = fopen("Clientes.txt", "r");
	lectura = fopen("Libros.txt","r");
	
	if(lectura==NULL || feof(lectura)){
		printf("\tNo hay libros para buscar\n");
	} 
	else if(fcliente==NULL || feof(fcliente)){
		printf("\tNo hay clientes registrados");
	}
	else if(renta==NULL || feof(renta)){
		printf("\tNo hay rentas registradas");
	}
	else {
		
		rewind(renta);
		rewind(fcliente);
		rewind(lectura);
		
		for(i=1;!feof(renta);i++){
			venta = realloc(venta, i*sizeof(struct Ventas));
			fscanf(renta, "%d %s %s %s %s %s %s\n", &tempID, temp,temp,temp,temp,temp,temp);
		}
		
		for(i=1;!feof(fcliente);i++){
			cliente = realloc(cliente, i*sizeof(struct Cliente));
			fscanf(fcliente, "%d %s %s %s %s %s %s\n", &tempID, temp,temp,temp,temp,temp,temp);
		}
		
		for(i=1;!feof(lectura);i++){
			libro = realloc(libro, i*sizeof(struct Libro));
			fscanf(lectura, "%d %s %s %s %s %s %d %s %d %d\n", &tempID, temp,temp,temp,temp,temp,&tempInt,temp,&tempInt,&tempInt);
		}
		
		rewind(renta);
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
		
		for(k=0;!feof(renta);k++){
			fscanf(renta, "%d %d %d %d %d %d\n", &venta[k].idCliente, &venta[k].idLibro, &venta[k].dias, &venta[k].fecha.dia, &venta[k].fecha.mes, &venta[k].fecha.anno);
		}
		maxRenta = k;
		
		fclose(renta);
		fclose(fcliente);
		fclose(lectura);
		
		printf("\tIntroduzca el ID del cliente\n");
		scanf("%d", &idCliente);
		
		printf("\tIntroduzca el ID del libro\n");
		scanf("%d", &idLibro);
		
		for(k=0;k<maxRenta;k++){
			if(idCliente == venta[k].idCliente && idLibro == venta[k].idLibro){
				encontrado = 1;
				break;
			}
			else encontrado = 0;
		}
		if(encontrado == 1){
			
			for(j=0;j<maxLib;j++){
				if(venta[k].idLibro == libro[j].ID){
					break;
				}
			}
			
			for(i=0;i<max;i++){
				if(venta[k].idCliente == cliente[i].ID){
					break;
				}
			}
			
			time_t tiempo = time(0); //Bloque que consigue la fecha de hoy
		    struct tm *tlocal = localtime(&tiempo);
		    char diac[3];
		    strftime(dia,3,"%d",tlocal);
		    char mesc[3];
		    strftime(mes,3,"%m",tlocal);
		    char annoc[3];
		    strftime(anno,3,"%y",tlocal);
		    
		    int dia = atoi(diac);
		    int mes = atoi(mesc);
		    int anno = atoi(annoc);
		    
		    //calculo, suponiendo que todos los meses son de 30 dias, y no hay años bisiestos
		    int diferencia = dia - venta[k].fecha.dia  + (30 * (mes - venta[k].fecha.mes)) + (365 * (anno - venta[k].fecha.anno));
		    
		    if(diferencia > venta[k].dias){
		    	diferencia = diferencia - venta[k].dias;
		    	multa = 15;
		    	for(l=1;l<diferencia;l++){
		    		multa = multa*2;
				}
			}
			else multa = 0;
			
			if(multa == 0){
				printf("\tMuy bien, libro entregado en tiempo y forma, no genera multas\n");
				getch();
			}
			else{
				printf("\tSe ah presentado un atraso de %d dias\n", diferencia);
				printf("\tSe cobraran %d de multa por atraso\n", multa);
				getch();
			}
			
			printf("\tSe ah regresado el libro%c", 63);
			printf("\t1.-Si\n\t2.-No\n");
			scanf("%d", &op);
			
			if(op == 1){
				libro[j].inventario++;
			}
			
			printf("\tDesea dejar una nota del cliente%c\n", 63);
			printf("\t1.-Si\n\t2.-No\n");
			scanf("%d", &op);
			
			if(op == 1){
				printf("\tEscribir la nota al cliente\n");
				scanf(" %s", cliente[i].notas);
			}
			
			printf("\tDesea dejar una nota sobre el libro%c\n", 63);
			printf("\t1.-Si\n\t2.-No\n");
			scanf("%d", &op);
			
			if(op == 1){
				printf("\tEscribir la nota del libro\n");
				scanf(" %s", libro[j].notas);
			}
			
			printf("\tDesea guardar los cambios%c", 63);
			printf("\t1.-Si\n\t2.-No\n");
			scanf("%d", &op);
			
			if(op == 1){
				escritura = fopen("Clientes.txt", "w");
				for(j=0;j<max;j++){
					fprintf(escritura, "%d %s %s %s %s %s %s\n",cliente[j].ID, cliente[j].nombre, cliente[j].apellido, cliente[j].correo, cliente[j].telefono, cliente[j].direccion, cliente[j].notas);
				}
				fclose(escritura);
				escritura = fopen("Libros.txt", "w");
				for(j=0;j<maxLib;j++){
					fprintf(escritura, "%d %s %s %s %s %s %d %s %d %d\n", 
						libro[j].ID, libro[j].titulo, libro[j].autor, libro[j].anno, libro[j].editorial, libro[j].isbn, libro[j].tipo, libro[j].notas, libro[j].precio, libro[j].inventario);
				}
				fclose(escritura);
				escritura = fopen("Rentas.txt", "w");
				for(j=0;j<maxRenta;j++){
					if(idCliente != venta[j].idCliente && idLibro != venta[j].idLibro)
						fprintf(escritura, "%d %d %d %s %s %s\n", venta[j].idCliente, venta[j].idLibro, venta[j].dias, venta[j].fecha.dia, venta[j].fecha.mes, venta[j].fecha.anno);
				}
				fclose(escritura);
				
				printf("\tCambios Guardados\n");
				getch();
			}
			else{
				printf("\tNo se guardaron cambios\n");
				getch();
			}
			
		}
		
	}
	free(venta);
	free(libro);
	free(cliente);
	Menu_Principal();
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
		printf("\tNo hay libros para buscar\n");
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
		
		printf("\tBuscar por titulo o por ISBN%c\n", 63);
		printf("\t1.-Titulo\n\t2.-ISBN\n");
		scanf("%d", &op);
		switch(op){
			case 1:
				printf("\tEscriba el titulo del libro\n");
				scanf(" %s", buscar);
				for(i=0;i<max;i++){
					if(strcmp(libro[i].titulo,buscar) == 0) {
						encontrado = 1;
						indice = i;
					}
				}
				break;
			case 2:
				printf("\tEscriba el ISBN del libro\n");
				scanf(" %s", buscar);
				for(i=0;i<max;i++){
					if(strcmp(libro[i].isbn,buscar) == 0){
						encontrado = 1;
						indice = i;
					}
				}
				break;
			default:
				printf("\tOpcion no encontrada\nRegresando");
				Comprar_Libro();
				return 0;
		}
		
		if(encontrado == 1){
			i = indice;
			Imprimir_Libro(libro[i]);
			if(libro[i].tipo == 2){
				do{
					printf("\tCuantos Libros desea comprar%c\n", 63);
					scanf("%d", &cantidad);
					if(cantidad > libro[i].inventario) printf("\tNo hay tantas unidades en inventario\n");
				}while(cantidad > libro[i].inventario);
				total = cantidad * libro[i].precio * 1.16;
				printf("\tTotal: %.2f\n", total);
				printf("\tDesea realizar la compra%c\n", 63);
				printf("\t1.-Si\n\t2.-No\n");
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
				else printf("\tLa compra no se realizo\n");
			}
			else{
				printf("\tEl libro no se encuentra disponible para la venta\n");
			}
		}
		else{
			printf("\tNo se ah encontrado el libro\n");
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
		printf("\tNo hay libros para buscar\n");
	} 
	else if(fcliente==NULL || feof(fcliente)){
		printf("\tNo hay clientes registrados");
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
		
		printf("\tBuscar por titulo o por ISBN%c\n", 63);
		printf("\t1.-Titulo\n\t2.-ISBN\n");
		scanf("%d", &op);
		switch(op){
			case 1:
				printf("\tEscriba el titulo del libro\n");
				scanf(" %s", buscar);
				for(i=0;i<max;i++){
					if(strcmp(libro[i].titulo,buscar) == 0) {
						encontrado = 1;
						indice = i;
					}
				}
				break;
			case 2:
				printf("\tEscriba el ISBN del libro\n");
				scanf(" %s", buscar);
				for(i=0;i<max;i++){
					if(strcmp(libro[i].isbn,buscar) == 0){
						encontrado = 1;
						indice = i;
					}
				}
				break;
			default:
				printf("\tOpcion no encontrada\n\tRegresando");
				Comprar_Libro();
				return 0;
		}
		
		if(encontrado == 1){
			i = indice;
			Imprimir_Libro(libro[i]);
			if(libro[i].tipo == 1){
				cantidad = 1;
				total = cantidad * libro[i].precio;
				printf("\tTotal: %.2f\n", total);
				do{
					printf("\tIngrese el ID del cliente\n");
					scanf("%d", &idCliente);
					for(j=0;j<max;j++){
						if(cliente[j].ID==idCliente) {
							encontrado = 1;
							clienteEncontrado = cliente[j].ID;
							Imprimir_Cliente(cliente[j]);
						}
					}
				}while(encontrado != 1);
				printf("\tCuantos dias va a rentar el libro%c\n", 63);
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
				
				printf("\tDesea realizar la renta%c\n", 63);
				printf("\t1.-Si\n\t2.-No\n");
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
				else printf("\tLa renta no se realizo\n");
			}
			else{
				printf("\tEl libro no se encuentra disponible para la renta\n");
			}
		}
		else{
			printf("\tNo se ah encontrado el libro\n");
		}
	}
	
	free(cliente);
	free(libro);

	fclose(lectura);
	fclose(fcliente);
	Menu_Biblioteca();
	return 0;
}

int Leer_Sala(){
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
		printf("\tNo hay libros para buscar\n");
	} 
	else if(fcliente==NULL || feof(fcliente)){
		printf("\tNo hay clientes registrados");
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
		
		printf("\tBuscar por titulo o por ISBN%c\n", 63);
		printf("\t1.-Titulo\n\t2.-ISBN\n");
		scanf("%d", &op);
		switch(op){
			case 1:
				printf("\tEscriba el titulo del libro\n");
				scanf(" %s", buscar);
				for(i=0;i<max;i++){
					if(strcmp(libro[i].titulo,buscar) == 0) {
						encontrado = 1;
						indice = i;
					}
				}
				break;
			case 2:
				printf("\tEscriba el ISBN del libro\n");
				scanf(" %s", buscar);
				for(i=0;i<max;i++){
					if(strcmp(libro[i].isbn,buscar) == 0){
						encontrado = 1;
						indice = i;
					}
				}
				break;
			default:
				printf("\tOpcion no encontrada\n\tRegresando");
				Comprar_Libro();
				return 0;
		}
		
		if(encontrado == 1){
			i = indice;
			Imprimir_Libro(libro[i]);
			if(libro[i].tipo == 3){
				do{
					printf("\tIngrese el ID del cliente\n");
					scanf("%d", &idCliente);
					for(j=0;j<max;j++){
						if(cliente[j].ID==idCliente) {
							encontrado = 1;
							clienteEncontrado = cliente[j].ID;
							Imprimir_Cliente(cliente[j]);
						}
					}
				}while(encontrado != 1);
				dias = 0;
				
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
				
				printf("\tDesea realizar el prestamo en sala%c\n", 63);
				printf("\t1.-Si\n\t2.-No\n");
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
				else printf("\tEl prestamo no se realizo\n");
			}
			else{
				printf("\tEl libro no se encuentra disponible para lectura en sala\n");
			}
		}
		else{
			printf("\tNo se ah encontrado el libro\n");
		}
	}
	
	free(cliente);
	free(libro);

	fclose(lectura);
	fclose(fcliente);
	Menu_Biblioteca();
	return 0;
}

int Menu_Inventario(){
	int op;
	system("cls");
	printf(bienvenida);
	printf("\tSe entro al menu de Inventario\n");
	printf("\t1.-Buscar por cliente\n");
	printf("\t2.-Buscar por libro\n");
	printf("\t3.-Regresar al menu principal\n");
	printf("\t9.-Salir del programa\n");
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
			printf("\tGracias por usar nuestro programa, vuelva pronto\n");
			getche();
			return 0;
		default:
			system("cls");
			printf("\tOpcion no encontrada, favor de seleccionar una opcion valida\n");
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
		printf("\tNo hay ventas registradas");
		noVentas = 1;
	}
	if(lectura==NULL || feof(lectura)){
		printf("\tNo hay clientes registrados\n");
	} 
	else if(libros==NULL || feof(libros)){
		printf("\tNo hay libros registrados\n");
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
			printf("\tCual seria el id del cliente a buscar%c\n", 63);
			scanf("%d", &busquedaID);
			
			for(i=0;i<max;i++){
				printf("\tid: %d\n", cliente[i].ID);
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
						printf("\tEl cliente rento el siguiente libro\n");
						Imprimir_Libro(libro[k]);
					}
				}
				else printf("\tEl cliente no ah rentado libros\n");
			}
			else printf("\tId No encontrado\n");
			
			printf("\tDesea buscar otro cliente%c\n", 63);
			printf("\t1.-Si\n\t2.-No\n");
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
	printf("\tBusqueda por Libro\n");
	printf("\t1.-Buscar por titulo\n");
	printf("\t2.-Buscar por Autor\n");
	printf("\t3.-Buscar por ISBN\n");
	printf("\t4.-Regresar al menu de inventario\n");
	printf("\t5.-Regresar al menu principal\n");
	printf("\t9.-Salir del programa\n");
	printf("\tOp: ");
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
			printf("\tGracias por usar nuestro programa, vuelva pronto\n");
			getche();
			return 0;
		default:
			system("cls");
			printf("\tOpcion no encontrada, favor de seleccionar una opcion valida\n");
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
		printf("\tNo hay libros para buscar\n");
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
		

			printf("\tEscriba el titulo del libro\n");
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
			printf("\tNo se ah encontrado el libro\n");
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
		printf("\tNo hay libros para buscar\n");
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
		
		printf("\tEscriba el ISBN del libro\n");
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
			printf("\tNo se ah encontrado el libro\n");
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
		printf("\tNo hay libros para buscar\n");
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
		
		printf("\tEscriba el autor del libro\n");
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
			printf("\tNo se ah encontrado el libro\n");
		}
		
	}
}

int Menu_Principal(){
	int op;
	system("cls");
	printf(bienvenida);
	printf("\t1.- Clientes\n");
	printf("\t2.- Libros\n");
	printf("\t3.- Biblioteca\n");
	printf("\t4.- Inventario\n");
	printf("\t5.- Salir\n");
	printf("\tOp: ");
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
			printf("\tGracias por usar nuestro programa, vuelva pronto\n");
			getche();
			return 0;
		default:
			system("cls");
			printf("\tOpcion no encontrada, favor de seleccionar una opcion valida\n");
			getche();
			fflush(stdin);
			Menu_Principal();		
	}
}

main(){
	Menu_Principal();
	return 0;
	
}
