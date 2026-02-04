all:
	cc src/templari.c -o templari

clean:
	rm templari

install:
	make
	mv templari /usr/local/bin/
