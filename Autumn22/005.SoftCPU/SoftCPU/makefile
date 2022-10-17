all: SoftCPU

COMPILE_DEFAULT_FLAGS = -I . -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_EJUDGE_CLIENT_SIDE
COMPILE_FLAGS = $(COMPILE_DEFAULT_FLAGS) -D_DEBUG
#COMPILE_FLAGS = $(COMPILE_DEFAULT_FLAGS) -DNDEBUG

COMPILE_O = @ g++ $(COMPILE_FLAGS) -c $^ -o $@

define ADD_SOURCE
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}.cpp
	${COMPILE_O}
endef

define ADD_LIBSOURCE
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}\${NAME}.cpp
	${COMPILE_O}
endef

STACKLIB_PATH = "..\..\004.Stack"
LINK_STACKLIB = -L$(STACKLIB_PATH) -lStackLib
# include ..\..\004.Stack\makefile-StackLib
# OBJECTS := ${OBJECTS} build\StackLib.a

NAME = main
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}.cpp
	${COMPILE_O}

NAME = ui
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}.cpp
	${COMPILE_O}

NAME = AsmCode
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ..\${NAME}.cpp
	${COMPILE_O}

NAME = cpu
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}.cpp
	${COMPILE_O}

NAME = loggerCPU
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: logger\${NAME}.cpp
	${COMPILE_O}

NAME = Regs
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}.cpp
	${COMPILE_O}

NAME = loggerRegs
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: logger\${NAME}.cpp
	${COMPILE_O}

#build\Stack.o: stack\Stack.cpp
#	@ g++ $(COMPILE_FLAGS) -c stack\Stack.cpp
#	@ move Stack.o build > NUL

NAME = cmdParser
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}\${NAME}.cpp
	${COMPILE_O}


STACKLIB_O := ${STACKLIB_O} StackLibO\Stack.o
STACKLIB_O := ${STACKLIB_O} StackLibO\logger.o
STACKLIB_O := ${STACKLIB_O} StackLibO\loggerStack.o
STACKLIB_O := ${STACKLIB_O} StackLibO\strFParser.o
STACKLIB_O := ${STACKLIB_O} StackLibO\DebugInfo.o
STACKLIB_O := ${STACKLIB_O} StackLibO\hash.o

SoftCPU: ${OBJECTS}
#	@ g++ ${LINK_STACKLIB} $(COMPILE_FLAGS) $^ -o build\SoftCPU
#	@ g++ -L. -lStackLib $(COMPILE_FLAGS) $^ -o build\SoftCPU
	@ g++ $(COMPILE_FLAGS) $^ -o build\SoftCPU ${STACKLIB_O}

clean:
	@ del build\*.o build\*.exe
