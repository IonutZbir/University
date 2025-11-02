#!/bin/bash   

# Il #!/bin/bash all'inizio di un file è chiamato "shebang". 
# Ha lo scopo di indicare al sistema con quale interprete eseguire lo script che segue. 
#
# Ecco cosa fa:
#
# - Indica l'Interprete: Dice al sistema che lo script dovrebbe essere eseguito usando 
#   l'interprete specificato dopo #!. Nel caso di #!/bin/bash, indica che lo script 
#    dovrebbe essere eseguito con l'interprete Bash.
# - Esecuzione Diretta: Permette di eseguire lo script come un programma direttamente 
#   dalla linea di comando (ad es. ./myscript.sh), senza dover chiamare esplicitamente 
#   l'interprete (bash myscript.sh).

CC=gcc #o gcc?


#-O0 Means “no optimization”: this level compiles the fastest and generates the most debuggable code.
#-O1 Somewhere between -O0 and -O2.
#-O2 Moderate level of optimization which enables most optimizations.
#-O3 Like -O2, except that it enables optimizations that take longer to perform or that may generate larger code 
#         (in an attempt to make the program run faster).
OPTIONS="-O2" 

# Differenti modi per scrivere su standard out
${CC} ${OPTIONS} 5.1_hello_world_1.c -o 5.1_hello_world_1
${CC} ${OPTIONS} 5.1_hello_world_2.c -o 5.1_hello_world_2
${CC} ${OPTIONS} 5.1_hello_world_3.c -o 5.1_hello_world_3

# Diverse modi di generare processi
${CC} ${OPTIONS} 5.2_my_first_fork_1.c -o 5.2_my_first_fork
${CC} ${OPTIONS} 5.2_my_first_fork_2.c -o 5.2_my_first_fork_2

# Gestione dei segnali
${CC} ${OPTIONS} 5.3_my_signal_1.c -o 5.3_my_signal_1 
${CC} ${OPTIONS} 5.3_my_signal_2.c -o 5.3_my_signal_2

# Interazione tra processi e PIPE (vedi esempio su slide)
${CC} ${OPTIONS} 5.4_fork_pipe.c -o 5.4_fork_pipe

# La mia prima bash
${CC} ${OPTIONS} 5.5_my_first_bash.c -o 5.5_my_first_bash
