# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -I./include
LDFLAGS = -L./libs -lSDL2 -lSDL2_image -no-pie

# Diretórios
SRC_DIR = ./src
BUILD_DIR = ./build
INCLUDE_DIR = ./include

# Arquivos
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
EXEC_NAME = solar-system

# Alvo principal
all: $(BUILD_DIR)/$(EXEC_NAME)

# Criação do executável
$(BUILD_DIR)/$(EXEC_NAME): $(OBJS) | create_build_dir
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Regra para compilar os objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | create_build_dir
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Criar diretório build
create_build_dir:
	mkdir -p $(BUILD_DIR)

# Limpeza
clean:
	rm -rf $(BUILD_DIR)/*
