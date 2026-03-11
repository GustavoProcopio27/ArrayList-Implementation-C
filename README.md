# ArrayList

Esta é uma biblioteca C com uma implementação de uma estrutura dinâmica genérica semelhante a um ArrayList de Java ou Vector C++. A ideia é ser capaz de armazenar qualquer tipo de dado disponivel na linguagem C, implementado atráves de cópia de bytes ``memcpy``
## Características

* Estrutura dinâmica baseada em array redimensionável

* Armazena qualquer tipo de dado

* Implementação baseada em cópia de memória

* Interface simples baseada em macros e funções

* Dependência apenas da biblioteca padrão de C

## Como compilar
```sh
gcc arraylist_demo.c arraylist.c -o demo
./demo
```

## Estrutura

A lista armazena internamente:

* ponteiro para memória alocada

* tamanho de cada elemento

* quantidade de elementos armazenados

* capacidade atual da lista
```C
typedef struct 
{
    void *data;             
    size_t length;         
    size_t capacity;       
    size_t element_size;    
} ArrayList;
```



# ⚠️ Aviso: Até segunda instancia a função de pop apesar de remover o elemento indexado, não o está retornando corretamente