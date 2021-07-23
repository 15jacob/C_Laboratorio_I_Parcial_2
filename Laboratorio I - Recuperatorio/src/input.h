#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#endif /* INPUT_H_ */

//--------------------------------------------------//

void new_line();
void row_break(int);

//--------------------------------------------------//

//Input Opcion Generico
int input_option(int*);

//Inputs
int input_int(int*, int, int(*pCriterio)(int*));
int input_char(char*, int);
int input_char_with_validation(char*, int, int(*pCriterio)(char*));
int input_string(char*, int, int(*pCriterio)(char*));
int input_file_name(char*, char*);

//Validaciones
int validation_int(int*, int, int);
int validation_int_unsigned(int*);
int validation_char_no_special_char(char*);
int validation_string_no_special_char(char*);
int validation_file_name(char*);

//Informa los intentos restantes
void intentos_restantes(int*);

//--------------------------------------------------//
