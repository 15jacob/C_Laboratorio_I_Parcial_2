#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "input.h"
#include "Controller.h"
#include "Author.h"
#include "Book.h"
#include "parser.h"
#include "listing.h"

/**
 * Recibe el Puntero a una Lista y el Puntero a una funcion Parser
 * Pide un nombre de archivo de donde cargar los datos y de poder abrirlo, lo manda al parser indicado
 * @param pList
 * @param archivoPedido
 * @param pParser
 * @return
 */
int Controller_Load_From_Text(LinkedList* pList, char* archivoPedido, int(*pParser)(FILE*, LinkedList*))
{
	int respuesta;
	respuesta = -2;

	char nombreArchivo[64];
	FILE *pArchivoCSV;

	if(pList != NULL)
	{
		respuesta = -1;

		//Pido nombre del archivo
		input_file_name(nombreArchivo, archivoPedido);
		pArchivoCSV = fopen(nombreArchivo,"r");

		//Si se pudo encontrar y abrir dicho archivo se envia a la Funcion Parser
		if(pArchivoCSV != NULL)
		{
			respuesta = pParser(pArchivoCSV , pList);
		}

		fclose(pArchivoCSV);
	}

    return respuesta;
}

//--------------------------------------------------//

/**
 * Recibe el Puntero a una lista de Libros y una Lista de Autores para mostrarla unificada
 * @param pListBooks
 * @param pListAuthors
 * @return
 */
int Controller_List_Books(LinkedList* pListBooks, LinkedList* pListAuthors)
{
	int contadorLibros;
	contadorLibros = -2;

	int lenBooks;
	lenBooks = ll_len(pListBooks);

	int lenAuthors;
	lenAuthors = ll_len(pListAuthors);

	if(pListBooks != NULL && lenBooks > 0)
	{
		contadorLibros = -1;

		//Si la Lista de Autores no es Nula, se envia a la funcion encargada del listado
		if(pListAuthors != NULL && lenAuthors > 0)
		{
			contadorLibros = list_books(pListBooks, pListAuthors);
		}
	}

	return contadorLibros;
}

//--------------------------------------------------//

/**
 * Recibe el Puntero a una Lista de Libros (Origen). El puntero a una Lista Filtrada (Destino). Y el puntero a una Funcion Criterio
 * La lista Origen sera Filtrada con el Criterio indicado, los resultados se almacenaran en una Lista auxiliar,
 * si dicho filtro no devuelve nulo, se cargara lo obtenido en la lista Destino
 * @param pListBooks
 * @param pListFiltered
 * @param pCriterio
 * @return
 */
int Controller_Filter_Books(LinkedList* pListBooks, LinkedList* pListFiltered, int(*pCriterio)(void*))
{
	int respuesta;
	respuesta = -2;

	LinkedList* pListAuxiliar;

	int len;
	len = ll_len(pListBooks);

	if(pListBooks != NULL && len > 0)
	{
		respuesta = -1;
		pListAuxiliar = ll_newLinkedList();

		//Si se pudo reservar memoria para la lista auxiliar, se filtra la lista origen con el criterio indicado, para alojar en el auxiliar
		if(pListAuxiliar != NULL)
		{
			respuesta = 0;
			pListAuxiliar = ll_filter(pListBooks, pCriterio);

			//Si el filtro realizado no da un resultado nulo, almaceno los resultados en la lista destino
			if(pListAuxiliar != NULL)
			{
				*pListFiltered = *pListAuxiliar;
				respuesta = ll_len(pListFiltered); //Cantidad de elementos que pasaron el filtro
			}
		}
	}

	return respuesta;
}

/**
 * Recibe el Puntero a una Lista de Libros (Origen). El puntero a una Lista Filtrada (Destino). Y el puntero a una Funcion Criterio
 * La lista Origen sera Analizada con el Criterio indicado, los resultados contados se almacenaran la lista destino
 * @param pListBooks
 * @param pListFiltered
 * @param pCriterio
 * @return
 */
int Controller_Count_Books(LinkedList* pListBooks, LinkedList* pListFiltered, int(*pCriterio)(void*))
{
	int respuesta;
	respuesta = -1;

	int len;
	len = ll_len(pListBooks);

	//Si la lista de libros no esta vacia, la envio a la funcion ll_count con el criterio indicado
	if(pListBooks != NULL && len > 0)
	{
		respuesta = ll_count(pListBooks, pCriterio);
	}

	return respuesta;
}

//--------------------------------------------------//

/**
 * Recibe el Puntero a una Lista de Libros. Y el nombre del archivo que se quiere guardar.
 * El nombre del archivo se le colocara al final una extension .csv
 * De cada libro se buscaran sus correspondientes datos, y se colocaran separados por comas
 * @param pListBooks
 * @param nombreArchivo
 * @return
 */
int Controller_Save_List_Books_As_Text(LinkedList* pListBooks, char* nombreArchivo)
{
	int contador;
	contador = -1;

	FILE *pArchivoTexto;
	char nombreArchivoConExtension[64];

	eBook *pBook;
    int idLibro;
    int idAutor;
    char titulo[64];
    char editorial[32];
    char idioma[16];
    int anho;
    int cantidadPaginas;

	int i;

	int len;
	len = ll_len(pListBooks);

	if(pListBooks != NULL && len > 0)
	{
		contador = 0;

		//Concatenando la extension al nombre de archivo indicado
		strcpy(nombreArchivoConExtension, nombreArchivo);
		strcat(nombreArchivoConExtension, ".csv");

		//Llamada al archivo en modo escritura
		pArchivoTexto = fopen(nombreArchivoConExtension,"w");

		if(pArchivoTexto != NULL)
		{
			//Titulos de las columnas
			fprintf(pArchivoTexto, "idLibro, idAutor, titulo, editorial, idioma, anho, cantidadPaginas\n");

			//Itero la lista de libros de principio a fin
			for(i = 0; i < len; i++)
			{
				pBook = (eBook*)ll_get(pListBooks, i); //Consigo el libro almacenado en la posicion actual del bucle

				//Si el libro obtenido no es nulo, fetcheo sus datos y los coloco uno detras del otro separados por comas
				if(pBook != NULL)
				{
					book_getIdLibro(pBook, &idLibro);
					book_getIdAutor(pBook, &idAutor);
					book_getTitulo(pBook, titulo);
					book_getEditorial(pBook, editorial);
					book_getIdioma(pBook, idioma);
					book_getAnho(pBook, &anho);
					book_getCantPaginas(pBook, &cantidadPaginas);

					fprintf(pArchivoTexto, "%d,%d,%s,%s,%s,%d,%d\n", idLibro, idAutor, titulo, editorial, idioma, anho, cantidadPaginas);

					contador++; //Libro cargado con exito = Uno mas para el conteo
				}
			}
		}

		fclose(pArchivoTexto);
	}

    return contador;
}

//--------------------------------------------------//
