#ifndef AUTHOR_H_
#define AUTHOR_H_

struct eAuthor
{
    int idAutor;
    char nombre[64];
}typedef eAuthor;

#endif /* AUTHOR_H_ */

//--------------------------------------------------//

eAuthor* author_new();
eAuthor* author_newParametros(char*, char*);
void author_delete(eAuthor*);

//--------------------------------------------------//

int author_getPosition(LinkedList*, int*);
int author_getId_By_Name(LinkedList*, char*);

int author_setId(eAuthor*, int);
int author_getId(eAuthor*, int*);

int author_setNombre(eAuthor*, char*);
int author_getNombre(eAuthor*, char*);

//--------------------------------------------------//
