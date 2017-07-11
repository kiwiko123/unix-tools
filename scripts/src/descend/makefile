CC = gcc
CFLAGS = -std=gnu11 -ggdb
OBJECTS = main.o descend.o
NAME = descend

descend: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o ${NAME}
	mv ${NAME}.exe ${NAME}

main.o: main.c descend.h
	${CC} ${CFLAGS} -c main.c

descend.o: descend.c descend.h
	${CC} ${CFLAGS} -c descend.c

clean:
	rm ${OBJECTS}
