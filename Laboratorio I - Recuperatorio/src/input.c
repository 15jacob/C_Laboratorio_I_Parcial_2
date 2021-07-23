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
 * Crea una nueva linea, puramente estetico
 */
void new_line()
{
	printf("\n");
}

/**
 * Crea una barra horizontal de guiones, recibe el largo (Max 100)
 * @param size
 */
void row_break(int size)
{
	int i;

	if(size > 0 && size < 101)
	{
		for(i = 0; i < size; i++)
		{
			printf("-");
		}
	}

	new_line();
}

//--------------------------------------------------//

/**
 * Pide el Ingreso de un Entero para seleccionar como opcion. Valida con unsigned
 * @return
 */
int input_option(int* opcion)
{
	int respuesta;

	printf("Ingrese Opcion: ");
	respuesta = input_int(opcion, 0, validation_int_unsigned);

	return respuesta;
}

/**
 * Recibe un puntero a un numero, la cantidad de reintentos, y el criterio que se utilizara para validarlo
 * @param numero
 * @param reintentos
 * @param pCriterio
 * @return
 */
int input_int(int* numero, int reintentos, int(*pCriterio)(int*))
{
	int respuesta;
	respuesta = -1;

	int numeroAux;
	char checker; //Se usa para corroborar que no haya caracteres especiales junto al numero

	int i;

	for(i = reintentos; i >= 0; i--)
	{
		if(scanf("%d%c", &numeroAux, &checker) == 2 && checker == '\n' && pCriterio(&numeroAux) == 1)
		{
			*numero = numeroAux;
			respuesta = 1;
			break;
		}
		else
		{
			intentos_restantes(&i);
		}
	}

	return respuesta;
}

/**
 * Pide el ingreso de un caracter, sin validaciones (Ideal para cuando los Caracteres Especiales no son problema)
 * @param caracter
 * @param reintentos
 * @return
 */
int input_char(char* caracter, int reintentos)
{
	int respuesta;
	respuesta = -1;

	char caracterIngresado;
	int i;

	for(i = reintentos; i >= 0; i--)
	{
		if(scanf("%c", &caracterIngresado) == 1)
		{
			*caracter = caracterIngresado;
			respuesta = 1;
			break;
		}
		else
		{
			intentos_restantes(&i);
		}
	}

	return respuesta;
}

/**
 * Pide el ingreso de un caracter, valida acorde al criterio que se le indique
 * @param caracter
 * @param reintentos
 * @param pCriterio
 * @return
 */
int input_char_with_validation(char* caracter, int reintentos, int(*pCriterio)(char*))
{
	int respuesta;
	respuesta = -1;

	char caracterIngresado;
	int i;

	for(i = reintentos; i >= 0; i--)
	{
		if(scanf("%c", &caracterIngresado) == 1 && pCriterio(&caracterIngresado) == 1)
		{
			*caracter = caracterIngresado;
			respuesta = 1;
			break;
		}
		else
		{
			intentos_restantes(&i);
		}
	}

	return respuesta;
}

/**
 * Recibe un puntero a char (string), la cantidad de reintentos disponibles y el criterio por el que se validara
 * @param string
 * @param reintentos
 * @param pCriterio
 * @return
 */
int input_string(char* string, int reintentos, int(*pCriterio)(char*))
{
	int respuesta;
	respuesta = 0;

	char stringIngresado[128];
	int i;

	for(i = reintentos; i >= 0; i--)
	{
		fflush(stdin);
		if(scanf("%s", stringIngresado) == 1 && pCriterio(stringIngresado) == 1)
		{
			strcpy(string, stringIngresado);
			respuesta = 1;
			break;
		}
		else
		{
			intentos_restantes(&i);
		}
	}

	return respuesta;
}

/**
 * Recibe un puntero a char, utiliza la funcion input_string para pedir el nombre de un archivo
 * @param string
 * @return
 */
int input_file_name(char* string, char* archivoPedido)
{
	int respuesta;

	//Pido ingresar el nombre del archivo correspondiente
	printf("Seleccione el archivo que contenga la lista de %s.\n", archivoPedido);
	printf("Incluyendo su extension (Ejemplo: listado.txt)\n");
	row_break(60);

	//Muestro archivos en el directorio (Solo Compatible Windows)
	#ifdef _WIN32
	printf("Archivos compatibles en el directorio:\n");
	system("dir /b /a-d NOT *.csv *.txt");
	row_break(60);
	#endif

	printf("Nombre del archivo: ");
	respuesta = input_string(string, 2, validation_file_name);

	return respuesta;
}

//--------------------------------------------------//

/**
 * Valida un entero siempre y cuando no sobrepase los limites indicados
 * @param numeroValidar
 * @param minimo
 * @param maximo
 * @return
 */
int validation_int(int* numeroValidar, int minimo, int maximo)
{
	int respuesta;
	respuesta = -1;

	if(numeroValidar != NULL)
	{
		if(*numeroValidar >= minimo && *numeroValidar <= maximo)
		{
			respuesta = 1;
		}
	}

	return respuesta;
}

/**
 * Valida un entero siempre y cuando sea mayor a 0
 * @param numeroValidar
 * @return
 */
int validation_int_unsigned(int* numeroValidar)
{
	int respuesta;
	respuesta = -1;

	if(numeroValidar != NULL)
	{
		if(*numeroValidar >= 0)
		{
			respuesta = 1;
		}
	}

	return respuesta;
}

///REVISAR
int validation_char_no_special_char(char* charValidar)
{
	int respuesta;
	respuesta = -1;

	fflush(stdin);
	if(isalpha(*charValidar))
	{
		respuesta = 1;
	}

    return respuesta;
}

/**
 * Valida un String ante los siguientes casos:
 * -Ingreso de Numeros en la Cadena
 * -Ingreso de Caracteres especiales en la cadena
 * @param stringValidar
 * @return
 */
int validation_string_no_special_char(char* stringValidar)
{
	int respuesta;
	int i;

	for(i = 0; i < strlen(stringValidar); i++)
	{
		//Si no se encuentran caracteres especiales se devuelve un 1
		respuesta = 1;

		//Chequeando si es un caracter especial y no un espacio
		if(isalpha(stringValidar[i]) == 0 && !isspace(stringValidar[i]))
		{
			respuesta = -1;
			break;
		}
	}

	return respuesta;
}

/**
 * Valida un String ante los siguientes casos.
 * -No puede contener caracteres especiales que no son admitidos por nombres de archivos
 * -No puede contener mas de un punto "."
 * -No puede contener espacios (Aunque deberia de poder, queda a corregir)
 *
 * @param stringValidar
 * @return
 */
int validation_file_name(char* stringValidar)
{
	int respuesta;

	int contadorPuntos;
	contadorPuntos = 0;

	int i;

	for(i = 0; i < strlen(stringValidar); i++)
	{
		if(stringValidar[i] == '.' && contadorPuntos == 0)
		{
			respuesta = 1;
			contadorPuntos++;
		}
		else
		{
			if(isalpha(stringValidar[i]) == 0)
			{
				respuesta = -1;
				break;
			}
		}
	}

	return respuesta;
}

/**
 * Muestra los intentos restantes
 * @param reintentos
 */
void intentos_restantes(int* reintentos)
{
	if(reintentos != NULL)
	{
		if(*reintentos > 0)
		{
			printf("Se han ingresado caracteres invalidos, reingrese (%d intentos restantes)\n", *reintentos);
		}
		else
		{
			printf("Se han ingresado caracteres invalidos\n");
		}
	}
}

//--------------------------------------------------//
