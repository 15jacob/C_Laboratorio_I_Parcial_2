#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "LinkedList.h"
#include "input.h"
#include "Author.h"
#include "Book.h"
#include "Controller.h"
#include "parser.h"
#include "listing.h"

//--------------------------------------------------//

/**
 * Recibe el Puntero a una Lista de Libros y el Puntero a una Lista de Autores.
 * Hace el matching entre el libro con su correspondiente autor, y lo manda a la funcion show_book
 * @param pListBooks
 * @param pListAuthors
 * @return Devuelve la cantidad de elementos que se estan mostrando
 */
int list_books(LinkedList* pListBooks, LinkedList* pListAuthors)
{
	int contadorLibros;
	contadorLibros = 0;

	eBook* pLibro;

	eAuthor* pAutor;
	int idAutor;
	int indexAutor;

	int len;
	len = ll_len(pListBooks);

	int i;

	if(pListBooks != NULL && len > 0)
	{
		row_break(100);
		printf("%25s %20s %20s %15s %5s %10s\n", "TITULO", "AUTOR", "EDITORIAL", "IDIOMA", "AÑO", "PAGINAS");

		//Itero entre la lista de Libros
		for(i = 0; i < len; i++)
		{
			//Consigo el Libro en la Posicion Actual
			pLibro = (eBook*)ll_get(pListBooks, i);

			//De dicho Libro, consigo el Id del Autor
			book_getIdAutor(pLibro, &idAutor);

			//Con el Id del Autor, busco su indice dentro de la lista de autores
			indexAutor = author_getPosition(pListAuthors, &idAutor);

			//Con el indice del Autor, consigo al Autor
			pAutor = (eAuthor*)ll_get(pListAuthors, indexAutor);

			//Mando a la funcion indicada el Libro y Autor conseguidos para ser mostrados
			if(show_book(pLibro, pAutor) == 1)
			{
				contadorLibros++;
			}
		}

		row_break(100);
	}

	return contadorLibros;
}

/**
 * Recibe el Puntero a un Libro y el Puntero a un Autor
 * Fetchea los datos correspondientes de ambos y los muestra
 * @param libro
 * @param autor
 * @return Devuelve 1 si se logra mostrar el libro, 0 si no
 */
int show_book(eBook* libro, eAuthor* autor)
{
	int respuesta;
	respuesta = 0;

	int idLibro;
	char nombreAutor[32];
	char titulo[64];
	char editorial[32];
	char idioma[16];
	int anho;
	int cantidadPaginas;

	//Consigo los datos del Libro y el Autor indicados para mostrarlos
	if(book_getIdLibro(libro, &idLibro) == 1 &&
	   author_getNombre(autor, nombreAutor) == 1 &&
	   book_getTitulo(libro, titulo) == 1 &&
	   book_getEditorial(libro, editorial) == 1 &&
	   book_getIdioma(libro, idioma) == 1 &&
	   book_getAnho(libro, &anho) == 1 &&
	   book_getCantPaginas(libro, &cantidadPaginas) == 1)
	{
		printf("%25s %20s %20s %15s %5d %10d\n", titulo, nombreAutor, editorial, idioma, anho, cantidadPaginas);
		respuesta = 1;
	}

	return respuesta;
}

//--------------------------------------------------//
