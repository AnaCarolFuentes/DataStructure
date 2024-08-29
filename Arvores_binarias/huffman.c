#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char byte;

//define structs
typedef struct nodeTree
{
    byte caracter;
    int frequency;
    struct nodeTree * left;
    struct nodeTree * right;
} NodeTree;

typedef struct nodeList
{
    NodeTree * node;
    struct  nodeList * next;
} NodeList;

typedef struct list
{
    NodeList * head;
    int elements;
} List;

NodeList * newNodeList (NodeTree * nodeTree);
NodeTree * newNodeTree (byte c, int frequency, NodeTree * left, NodeTree * right);
void insertList (List * list, NodeList * newNode);
int printList (List * list);
void inicializeList (List * list);
NodeTree * popMinList (List * list);
NodeTree * buildHuffmanTree (List * list, byte * c, int * frequency);
void printHuffmanTree (NodeTree * root); //Fazer essa função
//void getHuffmanCode(NodeTree * root);
void freeHuffmanTree (NodeTree * root);
void buildFrequencyandBufferArray (char * file_name, int * frequency, byte ** buffer);
void printFrequencyArray (int * frequency);
void getBitHuffmanCode(FILE * file_zip, NodeTree * root, unsigned int path, int depth);
void createFileZip (char * file_name, NodeTree * root, unsigned int path, int depth);
void mensagemErro(char * mensagem);

int main()
{
    /* Lista de prioridade funcionando
    List list;
    

    inicializeList(&list);

    NodeList * newNode = newNodeList(newNodeTree('a', 20, NULL, NULL));
    insertList(&list, newNode);
    NodeList * newNode1 = newNodeList(newNodeTree('b', 15, NULL, NULL));
    insertList(&list, newNode1);
    NodeList * newNode2 = newNodeList(newNodeTree('a', 17, NULL, NULL));
    insertList(&list, newNode2);
    printList(&list);
    */

    byte * buffer = NULL;
    int frequency[256] = {0};

    buildFrequencyandBufferArray("arquivo.txt", frequency, &buffer);

   // printf("Conteudo do arquivo: \n%s\n", buffer);

    // Exibe a frequência de cada caractere
    //printFrequencyArray (frequency);
    
    List list;
    NodeTree * root = buildHuffmanTree(&list, buffer, frequency);

    printHuffmanTree(root);
    
    //freeHuffmanTree (root);

    createFileZip("huffman.zip", root, 0, 0);
    //getBitHuffmanCode("huffman.zip", root, 0, 0);
    
}

void inicializeList (List * list)
{
    list->head = NULL;
    list->elements = 0;
}
NodeList * newNodeList (NodeTree * nodeTree)
{
    NodeList * newNode = (NodeList*) malloc (sizeof(NodeList));
    if(newNode == NULL) return NULL;

    newNode->node = nodeTree;
    newNode->next = NULL;

    return newNode;
}

NodeTree * newNodeTree (byte c, int frequency, NodeTree * left, NodeTree * right)
{
    NodeTree * newNode = (NodeTree*) malloc (sizeof(NodeTree));
    if(newNode == NULL) return NULL;

    newNode->caracter = c;
    newNode->frequency = frequency;
    newNode->left = left;
    newNode->right = right;

    return newNode;
}

void insertList (List * list, NodeList * newNode)
{
    if(list->head == NULL) 
        list->head = newNode;

    else if(list->head->node->frequency > newNode->node->frequency)
    {
        newNode->next = list->head;
        list->head = newNode;
    } 
    else
    {
        NodeList * aux = list->head;
        NodeList * aux2 = list->head->next;
        //Find the right position
        while(aux2 != NULL && aux2->node->frequency <= newNode->node->frequency)
        {
            aux = aux2;
            aux2 = aux2->next;
        }
        
        aux->next = newNode;
        newNode->next = aux2;
    }

    list->elements++;
}

int printList (List * list)
{
    if(list->head == NULL)
        return 0;
    
    NodeList * aux = list->head;

    printf("------List------\n");
    while(aux != NULL)
    {
        printf("Frequency: %d\n", aux->node->frequency);
        printf("Byte: %c\n", aux->node->caracter);
        aux = aux->next;
    }
}

NodeTree * popMinList (List * list)
{
    if(list->head == NULL)
        return NULL;
    
    NodeList * auxList = list->head;

    NodeTree * auxTree = auxList->node;

    list->head = auxList->next;
    free(auxList);
    auxList = NULL;
    list->elements--;

    //retorno o nó da árvore que eu apaguei
    return auxTree;
}

NodeTree * buildHuffmanTree (List * list, byte * c, int * frequency)
{
    inicializeList(list);

    for(int i = 0; i < 256; i++)
    {   
        if(frequency[i] > 0)
            insertList(list, newNodeList(newNodeTree(i, frequency[i], NULL, NULL)));
    }

    while(list->elements > 1)
    {
        NodeTree * left = popMinList(list);
        NodeTree * right = popMinList(list);

        NodeTree * newNode = newNodeTree('$', left->frequency + right->frequency, left, right);

        insertList(list, newNodeList(newNode));
    }
    return popMinList(list);
}

//Pre order 
//Function created to test
void printHuffmanTree(NodeTree * root)
{
	if(root == NULL)
		return;

	if(root->frequency){
		printf("%d\n", root->frequency);
		printf("%c\n", root->caracter);
        printf("---------\n");
	}

	printHuffmanTree(root->left);
	printHuffmanTree(root->right);
}


void freeHuffmanTree (NodeTree * root)
{
    if(root != NULL)   
    {
        freeHuffmanTree(root->left);
        freeHuffmanTree(root->right);
        free(root);
    }   
}

void buildFrequencyandBufferArray (char * file_name, int frequency[256], byte ** buffer)
{
    FILE * file;
    int fileSize;
    int i = 0;

    // Abre o arquivo no modo leitura
    file = fopen(file_name, "r");
    if (file == NULL) 
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Move o ponteiro do arquivo para o final
    fseek(file, 0, SEEK_END);
    // Obtém o tamanho do arquivo
    fileSize = ftell(file);
    // Volta o ponteiro para o início do arquivo
    rewind(file);

    *buffer = (byte*) malloc(fileSize * sizeof(byte));

    if (*buffer == NULL) 
    {
        perror("Erro ao alocar memória");
        fclose(file);
        return;
    }

    while (i < fileSize) {
        //a função fgetc() retorna o caractere que é lido como um número inteiro
        (*buffer)[i] = fgetc(file);
        frequency[(unsigned char)(*buffer)[i]]++; // Incrementa a frequência do caractere lido
        i++;
    }

    fclose(file);
}

void printFrequencyArray (int * frequency)
{
    printf("\nFrequencia dos caracteres:\n");
        for (int i = 0; i < 256; i++) {
            if (frequency[i] > 0) {
                printf("'%c': %d vez(es)\n", i, frequency[i]);
            }
        }
}


// Função recursiva para percorrer a árvore binária
void getBitHuffmanCode(FILE * file_zip, NodeTree * root, unsigned int path, int depth)
{
    // Se o nó atual é NULL, retorne
    if (root == NULL) {
        return;
    }

    // Se é uma folha, imprima o caminho até aqui
    if (root->left == NULL && root->right == NULL) 
    {
        fprintf(file_zip, "Folha %c: ", root->caracter);
        for (int i = depth - 1; i >= 0; i--) 
        {
            //path >> i: Desloca o valor path para a direita por i posições, trazendo o bit de interesse para a posição menos significativa.
            //& 1: Aplica uma máscara para extrair apenas o bit menos significativo, que é o bit de interesse.
            fprintf(file_zip, "%d", (path >> i) & 1);
        }
        fprintf(file_zip, "\n");
        //perguntar como eu posso resolver o problema de ler somente 1 caracter
        return;
    }

    // Recursão para a esquerda com bit 0
    // <<-> operador de deslocamento para a esquerda (bitwise left shift)
    getBitHuffmanCode(file_zip, root->left, path << 1, depth + 1);

    // Recursão para a direita com bit 1
    getBitHuffmanCode(file_zip, root->right, (path << 1) | 1, depth + 1);
}

void mensagemErro(char * mensagem)
{
    printf("Erro ao %s arquivo\n", mensagem);
}

void createFileZip (char * file_name, NodeTree * root, unsigned int path, int depth)
{
    FILE * zip;
    //strcat(file_name, ".zip");
    zip = fopen(file_name, "w");

    if (zip == NULL) 
    {
        mensagemErro("criar");
        return;
    }

    getBitHuffmanCode(zip, root, path, depth);
    
    //fclose(zip);
}