chook: main.c
	${CC} $< -o $@ -O2 -l curl -std=gnu99
