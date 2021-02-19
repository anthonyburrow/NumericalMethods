CXX = g++

BIN_DIR = ./bin
SRC_DIR = ./src

NAME = main
TARGET = $(BIN_DIR)/$(NAME)

SRC = $(NAME) otherdependency1 otherdependency2
SRC_LIST = $(addprefix $(SRC_DIR)/, $(SRC))

OBJ = $(addsuffix .o, $(SRC))
OBJ_LIST = $(addprefix $(BIN_DIR)/, $(OBJ))

# Create executable from objects
$(TARGET): $(OBJ_LIST)
	$(CXX) $(OBJ_LIST) -o $(TARGET)

# Because "main" cpp does not have a header file
$(TARGET).o: $(SRC_DIR)/$(NAME).cpp
	mkdir -p $(@D)
	$(CXX) -c $(SRC_DIR)/$(NAME).cpp -o $(TARGET).o

# Compile all other objects objects
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(CXX) -c $< -o $@

clean:
	$(RM) $(BIN_DIR)/*.o $(TARGET)
