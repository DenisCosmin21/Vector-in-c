#ifndef VECTOR
#define VECTOR

typedef enum
  {
    Destructed,
    NotDestructed
  }DestructType;

typedef enum
  {
    Char,
    Int,
    Float,
    String,
    Struct
  }DataType;

typedef struct
{
  void *elements;
  size_t count;
  size_t max_size;
  size_t type_size;
  DestructType type;
  DataType tip_date;
}vector;

void alloc_vector(vector *elem);

vector initialize(size_t type_size, DataType tip);

void push_back(vector *elem, void *value);

void pop(vector *elem);

void destruct(vector *elem);

void show_elements(vector elem);

void *get_elem(vector elem, size_t poz);

vector vec_cat(vector v1, vector v2);

size_t size(vector elem);
#endif
