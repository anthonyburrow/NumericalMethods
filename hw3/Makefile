CXX = g++
CXXFLAGS =

BIN_DIR = ./bin
SRC_DIR = ./src

DIR_GUARD = mkdir -p $(@D)


# Target 1
NAME1 = myEuler
TARGET1 = $(BIN_DIR)/$(NAME1)
SRC1 = $(NAME1) euler io

_OBJ_LIST = $(addsuffix .o, $(SRC1))
OBJ_LIST1 = $(addprefix $(BIN_DIR)/, $(_OBJ_LIST))

$(TARGET1): $(OBJ_LIST1)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TARGET1).o: $(SRC_DIR)/$(NAME1).cpp
	$(DIR_GUARD)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Target 2
NAME2 = myEulerPC
TARGET2 = $(BIN_DIR)/$(NAME2)
SRC2 = $(NAME2) euler io

_OBJ_LIST = $(addsuffix .o, $(SRC2))
OBJ_LIST2 = $(addprefix $(BIN_DIR)/, $(_OBJ_LIST))

$(TARGET2): $(OBJ_LIST2)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TARGET2).o: $(SRC_DIR)/$(NAME2).cpp
	$(DIR_GUARD)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Compile all other objects
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(TARGET1) $(TARGET2)

clean:
	$(RM) $(BIN_DIR)/*.o $(TARGET1) $(TARGET2)
