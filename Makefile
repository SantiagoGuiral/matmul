# Written by Santiago Guiral - Emmanuel Gomez
# UdeA - Aug. 2021

CC = gcc
RM = rm -rf
LIBS = -lpthread
CFLAGS= -O0 -Wall -ggdb3
MATMUL=matmul

COARSE=coarsemm
FINE=finemm
SEQ=sequential

UTILS=utils
QUEUE=pt_queue


$(MATMUL): $(MATMUL).c $(SEQ).o $(UTILS).o $(QUEUE).o $(FINE).o $(COARSE).o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(SEQ).o: $(SEQ).c $(SEQ).h
	$(CC) $(CFLAGS) -c $(SEQ).c $(LIBS)

$(UTILS).o: $(UTILS).c $(UTILS).h
	$(CC) $(CFLAGS) -c $(UTILS).c $(LIBS)

$(QUEUE).o: $(QUEUE).c $(QUEUE).h
	$(CC) $(CFLAGS) -c $(QUEUE).c $(LIBS)

$(FINE).o: $(FINE).c $(FINE).h
	$(CC) $(CFLAGS) -c $(FINE).c $(LIBS)

$(COARSE).o: $(COARSE).c $(COARSE).h
	$(CC) $(CFLAGS) -c $(COARSE).c $(LIBS)

clean: 
	$(RM) *.o
	$(RM) $(MATMUL)
