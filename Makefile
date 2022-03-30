mode = DEBUG
output = test

${output}:main.c
	gcc $^ -D${mode} -o $@

.PHONY:clean run

clean:
	rm test
run: 
	make
	./${output}
