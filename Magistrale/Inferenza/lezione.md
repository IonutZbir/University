# Metodo di Massima Verosimiglianza

Supponiamo di avere di fronte a noi due urne, una con $90$ palline bianche e $10$ nere, e l’altra con $10$ nere e $90$ bianche; identifichiamo le urne con la proporzione di palline bianche che contengono (denotata con $p$), in modo tale che la prima urna corrisponda a $p = .9$ e la seconda a $p = .1$

Viene estratta una singola pallina e non sappiamo da quale urna venga; osserviamo però che la pallina è bianca. 

Dovendo cercare di risalire all’urna di provenienza, sembra naturale scegliere quella che rende più probabile osservare quello che abbiamo effettivamente osservato, cioè l’urna che contiene la maggiore proporzione di palline bianche; in altre parole, dall’osservazione "è stata estratta una pallina bianca" sembra naturale far discendere lo stimatore $\hat{p} = 0.9$

Supponiamo ora che invece di una sola pallina ne siano estratte $5$, e che risultino essere $3$ bianche e $2$ nere; immaginiamo altresì che l’alternativa non sia solo tra due urne, ma tra un continuo di urne con tutte le possibili proporzioni di palline bianche tra $0$ ed $1$, identificate sempre con $p$. 

In questo caso, la probabilità di osservare $3$ bianche e $2$ nere è data da una legge binomiale:
$$Pr(3b,2n)=\binom{5}{3}p^{3}(1-p)^{2}$$
ed è facilmente verificabile che questa probabilità è massimizzata prendendo $\hat{p}=\frac{3}{5}$

Questo esempio molto semplice dovrebbe aiutare a capire l’idea che è alla base degli stimatori di massima verosimiglianza - si tratta di costruire la funzione di probabilità (o di densità, nel caso continuo) relativa ad un certo campione aletaorio, e vederla quindi non più come funzione del campione, ma come funzione (aleatoria) dei parametri, prendendo come date le osservazioni. 

In altre parole, si ha la seguente definizione:

>[!definition]- Funzione di Verosimiglianza
>Sia $X_{1},\dots,X_{n}$ un campione aleatorio con legge (=funzione di prob. o densità, a seconda del caso discreto o continuo) $f_{\theta},\theta\in\mathbb R^{p}$
>La **funzione di verosimiglianza** $L:\mathbb R^{p}\to\mathbb R$ è quindi definita come $$L(\theta;X_{1},\dots,X_{n}):=\prod_{i=1}^{n}f(X_{i};\theta)=f(X_{1},\dots,X_{n};\theta)$$

**oss**

Vediamo che la definizione di funzione di verosimiglianza in qualche modo "assomiglia" alla densità congiunta.
Quello che cambia è che la verosimiglianza è funzione del parametro prendendo i valori di $X_{1},\dots,X_{n}$ come dati, mentre la densità congiunta prende il parametro $\theta$ come dato ed è funzione dei possibili valori delle osservazioni $x_{1},\dots,x_{n}$

Definiamo poi il concetto di **stimatore di massima verosimiglianza (ML)**

>[!definition]- Stimatore di massima verosimiglianza (ML)
>Data $L$ la funzione di verosimiglianza appena definita, indichiamo con $\hat{\theta}$ lo **stimatore di massima verosimiglianza**, in questo modo: $$\hat{\theta}:=\underset{\theta}{\arg\max}\space L(\theta;X_{1},\dots,X_{n})$$
>Ovvero quel valore di $\theta$ che **massimizza** il risultato della funzione $L$

Vediamo ora una carrellata di esempi

**Esempio 1**

Prendiamo un campione aleatorio di variabili Bernoulliane $X_{1},\dots,X_n\sim Ber(\theta)$, dove $$X_{i}=\begin{cases}
1&\theta\space(p)\\0&1-\theta\space(1-p)
\end{cases}$$ 
La funzione di verosimiglianza sarà quindi:
$$L(\theta;X_1,\dots,X_{n})=\theta^{\sum\limits_{i=1}^{n}X_{i}}(1-\theta)^{n-\sum\limits_{i=1}^{n}X_{i}}$$
Sfruttiamo la $\log$-verosimiglianza, in modo tale da eliminare produttorie varie e rimanere con solamente le sommatorie

La $\log L$ sarà quindi $$\log L=\left(\sum\limits_{i=1}^{n}X_{i}\right)\log(\theta)+\left(n-\sum\limits_{i=1}^{n}X_{i}\right)\log(1-\theta)$$
Dobbiamo ora massimizzare la $\log L$, facendone la derivata e ponendola uguale a $0$; così facendo otteniamo che 
$$\begin{align*}
\frac{d\log L}{d\theta}&=\frac{\sum\limits_{i=1}^{n}X_{i}}{\theta}-\frac{n-\sum\limits_{i=1}^{n}X_{i}}{1-\theta}\\&=\frac{\sum\limits_{i=1}^{n}X_{i}-n\theta}{\theta(1-\theta)}
\end{align*}$$
Ponendo questo uguale a $0$ otteniamo che 
$$\hat{\theta}_{ML}=\frac{1}{n}\sum\limits_{i=1}^{n}X_{i}$$
Piccola osservazione, avremmo potuto scrivere la verosimiglianza come 
$$L(\theta;X_1,\dots,X_{n})=\dbinom{n}{\sum\limits_{i=1}^nX_{i}}\theta^{\sum\limits_{i=1}^{n}X_{i}}(1-\theta)^{n-\sum\limits_{i=1}^{n}X_{i}}$$
La cosa che cambia fra la prima equazione e la seconda è puramente "filosofica", ovvero scritta nel secondo modo noi stiamo prendendo una *qualsiasi sequenza di successi*, mentre nel primo caso stiamo prendendo *una sequenza esatta di successi*.

Entrambe le versioni sono equivalenti

**Esempio 2**

Prendiamo un campione aleatorio di variabili esponenziali $X_{1},\dots,X_n$, con densità $$\begin{align*}f(x)=&\lambda e^{-\lambda x},x\geq0\\=&\frac{1}{\theta}e^{-\frac{x}{\theta}},x\geq0\end{align*}$$
Notiamo le che due rappresentazioni della densità sono equivalenti

Risolviamo per $\lambda$, ottenendo che la verosimiglianza è pari a
$$L(\lambda;X_{1},\dots,X_{n})=\lambda^{n}e^{-\lambda\sum\limits_{i=1}^{n}X_{i}}$$
La log-verosimiglianza è quindi:
$$\log L=n\log(\lambda)-\lambda\sum\limits_{i=1}^{n}X_{i}$$
Facciamo la derivata per $\lambda$ e la poniamo $=0$ per ottenere lo stimatore $\hat{\lambda}_{ML}$
$$\frac{d\log L}{d\lambda}=\frac{n}{\lambda}-\sum\limits_{i=1}^{n}X_{i}\underbrace{\implies}_{\text{ponendo la der. uguale a 0}}\hat{\lambda}_{ML}=\frac{n}{\sum\limits_{i=1}^{n}X_{i}}$$
**oss**

(1) Lo stimatore non dipende da come viene scritta la densità della funzione
(2) Non si può avere uno stimatore che sia non distorto, e allo stesso tempo invariante

**Esempio 3**

Prendiamo $X_{1},\dots,X_{n}\sim N(\mu,\sigma^{2})$ i.id

Vale allora che la verosimiglianza è
$$L(\mu,\sigma^{2};X_1,\dots,X_{n})=\frac{1}{(2\pi)^{\frac{n}{2}}}\frac{1}{(\sigma^{2})^{\frac{n}{2}}}e^{-\frac{1}{2}\sum\limits_{i=1}^{n}\frac{(X_{i}-\mu)^{2}}{\sigma^{2}}}$$

**oss**

La densità di una v.a Normale (Gaussiana) cambia a seconda dei valori di $\mu,\sigma^{2}$. 
Alcuni esempi sono:
$$\begin{align*}&N(0,1)=\frac{1}{\sqrt{2\pi}}e^{-\frac{1}{2}X}\\&N(\mu,\sigma^{2})=\frac{1}{\sqrt{2\pi\sigma^{2}}}e^{-\frac{1}{2}\frac{(X-\mu)}{\sigma}}\end{align*}$$
Ritornando all'esempio, la log-verosimiglianza è
$$\log L=-\frac{n}{2}\log(2\pi)-\frac{n}{2}\log(\sigma^{2})-\frac{1}{2}\sum\limits_{i=1}^{n}\frac{(X_{i}-\mu)^{2}}{\sigma^{2}}$$
A questo punto dobbiamo derivare e porre uguale a $0$, però qui non abbiamo più un solo parametro, ma ne abbiamo ben $2$ (nel mondo del Machine Learning in generale $\theta$ non è un parametro solo ma un vettore di parametri)

Dobbiamo quindi fare le derivate parziali, una per $\mu$ e l'altra per $\sigma^{2}$, ottenendo 
$$\begin{align*}&\frac{d\log L}{d\mu}=\frac{1}{\sigma^{2}}\sum\limits_{i=1}^{n}(X_{i}-\mu)\\&\frac{d\log L}{d\sigma^{2}}=-\frac{n}{2\sigma^{2}}+\frac{1}{2\sigma^{4}}\sum\limits_{i=1}^{n}(X_{i}-\mu)^{2}\end{align*}$$
Ponendole $=0$ otteniamo che 
$$\begin{align*}&\hat{\mu}_{ML}=\frac{1}{n}\sum\limits_{i=1}^{n}X_{i}\\&\hat{\sigma}^{2}_{ML}=\frac{1}{n}\sum\limits_{i=1}^{n}(X_{i}-\overline{X}_{n})^{2},\quad\overline{X}_{n}=\frac{1}{n}\sum\limits_{i=1}^{n}X_{i}\end{align*}$$