#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "LinkedList.h"
#include "input.h"
#include "Book.h"
#include "Author.h"
#include "Controller.h"
#include "parser.h"
#include "listing.h"

/**
 * Constructor por Defecto
 * @return
 */
eBook* book_new()
{
	eBook* pBook;
	pBook = (eBook*)calloc(sizeof(eBook), 1);

	return pBook;
}

/**
 * Constructor por Parametros
 * @param idVueloStr
 * @param idAvionStr
 * @param idPilotoStr
 * @param fechaStr
 * @param destinoStr
 * @param cantPasajerosStr
 * @param horaDespegueStr
 * @param horaLlegadaStr
 * @return
 */
eBook* book_newParametros(char* idLibroStr, char* idAutorStr, char* tituloStr, char* editorialStr, char* idiomaStr, char* anhoStr, char* cantidadPaginasStr)
{
	eBook* pLibro;
	pLibro = book_new();

    int idLibro;
    int idAutor;
    int anho;
    int cantidadPaginas;

	if(pLibro != NULL)
	{
		//Parseo de los valores Numericos
		idLibro = atoi(idLibroStr);
		idAutor = atoi(idAutorStr);
		anho = atoi(anhoStr);
		cantidadPaginas = atoi(cantidadPaginasStr);

		//Si los datos no son los esperados o no logran setearse por algun motivo, se devolvera un puntero a nulo
		if(book_setIdLibro(pLibro, idLibro) == 0 ||
		   book_setIdAutor(pLibro, idAutor) == 0 ||
		   book_setTitulo(pLibro, tituloStr) == 0 ||
		   book_setEditorial(pLibro, editorialStr) == 0 ||
		   book_setIdioma(pLibro, idiomaStr) == 0 ||
		   book_setAnho(pLibro, anho) == 0 ||
		   book_setCantPaginas(pLibro, cantidadPaginas) == 0)
		{
			pLibro = NULL;
		}
	}

	return pLibro;
}

/**
 * Borra el Vuelo Indicado
 * @param this
 */
void book_delete(eBook* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

//--------------------------------------------------//

///Getters y Setters
int book_getIdLibro(eBook* this, int* idLibro)
{
	int respuesta;
	respuesta = 0;

    if(this != NULL)
    {
        *idLibro = this->idLibro;
        respuesta = 1;
    }

    return respuesta;
}

int book_setIdLibro(eBook* this, int idLibro)
{
	int respuesta;
	respuesta = 0;

	if(this != NULL && idLibro > 0)
	{
		this->idLibro = idLibro;
		respuesta = 1;
	}

	return respuesta;
}

int book_getIdAutor(eBook* this, int* idAutor)
{
	int respuesta;
	respuesta = 0;

    if(this != NULL)
    {
        *idAutor = this->idAutor;
        respuesta = 1;
    }

    return respuesta;
}

int book_setIdAutor(eBook* this, int idAutor)
{
	int respuesta;
	respuesta = 0;

	if(this != NULL && idAutor > 0)
	{
		this->idAutor = idAutor;
		respuesta = 1;
	}

	return respuesta;
}

int book_getTitulo(eBook* this, char* titulo)
{
	int respuesta;
	respuesta = 0;

	if(this != NULL)
	{
		strcpy(titulo, this->titulo);
		respuesta = 1;
	}

	return respuesta;
}

int book_setTitulo(eBook* this, char* titulo)
{
	int respuesta;
	respuesta = 0;

	if(this != NULL && validation_string_no_special_char(titulo) == 1)
	{
		strcpy(this->titulo, titulo);
		respuesta = 1;
	}

	return respuesta;
}

int book_getEditorial(eBook* this, char* editorial)
{
	int respuesta;
	respuesta = 0;

	if(this != NULL)
	{
		strcpy(editorial, this->editorial);
		respuesta = 1;
	}

	return respuesta;
}

int book_setEditorial(eBook* this, char* editorial)
{
	int respuesta;
	respuesta = 0;

	if(this != NULL && validation_string_no_special_char(editorial) == 1)
	{
		strcpy(this->editorial, editorial);
		respuesta = 1;
	}

	return respuesta;
}

int book_getIdioma(eBook* this, char* idioma)
{
	int respuesta;
	respuesta = 0;

	if(this != NULL)
	{
		strcpy(idioma, this->idioma);
		respuesta = 1;
	}

	return respuesta;
}

int book_setIdioma(eBook* this, char* idioma)
{
	int respuesta;
	respuesta = 0;

	if(this != NULL && validation_string_no_special_char(idioma) == 1)
	{
		strcpy(this->idioma, idioma);
		respuesta = 1;
	}

	return respuesta;
}

int book_getAnho(eBook* this, int* anho)
{
	int respuesta;
	respuesta = 0;

    if(this != NULL)
    {
        *anho = this->anho;
        respuesta = 1;
    }

    return respuesta;
}

int book_setAnho(eBook* this, int anho)
{
	int respuesta;
	respuesta = 0;

	//Se usa dicha validacion porque si bien es poco probable, un avion puede tener 0 pasajeros
	if(this != NULL && validation_int_unsigned(&anho) == 1)
	{
		this->anho = anho;
		respuesta = 1;
	}

	return respuesta;
}

int book_getCantPaginas(eBook* this, int* cantidadPaginas)
{
	int respuesta;
	respuesta = 0;

    if(this != NULL)
    {
        *cantidadPaginas = this->cantidadPaginas;
        respuesta = 1;
    }

    return respuesta;
}

int book_setCantPaginas(eBook* this, int cantidadPaginas)
{
	int respuesta;
	respuesta = 0;

	//Se usa dicha validacion puesto que existen las "0hs"
	if(this != NULL && validation_int_unsigned(&cantidadPaginas) == 1)
	{
		this->cantidadPaginas = cantidadPaginas;
		respuesta = 1;
	}

	return respuesta;
}

//--------------------------------------------------//

///Funciones Criterio (Para filtros y Conteos)
int book_isStephenKing(eBook* pBook)
{
	int respuesta;
	respuesta = 0;

	int idAutor;

	if(pBook != NULL)
	{
		//Consigo el Id del Autor
		book_getIdAutor(pBook, &idAutor);

		//Comparo el Id conseguido con el Id Buscado // 1 == Id de Stephen King
		if(idAutor == 1)
		{
			respuesta = 1;
		}
	}

	return respuesta;
}

int book_isPhilipDick(eBook* pBook)
{
	int respuesta;
	respuesta = 0;

	int idAutor;

	if(pBook != NULL)
	{
		//Consigo el Id del Autor
		book_getIdAutor(pBook, &idAutor);

		//Comparo el Id conseguido con el Id Buscado // 1 == Id de Stephen King
		if(idAutor == 5)
		{
			respuesta = 1;
		}
	}

	return respuesta;
}

int book_isBefore2000(eBook* pBook)
{
	int respuesta;
	respuesta = 0;

	int anho;

	if(pBook != NULL)
	{
		//Consigo el Año del Libro
		book_getAnho(pBook, &anho);

		//Si el año es anterior al 2000 se devuelve un true
		if(anho < 2000)
		{
			respuesta = 1;
		}
	}

	return respuesta;
}

int book_isNotSpanish(eBook* pBook)
{
	int respuesta;
	respuesta = 0;

	char idioma[16];

	if(pBook != NULL)
	{
		//Consigo el Idioma del Libro
		book_getIdioma(pBook, idioma);

		//Si el idioma no es "Español" se devuelve un true
		if((strcmpi(idioma, "Espanol") != 0))
		{
			respuesta = 1;
		}
	}

	return respuesta;
}

//--------------------------------------------------//
