# Stimatori e le loro proprietà

Diamo prima di tutto una defizione

>[!definition]- Campione Aleatorio (Random Sample)
>È un insieme di variabili aleatorie indipendenti ed identicamente distribuite $X_{1},\dots,X_{n}$ definite su uno spazio di prob $\{\Omega,\mathcal F,P\}$

**oss**:
In realtà ne l'ipotesi di indipendenza ne quella di identica distribuzione sono necessarie e saranno entrambe abbandonate più avanti

Supponiamo ora che la misura di probabilità $P$ sia nota solo a meno di un valore di un certo parametro $\theta$, ottenendo quindi $P_{\theta}$

In genere, si definisce 
- *Statistica Parametrica* la disciplina che studia le tecniche per risalire al valore di $\theta$ nel caso in cui esso appartenga ad uno spazio di dimensione finita, $\theta\in\mathbb R^{p},p\in\mathbb N$ 
- *Statistica Non Parametrica* la disciplina che studia il caso in cui $\theta$ ha dimensione infinita

Diamo ora la definizione di stimatore

>[!definition]- Stimatore
>Uno **stimatore** di un certo parametro $\theta\in\mathbb R^{p}$ è una funzione (o meglio successione di funzioni) misurabile $T_{n}:\mathbb R^{n}\to\mathbb R^{p}$ di un campione aleatorio.
>Si scrive come: $$T_{n}=\hat\theta_{n}=T_{n}(X_{1},\dots,X_{n})$$

**oss** : La definizione è lasciata volutamente molto generica: qualsiasi funzione misurabile è uno stimatore, quindi il punto cruciale sarà determinare quali siano le proprietà che consentono di valutare la qualità e bontà della scelta fatta

Vediamo alcuni esempi di stimatori

**Esempio 1**
L'esempio più ovvio di stimatore (per il valor medio $\mu=\mathbb E[X_{i}]$) è la media aritmetica, cioè
$$\hat X_{n}=\hat\mu_{n}=\frac{1}{n}\sum\limits_{i=1}^{n}X_{i}$$

**Esempio 2**
Altro stimatore naturale è la cosidetta varianza empirica (che stima $\sigma^2=Var(X_{i})$), cioè
$$S_{n}^{2}=\hat\sigma_{n}^{2}=\frac{1}{n}\sum\limits_{i=1}^{n}(X_{i}-\hat\mu_{n})^2$$
## Criteri per valutare gli stimatori

Ci sono $4$ criteri per valutare gli stimatori, essi sono:
1. **Correttezza** (anche chiamata Non-Distorsione/Asintotica non distorsione), cioè $$\mathbb E[T_{n}]=\theta,\quad\left(\lim_{n\to\infty}\mathbb E[T_{n}]=\theta\right)$$**condizione non fondamentale**
2. **Consistenza**, che si divide per ogni metodo di convergenza studiato, infatti abbiamo:
	1. *consistenza debole* (convergenza in probabilità) : $T_{n}\to_p\theta$ quando $n\to\infty$
	2. *consistenza forte* (convergenza quasi certa) : $T_{n}\to_{q.c}\theta$ quando $n\to\infty$
	3. *consistenza $r$-esima* (convergerza in media $r$-esima) : $T_{n}\to_r\theta$ quando $n\to\infty$
	4. *consistenza completa* (convergenza completa) : $T_{n}\to_{c.c}\theta$ quando $n\to\infty$
3. **Efficienza**, che dice che presi due stimatori distinti $T_{n},T^{'}_{n}$, tra i due scegliamo quello con varianza minore, quindi diremo che $T_{n}$ è più *efficiente di* $T^{'}_{n}$ se e solo se $$Var(T_{n})\leq Var(T^{'}_{n})$$
4. **Asintotica Gaussianità**, che afferma che quando $n\to\infty$ deve valere che $$\frac{T_{n}-\theta}{\sqrt{Var(T_{n})}}\to_{d}N(0,1)\quad\text{CLT}$$

Vediamo qualche osservazione 
1) In generale, vale che $1.\cancel\implies 2.$ 
2) $2.\implies 1.$ solo se si tratta di consistenza in media $r$-esima, con $r\geq1$. In tutti gli altri casi vale che $2. \cancel\implies 1.$
	1) per la seconda parte di questa affermazione, basta prendere $$T_{n}=\begin{cases}0&1- \frac{1}{n^{2}}\\ n^2& \frac{1}{n^{2}}\end{cases},\theta=0\implies T_{n}\to0\space ma\space \mathbb E[T_n]=1\neq\theta$$
	2) per la prima parte, basta usare il seguente lemma, che afferma che $T_{n}\to_{r}\theta,r\geq1\implies\mathbb E[T_{n}]\to\theta$. La dimostrazione è la seguente $$\lim_{n\to\infty}\mathbb E[T_{n}-\theta]=0\space perchè\space\big|\mathbb E[T_{n}-\theta]\big|\leq\mathbb E[T_{n}-\theta]$$

Vediamo ora qualche esempio 

**Esempio 1**: Media aritmetica $X_{n}= \frac{1}{n}\sum\limits_{i=1}^{n}X_{i}$. 
Se le $X_{i}\sim$ i.i.d con $\mathbb E[X_{i}]=\mu$ e $Var(X_{i})=\sigma^{2}$ allora vale che 
- Non Distorsione? $\checkmark$ 
- Consistente? $\checkmark$
- Efficiente? $\checkmark$ (vedremo poi)
- Asintotica Gaussianità? $\checkmark$ (vale il CLT)
