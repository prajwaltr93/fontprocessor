CFLAGS = -I/usr/local/include/freetype2 
LINKS = -L/usr/local/lib -lfreetype  
all: Makefile fontprocessor.c
	$(CC) fontprocessor.c -o renderer $(CFLAGS) $(LINKS) 
clean:
	rm -rf fontprocessor
