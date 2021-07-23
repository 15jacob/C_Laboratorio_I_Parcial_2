//Jacob Cristopher 1F
//Laboratorio I - Recuperatorio

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "LinkedList.h"
#include "input.h"
#include "Author.h"
#include "Book.h"
#include "Controller.h"
#include "parser.h"
#include "listing.h"

/****************************************************
    Consigna:
	1. Cargar ambas listas desde sus respectivos archivos csv.
	2. Listar los datos relacionados. No se deben visualizar Ids.
	3. Utilizar la función ll_filter para realizar dos filtros distintos.
	4. Utilizar la función ll_count para realizar dos cálculos (contador/acumulador)
	5. Guardar en un archivo csv los datos de alguno de los dos filtros del punto 3.

	Menu:
    1. Cargar Listas (Libros y Autores)
    2. Listar Todos los Libros
    3. Filtrar: Libros de Stephen King
    4. Filtrar: Libros anteriores al año 2000
    5. Contar: Libros de Philip K. Dick
    6. Contar: Libros que no esten en Español
    7. Guardar Lista: Libros de Stephen King
    8. Guardar Lista: Libros anteriores al año 2000
   	9. Salir

*****************************************************/

int main()
{
	setbuf(stdout, NULL);

	int respuesta;
	int opcionSeleccionada;

	//Listas Principales
	LinkedList* listaLibros;
	listaLibros = ll_newLinkedList();

	LinkedList* listaAutores;
	listaAutores = ll_newLinkedList();

	//Listas Filtradas y Criterio
	void* pCriterio;
	char nombreArchivoGuardado[64];

	LinkedList* listaFiltradaAutor; //Opcion 3
	listaFiltradaAutor = ll_newLinkedList();

	LinkedList* listaFiltradaAnho; //Opcion 4
	listaFiltradaAnho = ll_newLinkedList();

    if(listaLibros != NULL && listaAutores != NULL && listaFiltradaAutor != NULL && listaFiltradaAnho != NULL)
    {
    	do
    	{
    		system("cls");
    		fflush(stdin);

    		printf("MENU PRINCIPAL\n");
    		printf("1. Cargar Listas (Libros y Autores)\n");
    		printf("2. Listar Todos los Libros\n");
    		printf("3. Filtrar: Libros de Stephen King\n");
    		printf("4. Filtrar: Libros anteriores al año 2000\n");
    		printf("5. Contar: Libros de Philip K. Dick\n");
    		printf("6. Contar: Libros que no esten en Español\n");
    		printf("7. Guardar Lista: Libros de Stephen King\n");
    		printf("8. Guardar Lista: Libros anteriores al año 2000\n");
   			printf("9. Salir\n");

    		opcionSeleccionada = 0;
    		input_option(&opcionSeleccionada);

    		if(opcionSeleccionada != -1)
    		{
    			system("cls");

				switch(opcionSeleccionada)
				{
					case 1:
						//Cargando Libros
						respuesta = Controller_Load_From_Text(listaLibros, "Libros", Parser_Books_FromText);
						new_line();

						switch(respuesta)
						{
							case -2:
								printf("Parece que no hay memoria para cargar los libros. La accion no se ha podido completar\n");
								break;
							case -1:
								printf("No se ha encontrado el archivo de libros indicado\n");
								break;
							case 0:
								printf("Ese archivo no contiene una lista de libros compatible!\n");
								break;
							default:
								printf("Se han cargado %d libros con exito!\n", respuesta);

								system("Pause");
								system("cls");

								//Cargando Autores
								respuesta =  Controller_Load_From_Text(listaAutores, "Autores", Parser_Authors_FromText);
								new_line();

								switch(respuesta)
								{
									case -2:
										printf("Parece que no hay memoria para cargar los autores. La accion no se ha podido completar\n");
										break;
									case -1:
										printf("No se ha encontrado el archivo de autores indicado\n");
										break;
									case 0:
										printf("Ese archivo no contiene una lista de autores compatible!\n");
										break;
									default:
										printf("Se han cargado %d autores con exito!\n", respuesta);
										break;
								}

								break;
						}

						//Si no se pudo cargar la Lista de Autores. Se limpia la lista de Libros para evitar duplicados
						if(respuesta < 1)
						{
							ll_clear(listaLibros);
						}

						break;

					case 2:
						respuesta = Controller_List_Books(listaLibros, listaAutores);
						new_line();

						switch(respuesta)
						{
							case -2:
								printf("No existe ninguna lista de libros cargada\n");
								break;
							case -1:
								printf("No existe ninguna lista de autores cargada\n");
								break;
							default:
								printf("Se han listado %d libros con exito!\n", respuesta);
								break;
						}

						break;

					case 3:
						pCriterio = book_isStephenKing;
						respuesta = Controller_Filter_Books(listaLibros, listaFiltradaAutor, pCriterio);
						new_line();

						switch(respuesta)
						{
							case -2:
								printf("No se ha encontrado una lista de libros cargada\n");
								break;
							case -1:
								printf("No hay memoria disponible para realizar esta accion\n");
								break;
							case 0:
								printf("No se han encontrado libros que coincidan con el filtro\n");
								break;
							case 1:
								printf("Se ha filtrado con exito %d libro de Stephen King\n", respuesta);
								break;
							default:
								printf("Se han filtrado con exito %d libros de Stephen King\n", respuesta);
								break;
						}

						break;

					case 4:
						pCriterio = book_isBefore2000;
						respuesta = Controller_Filter_Books(listaLibros, listaFiltradaAnho, pCriterio);
						new_line();

						switch(respuesta)
						{
							case -2:
								printf("No se ha encontrado una lista de libros cargada\n");
								break;
							case -1:
								printf("No hay memoria disponible para realizar esta accion\n");
								break;
							case 0:
								printf("No se han encontrado libros que coincidan con el filtro\n");
								break;
							case 1:
								printf("Se ha filtrado con exito %d libro previo al año 2000\n", respuesta);
								break;
							default:
								printf("Se han filtrado con exito %d libros previos al año 2000\n", respuesta);
								break;
						}

						break;

					case 5:
						pCriterio = book_isPhilipDick;
						respuesta = Controller_Count_Books(listaLibros, listaFiltradaAnho, pCriterio);
						new_line();

						switch(respuesta)
						{
							case -1:
								printf("No se ha encontrado una lista de libros cargada\n");
								break;
							case 0:
								printf("No se han encontrado libros que coincidan con la busqueda\n");
								break;
							case 1:
								printf("Existe %d libro de Philip K. Dick en la lista\n", respuesta);
								break;
							default:
								printf("Existen %d libros de Philip K. Dick en la lista\n", respuesta);
								break;
						}

						break;

					case 6:
						pCriterio = book_isNotSpanish;
						respuesta = Controller_Count_Books(listaLibros, listaFiltradaAnho, pCriterio);
						new_line();

						switch(respuesta)
						{
							case -1:
								printf("No se ha encontrado una lista de libros cargada\n");
								break;
							case 0:
								printf("No se han encontrado libros que coincidan con la busqueda\n");
								break;
							case 1:
								printf("Existe %d libro de idioma extranjero en la lista\n", respuesta);
								break;
							default:
								printf("Existen %d libros de idioma extranjero en la lista\n", respuesta);
								break;
						}

						break;

					case 7:
						strcpy(nombreArchivoGuardado, "Libros de Stephen King");
						respuesta = Controller_Save_List_Books_As_Text(listaFiltradaAutor, nombreArchivoGuardado);
						new_line();

						switch(respuesta)
						{
							case -1:
								printf("Esta lista esta vacia\n");
								break;
							case 0:
								printf("No se ha podido crear el archivo\n");
								break;
							case 1:
								printf("Se ha guardado %d libro en el archivo %s\n", respuesta, nombreArchivoGuardado);
								break;
							default:
								printf("Se han guardado %d libros en el archivo %s\n", respuesta, nombreArchivoGuardado);
								break;
						}

						break;

					case 8:
						strcpy(nombreArchivoGuardado, "Lista Libros Previos al 2000");
						respuesta = Controller_Save_List_Books_As_Text(listaFiltradaAnho, nombreArchivoGuardado);
						new_line();

						switch(respuesta)
						{
							case -1:
								printf("Esta lista esta vacia\n");
								break;
							case 0:
								printf("No se ha podido crear el archivo\n");
								break;
							case 1:
								printf("Se ha guardado %d libro en el archivo %s\n", respuesta, nombreArchivoGuardado);
								break;
							default:
								printf("Se han guardado %d libros en el archivo %s\n", respuesta, nombreArchivoGuardado);
								break;
						}

						break;

					case 9:
						printf("Saliendo del Programa\n");
						break;

					default:
						printf("Esa opcion es incorrecta\n");
						break;
				}
    		}

    		row_break(60);
    		system("pause");
    	}
    	while(opcionSeleccionada != 9);
    }

    return 0;
}
