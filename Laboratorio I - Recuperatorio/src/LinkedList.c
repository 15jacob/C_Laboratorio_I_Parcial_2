#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

//----------------------------WARNING----------------------------//

//---------------------COMENTARIO HELL AHEAD---------------------//

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = NULL;

    //Creo espacio en memoria dinamica e inicializo los campos
    this = (LinkedList*)calloc(sizeof(LinkedList), 1);

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    //Si la LinkedList no es nula, almaceno el valor size para devolverlo
    if(this != NULL)
    {
    	returnAux = this->size;
    }

    return returnAux;
}

/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pNodo;
	pNodo = NULL;

	int len;
	len = ll_len(this);

	int i;

    if(this != NULL && nodeIndex >= 0 && nodeIndex < len)
    {
    	//Asigno al nodo el primer nodo
        pNodo = this->pFirstNode;

        //En base a lo anterior, avanzo de nodo en nodo hasta llegar al nodo en el indice indicado
        for(i = 0; i < nodeIndex; i++)
        {
          	pNodo = pNodo->pNextNode;
        }
    }

    return pNodo;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}

/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;

    Node* pUltimoNodo;
    Node* pNodo;

	int len;
	len = ll_len(this);

	//Si la LinkedList no es nula, y el indice se encuentra entre 0 y el tamaño de la misma
	if(this != NULL && nodeIndex >= 0 && nodeIndex <= len)
	{
		//Creo el espacio en memoria dinamica para el nodo que voy a crear
		pNodo = (Node*)calloc(sizeof(Node), 1);

		//Si se pudo crear el espacio en memoria dinamica
		if(pNodo != NULL)
		{
			//Si el nodo no es nulo, le asocio el elemento. Mientras tanto el proximo nodo sera nulo
			pNodo->pElement = pElement;

			//Si el indice indicado es 0 se colocara al nuevo nodo como el primer nodo
			if(nodeIndex == 0)
			{
				pNodo->pNextNode = this->pFirstNode; //El nuevo nodo se coloca como primer nodo, y lo hago que apunte al que antes era el primer nodo
				this->pFirstNode = pNodo; //La LinkedList ahora utiliza como primer nodo, el que acabo de crear
			}
			//Si el indice indicado es mayor a 0 y menor al len
			else
			{
				//Busco al nodo anterior
				pUltimoNodo = getNode(this, nodeIndex-1);

				if(pUltimoNodo != NULL)
				{
					//Si el indice es menor al len
					if(nodeIndex < len)
					{
						pNodo->pNextNode = pUltimoNodo->pNextNode; //El nuevo nodo va a apuntar al nodo que el nodo anterior antes apuntaba
						pUltimoNodo->pNextNode = pNodo; //El nodo anterior a mi nodo, ahora va a apuntar al nuevo nodo creado
					}
					//Si el indice es igual al len (a.k.a. el ultimo nodo)
					else
					{
						pNodo->pNextNode = NULL; //Como es el ultimo nodo de la lista, por el momento no va a apuntar a ningun otro
						pUltimoNodo->pNextNode = pNodo; //El que antes era ultimo nodo, ahora tiene uno que le sigue al que va a apuntar
					}
				}
			}

			//Incremento el tamaño de la LinkedList y seteo el 0 para el return
			len++;
			this->size = len;

			returnAux = 0;
		}
	}

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}

/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    int len;
    len = ll_len(this);

    //Si la LinkedList no es nula, agrego el nodo al final
    if(this != NULL)
    {
        returnAux = addNode(this, len, pElement);
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;

    Node* pNodo;

    int len;
    len = ll_len(this);

    //Si la LinkedList no es nula, y el indice indicado sea mayor o igual a cero, y menor al tamaño
    if(this != NULL && index >= 0 && index < len)
    {
    	//Consigo el nodo de la posicion indicada
    	pNodo = getNode(this, index);

    	//Almaceno el pElement en el retorno
    	returnAux = pNodo->pElement;
    }

    return returnAux;
}

/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    int len;
    len = ll_len(this);

    Node* pNodo;

    //Si la LinkedList no es nula, y el indice indicado sea mayor o igual a cero, y menor al tamaño
    if(this != NULL && index >= 0 && index < len)
    {
    	//Consigo el nodo de la posicion indicada
        pNodo = getNode(this, index);

        //Asigno al elemento en dicho nodo, el elemento nuevo
        pNodo->pElement = pElement;
        returnAux = 0;
    }

    return returnAux;
}

/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;

    int len;
    len = ll_len(this);

    Node* pNodo;
    Node* pNodoAnterior;

    //Si la LinkedList no es nula, y el indice indicado sea mayor o igual a cero, y menor al tamaño
    if(this != NULL && index >= 0 && index < len)
    {
    	//Consigo el nodo de la posicion indicada
        pNodo = getNode(this, index);

        if(pNodo != NULL)
        {
        	//Si el indice indicado es el primero se reemplaza el primer nodo de la LinkedList por el que le sigue
        	if(index == 0)
        	{
                this->pFirstNode = pNodo->pNextNode;
        	}
        	//Si es cualquier otro, se requerira el uso de un nodo auxiliar para configurar tambien al nodo que apunta al que vamos a borrar
        	else
        	{
        		pNodoAnterior = getNode(this, index-1); //Index-1 --> El anterior a la posicion que vamos a borrar
        		pNodoAnterior->pNextNode = pNodo->pNextNode; //A dicho nodo, le asigno que ahora apunte al que sigue al nodo que vamos a borrar
        	}

			//Libero la memoria del auxiliar para el nodo
        	free(pNodo);

        	//Al ser borrado un elemento de la lista, la misma se reduce en 1
        	len--;
        	this->size = len;

        	returnAux = 0;
        }
    }

    return returnAux;
}

/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    int len;
    len = ll_len(this);

    int i;

    //Si la lista no es nula, se pueden borrar elementos
    if(this != NULL)
    {
    	//Borrado secuencial de todos los nodos
    	for(i = len-1; i >= 0; i--)
    	{
    		ll_remove(this, i);
    	}

    	returnAux = 0;
    }

    return returnAux;
}

/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	//Borra los Elementos (Nodos) dentro de la lista
    	returnAux = ll_clear(this);

    	if(returnAux == 0)
    	{
    		//Libero la memoria dinamica que era ocupada por la LinkedList
    		free(this);
    	}
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    int len;
    len = ll_len(this);

    int i;

    void* pElementAuxiliar;

    //Si la LinkedList no es nula puedo buscar elementos dentro
    if(this != NULL)
    {
    	//Recorro la lista en busca del elemento indicado
    	for(i = 0; i < len; i++)
    	{
    		pElementAuxiliar = ll_get(this, i);

    		//Si la funcion get consigue un elemento que coincide con aquel que estoy buscando
    		if(pElementAuxiliar == pElement)
    		{
    			returnAux = i; //Devuelvo el indice donde hubo coincidencia
    			break;
    		}
    	}
    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    int len;
    len = ll_len(this);

    //Si la lista no es nula puedo chequear si esta vacia o no
    if(this != NULL)
    {
    	returnAux = 1;

    	//Si existe aunque sea un elemento dentro de la lista
    	if(len > 0)
    	{
    		returnAux = 0;
    	}
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    int len;
    len = ll_len(this);

    //Si la LinkedList no es nula y el indice indicado se encuentra entre 0 y el ultimo elemento inclusive. Puedo pushear un elemento
    if(this != NULL && index >= 0 && index <= len)
    {
    	//Pusheo al elemento en cuestion en el indice indicado
    	returnAux = addNode(this, index, pElement);
    }

    return returnAux;
}

/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;

    int len;
    len = ll_len(this);

    //Si la LinkedList no es nula y el indice indicado se encuentra entre 0 y el ultimo elemento inclusive. Puedo popear un elemento
    if(this != NULL && index >= 0 && index <= len)
    {
    	//Consigo el puntero al elemento en dicho indice
    	returnAux = ll_get(this, index);

    	//Si lo encuentro, lo borro
    	if(returnAux != NULL)
    	{
    		ll_remove(this, index);
    	}
    }

    return returnAux;
}

/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    int banderaBusqueda;

    //Si la LinkedList no es nula, puedo chequear si el elemento existe dentro
    if(this != NULL)
    {
    	returnAux = 0;
    	banderaBusqueda = ll_indexOf(this, pElement);

    	//Si IndexOf devuelve un indice valido (Osea, 0 o mayor), se da por satisfactoria la busqueda
    	if(banderaBusqueda >= 0)
    	{
    		returnAux = 1;
    	}
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;

    void* pElementoAux;

    int len2;
    len2 = ll_len(this2); //Guardo el largo de la lista2 para poder recorrerla

    int i;
    int banderaContains;

    if(this != NULL && this2 != NULL)
    {
    	returnAux = 1;

    	for(i = 0; i < len2; i++)
    	{
    		pElementoAux = ll_get(this2, i); //Traer a un elemento de la lista2
    		banderaContains = ll_contains(this, pElementoAux); // Pasarlo a la funcion contains con la primer lista

    		//Si la funcion anterior devolviese 1 significaria que el elemento en cuestion se encuentra en dicha lista
    		if(banderaContains == 0)
    		{
    			returnAux = 0;
    			break;
    		}
    	}
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this, int from, int to)
{
    LinkedList* clonedList = NULL;
    void* pElementoAuxiliar;

    int len;
    len = ll_len(this);

    int i;

    if(this != NULL && from >= 0 && to <= len && from < to)
    {
    	//Creo espacio en memoria dinamica para la lista
    	clonedList = ll_newLinkedList();

    	//Si se pudo encontrar espacio
    	if(clonedList != NULL)
    	{
    		//Recorro el espacio entre las posiciones indicadas
			for(i = from; i < to; i++)
			{
				//Obtengo el elemento dentro del nodo actual
				pElementoAuxiliar = ll_get(this, i);

				//Coloco ese elemento dentro de un nuevo nodo en mi sublista
				ll_add(clonedList, pElementoAuxiliar);
			}
    	}
    }

    return clonedList;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* clonedList = NULL;

    int len;
    len = ll_len(this);

    if(this != NULL)
    {
    	//Llamo a la funcion sublist para que clone desde la posicion 0 hasta la ultima
    	clonedList = ll_subList(this, 0, len);
    }

    return clonedList;
}

/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pCriterio Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL (0) Si ok
 */
int ll_sort(LinkedList* this, int(*pCriterio)(void* ,void*), int order)
{
    int returnAux = -1;

	void* pElementoAuxiliar1;
	void* pElementoAuxiliar2;

    int len;
    len = ll_len(this);

	int i;
	int j;
	int comparativa;

	if(this != NULL && pCriterio != NULL && (order == 1 || order == 0))
	{
		//Burbujeo
		for (i = 0; i < len-1; i++)
		{
			for (j = i+1; j < len; j++)
			{
				//Consigo ambos elementos para poder compararlos
				pElementoAuxiliar1 = ll_get(this, i);
				pElementoAuxiliar2 = ll_get(this, j);

				//Comparativa almacena el resultado, idealmente la funcion retornaria 1 si el primer elemento es mayor que el segundo, un 0 si son iguales, y un -1 si estan bien ordenados
				comparativa = pCriterio(pElementoAuxiliar1, pElementoAuxiliar2);

				//Si la comparativa indica que el primer elemento deberia estar por delante del segundo y el orden es ASCENDENTE
				//Si la comparativa indica que el primer elemento deberia estar por delante del segundo y el orden es DESCENDENTE
				if((comparativa == 1 && order == 1) || (comparativa == -1 && order == 0))
				{
					//Swapeo de los elementos
					ll_set(this, i, pElementoAuxiliar2);
					ll_set(this, j, pElementoAuxiliar1);
				}

			}
		}
		returnAux = 0;
	}

    return returnAux;
}

/**
 * Recibe el puntero de una lista y el puntero de una funcion criterio para contar resultados
 * Itera los nodos de la lista y los envia a la funcion criterio indicada, las devoluciones se iran acumulando en la variable contador
 * @param this
 * @param pCriterio
 * @return
 */
int ll_count(LinkedList* this, int(*pCriterio)(void*))
{
	int contador;
	contador = 0;

	void* pElementAux;

	int len;
	len = ll_len(this);

	int i;

	if(this != NULL && pCriterio != NULL && len > 0)
	{
		//Itero la lista de principio a fin
		for(i = 0; i < len; i++)
		{
			//Obtengo el elemento en la posicion que se esta analizando
			pElementAux = ll_get(this, i);

			//Envio el elemento a la funcion Criterio, el resultado se ira acumulando en contador
			contador += pCriterio(pElementAux);
		}
	}

	return contador;
}

/**
 * Recibe el puntero de una lista y el puntero de una funcion criterio para filtrar resultados
 * Itera los nodos de la lista y los envia a la funcion criterio indicada,
 * si las devoluciones son positivas, se van agregando los elementos "aprobados" a la linkedlist
 * @param this
 * @param pCriterio
 * @return
 */
LinkedList* ll_filter(LinkedList* this, int (*pCriterio)(void*))
{
	LinkedList* pListaFiltrada;

	int respuesta;
	void* pElementAux;

    int len;
    len = ll_len(this);

	int i;

	if(this != NULL && pCriterio != NULL && len > 0)
	{
		pListaFiltrada = ll_newLinkedList();

		if(pListaFiltrada != NULL)
		{
			//Itero la lista de principio a fin
			for(i = 0; i < len; i++)
			{
				//Obtengo el elemento en la posicion que se esta analizando
				pElementAux = ll_get(this, i);

				//Envio el elemento a la funcion Criterio, la misma decidira si el elemento se debe o no agregar
				respuesta = pCriterio(pElementAux);

				//Si el elemento cumple el criterio se agrega a la lista filtrada
				if(respuesta == 1)
				{
					ll_add(pListaFiltrada, pElementAux);
				}
			}
		}
	}

	return pListaFiltrada;
}

//--------------------------------------------------//
