 #export $BIN_PATH to your PATH variable: export PATH=${PATH}:~/bin
 #define ARG when calling a rule. Ex) make ARG=echo ; make fclean ARG=export...
 #cleana and fcleana will clean all objects and executables

 ARG = echo
 SRC = ms_$(ARG).c
 OBJ = ms_$(ARG).o
 BIN = ms_$(ARG)

 SRC_ALL = $(wildcard *.c)
 OBJ_ALL = $(SRC_ALL:%.c=%.o)
 BIN_ALL = $(SRC_ALL:%.c=%)
 
 BIN_PATH = ~/bin
 FLAGS = -Werror -Wextra -Wall

 all: $(BIN)

$(BIN): $(OBJ)
	gcc -o $@ $^ -L. -lft
	cp $(BIN) $(BIN_PATH)

%.o: %.c
	gcc -c -g $(FLAGS) $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(BIN)
	rm -f $(BIN_PATH)/$(BIN)

cleana:
	rm -f $(OBJ_ALL)

fcleana: cleana
	rm -f $(BIN_ALL)
	rm -f $(BIN_PATH)/$(BIN_ALL)

