# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = $(wildcard *.c)   # Encontra todos os arquivos .c no diretório atual
EXEC = $(SRC:.c=.exe)    # Define os arquivos .exe correspondentes aos arquivos .c

# Regras
all: $(EXEC)  # Alvo padrão que vai gerar os arquivos .exe

# Como gerar os arquivos .exe diretamente
%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Limpar arquivos gerados
clean:
	rm -f $(EXEC)


