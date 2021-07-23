#ifndef BOOK_H_
#define BOOK_H_

struct eBook
{
	//PK
    int idLibro;

    //FK
    int idAutor;

    char titulo[64];
    char editorial[32];
    char idioma[16];
    int anho;
    int cantidadPaginas;

}typedef eBook;

#endif /* BOOK_H_ */

//--------------------------------------------------//

eBook* book_new();
eBook* book_newParametros(char*, char*, char*, char*, char*, char*, char*);
void book_delete(eBook*);

//--------------------------------------------------//

int book_getIdLibro(eBook*, int*);
int book_setIdLibro(eBook*, int);

int book_getIdAutor(eBook*, int*);
int book_setIdAutor(eBook*, int);

int book_getTitulo(eBook*, char*);
int book_setTitulo(eBook*, char*);

int book_getEditorial(eBook*, char*);
int book_setEditorial(eBook*, char*);

int book_getIdioma(eBook*, char*);
int book_setIdioma(eBook*, char*);

int book_getAnho(eBook*, int*);
int book_setAnho(eBook*, int);

int book_getCantPaginas(eBook*, int*);
int book_setCantPaginas(eBook*, int);

//--------------------------------------------------//

int book_isStephenKing(eBook*);
int book_isPhilipDick(eBook*);

int book_isBefore2000(eBook*);
int book_isNotSpanish(eBook*);

//--------------------------------------------------//
