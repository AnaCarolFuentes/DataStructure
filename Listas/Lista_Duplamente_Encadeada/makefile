# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Iinclude

# Diretórios
SRCDIR = src
INCDIR = include

# Arquivos de código-fonte
SRCFILES = $(SRCDIR)/gerencia_estoque.c $(INCDIR)/funcoes.c

# Arquivo de saída
TARGET = programa

# Regra padrão
all: $(TARGET)

# Regra para compilar o programa
$(TARGET): $(SRCFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCFILES)

# Regra para limpar arquivos compilados
clean:
	rm -f $(TARGET)
