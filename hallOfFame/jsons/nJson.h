#ifndef NJSON_H_INCLUDED
#define NJSON_H_INCLUDED

// El tipo que se usar� para las funciones de escritura.
typedef void* Write(FILE*, void*);

/*
Estructura que guarda un dato de un nJson.
@var name: nombre del dato.
@var value: valor del dato.
@var next: dato siguiente (s�mil lista enlazada).
@var isArray: si el dato es un array (!=0) o no (==0).
@var length: longitud del array del dato.
@var func: puntero a la funci�n que se llamar� para escribir el dato.
*/
typedef struct _data{
    char* name;
    void* value;
    struct _data* next;
    char isArray;
    unsigned length;
    Write* func;
}Data;

/*
Estructura que guarda todas las propiedades del JSON.
@var name: nombre del JSON.
@var data: puntero al primer dato del JSON.
*/
typedef struct _nJson{
    char* name;
    Data* data;
}nJson;

/*
M�todo auxiliar para buscar un dato con cierto nombre recursivamente
(si this->name == name lo devuelve, caso contrario, pasa al siguiente).
@param this: puntero al dato a comparar.
@param data: nombre del dato que se busca.
@return: puntero al dato o NULL si no lo encuentra.
*/
Data* data_hasData(Data* this, char* name);

/*
M�todo auxiliar para agregar un dato a la lista recursivamente
(si this est� vac�o, crea el dato, caso contrario, pasa al siguiente).
@param this: puntero al dato que se est� evaluando.
@param name: nombre del dato a agregar.
@param value: valor del dato a agregar.
@param size: tama�o del dato a agregar.
@param isArray: si el dato es un array (!=0) o no (==0).
@param length: longitud del array del dato.
@param func: puntero a la funci�n que imprimir� el dato.
@return: puntero al primer dato.
*/
Data* data_addData(Data* this, char* name, void* value, unsigned valueSize,
    char isArray, unsigned length, Write func);

/*
M�todo auxiliar para liberar un dato recursivamente
(se libera y llama a la misma funci�n con su siguiente).
@param this: puntero al dato a liberar.
*/
void data_freeData(Data* this);

/*
Inicializa un nJson y fija un nombre y un primer dato.
@param this: puntero al nJson a inicializar.
@param name: nombre que tendr� el nJson.
@param dataName: nombre del primer dato.
@param value: valor del primer dato.
@param size: tama�o del primer dato.
@param isArray: si el dato es un array (!=0) o no (==0).
@param length: longitud del array del dato.
@param func: puntero a la funci�n que imprimir� el dato.
@return: puntero al nJson inicializado.
*/
nJson* nJson_init(nJson* this, char* name, char* dataName, void* value,
    unsigned size, char isArray, unsigned length, Write func);

/*
Reemplaza el nombre de un nJson.
@param this: puntero al nJson.
@param name: nuevo nombre.
*/
void nJson_setName(nJson* this, char* name);

/*
M�todo para saber si el nJson tiene cierto dato.
@param this: nJson en cuesti�n.
@param name: nombre del dato.
@return: verdadero (1) o falso (0).
*/
char nJson_hasData(nJson* this, char* name);

/*
Agrega un dato al nJson.
@param this: puntero al nJson.
@param name: nombre del dato.
@param value: valor del dato.
@param size: tama�o del dato.
@param isArray: si el dato es un array (!=0) o no (==0).
@param length: longitud del array del dato.
@param func: puntero a la funci�n que imprimir� el dato.
*/
void nJson_setData(nJson* this, char* name, void* value, unsigned size,
    char isArray, unsigned length, Write func);

/*
Escribe un dato del nJson.
@param this: puntero al nJson.
@param file: salida a la cual escribir.
@param name: nombre del dato.
*/
void nJson_writeData(FILE* file, nJson* this, char* name);

/*
Escribe un valor, interpret�ndolo como int.
@param file: salida a la cual escribir.
@param value: puntero al valor.
@return: puntero a la siguiente posici�n (para escribir arrays).
*/
void* nJson_writeInt(FILE* file, void* value);

/*
Escribe un valor, interpret�ndolo como unsigned.
@param file: salida a la cual escribir.
@param value: puntero al valor.
@return: puntero a la siguiente posici�n (para escribir arrays).
*/
void* nJson_writeUnsigned(FILE* file, void* value);

/*
Escribe un valor, interpret�ndolo como double.
@param file: salida a la cual escribir.
@param value: puntero al valor.
@return: puntero a la siguiente posici�n (para escribir arrays).
*/
void* nJson_writeDouble(FILE* file, void* value);

/*
Escribe un valor, interpret�ndolo como long.
@param file: salida a la cual escribir.
@param value: puntero al valor.
@return: puntero a la siguiente posici�n (para escribir arrays).
*/
void* nJson_writeLong(FILE* file, void* value);

/*
Escribe un valor, interpret�ndolo como float.
@param file: salida a la cual escribir.
@param value: puntero al valor.
@return: puntero a la siguiente posici�n (para escribir arrays).
*/
void* nJson_writeFloat(FILE* file, void* value);

/*
Escribe un valor, interpret�ndolo como short.
@param file: salida a la cual escribir.
@param value: puntero al valor.
@return: puntero a la siguiente posici�n (para escribir arrays).
*/
void* nJson_writeShort(FILE* file, void* value);

/*
Escribe un valor, interpret�ndolo como unsigned short.
@param file: salida a la cual escribir.
@param value: puntero al valor.
@return: puntero a la siguiente posici�n (para escribir arrays).
*/
void* nJson_writeUnsignedShort(FILE* file, void* value);

/*
Escribe un valor, interpret�ndolo como string.
@param file: salida a la cual escribir.
@param value: puntero al valor.
@return: puntero a la siguiente posici�n (para escribir arrays).
*/
void* nJson_writeString(FILE* file, void* value);

/*
Escribe un valor, interpret�ndolo como boolean (char).
@param file: salida a la cual escribir.
@param value: puntero al valor.
@return: puntero a la siguiente posici�n (para escribir arrays).
*/
void* nJson_writeBoolean(FILE* file, void* value);

/*
Escribe un valor, interpret�ndolo como nJson.
@param file: salida a la cual escribir.
@param value: puntero al valor.
@return: puntero a la siguiente posici�n (para escribir arrays).
*/
void* nJson_writenJson(FILE* file, void* value);

/*
Comprueba si un puntero a nJson es v�lido o no.
Si no es v�lido, corta la ejecuci�n devolviendo 1.
@param this: puntero a comprobar.
*/
void nJson_checknJson(nJson* this);

/*
Comprueba si un puntero a dato es v�lido o no.
Si no es v�lido, corta la ejecuci�n devolviendo 2.
@param this: puntero a comprobar.
*/
void nJson_checkData(Data* this);

/*
Comprueba si un puntero a archivo es v�lido o no.
Si no es v�lido, corta la ejecuci�n devolviendo 3.
@param this: puntero a comprobar.
*/
void nJson_checkFile(FILE* this);

/*
Comprueba si un puntero a valor es v�lido o no.
Si no es v�lido, corta la ejecuci�n devolviendo 4.
@param this: puntero a comprobar.
*/
void nJson_checkValue(void* this);

/*
Comprueba si la longitud de un array es v�lida o no.
Si no es v�lido, corta la ejecuci�n devolviendo 5.
@param this: longitud a comprobar.
*/
void nJson_checkLength(unsigned this);

/*
Fija la posici�n de escritura al pen�ltimo caracter,
para que la pr�xima escritura sobrescriba el �ltimo.
@param file: salida a modificar.
*/
void nJson_eraseLastCharacter(FILE* file);

/*
Finaliza la escritura.
@param file: salida a finalizar.
*/
void nJson_endWrite(FILE* file);

/*
Devuelve el mensaje de error correspondiente a un id espec�fico.
@param id: el id del error (c�digo de retorno).
@return: el string correspondiente al id utilizado.
*/
char* nJson_getError(int id);

/*
Libera todos los recursos utilizados por el nJson.
@param this: puntero al nJson a liberar.
*/
void nJson_free(nJson* this);

#endif // NJSON_H_INCLUDED
