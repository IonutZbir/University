import networkx as nx
import matplotlib.pyplot as plt
from networkx.drawing.nx_pydot import graphviz_layout

def crea_albero_binario(n):
    G = nx.Graph()

    G.add_node(1, value=2, colore="R")
    for i in range(2, n+1 ):
        if i == 5:
            G.add_node(i, value=i, colore="R")
        else:
            G.add_node(i, value=i * 2, colore="R" if i % 2 == 0 else "N")

    for i in range(1, (n//2)+1):
        G.add_edge(i, 2*i)
        G.add_edge(i, 2*i+1)

    return G

# Visualizzazione dell'albero binario
def visualizza_albero(graph):
    pos = graphviz_layout(graph, prog="dot")
    i = 1
    for nodo in graph.nodes(data=True):
        if 'colore' not in nodo[1]:
            nodo[1]['colore'] = 'N'
        if 'value' not in nodo[1]:
            nodo[1]['value'] = (i * 2) + 1
        i += 1

    colors = [nodo[1]['colore'] for nodo in graph.nodes(data=True)]
    values = [nodo[1]['value'] for nodo in graph.nodes(data=True)]

    fig, ax = plt.subplots(figsize=(10, 10))
    nx.draw(graph, pos, with_labels=True, font_weight='bold', node_size=700, font_size=8, node_color='lightgray', edge_color="gray", linewidths=0.5, ax=ax)

    # Mostra l'informazione sul colore e il valore accanto ai nodi
    for nodo, colore, val in zip(graph.nodes, colors, values):
        x, y = pos[nodo]
        ax.text(x, y, f'Colore: {colore}\nValue: {val}', ha='center', va='center', bbox=dict(facecolor='white', edgecolor='white', boxstyle='round,pad=0.3'))

    plt.show()

# Implementazione dell'algoritmo MaxRosso
def MaxRosso(graph, current_node, visited=None):
    # Mediante l'utilizzo di un set, tengo conto dei nodi visitati, principalmente dei padri, cosi la dfs verrà effettuta solo sui figli sinistri e destri

    if visited is None:
        visited = set()

    if current_node is None or current_node in visited: ## se il nodo attuale è None oppure è gia stato visitato
        return 0

    visited.add(current_node)
    node = graph.nodes[current_node]
    col = node['colore']
    val = node['value']

    if col == 'N':
        return 0


    neighbors = list(graph.neighbors(current_node))

    # Ricorsivamente calcola il valore massimo del cammino rosso per ciascun vicino (figlio)
    max_neighboors = [MaxRosso(graph, neighbor, visited) for neighbor in neighbors]
    print(f'Node {current_node} - Colore: {node["colore"]}, Value: {node["value"]}')
    print(neighbors)

    return val + max(max_neighboors)

# Specifica il numero di nodi nell'albero binario
nodi = 22

# Crea l'albero binario
albero_binario = crea_albero_binario(nodi)
root_node = 1
result = MaxRosso(albero_binario, root_node)
print("Risultato dell'algoritmo MaxRosso:", result)

# Visualizza l'albero binario
visualizza_albero(albero_binario)

# Esegui l'algoritmo max_rosso partendo dalla radice


