# Written by Santiago Guiral - Emmanuel Gomez
# UdeA - Aug. 2021

CC = gcc
RM = rm -rf
LIBS = -lpthread
CFLAGS= -O0 -Wall -g
MATMUL=matmul

COARSE=coarsemul
FINE=finemul
SEQ=sequential
UTILS=utils
QUEUE=pt_queue


$(MATMUL): $(MATMUL).c $(SEQ).o $(UTILS).o $(QUEUE).o #$(COARSE).o $(FINE).o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(SEQ).o: $(SEQ).c $(SEQ).h
	$(CC) $(CFLAGS) -c $(SEQ).c $(LIBS)

$(UTILS).o: $(UTILS).c $(UTILS).h
	$(CC) $(CFLAGS) -c $(UTILS).c $(LIBS)

$(QUEUE).o: $(QUEUE).c $(QUEUE).h
	$(CC) $(CFLAGS) -c $(QUEUE).c $(LIBS)

#$(COARSE).o: $(COARSE).c $(COARSE).h
#	$(CC) $(CFLAGS) -c $(COARSE).c $(LIBS)

#$(FINE).o: $(FINE).c $(FINE).h
#	$(CC) $(CFLAGS) -c $(FINE).c $(LIBS)

clean: 
	$(RM) *.o
	$(RM) $(MATMUL)
