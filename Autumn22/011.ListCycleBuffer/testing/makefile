all: Testing

COMPILE_DEFAULT_FLAGS = -I. -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_EJUDGE_CLIENT_SIDE
COMPILE_FLAGS = $(COMPILE_DEFAULT_FLAGS) -D_DEBUG
#COMPILE_FLAGS = $(COMPILE_DEFAULT_FLAGS) -DNDEBUG

COMPILE_O = @ g++ $(COMPILE_FLAGS) -c $^ -o $@

LIBLIST_PATH := .\..\build
LIBLIST_HEADERS := $(LIBLIST_PATH)\..\headers
LIBLIST_NAME := List
LIBLIST_LINK := -L$(LIBLIST_PATH) -l$(LIBLIST_NAME)
LIBLIST_INCLUDE := -I$(LIBLIST_HEADERS)

LIBCMDPARSER_PATH := .\..\..\009.cmdParser\build
LIBCMDPARSER_HEADERS := $(LIBCMDPARSER_PATH)\..\headers
LIBCMDPARSER_NAME := cmdParser
LIBCMDPARSER_LINK := -L$(LIBCMDPARSER_PATH) -l$(LIBCMDPARSER_NAME)
LIBCMDPARSER_INCLUDE := -I$(LIBCMDPARSER_HEADERS)

LIBTESTINGSYSTEM_PATH := .\..\..\008.TestingSystem\build
LIBTESTINGSYSTEM_HEADERS := $(LIBTESTINGSYSTEM_PATH)\..\headers
LIBTESTINGSYSTEM_NAME := testingSystem
LIBTESTINGSYSTEM_LINK := -L$(LIBTESTINGSYSTEM_PATH) -l$(LIBTESTINGSYSTEM_NAME)
LIBTESTINGSYSTEM_INCLUDE := -I$(LIBTESTINGSYSTEM_HEADERS)

LIBLOGGER_PATH := .\..\..\010.logger\build
LIBLOGGER_HEADERS := $(LIBLOGGER_PATH)\..\headers
LIBLOGGER_NAME := logger
LIBLOGGER_LINK := -L$(LIBLOGGER_PATH) -l$(LIBLOGGER_NAME)
LIBLOGGER_INCLUDE := -I$(LIBLOGGER_HEADERS)

LIBGRAPHVIZBUF_PATH := .\..\..\013.graphvizBuf\build
LIBGRAPHVIZBUF_HEADERS := $(LIBGRAPHVIZBUF_PATH)\..\headers
LIBGRAPHVIZBUF_NAME := graphvizBuf
LIBGRAPHVIZBUF_LINK := -L$(LIBGRAPHVIZBUF_PATH) -l$(LIBGRAPHVIZBUF_NAME)
LIBGRAPHVIZBUF_INCLUDE := -I$(LIBGRAPHVIZBUF_HEADERS)

COMPILE_FLAGS += $(LIBLIST_INCLUDE) $(LIBTESTINGSYSTEM_INCLUDE) $(LIBCMDPARSER_INCLUDE) $(LIBLOGGER_INCLUDE) $(LIBGRAPHVIZBUF_INCLUDE)
LINK_FLAGS     = $(LIBLIST_LINK)    $(LIBTESTINGSYSTEM_LINK)    $(LIBCMDPARSER_LINK)    $(LIBLOGGER_LINK)    $(LIBGRAPHVIZBUF_LINK)


NAME = main
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}.cpp
	${COMPILE_O}

Testing: ${OBJECTS} ${LIBLIST_PATH}\$(LIBLIST_NAME).lib
	@ g++ $(COMPILE_FLAGS) $^ -o build\testing $(LINK_FLAGS)
#	echo relink

clean:
	@ del build\*.o build\*.exe
