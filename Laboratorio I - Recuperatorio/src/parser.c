#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "input.h"
#include "Controller.h"
#include "parser.h"
#include "Author.h"
#include "Book.h"
#include "listing.h"

//--------------------------------------------------//

/**
 * Recibe un puntero a un archivo y un puntero a LinkedList.
 * Recorre el archivo fetcheando la data y construyendola para poder agregarla a la LinkedList
 * @param pFile
 * @param pList
 * @return
 */
int Parser_Books_FromText(FILE* pFile , LinkedList* pList)
{
	int contadorLibros;
	contadorLibros = 0;

	int contadorCampos;

	eBook* pLibro;
    char idLibro[16];
    char idAutor[16];
    char titulo[64];
    char editorial[32];
    char idioma[16];
    char anho[8];
    char cantidadPaginas[4];

    while(!feof(pFile))
	{
		//Separa la data en cadenas
    	contadorCampos = fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", idLibro, idAutor, titulo, editorial, idioma, anho, cantidadPaginas);

		//Si se consiguieron los campos requeridos se carga en la variable auxiliar con el constructor por parametros
		if(contadorCampos == 7)
		{
			pLibro = book_newParametros(idLibro, idAutor, titulo, editorial, idioma, anho, cantidadPaginas);

			//Si la funcion anterior no devuelve un puntero a nulo, dicho elemento se carga en la LinkedList
			if(pLibro != NULL)
			{
				//Si se pudo agregar al elemento satisfactoriamente, se suma al contador
				if(ll_add(pList, (eBook*)pLibro) == 0)
				{
					contadorLibros++;
				}
			}
		}
	}

    return contadorLibros;
}

/**
 * Recibe un puntero a un archivo y un puntero a LinkedList.
 * Recorre el archivo fetcheando la data y construyendola para poder agregarla a la LinkedList
 * @param pFile
 * @param pList
 * @return
 */
int Parser_Authors_FromText(FILE* pFile , LinkedList* pList)
{
	int contadorAutores;
	contadorAutores = 0;

	int contadorCampos;

	eAuthor* pAutor;
    char idAutor[8];
    char nombre[64];

    while(!feof(pFile))
	{
    	//Separa la data en cadenas
    	contadorCampos = fscanf(pFile,"%[^,],%[^\n]\n", idAutor, nombre);

    	//Si se consiguieron los campos requeridos se carga en la variable auxiliar con el constructor por parametros
		if(contadorCampos == 2)
		{
			pAutor = author_newParametros(idAutor, nombre);

			//Si la funcion anterior no devuelve un puntero a nulo, dicho elemento se carga en la LinkedList
			if(pAutor != NULL)
			{
				//Si se pudo agregar al elemento satisfactoriamente, se suma al contador
				if(ll_add(pList, (eAuthor*)pAutor) == 0)
				{
					contadorAutores++;
				}
			}
		}
	}

    return contadorAutores;
}

//--------------------------------------------------//
