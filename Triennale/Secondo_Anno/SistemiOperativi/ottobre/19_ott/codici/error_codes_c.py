import os

# Uso codici di errori generati da eseguibili C

file = "5.3_my_signal_2.c"
exec = "main"
cmd = f"gcc {file} -o {exec} && ./{exec}" 
r = os.system(cmd)
if r == 0:
    print("Esecuzione andata a buon fine con codice =", str(r));
