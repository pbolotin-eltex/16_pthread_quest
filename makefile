# Make

.PHONY = clean
KEYS :=
LIBS := -lpthread
CC := gcc

pthread_quest : pthread_quest.o
	$(CC) $(KEYS) pthread_quest.o -o pthread_quest $(LIBS)

pthread_quest.o : pthread_quest.c
	$(CC) $(KEYS) -c pthread_quest.c -o pthread_quest.o $(LIBS)

clean :
	rm -f *.o *.gch textEdit