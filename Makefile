C_PATH := c_file
H_PATH := h_file

#c_file/clinet.c c_file/server.c
C_FILE_WITH_PATH := $(foreach dir, $(C_PATH), $(wildcard $(dir)/*.c))
H_FILE_WITH_PATH := $(foreach dir, $(H_PATH), $(wildcard $(dir)/*.h))

#clinet.c server.c
C_FILE := $(notdir $(C_FILE_WITH_PATH))
H_FILE := $(notdir $(H_FILE_WITH_PATH)) 

#obj/clinet.o obj/server.o
C_OBJ_WITH_PATH := $(patsubst %.c, obj/%.o, $(C_FILE))

#clinet.o server.o
C_OBJ := $(notdir $(C_OBJ_WITH_PATH))

VPATH := $(C_PATH):$(H_PATH)

#out/clinet out/server
OUT_FILE_WITH_PATH := $(patsubst %.c, out/% ,$(C_FILE))

all:$(OUT_FILE_WITH_PATH)

$(OUT_FILE_WITH_PATH) : out/% : obj/%.o
	gcc -Wall  -g $^ -o $@

#gcc -Wall -c c_file/clinet.c -o obj/clinet.o
$(C_OBJ_WITH_PATH) : obj/%.o : %.c
	gcc -Wall -g -c $^ -I $(H_PATH) -o $@

# $(C_OBJ_WITH_PATH) : $(C_FILE_WITH_PATH)
# 	gcc -Wall -c $< -I $(H_PATH) -o $@

.PHONY:clear

clear:
	rm $(C_OBJ_WITH_PATH) $(OUT_FILE_WITH_PATH)

print:
	@echo C_PATH = $(C_PATH)
	@echo C_FILE_WITH_PATH = $(C_FILE_WITH_PATH)
	@echo C_FILE = $(C_FILE)
	@echo C_OBJ_WITH_PATH = $(C_OBJ_WITH_PATH)
	@echo C_OBJ = $(C_OBJ) 
	@echo OUT_FILE_WITH_PATH = $(OUT_FILE_WITH_PATH)
	@echo TARGET = $(TARGET)