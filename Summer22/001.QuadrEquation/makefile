all: QuadrEquation tests

COMPILE_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE

QuadrEquation: build\main.o build\quadrEquationIO.o build\QuadrEquation.o
	@ g++ $(COMPILE_FLAGS) build\main.o build\quadrEquationIO.o build\QuadrEquation.o -o build\QuadrEquation

build\main.o: main.cpp
	@ g++ $(COMPILE_FLAGS) -c main.cpp
	@ move main.o build > NUL

build\quadrEquationIO.o: quadrEquationIO.cpp
	@ g++ $(COMPILE_FLAGS) -c quadrEquationIO.cpp
	@ move quadrEquationIO.o build > NUL

build\QuadrEquation.o: QuadrEquation.cpp
	@ g++ $(COMPILE_FLAGS) -c QuadrEquation.cpp
	@ move QuadrEquation.o build > NUL


tests: build\testMain.o build\autoTest.o build\tests.o
	@ g++ $(COMPILE_FLAGS) build\testMain.o build\autoTest.o build\tests.o build\QuadrEquation.o -o build\tests
	@ .\build\tests.exe

build\testMain.o: tests\testMain.cpp
	@ g++ $(COMPILE_FLAGS) -c tests\testMain.cpp -I .
	@ move testMain.o build > NUL

build\autoTest.o: tests\autoTest.cpp
	@ g++ $(COMPILE_FLAGS) -c tests\autoTest.cpp -I .
	@ move autoTest.o build > NUL

build\tests.o: tests\tests.cpp
	@ g++ $(COMPILE_FLAGS) -c tests\tests.cpp -I .
	@ move tests.o build > NUL

clean:
	@ del build\*.o build\*.exe
