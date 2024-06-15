#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#include <string.h>

/*Pentru folosirea bibliotecii se va folosi functia de initializare pe un vector. Functia de initializare va prelua dimensiunea tipului de date folosit, si tipul ei cum ar fi Char Float Int String sau Struct
  functia de afisare functioneaza doar pe elementele de tip Int Float String sau Char, pentru cele de tip struct va fi nevoie sa creeati o implementare proprie, folosind size(vector) pentru numarul de elemente, get_elem pentru a prelua un element din vector, si apoi afisarea elementelor element cu element. La final de program este necesara folosirea functiei de destruct(vector) care va elibera memoria alocata*/
void alloc_vector(vector *elem)
{
  if(elem->count >= elem->max_size){
    if(elem->max_size < 4){
      elem->max_size = elem->max_size + 1;
    }
    else{
      elem->max_size = elem->max_size / 2 * 3;
    }
    elem->elements = realloc(elem->elements, elem->max_size * elem->type_size);
    assert(elem->elements != NULL);
  }
}

vector initialize(size_t type_size, DataType tip)
{
  assert("Vector deja initializat" && type_size > 0);
  return (vector){.elements = NULL, .count = 0, .max_size = 0, .type_size = type_size, .type = NotDestructed, .tip_date = tip};
}

void push_back(vector *elem, void *value)
{
  switch(elem->tip_date){
  case String:
    alloc_vector(elem);
    memcpy(elem->elements + (elem->count * elem->type_size), &value, elem->type_size);
    break;
  default:
    alloc_vector(elem);
    memcpy(elem->elements + (elem->count * elem->type_size), value, elem->type_size);
    break;
  }
  elem->count++;
}

void pop(vector *elem)
{
  assert(elem->count > 0);
  elem->count--;
}

void destruct(vector *elem)
{
  assert(elem->type == NotDestructed);
  free(elem->elements);
  elem->max_size = 0;
  elem->count = 0;
  elem->type = Destructed;
  elem->type_size =  0;
}

size_t size(vector elem)
{
  return elem.count;
}

void *get_elem(vector elem, size_t poz)
{
  assert(poz < elem.count && "pozitie inafara indexului vectorului");
  return (elem.elements + (poz * elem.type_size));
}

vector vec_cat(vector v1, vector v2)
{
  assert(v1.elements != v2.elements && "Adresele nu se pot suprapune");
  assert((v1.type == NotDestructed) && (v2.type == NotDestructed) && "Nu pot fi folositi vectori neinitializati");
  assert(v1.tip_date == v2.tip_date && "Nu se pot folosi vectori de tipuri diferite de date");
  vector vec_rez = initialize(v1.type_size, v1.tip_date);
  for(size_t i = 0;i < v1.count;i++){
    push_back(&vec_rez, (get_elem(v1, i)));
  }
  for(size_t i = 0;i < v2.count;i++){
    push_back(&vec_rez, (get_elem(v2, i)));
  }
  return vec_rez;
}
  
void show_elements(vector elem)
{
  assert(elem.tip_date != Struct && "Nu se poate afisa acest tip de date");
  switch(elem.tip_date){
  case String:
    char **to_string = (char **)elem.elements;
    for(char **start = to_string;start != to_string + elem.count;start++){
      printf("%s/n", *start);
    }
    break;
  case Int:
    int *to_int = (int *)elem.elements;
    for(int *start = to_int; start != to_int + elem.count;start++){
      printf("%d ", *start);
    }
    break;
  case Char :
    char *to_char = (char *)elem.elements;
    for(char *start = to_char;start != to_char + elem.count;start++){
      printf("%c ", *start);
    }
    break;
  default:
    float *to_float = (float *)elem.elements;
    for(float *start = to_float;start != to_float + elem.count;start++){
      printf("%f ", *start);
    }
    break;
  }
  printf("\n");
}

	  
    
