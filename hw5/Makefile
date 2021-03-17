CXX = g++
CXXFLAGS =

CC = gcc
CCFLAGS =

BIN_DIR = ./bin
SRC_DIR = ./src

# Create directories required
MAKE_DIRS = ./bin ./output ./doc/figs
MKDIR_P = mkdir -p

.PHONY: directories $(MAKE_DIRS)

directories: $(MAKE_DIRS)

$(MAKE_DIRS):
	$(MKDIR_P) $@


# Target 1
NAME1 = myFTCS
TARGET1 = $(BIN_DIR)/$(NAME1)
_SRC1 = $(NAME1)
_SRC2 = io ftcs
SRC1 = $(_SRC1) $(_SRC2)

_OBJ_LIST = $(addsuffix .o, $(SRC1))
OBJ_LIST1 = $(addprefix $(BIN_DIR)/, $(_OBJ_LIST))

$(TARGET1): $(OBJ_LIST1)
	$(CXX) $(CXXFLAGS) $^ -o $@


# Target 2
NAME2 = myCN
TARGET2 = $(BIN_DIR)/$(NAME2)
_SRC1 = $(NAME2)
_SRC2 = io crankNicholson
SRC2 = $(_SRC1) $(_SRC2)

_OBJ_LIST = $(addsuffix .o, $(SRC2))
OBJ_LIST2 = $(addprefix $(BIN_DIR)/, $(_OBJ_LIST))

$(TARGET2): $(OBJ_LIST2)
	$(CXX) $(CXXFLAGS) $^ -o $@


# Compile all other objects
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(DIR_GUARD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $(CCFLAGS) -c $< -o $@

all: directories $(TARGET1) $(TARGET2)

TESTS = $(TARGET2)

test: directories $(TESTS)

clean:
	$(RM) $(BIN_DIR)/*.o $(TARGET1) $(TARGET2)
