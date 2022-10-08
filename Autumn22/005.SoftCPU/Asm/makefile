all: Asm

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

NAME = main
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}.cpp
	${COMPILE_O}

NAME = ui
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}.cpp
	${COMPILE_O}

NAME = asm
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}.cpp
	${COMPILE_O}

NAME = AsmCode
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ..\${NAME}.cpp
	${COMPILE_O}

NAME = fileIO
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}.cpp
	${COMPILE_O}


NAME = ListOfLines
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}\${NAME}.cpp
	${COMPILE_O}

NAME = strAsmLang
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}\${NAME}.cpp
	${COMPILE_O}

NAME = cmdParser
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}\${NAME}.cpp
	${COMPILE_O}


Asm: ${OBJECTS}
	@ g++ $(COMPILE_FLAGS) $^ -o build\Asm

clean:
	@ del build\*.o build\*.exe
