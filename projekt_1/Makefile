#Makefile
#riesenie IJC DU 1, pouzite v prikladoch a aj b 
#autor: Igor Lacko, FIT (xlackoi00)

#premenne
CC = gcc 
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra
TARGETS = primes primes-i no-comment
LDFLAGS = -lm 
INLINE_DEFINITION = -DUSE_INLINE
PRIMES_DEPENDENCIES = eratosthenes.o error.o primes.o 
INLINE_DEPENDENCIES = eratosthenes-i.o error-i.o primes-i.o bitset-i.o 
NO_COMMENT_DEPENDENCIES = error.o no-comment.o error.h

#vsetky spustitelne subory 
all: $(TARGETS)

#individualne spustitelne subory a ich zavislosti 
primes: $(PRIMES_DEPENDENCIES) 
	$(CC) $(PRIMES_DEPENDENCIES) $(LDFLAGS) -o $@
primes-i: $(INLINE_DEPENDENCIES) 
	$(CC) $(INLINE_DEPENDENCIES) $(LDFLAGS) -o $@
no-comment: $(NO_COMMENT_DEPENDENCIES)
	$(CC) $(NO_COMMENT_DEPENDENCIES) -o $@

#pravidlo pre preklad do objektovych suborov 
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

#specialne modifikovane pravidlo na predoslom riadku pre primes-i (pridanie DUSE_INLINE)
%-i.o : %.c 
	$(CC) $(INLINE_DEFINITION) $(CFLAGS) -c $< -o $@

#zavislosti objektovych suborov 
error.o: error.c error.h 
eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h  
primes.o: primes.c bitset.h error.h 
error-i.o: error.c error.h 
eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h 
bitset-i.o: bitset.h bitset.c 
primes-i.o: primes.c bitset.h error.h 
no-comment.o :no-comment.c error.h 


#clean
clean:
	rm -f $(TARGETS) $(wildcard *.o)

#run
run: primes primes-i
	ulimit -s 82000 && ./primes && ./primes-i
