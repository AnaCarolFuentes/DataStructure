/*
Ana Carolina Fuentes
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produto 
{
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
    struct produto * proximo;
    struct produto * anterior;
} Produto;

typedef struct Lista {
    Produto * inicio;
    Produto * fim;
    int quantidade;
} Lista;

//Protótipo das funções
int inicializarLista(Lista *);
int imprimirLista(Lista *);
int imprimirProduto(Produto *);
int moverParaInicio(Lista *, int);
int adicionarProdutoInicio(Lista *, Produto *);
int adicionarProdutoFim(Lista *, Produto *);
int adicionarProdutoMeio(Lista *, Produto *, int);
int removerProduto(Lista *, int);
int atualizarQuantidade(Lista *, int, int);
int encontrarCodigo(Lista *, int);
Produto * buscarProduto(Lista *, int);
Produto * novoProduto();
void mensagemListaVazia(char *);
void mensagemValida(char *, int);
void lerDadosProduto(Produto *);
void menuOpcoes(Lista *);


int main()
{
    Lista estoque;
    inicializarLista(&estoque);

    menuOpcoes(&estoque);
}

void menuOpcoes(Lista * estoque)
{
    int opcao = 1;

    //Menu opcoes
    do
    {
        int posicao;
        int retorno;
        int codigo;
        int quantidade;

        printf("\n------GERENCIAMENTO DE ESTOQUE-----\n");
        printf("1 - Adicionar produto no Inicio do Estoque\n");
        printf("2 - Adicionar produto no Fim do Estoque\n");
        printf("3 - Adicionar produto em uma posicao especifica do Estoque\n");
        printf("4 - Remover produto do Estoque\n");
        printf("5 - Atualizar quantidade do produto\n");
        printf("6 - Buscar produto no Estoque\n");
        printf("7 - Imprimir produtos do Estoque\n");
        printf("8 - Mover produto para o Inicio do Estoque\n");
        printf("0 - Sair\n");

        printf("Opcao: ");
        scanf("%d", &opcao);
        if(opcao == 0)
            break;

        switch (opcao)
        {
        case 1:
            retorno = adicionarProdutoInicio(estoque, novoProduto());
            mensagemValida("adicionar", retorno);
            break;

        case 2:
            retorno = adicionarProdutoFim(estoque, novoProduto());
            mensagemValida("adicionar", retorno);
            break;

        case 3:
            printf("Digite a posicao desejada: ");
            scanf("%d", &posicao);
            if(posicao > estoque->quantidade || posicao < 1)
            {
                printf("Posicao invalida!\n");
                break;
            }
            retorno = adicionarProdutoMeio(estoque, novoProduto(), posicao);
            mensagemValida("adicionar", retorno);
            break;
        
        case 4: 
            printf("Digite o codigo do produto que deseja remover: ");
            scanf("%d", &codigo);

            retorno = removerProduto(estoque, codigo);
            mensagemValida("remover", retorno);
            printf("Codigo do produto removido: %d\n", codigo);
            break;

        case 5:
            printf("Digite o codigo do produto que deseja alterar a quantidade: ");
            scanf("%d", &codigo);
            printf("Digite a nova quantidade: ");
            scanf("%d", &quantidade);

            retorno = atualizarQuantidade(estoque, codigo, quantidade);

            if(retorno == 1) 
                mensagemValida("atualizar quantidade do", retorno);
            else if(retorno == 0)
                printf("Codigo do produto nao encontrado!\n");
            break;

        case 6:
            printf("Digite o codigo do produto que deseja buscar: ");
            scanf("%d", &codigo);
            Produto * produto = buscarProduto(estoque, codigo);

            if(produto == NULL)
                printf("Codigo do produto nao encontrado!\n");
            else
                imprimirProduto(produto);
            break;
        case 7:
            imprimirLista(estoque);
            break;
        case 8:
            printf("Digite o codigo do produto que deseja mover para o inicio: ");
            scanf("%d", &codigo);
            retorno = moverParaInicio(estoque, codigo);
            if(retorno == 0) 
                printf("Codigo do produto nao encontrado!\n");
            else
                printf("Sucesso ao mover produto para o inicio do estoque!\n");
            break;
        
        default:
            break;
        }
    } while (opcao != 0);
}

int inicializarLista (Lista * lista)
{
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quantidade = 0;
    return 1;
}

int imprimirLista(Lista * lista)
{
    if(lista->inicio == NULL)
    {
        mensagemListaVazia("imprimir");
        return -1;
    }

    Produto * aux = lista->inicio;
    printf("-----------IMPRIMINDO PRODUTOS DO ESTOQUE--------\n");
    while(aux != NULL)
    {
        printf("-----------------------------\n");
        printf("Codigo: %d\n", aux->codigo);
        printf("Nome: %s\n", aux->nome);
        printf("Quantidade: %d\n", aux->quantidade);
        printf("Preco: R$ %.2f\n", aux->preco);
        printf("-----------------------------\n");
        
        aux = aux->proximo;
    }
    return 1;

}

void mensagemListaVazia(char * mensagem)
{
    printf("Nao foi possivel %s a/na lista, pois ela esta vazia\n", mensagem);
}

Produto * novoProduto ()
{
    Produto * novoProduto = (Produto*) malloc (sizeof(Produto));

    if(novoProduto == NULL)
        return NULL;
    
    novoProduto->proximo = NULL;
    novoProduto->anterior = NULL;

    lerDadosProduto (novoProduto);
    return novoProduto;
}

void lerDadosProduto (Produto * produto)
{
    int codigo, quantidade;
    char nome[50];
    float preco;
    printf("------CADASTRAR NOVO PRODUTO------\n");
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);
    produto->codigo = codigo;
    printf("Digite o nome do produto: ");
    scanf("%s", nome);
    strcpy(produto->nome, nome);

    printf("Digite a quantidade do produto: ");
    scanf("%d", &quantidade);
    produto->quantidade = quantidade;

    printf("Digite o preco do produto: ");
    scanf("%f", &preco);
    produto->preco = preco;

    printf("-------------------------\n");
}

int adicionarProdutoInicio(Lista * lista, Produto * produto)
{
    if(lista->inicio == NULL)
    {
        lista->inicio = produto;
        lista->fim = produto;
    }
    else 
    {
        produto->proximo = lista->inicio;
        lista->inicio->anterior = produto;
        lista->inicio = produto;
    }

    lista->quantidade++;
    return 1;
}

int adicionarProdutoFim(Lista * lista, Produto * produto)
{
    if(lista->inicio == NULL)
    {
        lista->inicio = produto;
        lista->fim = produto;
    }
    else
    {
        lista->fim->proximo = produto;
        produto->anterior = lista->fim;
        lista->fim = produto;
    }
    lista->quantidade++;
    return 1;
}

int adicionarProdutoMeio(Lista * lista, Produto * produto, int posicao)
{
    if(lista->inicio == NULL)
    {
        lista->inicio = produto;
        lista->fim = produto;
    }
    else if (posicao == 1)
    {
        produto->proximo = lista->inicio;
        lista->inicio->anterior = produto;
        lista->inicio = produto;
    }
    else
    {
        int i = 0;
        Produto * aux = lista->inicio;

        for(i = 1; i < posicao - 1 && aux->proximo != NULL; i++)
        {
            aux = aux->proximo;
        }

        produto->proximo = aux->proximo;
        produto->anterior = aux;

        if(aux->proximo != NULL)
            aux->proximo->anterior = produto;
        else  
            lista->fim = produto;
        
        aux->proximo = produto;
    }
    lista->quantidade++;
    return 1;
}

void mensagemValida(char * mensagem, int retorno)
{
    if(retorno == 1)
        printf("Secesso ao %s produto no estoque!\n", mensagem);
    else
        printf("Falha ao %s produto no estoque\n", mensagem);
}

int atualizarQuantidade (Lista * lista, int codigo, int novaQuantidade)
{
    if(lista->inicio == NULL)
    {
        mensagemListaVazia("atualizar quantidade");
        return -1;
    }

    Produto * aux = lista->inicio;
    int encontrou = 0;

    while(aux != NULL)
    {
        if(aux->codigo == codigo)
        {
            aux->quantidade = novaQuantidade;
            encontrou = 1;
            break;
        }
        aux = aux->proximo;
    }

    return (encontrou == 1) ? 1 : 0;
}

//pergunta: posso considerar que nunca vai existir 2 produtos com o mesmo codigo? pq ele seria a key da minha table em banco de dados?
int removerProduto(Lista * lista, int codigo)
{
    if(lista->inicio == NULL)
    {
        mensagemListaVazia("remover produto");
        return -1;
    }

    Produto * aux = lista->inicio;

    while(aux != NULL)
    {
        if(aux->codigo == codigo)
        {
            if(aux == lista->inicio)
            {
                lista->inicio = aux->proximo;
                
                if(lista->inicio != NULL)
                    lista->inicio->anterior = NULL;
                free(aux);
                aux = lista->inicio;
            }
            else if(aux == lista->fim)
            {
                lista->fim = aux->anterior;
                aux->anterior->proximo = NULL;
                free(aux);
                aux = NULL;
            }
            else
            {
                Produto * aux2;
                aux->anterior->proximo = aux->proximo;
                aux->proximo->anterior = aux->anterior;
                aux2 = aux->proximo;
                free(aux);
                aux = aux2;
            }
            return 1;
        } 
        else
        {
            aux = aux->proximo;
        }
    }

    return 0;
}

Produto * buscarProduto(Lista* lista, int codigo)
{
    if(lista->inicio != NULL)
    {
        Produto * aux = lista->inicio;

        while(aux != NULL)
        {
            if(aux->codigo == codigo)
                return aux;
            aux = aux->proximo;
        }
    }

    return NULL;
}

int imprimirProduto(Produto * produto)
{
    if(produto == NULL)
        return 0;

    printf("----IMPRIMINDO PRODUTO------\n");
    printf("-----------------------------\n");
        printf("Codigo: %d\n", produto->codigo);
        printf("Nome: %s\n", produto->nome);
        printf("Quantidade: %d\n", produto->quantidade);
        printf("Preco: R$ %.2f\n", produto->preco);
        printf("-----------------------------\n");
        return 1;
}

int moverParaInicio(Lista * lista, int codigo)
{
    if(lista->inicio != NULL)
    {
        Produto * aux = lista->inicio;

        while(aux != NULL)
        {
            if(aux->codigo == codigo)
            {
                if(aux == lista->fim)
                {
                    aux->anterior->proximo = NULL;
                    lista->fim = aux->anterior;
                    aux->anterior = NULL;
                    aux->proximo = lista->inicio;
                    lista->inicio = aux;
                }
                else
                {
                    aux->anterior->proximo = aux->proximo;
                    aux->proximo->anterior = aux->anterior;
                    aux->proximo = lista->inicio;
                    aux->anterior = NULL;
                }
                return 1;
            }
            aux = aux->proximo;
        }
    }

    return 0;
}

int encontrarCodigo(Lista * lista, int codigo)
{
    if(lista->inicio != NULL)
    {
        Produto * aux = lista->inicio;
        while(aux != NULL)
        {
            if(aux->codigo == codigo)
                return 1;
            aux = aux->proximo;
        }
    }

    return 0;
}

//Perguntas 
/*
Onde é melhor para eu rodar a verificacão se o código já existe no estoque para que não tenha mais produtos com um mesmo código?
*/