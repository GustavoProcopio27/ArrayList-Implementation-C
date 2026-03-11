#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stddef.h>

/**
 * @brief Estrutura dinâmica genérica semelhante a um ArrayList ou Vector.
 *  
 * Armazena elementos contíguos em memória, permitindo crescimento dinâmico
 * conforme novos elementos são adicionados.
 *
**/
typedef struct 
{
    void *data;             /**< Ponteiro para o início do bloco de memória que armazena os elementos */
    size_t length;          /**< Número de elementos atualmente armazenados */
    size_t capacity;        /**< Capacidade máxima antes de precisar realocar memória */
    size_t element_size;    /**< Tamanho em bytes de cada elemento */
} ArrayList;

// ===============================================================================================================

/**
 * @brief Macro para inicialização da estrutura ArrayList
 * Permite criar a lista passando o tipo dos elementos a serem armazenados
 * 
 * @param type Tipo de dado a ser armazenado
 * 
 **/
#define arraylist_init(type) arraylist_new(sizeof(type))
ArrayList *arraylist_new(size_t element_size);


// ===============================================================================================================

/**
 * @brief Macro para anexação de um novo dado na estrutura ArrayList
 * adicionar elementos do mesmo tipo da lista iniciada
 *
 * @param arrayList arraylist instanciada
 * @param element elemento a ser adicionado 
 **/
#define arraylist_add(arraylist, element, type)                       \
    do                                                                \
    {                                                                 \
        type temp = (element);                                        \
        /*! Alternativa com compound literal(C99):*/                  \
        /* Não usada aqui porque alguns editores de texto não */      \
        /* lidam bem com macros desse tipo e geram warnings. */       \
        /*_arraylist_append(arraylist, &(typeof(element)){element})*/ \
        _arraylist_append(arraylist, &temp);                          \
    } while (0)

void _arraylist_append(ArrayList *arrayList, void *element);

// ===============================================================================================================

/**
 * @brief Macro para remoção de um dado na estrutura ArrayList
 *
 *
 * @param arrayList arraylist instanciada
 * @param index indice do elemento
 * @param type tipo da arraylist instanciada  e do elemento
 * @return Elemento removido
 **/
#define arraylist_pop(arraylist, index, type) \
    ((type*)_arraylist_pop(arraylist, index))
void *_arraylist_pop(ArrayList *arrayList, int index);

// ===============================================================================================================

/**
 * @brief Macro para busca de um dado na estrutura ArrayList
 *
 *
 * @param arrayList arraylist instanciada
 * @param index indice do elemento
 * @param type tipo da arraylist instanciada e do elemento
 * @return Elemento buscado
**/
#define arraylist_get(arraylist, index, type) \
    (*(type *)_arraylist_get_element_address(arraylist, index)) // O primeiro * vai desreferenciar o endereço, retornando o valor normal delevoid arraylist_set(ArrayList *arrayList, int index, int element);
void *_arraylist_get_element_address(ArrayList *arrayList, int index);

// ===============================================================================================================

/**
 * @brief Macro para modificação de um dado na estrutura ArrayList
 *
 *
 * @param arrayList arraylist instanciada
 * @param index indice do elemento a ser substituido
 * @param element valor a pelo qual o elemento será trocado
 * @return Elemento buscado
**/
#define arraylist_set(arraylist, index, element, type)                \
    do                                                                \
    {                                                                 \
        type temp = (element);                                        \
        /*! Alternativa com compound literal(C99):*/                  \
        /* Não usada aqui porque alguns editores de texto não */      \
        /* lidam bem com macros desse tipo e geram warnings. */       \
        /*_arraylist_append(arraylist, &(typeof(element)){element})*/ \
        _arraylist_set(arraylist, index, &temp);                      \
    } while (0)
void _arraylist_set(ArrayList *arrayList, int index, void *element);
// ===============================================================================================================

/**
 * @brief Macro para busca do indice deum dado na estrutura ArrayList
 *
 *
 * @param arrayList arraylist instanciada
 * @param element valor do elemento que se deseja saber o indice
 * @return Indice do elemento
**/
#define arraylist_indexOf(arraylist, element, type)                   \
    do                                                                \
    {                                                                 \
        type temp = (element);                                        \
        /*! Alternativa com compound literal(C99):*/                  \
        /* Não usada aqui porque alguns editores de texto não */      \
        /* lidam bem com macros desse tipo e geram warnings. */       \
        /*_arraylist_append(arraylist, &(typeof(element)){element})*/ \
        _arraylist_indexOf(arraylist, &temp)                          \
    } while (0)

int _arraylist_indexOf(ArrayList *arrayList, void* element);


// ===============================================================================================================
/**
 * @brief Macro para busca contagem do número de vezes que um elemento da arraylist aparece
 *
 *
 * @param arrayList arraylist instanciada
 * @param element valor do elemento que se deseja saber a quantidade de vezes
 * @return Número de vezes que o elemento aparece na lista
 **/
#define arraylist_count(arraylist, element)                           \
    do                                                                \
    {                                                                 \
        type temp = (element);                                        \
        /*! Alternativa com compound literal(C99):*/                  \
        /* Não usada aqui porque alguns editores de texto não */      \
        /* lidam bem com macros desse tipo e geram warnings. */       \
        /*_arraylist_append(arraylist, &(typeof(element)){element})*/ \
        _arraylist_count(arraylist, &temp)                            \
    } while (0)
int _arraylist_count(ArrayList *arrayList, void* element);

// ===============================================================================================================
/**
 * @brief Macro para busca limpeza da arraylist
 * retorna a arraylist para as condições iniciais pós-instanciação
 *
 * @param arrayList arraylist instanciada
**/
void arraylist_clear(ArrayList *arrayList);

// ===============================================================================================================
/**
 * @brief Macro para busca liberação da memória alocada para arraylist
 *
 * @param arrayList arraylist instanciada
 **/
void arraylist_free(ArrayList *arrayList);

#endif




// Eai, primeira biblioteca feita em C após uns 3 anos sem mexer nisso
// Seria bom poder pular a matéria na faculdade com isso
// o chatgpt ajudou com sintaxe nas macros e verificando pontos com falta de checagem nos pointers,
// além de me explicar pointers genericos mais a fundo, permitindo usar outros tipos na estrutura
// Tambem com o readme pq tava com preguiça de escrever

// Posso voltar ao java ou ao python depois dessa? Minha stack com java e python é tão mais agradável