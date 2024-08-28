/*Ana Carolina Fuentes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    struct node * proximo;
    int dado;
} Node;

typedef struct 
{
   Node * fim;
   Node * inicio;
   int tam;
} Lista;

//Protótipo das funções 
int insereNoInicio (Lista *, int);
int insereNoFim (Lista *, int);
int inicializaLista (Lista *);
Lista * concatena (Lista *, Lista *);
int imprimeLista(Lista *);
Lista * separaPosicao (Lista *, int);
void mensagemListaVazia (char []);
void mensagemSepararLista (char []);

int main()
{

    Lista l1;
    int resultado;

    //inicializa uma lista criada
    inicializaLista(&l1);

    //insere elementos no início da lista criada
    insereNoInicio(&l1, 1);
    insereNoInicio(&l1, 2);
    insereNoInicio(&l1, 3);
    insereNoInicio(&l1, 4);
    insereNoInicio(&l1, 5);
    insereNoInicio(&l1, 6);

    //insere elementos no fim da lista criada
    insereNoFim(&l1, 7);
    insereNoFim(&l1, 9);
    insereNoFim(&l1, 10);

    //imprime a lista criada
    printf("\n----------Imprimindo Lista1------------\n");
    imprimeLista(&l1);
    printf("\n---------------------------------------\n");


    //cria outra lista para guardar o endereço recebido da função separa()
    //A funçao separa vai retornar um endereço para um subconjunto da lista 1
    Lista * novaLista = separa(&l1, 5);

    //imprime a lista 1 depois de ser separada
    printf("\n----------Imprimindo Lista1------------\n");
    imprimeLista(&l1);
    printf("\n---------------------------------------\n");

    printf("\n----------Imprimindo subconjunto de Lista 1------------\n");
    imprimeLista(novaLista);
    printf("\n---------------------------------------\n");
    
}

//Insere no inicio da lista
int insereNoInicio (Lista * lista, int dado)
{
    Node * novo = (Node*) malloc (sizeof(Node));
    
    if(novo == NULL)
        return 0;
    
    novo->dado = dado;

    if(lista->inicio == NULL)
    {
        lista->inicio = novo;
        lista->fim = novo;
        novo->proximo = NULL;
        lista->tam++;
    }
    else
    {
        novo->proximo = lista->inicio;
        lista->inicio = novo;
        lista->tam++;
    }

    return 1;
}

//Insere no fim da lista
int insereNoFim (Lista * lista, int dado)
{
    Node * novo = (Node*) malloc (sizeof(Node));
    
    if(novo == NULL)
        return 0;
    
    novo->dado = dado;

    if(lista->inicio == NULL)
    {
        lista->inicio = novo;
        lista->fim = novo;
        novo->proximo = NULL;
        lista->tam++;
    }
    else
    {
        lista->fim->proximo = novo;
        lista->fim = novo;
        novo->proximo = NULL;
        lista->tam++;
    }
    
    return 1;
}

//Inicializa a lista
int inicializaLista (Lista * lista)
{
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
    return 1;
}

//Concatena duas listas
Lista * concatena (Lista * list1, Lista * list2)
{
    if(list1->inicio == NULL && list2->inicio == NULL)
    {
        mensagemListaVazia("concatenar");
        return NULL;
    }

    else if(list1->inicio == NULL)
        return list2;


    else if(list2->inicio == NULL)
        return list1;

    

    list1->fim->proximo = list2->inicio;
    list1->fim = list2->fim;
        return list1;
}

//Separa duas listas pela posicao
Lista * separaPosicao (Lista * list, int l)
{
    int i;

    if(l < 2 || l >= list->tam)
    {
        mensagemSepararLista("separar");
        return NULL;
    }

    Lista * novaLista = (Lista*) malloc (sizeof(Lista));

    if(novaLista == NULL)
        return NULL;
    
    inicializaLista(novaLista);

    Node * aux = list->inicio;

    for(i = 1; i < l; i++)
    {
        aux = aux->proximo;
    }

    novaLista->inicio = aux->proximo;
    novaLista->fim = list->fim;
    int auxTam = list->tam;
    list->fim = aux;
    list->fim->proximo = NULL;
    novaLista->tam = list->tam - l;
    list->tam = l;
    return novaLista;

}

//Imprime a lista
int imprimeLista(Lista * list)
{
    int cont = 1;
    if(list->inicio == NULL)
    {
        mensagemListaVazia("imprimir");
        return 0;
    }
    
    Node * aux = list->inicio;

    while(aux != NULL)
    {
        printf("Dado %d : %d\n", cont++, aux->dado);
        aux = aux->proximo;
    }
    return 1;
}

void mensagemListaVazia (char mensagem[])
{
    printf("Nao foi possivel %s na lista, pois a lista esta vazia\n", mensagem);
}

void mensagemSepararLista (char mensagem[])
{
    printf("Nao foi possivel %s a lista\n", mensagem);
}






