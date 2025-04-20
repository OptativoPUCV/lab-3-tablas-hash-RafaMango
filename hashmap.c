#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

/*
2.- Implemente la función void insertMap(HashMap * map, char * key, void * value). Esta función inserta un nuevo dato (key,value) en el mapa y actualiza el índice current a esa posición. Recuerde que para insertar un par (clave,valor) debe:

a - Aplicar la función hash a la clave para obtener la posición donde debería insertar el nuevo par ---

b - Si la casilla se encuentra ocupada (ecual), avance hasta una casilla disponible (método de resolución de colisiones). Una casilla disponible es una casilla nula, pero también una que tenga un par inválido (key==NULL).

c - Ingrese el par en la casilla que encontró.

No inserte claves repetidas. Recuerde que el arreglo es circular. Recuerde actualizar la variable size.
*/
void insertMap(HashMap * map, char * key, void * value)
{
    if(map == NULL || key == NULL)return;  //si es null no se puede

    long dato = hash(key, map->capacity);
    long datoOriginal = dato;

    while(map->buckets[dato] != NULL && map->buckets[dato]->key != NULL  )
    {
        if(is_equal(map->buckets[dato]->key, key))return;
        //tengo que cambiar a dato aqui, segun capacidad 
        if(dato == datoOriginal) return;

    }
    
    Pair* nuevoPar = createPair(strdup(key), value); //
    map->buckets[dato] = nuevoPar;
    map->size++; //
    map->current = dato;
}

void enlarge(HashMap * map) 
{
    enlarge_called = 1; //no borrar (testing purposes)


}

/*
1.- Implemente la función createMap en el archivo hashmap.c. Esta función crea una variable de tipo HashMap, 
inicializa el arreglo de buckets con casillas nulas, inicializa el resto de variables y retorna el mapa. Inicialice el índice current a -1.
*/

HashMap * createMap(long capacity)
{
    HashMap *map = (HashMap*)malloc(sizeof(HashMap)); //asignar memoria al maphash
    map->buckets = (Pair**)calloc(capacity, sizeof(Pair*)); //inizializar memoria a las casillas?
    map->capacity = capacity;
    map->size = 0; //Inicializa en 0
    map->current = -1; //Invalido de momento
    return map;
}

void eraseMap(HashMap * map,  char * key)
{    


}
/*
3.- Implemente la función Pair * searchMap(HashMap * map, char * key), la cual retorna el Pair asociado a la clave ingresada. 
Recuerde que para buscar el par debe:

a - Usar la función hash para obtener la posición donde puede encontrarse el par con la clave---

b - Si la clave no se encuentra avance hasta encontrarla (método de resolución de colisiones)

c - Si llega a una casilla nula, retorne NULL inmediatamente (no siga avanzando, la clave no está)--

Recuerde actualizar el índice current a la posición encontrada. Recuerde que el arreglo es circular.
*/
Pair * searchMap(HashMap * map,  char * key) 
{   
    if(map == NULL || key == NULL)return NULL;

    long dato = hash(key, map->capacity);

    while(map->buckets[dato] != NULL)
    {
        if(map->buckets[dato]->key != NULL && is_equal(map->buckets[dato]->key, key));
        {
            map->current = dato;
            return map->buckets[dato];
        }
        //actualizar indice
    }

    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
