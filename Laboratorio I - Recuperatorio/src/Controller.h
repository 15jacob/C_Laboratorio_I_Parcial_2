#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#endif /* CONTROLLER_H_ */

//--------------------------------------------------//

int Controller_Load_From_Text(LinkedList*, char*, int(*pParser)(FILE*, LinkedList*));

//--------------------------------------------------//

int Controller_List_Books(LinkedList*, LinkedList*);

//--------------------------------------------------//

int Controller_Filter_Books(LinkedList*, LinkedList*, int(*pCriterio)(void*));
int Controller_Count_Books(LinkedList*, int(*pCriterio)(void*));

//--------------------------------------------------//

int Controller_Save_List_Books_As_Text(LinkedList*, char*);

//--------------------------------------------------//
