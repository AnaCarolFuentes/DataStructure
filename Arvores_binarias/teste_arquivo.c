#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char *buffer;
    int frequency[256] = {0}; // Inicializa todas as frequências como 0
    int fileSize;
    int i = 0;
    
    // Abre o arquivo no modo leitura
    file = fopen("arquivo.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Move o ponteiro do arquivo para o final
    fseek(file, 0, SEEK_END);
    // Obtém o tamanho do arquivo
    fileSize = ftell(file);
    // Volta o ponteiro para o início do arquivo
    rewind(file);

    // Aloca memória suficiente para armazenar todos os caracteres mais o '\0'
    buffer = (char *)malloc((fileSize + 1) * sizeof(char));
    if (buffer == NULL) {
        perror("Erro ao alocar memória");
        fclose(file);
        return 1;
    }

    // Lê cada caractere do arquivo e armazena no buffer
    while (i < fileSize) {
        buffer[i] = fgetc(file);
        frequency[(unsigned char)buffer[i]]++; // Incrementa a frequência do caractere lido
        i++;
    }
    buffer[i] = '\0'; // Adiciona o terminador nulo ao final do buffer

    // Exibe o conteúdo armazenado no buffer
    printf("Conteúdo do arquivo:\n%s\n", buffer);

    // Exibe a frequência de cada caractere
    printf("\nFrequência de cada caractere:\n");
    for (i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            printf("'%c' : %d\n", i, frequency[i]);
        }
    }

    // Libera a memória alocada
    free(buffer);
    // Fecha o arquivo
    fclose(file);

    return 0;
}
