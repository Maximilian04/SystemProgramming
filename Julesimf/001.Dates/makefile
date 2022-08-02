all: date

date: build\main.o build\date.o build\gregCalendar.o
	gcc build\main.o build\date.o build\gregCalendar.o -o build\date

build\main.o: main.c
	gcc -c main.c
	move main.o build

build\date.o: date.c
	gcc -c date.c
	move date.o build

build\gregCalendar.o: gregCalendar.c
	gcc -c gregCalendar.c
	move gregCalendar.o build

clean:
	del build\*.o
