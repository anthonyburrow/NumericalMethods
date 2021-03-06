CXX = g++
CXXFLAGS =

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
NAME1 = myODEInt
TARGET1 = $(BIN_DIR)/$(NAME1)
_SRC1 = $(NAME1)
_SRC2 = odeint bsstep pzextr mmid
_SRC3 = io
SRC1 = $(_SRC1) $(_SRC2) $(_SRC3)

_OBJ_LIST = $(addsuffix .o, $(SRC1))
OBJ_LIST1 = $(addprefix $(BIN_DIR)/, $(_OBJ_LIST))

$(TARGET1): $(OBJ_LIST1)
	$(CXX) $(CXXFLAGS) $^ -o $@


# Target 2
NAME2 = myLeapfrog
TARGET2 = $(BIN_DIR)/$(NAME2)
SRC2 = $(NAME2) leapfrog io

_OBJ_LIST = $(addsuffix .o, $(SRC2))
OBJ_LIST2 = $(addprefix $(BIN_DIR)/, $(_OBJ_LIST))

$(TARGET2): $(OBJ_LIST2)
	$(CXX) $(CXXFLAGS) $^ -o $@


# Target 3
NAME3 = myVelVerlet
TARGET3 = $(BIN_DIR)/$(NAME3)
SRC3 = $(NAME3) velVerlet io

_OBJ_LIST = $(addsuffix .o, $(SRC3))
OBJ_LIST3 = $(addprefix $(BIN_DIR)/, $(_OBJ_LIST))

$(TARGET3): $(OBJ_LIST3)
	$(CXX) $(CXXFLAGS) $^ -o $@


# Compile all other objects
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(DIR_GUARD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: directories $(TARGET1) $(TARGET2) $(TARGET3)

TESTS = $(TARGET1)

test: directories $(TESTS)

clean:
	$(RM) $(BIN_DIR)/*.o $(TARGET1) $(TARGET2) $(TARGET3)
