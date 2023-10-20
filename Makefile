# Diretórios
SRC_DIR = src
INC_DIR = inc
OUT_DIR = out

# Compilador e opções
CC = gcc
CFLAGS = -Wall -I$(INC_DIR)

# Lista de fontes e objetos
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SOURCES))

# Nome do executável
EXECUTABLE = $(OUT_DIR)/main

# Nome do arquivo ZIP
ZIP_FILE = projeto.zip

# Lista de arquivos a serem incluídos no arquivo ZIP, incluindo o próprio makefile
ZIP_FILES := $(SOURCES) $(wildcard $(INC_DIR)/*.h) Makefile

# Regra de compilação
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

# Regra de linkagem
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Regra para criar diretórios, se necessário
$(shell mkdir -p $(OUT_DIR))

# Comando para limpar arquivos temporários
clean:
	rm -rf $(OUT_DIR) $(EXECUTABLE) $(ZIP_FILE)

# Regra para executar o programa
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Regra para criar o arquivo ZIP
zip:
	zip $(ZIP_FILE) $(ZIP_FILES)

# Regra para compilar o programa (make all)
all: $(EXECUTABLE) 
