

FILE=hw5.c

default: run

run: cache
	./cache

gdb: cache
	gdb cache

cache: ${FILE}
	gcc -g -O0 -o cache ${FILE}

vi: ${FILE}
	vi ${FILE}

dist:
	dir=`basename $$PWD`; cd ..; tar cvf $$dir.tar ./$$dir; gzip $$dir.tar
	dir=`basename $$PWD`; ls -l ../$$dir.tar.gz
