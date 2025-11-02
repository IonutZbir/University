0. Installare gcc e gdb (quest'ultimo necessario solo nel caso si voglia usare Visual Studio Code)
1. Installazione Visual Studio Code (opzionale!)
2. Installazione estensione per WSL 
3. Installazione C/C++ extension pack (dopo essersi connesso a WSL, perche' vogliamo che questa estensione sia installata in WSL)
4. Programmi
    Per compilare usate, ricordate di attivare  gcc -Wall --pedantic ... ...
    - address
    - endianess
    - conversion
    - udpserver, con una sleep di 10 secondi per permettere di eseguire i comandi ss o lsof
      (si noti che il server non termina mai. Occorre usare CTRL-C o usare il comando kill, dopo aver trovato il pid con lsof)
5. Comandi ss e lsof e Wireshark

Riferimenti utili per le socket:
 * Stevens, W.R., Fenner, B., & Rudoff, A.M. (2003). UNIX Network Programming: The Sockets Networking API. (3rd ed., Vol. 1). Addison Wesley
 * man pages: es., man socket etc..
 * (non verificato nel dettaglio) Beej's Guide to Network Programming: https://beej.us/guide/bgnet/
