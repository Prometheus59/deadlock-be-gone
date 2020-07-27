warnings_BAD: *.c
	gcc -Werror -Wall -g -std=gnu99 -o test *.c -lrt
	
warnings_OK: *.c
	gcc -Wall -g -std=gnu99 -o test *.c -lrt
	
clean: *.c
	rm test