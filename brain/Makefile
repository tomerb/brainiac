# 1. Compile every *.cpp in the folder
# 2. All obj files under obj folder
# 3. static library .a at lib folder
# 4. run 'make dirmake' before calling 'make'


CC = g++
OUT_FILE_NAME = libbrainiac.a

CFLAGS = -O0 -g -Wall -Werror -Wextra -c -fPIC

YAML_CPP_DIR = ../libs/yaml-cpp

SRC_DIR = ./src
INC = -I$(SRC_DIR) -I$(YAML_CPP_DIR)/include

OBJ_DIR=./obj

OUT_DIR=./lib

# Enumerating of every *.cpp as *.o and using that as dependency.
# filter list of .c files in a directory.
# FILES =dump_l.c \
#	kter.c \
#
# $(OUT_FILE_NAME): $(patsubst %.c,$(OBJ_DIR)/%.o,$(wildcard $(FILES)))


# Enumerating of every *.cpp as *.o and using that as dependency
$(OUT_FILE_NAME): $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.cpp))
	ar -r -o $(OUT_DIR)/$@ $^

#Compiling every *.cpp to *.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp dirmake yaml-cpp
	$(CC) -c $(INC) $(CFLAGS) -o $@  $<

dirmake:
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OBJ_DIR)

yaml-cpp:
	@mkdir -p $(YAML_CPP_DIR)/build
	@cd $(YAML_CPP_DIR)/build && cmake .. && make -j4

clean:
	rm -f $(OBJ_DIR)/*.o $(OUT_DIR)/$(OUT_FILE_NAME) Makefile.bak $(YAML_CPP_DIR)/build

rebuild: clean build
