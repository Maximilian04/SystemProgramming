all: date tests

date: build\main.o build\date.o build\gregCalendar.o
	@ gcc build\main.o build\date.o build\gregCalendar.o -o build\date

build\main.o: main.c
	@ gcc -c main.c
	@ move main.o build > build/trashlog.txt

build\date.o: date.c
	@ gcc -c date.c
	@ move date.o build > build/trashlog.txt

build\gregCalendar.o: gregCalendar.c
	@ gcc -c gregCalendar.c
	@ move gregCalendar.o build > build/trashlog.txt

tests: build\tests.o date
	@ gcc build\tests.o build\date.o build\gregCalendar.o -o build\tests
	@ .\build\tests.exe

build\tests.o: tests.c
	@ gcc -c tests.c
	@ move tests.o build > build/trashlog.txt

clean:
	@ del build\*.o
