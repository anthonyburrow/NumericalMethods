CC=mpicc
CXX=mpic++
FC=mpif90
FFLAGS=
FLINKER=mpif90

BIN_DIR = ./bin
SRC_DIR = ./src

# Directories
MAKE_DIRS = $(BIN_DIR)
MKDIR_P = mkdir -p

.PHONY: directories $(MAKE_DIRS)

directories: $(MAKE_DIRS)

$(MAKE_DIRS):
	$(MKDIR_P) $@

# Targets
TARGET1 = vtop1
$(TARGET1): directories $(BIN_DIR)/$(TARGET1).o
	$(FLINKER) $(FFLAGS) -o $(BIN_DIR)/$@ $(BIN_DIR)/$(TARGET1).o


# Recipes
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.f
	$(FC) $(FFLAGS) -c $< -o $@


clean:
	/bin/rm -r $(BIN_DIR)
