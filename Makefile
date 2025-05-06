all:
	gcc -o mini-shell src/main.c src/parser.c src/execute_commands.c src/builtins.c src/host_name.c
