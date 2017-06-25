CC = clang
CFLAGS = -std=c11 -ggdb
OBJECTS = fls.o main.o

fls: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o fls

fls.o: fls.c fls.h
	${CC} ${CFLAGS} -c fls.c

main.o: main.c fls.h
	${CC} ${CFLAGS} -c main.c

clean:
	rm ${OBJECTS}
