# Alcuni algoritmi per calcolare l'n-esimo numero di Fibonacci

#### 1. Formula

```
fibonacci1(intero n) -> intero
    return 1/sqrt(5) * ((phi)^n - (phi')^n)
```

**Complessità Temporale**: $T(n) = O(1)$

- $\phi \approx 1.618$
- $\phi' \approx - 0.618$

Il problema di questo algoritmo è la precisione. 
Infatti la precisione di questa formula dipende dall'approsimazione di $\phi$. Piu è precisa l'approsimazione più l' $n-esimo$ numero di Fibonacci è preciso.

#### 2. Ricorsione

```
fibonacci2(intero n) -> intero
    if( n<=2 ) then return 1
    else return fibonacci2(n - 1) + fibonacci2(n - 2)
```

Approccio ricorsivo, usando direttamente la definizione dell' $n-esimo$ numero di Fibonacci.

**Complessità Temporale**: $T(n) = O(\phi^n) = o(2^n)$, di conseguenza è un algoritmo lento.

#### 3. Programmazione Dinamica

L'algoritmo fibonacci2 è lento poichè continua a ricalcolare ripetutamente la soluzione 
dello stesso sottoproblema. Perché non memorizzare allora in un array le soluzioni dei sottoproblemi?

```
fibonacci3(intero n) -> intero
    sia Fib un array di n interi
    Fib[1] = 1
    Fib[2] = 2
    for i = 3 to n do
        Fib[i] = Fib[i - 1] + Fib[i - 2]
    return Fib[n]
```

**Complessità Temporale**: $T(n) = O(n)$  
**Complessità Spaziale**: $S(n) = O(n)$

#### 4. Memoria Costante

L'algoritmo fibonacci3 usa un array di dimensione $n$ prefissata. In realtà non ci serve mantenere tutti i valori di $F_{n}$ precedenti,
ma solo gli ultimi due, riducendo lo spazio a poche variabili in tutto.

```
fibonacci4(intero n) -> intero
    a = 1
    b = 2
    for i = 3 to n do
        c = a + b
        a = b
        b = c
    return c
```

**Complessità Temporale**: $T(n) = O(n)$  
**Complessità Spaziale**: $S(n) = O(1)$

#### 5. Potenze Matrici

E' possibile dimostrare per induzione la seguente proprietà di matrici:

$$
\left(\begin{array}{cc} 
1 & 1\\
1 & 0
\end{array}\right)^{n}
=\left(\begin{array}{cc} 
F_{n+1} & F_{n}\\
F_{n} & F_{n-1}
\end{array}\right)
$$

Usando questa proprietà, possiamo progettare il seguento algoritmo:

Siano

$$
I = 
\left(\begin{array}{cc} 
1 & 0\\
0 & 1
\end{array}\right)
$$



$$
M = \left(\begin{array}{cc} 
1 & 1\\
1 & 0
\end{array}\right)
$$  

```
fibonacci5(intero n) -> intero
    for i = 1 to n - 1 do 
        M = M * I
    return M[0][0]
```
**Complessità Temporale**: $T(n) = O(n)$

#### 6. Potenze Matrici Ottimizzato

Possiamo calcolare la $n-esima$ potenza elevando al quadtrado la $\frac{n}{2}-esima$ potenza. Se $n$ è dispari eseguiamo un ulteriore moltiplicazione.

$3^2 = 9$, $3^4 = (9)^2 = 81$, $3^8 = (81)^2 = 6561 =>$ Ho eseguito solo 3 prodotti invece che 7.

```
fibonacci6(intero n) -> intero
    N = potenzaDiMatrice(M, n - 1)
    return N[0][0]

potenzaDiMatrice(matrice A, intero k)
    if (k = 0) then return I
    else
        M = potenzaDiMatrice(A, k/2)
        M = M * M
    if (k è dispari) then M = M * A
    return M
```

**Complessità Temporale**: $T(n) = log(n)$
**Complessità Spaziale**: $S(n) = log(n)$


## Riepilogo

|            | T(n)        | S(n)        |
| ---------- | ----------- | ----------- |
| fibonacci1 | $O(1)$      | $O(1)$      |
| fibonacci2 | $\phi(n)$   | $O(n)$      |
| fibonacci3 | $O(n)$      | $O(n)$      |
| fibonacci4 | $O(n)$      | $O(1)$      |
| fibonacci5 | $O(n)$      | $O(1)$      |
| fibonacci6 | $O(log(n))$ | $O(log(n))$ |

