#Makefile, IJC DU2, pouzite v prikladoch a aj b
#autor: Igor Lacko, FIT (xlackoi00)

CC = gcc 
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
TARGETS = tail wordcount wordcount-dynamic
WORDCOUNT_DEPENDENCIES = io.o wordcount.o 
LIB_FILES =  htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_size.o htab_statistics.o

all: $(TARGETS)

#-----               CIELE               -----#
tail: tail.c 
	$(CC) $(CFLAGS) $< -o $@ 

wordcount: $(WORDCOUNT_DEPENDENCIES) libhtab.a 
	$(CC) -o $@ -static wordcount.o io.o -L. -lhtab

wordcount-dynamic: $(WORDCOUNT_DEPENDENCIES) libhtab.so
	$(CC) -o $@ -Wl,-rpath,. wordcount.o io.o -L. -lhtab  

#-----             KNIZNICE             -----#

libhtab.a: $(LIB_FILES) htab.h htab_private.h
	ar crs $@ $(LIB_FILES)


libhtab.so : $(LIB_FILES) htab.h htab_private.h 
	$(CC) -shared -fPIC $(LIB_FILES) -o $@

#-----          OBJEKTY                -----#

%.o : %.c
	$(CC) $(CFLAGS) -c -fPIC $< -o $@ 


#-----               RUN               -----#

run: $(TARGETS)
	./tail < tail.c && ./wordcount < tail.c && ./wordcount-dynamic < tail.c



#-----          CLEAN                  -----#

clean:
	rm -f $(TARGETS) *.o libhtab.a libhtab.so