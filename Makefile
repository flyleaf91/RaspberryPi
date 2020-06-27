all:
	gcc sort.c tools/*.c -o sort -Iincludes

clean:
	rm sort
