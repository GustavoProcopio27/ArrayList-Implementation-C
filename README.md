# ArrayList (C)

Uma pequena biblioteca C com uma implementação de uma estrutura dinâmica genérica semelhante a um ```ArrayList``` de **Java** ou ao ```std::vector``` de **C++**. 

A estrutura permite armazenar qualquer tipo de dado de forma contígua na memória e cresce dinamicamente conforme novos elementos são adicionados.

A implementação utiliza cópia de memória (```memcpy```) e ponteiros genéricos (```void*```) para permitir que qualquer tipo seja armazenado.

## ✨ Características:

* Estrutura dinâmica baseada em array redimensionável

* Armazena qualquer tipo de dado

* Elementos armazenados em memória contígua

* Crescimento automático da capacidade
* Interface simples com macros e funções

* Dependência apenas da biblioteca padrão de C

## 🚀 Como compilar:
```sh
gcc arraylist_demo.c arraylist.c -o demo
./demo
```
Ou compile com qualquer projeto que inclua:
```md
arraylist.c
arraylist.h
```
## 🛠️ Funcionamento interno:
A estrutura armazena os elementos em um bloco contínuo de memória, iniciado com capacidade para 8 elementos do tipo passado na inicialização.
Quando a capacidade é excedida, a memória é realocada com ```realloc()``` aumentando a capacidade.

A capacidade cresce em 1.5x +1 a cada expansão:
```C 
    arrayList->capacity = arrayList->capacity*3 / 2 + 1;
```
Isso evita realocações frequentes, ou expansão muito rápida da capacidade além da necessidade.

## 📦 Estrutura da ArrayList:

```C
typedef struct 
{
    void *data;             // Ponteiro para o bloco de memória que armazena os elementos   
    size_t length;          // Número atual de elementos armazenados
    size_t capacity;        // Capacidade máxima antes de precisar realocar memória    
    size_t element_size;    // Tamanho em bytes de cada elemento     
} ArrayList;
```
#### Campos:

|       Campo         |                 Descrição                  |
| ------------------- | ------------------------------------------ | 
|     ```data```      | ponteiro para o início do bloco de memória |
|     ```length```    |  número de elementos atualmente na lista   |
|   ```capacity```    |    quantidade máxima antes de realocar     |
|  ```element_size``` |        tamanho do tipo armazenado          |


## </> API:
A biblioteca utiliza macros para fornecer auxílio na tipagem e internamente gera funções que trabalham com ```void*```

### Inicialização:
```ArrayList* arraylist_init(type);```

Cria uma nova lista capaz de armazenar elementos do tipo especificado.

```C
ArrayList *list = arraylist_init(int);
```
Internamente chama: ```arraylist_new(sizeof(type))```

---
```ArrayList* arraylist_init_from(void* array, size_t length, size_t capacity, type)```

Cria uma nova lista capaz de armazenar elementos do tipo especificado, inicializando-a com elementos de uma array passada.
```C
int teste[] = {1,2,3,4,5};

ArrayList* list = arraylist_init_from(teste,5,0, int);
```

---

### Adicionar elemento:
```void arraylist_add(ArrayList* arraylist, type element, type); ```  

Adiciona um elemento ao final da lista.
```C
int a=29
arraylist_add(list, 10, int);
arraylist_add(list, a, int);
```
Funcionamento:

1.  macro cria uma variável temporária do tipo especificado
> ⚠️ Aviso: não foi utilizado compound literal por compatibilidade com editores de texto, evitando criação de warnings

2. Passa o endereço dessa variável para _arraylist_append

3. O valor é copiado com memcpy
---
### Remover elemento:
```type* arraylist_pop(ArrayList* arraylist,int index, type);``` 

Remove o elemento no índice especificado e retorna uma cópia alocada.

> ⚠️ Importante: O retorno precisa ser liberado com free().

---

### Obter elemento:
```type arraylist_get(ArrayList* arraylist, int index, type);```

Retorna o valor do elemento no índice especificado.

```C
int value = arraylist_get(list, 0, int);
```
Internamente:

* calcula o endereço do elemento

* converte para o tipo correto

* retorna o valor desreferenciado

---
### Modificar elemento
```void arraylist_set(ArrayList* arraylist,int index, type element, type) ``` 

Substitui o elemento no índice especificado.
```C
arraylist_set(list, 0, 99, int);
```

---
### Buscar índice:
```int arraylist_indexOf(ArrayList* arraylist, type element, type)``` 

Retorna o índice da primeira ocorrência do elemento.
```C
int index = arraylist_indexOf(list, 10, int);
```
Se não for encontrado retorna ```-1```
Utiliza *linear search* devido a lista poder não estar ordenada

---
### Contar ocorrências:
```int arraylist_count(ArrayList* arraylist, type element) ```                          
Conta quantas vezes um elemento aparece na lista.
```C
int teste[] = {1,2,10,10,5};

ArrayList* list = arraylist_init_from(teste,5,0, int);
int count = arraylist_count(list, 10);
```

---

### Limpar lista:
```void arraylist_clear(ArrayList* arrayList);```

Remove todos os elementos e retorna a lista para seu estado inicial.
Efeitos:

- ```length = 0```
- ```capacity = 8```
- memória é realocada
```C
int teste[] = {1,2,3,4,5};

ArrayList* list = arraylist_init_from(teste,5,0, int);
arraylist_clear(list)
```
---

### Liberar memória:
```void arraylist_free(ArrayList* arrayList);```
Libera completamente a lista.

```C
ArrayList *list = arraylist_init(string);

arraylist_free(list);
```
Isso libera:

- o bloco de dados

- a estrutura ArrayList


### Iteração:
```arraylist_foreach(arraylist, func, type)```
Executa uma função sobre todos elementos da lista, 
A função deve receber type* e retornar void

Exemplo:
```C
void print_square_list_int(int* val){
    static int counter = 0;
    printf("index %d: %d\n", counter,((*val) * (*val)));
    counter++;
}

int teste[] = {1,10,10,4,5};

ArrayList* list = arraylist_init_from(teste,5,0, int);
arraylist_foreach(list,print_square_list_int,int);
```


---

### Mapeamento:
```arraylist_map(arraylist, func, type)```

Executa uma função sobre todos elementos da arraylist modificando ela
Retorna uma nova lista
Exemplo:
```C
void* mult_by_pi(void* v)
{
    static float  res;
    int val = *(int*)v;
    res = (float) val;
    res*=3.1415f;
    return &res;
}


int teste[] = {1,10,10,4,5};

ArrayList *list = arraylist_init_from(teste,5,0, int);

ArrayList *list2 = arraylist_map(list,mult_by_pi,float);

arraylist_free(list);
arraylist_free(list2);
```



É de responsabilidade do usuário liberar a nova lista com ```arraylist_free()```



## 🔜 Melhorias futuras:

Algumas ideias para evoluir a biblioteca:

* ordenação

* suporte a comparadores customizados


