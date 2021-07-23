#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "input.h"
#include "Author.h"
#include "Book.h"
#include "Controller.h"
#include "parser.h"
#include "listing.h"

/**
 * Constructor por Defecto
 * @return
 */
eAuthor* author_new()
{
	eAuthor* pAuthor;
	pAuthor = (eAuthor*)calloc(sizeof(eAuthor), 1);

	return pAuthor;
}

/**
 * Constructor por Parametros
 * @param idStr
 * @param nombreStr
 * @return
 */
eAuthor* author_newParametros(char* idStr, char* nombreStr)
{
	eAuthor* pAuthor;
	pAuthor = author_new();

    int id;

	if(pAuthor != NULL)
	{
		//Parseo de los valores Numericos
		id = atoi(idStr);

		//Si los datos no son los esperados o no logran setearse por algun motivo, se devolvera un puntero a nulo
		if(author_setId(pAuthor, id) == 0 ||
		   author_setNombre(pAuthor, nombreStr) == 0)
		{
			pAuthor = NULL;
		}
	}

	return pAuthor;
}

/**
 * Borra un Autor
 * @param pList
 * @return
 */
void author_delete(eAuthor* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

//--------------------------------------------------//

/**
 * Busca en la Lista de Autores el Id correspondiente y devuelve su posicion. Si el mismo no existe devolvera -1
 * @param pListAuthors
 * @param idAutor
 * @return
 */
int author_getPosition(LinkedList* pListAuthors, int* idAutor)
{
	int respuesta;
	respuesta = -1;

	eAuthor* pAutorAux;
	int idAuxiliar;

	int len;
	len = ll_len(pListAuthors);

	int i;

	if(pListAuthors != NULL && len > 0)
	{
		pAutorAux = author_new(); //Auxiliar donde se almacenara el autor siendo analizado

		if(pAutorAux != NULL)
		{
			for(i = 0; i < len; i++)
			{
				//Consigo al Autor
				pAutorAux = (eAuthor*)ll_get(pListAuthors, i);

				//Consigo el Id
				author_getId(pAutorAux, &idAuxiliar);

				//Comparo el Id Conseguido con el Id Buscado
				if(idAuxiliar == *idAutor)
				{
					respuesta = i; //Si coincide, consigo su posicion para retornar y breakeo del bucle
					break;
				}
			}
		}
	}

	return respuesta;
}

/**
 * Busca en la lista de Autores el nombre correspondiente y devuelve su id. Si el mismo no existe devolvera -1
 * @param pListAuthors
 * @param nombreBuscado
 * @return
 */
int author_getId_By_Name(LinkedList* pListAuthors, char* nombre)
{
	int idAutor;
	idAutor = -1;

	eAuthor* pAutorAux;
	char nombreEncontrado[64];

	int len;
	len = ll_len(pListAuthors);

	int i;

	if(pListAuthors != NULL && len > 0)
	{
		pAutorAux = author_new(); //Auxiliar donde se almacenara el autor siendo analizado

		if(pAutorAux != NULL)
		{
			for(i = 0; i < len; i++)
			{
				//Consigo al Autor
				pAutorAux = (eAuthor*)ll_get(pListAuthors, i);

				//Consigo el Nombre
				author_getNombre(pAutorAux, nombreEncontrado);

				//Comparo el Nombre Conseguido con el Nombre Buscado
				if(strcmpi(nombreEncontrado, nombre) == 0)
				{
					author_getId(pAutorAux, &idAutor); //Si coincide, consigo el Id para retornar y breakeo del bucle
					break;
				}
			}
		}
	}

	return idAutor;
}

///Getters y Setters
int author_setId(eAuthor* this, int idAutor)
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

int author_getId(eAuthor* this, int* idAutor)
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

int author_setNombre(eAuthor* this, char* nombre)
{
	int respuesta;
	respuesta = 0;

	if(this != NULL && validation_string_no_special_char(nombre) == 1)
	{
		strcpy(this->nombre, nombre);
		respuesta = 1;
	}

	return respuesta;
}

int author_getNombre(eAuthor* this, char* nombre)
{
	int respuesta;
	respuesta = 0;

    if(this != NULL)
    {
    	strcpy(nombre, this->nombre);
    	respuesta = 1;
    }

    return respuesta;
}

//--------------------------------------------------//
