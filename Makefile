all: shell

shell: advshell.o chdir.o piping.o redirection.o shellconf.o prompt.o alias.o
		g++ advshell.o chdir.o piping.o redirection.o shellconf.o prompt.o alias.o -o shell 

advshell.o: advshell.cpp
		g++ -c advshell.cpp
chdir.o: chdir.cpp
		g++ -c chdir.cpp
piping.o: piping.cpp
		g++ -c piping.cpp
redirection.o: redirection.cpp
		g++ -c redirection.cpp
shellconf.o: shellconf.cpp
		g++ -c shellconf.cpp
prompt.o: prompt.cpp
		g++ -c prompt.cpp
alias.o: alias.cpp
		g++ -c alias.cpp
