#OBJS specifies which files to compile as part of the project
OBJS = ./src/*.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
LUA_INCLUDE_PATH = "-IC:/Program Files (x86)/Lua/5.1/include"

INCLUDE_PATHS = -IE:/SDL2/include/SDL2  $(LUA_INCLUDE_PATH)

#LIBRARY_PATHS specifies the additional library paths we'll need
LUA_LIB_PATH = "C:\Program Files (x86)\Lua\5.1\lib"
LIBRARY_PATHS = -LE:\SDL2\lib -L$(LUA_LIB_PATH)

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = 1

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)