# 1. Compile every *.cpp in the folder
# 2. All obj files under obj folder
# 3. static library .a at lib folder
# 4. run 'make dirmake' before calling 'make'


CC = g++
OUT_FILE_NAME = brainiac$(shell python3-config --extension-suffix)

CFLAGS = -Wall -Werror -Wextra -fPIC

LDFLAGS = -L../brain/lib -lbrainiac

INC = -I../libs/pybind11/include -I/usr/include/python3.11 -I../brain/src

OBJ_DIR=.

OUT_DIR=.

PYBIND_DIR=../libs/pybind11/build

# Enumerating of every *.cpp as *.o and using that as dependency.
# filter list of .c files in a directory.
# FILES =dump_l.c \
#	kter.c \
#
# $(OUT_FILE_NAME): $(patsubst %.c,$(OBJ_DIR)/%.o,$(wildcard $(FILES)))


# Enumerating of every *.cpp as *.o and using that as dependency
$(OUT_FILE_NAME): $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(wildcard *.cpp))
	$(CC) $^ -shared -Wl,-soname,$(OUT_FILE_NAME) $(LDFLAGS) -o $@

#Compiling every *.cpp to *.o
$(OBJ_DIR)/%.o: %.cpp dirmake pybind
	$(CC) -c $(INC) $(CFLAGS) -o $@  $<

dirmake:
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OBJ_DIR)

pybind:
	@mkdir -p $(PYBIND_DIR)
	@cd $(PYBIND_DIR) && cmake .. && make -j4

clean:
	rm -f $(OBJ_DIR)/*.o $(OUT_DIR)/$(OUT_FILE_NAME) Makefile.bak

rebuild: clean build
