all: thread_proj.c
	gcc -pthread -o thread_proj thread_proj.c

clean: 
	$(RM) thread_proj
