import networkx as nx
import matplotlib.pyplot as plt
from networkx.drawing.nx_pydot import graphviz_layout

def crea_albero_binario(n):
    G = nx.Graph()

    G.add_node(1, value=2, colore="R")
    for i in range(2, n):
        G.add_node(i, value=i * 2)

    for i in range(1, n//2+1):
        G.add_edge(i, 2*i)
        G.add_edge(i, 2*i+1)

    return G



# Visualizzazione dell'albero binario
def visualizza_albero(graph):
    pos = graphviz_layout(graph, prog="dot")
    i = 1
    for nodo in graph.nodes(data=True):
        if 'value' not in nodo[1]:
            nodo[1]['value'] = (i * 2) + 1
        i += 1

    values = [nodo[1]['value'] for nodo in graph.nodes(data=True)]

    fig, ax = plt.subplots(figsize=(10, 10))
    nx.draw(graph, pos, with_labels=True, font_weight='bold', node_size=700, font_size=8, node_color='lightgray', edge_color="gray", linewidths=0.5, ax=ax)

    # Mostra l'informazione sul colore e il valore accanto ai nodi
    for nodo, val in zip(graph.nodes, values):
        x, y = pos[nodo]
        ax.text(x, y, f'Value: {val}', ha='center', va='center', bbox=dict(facecolor='white', edgecolor='white', boxstyle='round,pad=0.3'))

    plt.show()

# Implementazione dell'algoritmo Calcola Profondità
def CalcolaProfondita(graph, current_node, height, ih, visited=None):
    # Mediante l'utilizzo di un set, tengo conto dei nodi visitati, principalmente dei padri, cosi la dfs verrà effettuta solo sui figli sinistri e destri

    if visited is None:
        visited = set()

    if current_node is None or current_node in visited: ## se il nodo attuale è None oppure è gia stato visitato
        return 0

    visited.add(current_node)
    node = graph.nodes[current_node]
    #val = node['value']

    neighbors = list(graph.neighbors(current_node))
    print(f'Node {current_node} - Height: {ih}')

    if ih >= height:
        print(neighbors)
        return sum([CalcolaProfondita(graph, neighbor, height, ih + 1, visited) for neighbor in neighbors]) + 1
    else:
        print(neighbors)
        return sum([CalcolaProfondita(graph, neighbor, height, ih + 1, visited) for neighbor in neighbors])




# Specifica il numero di nodi nell'albero binario
nodi = 8

# Crea l'albero binario
albero_binario = crea_albero_binario(nodi)
tree = nx.balanced_tree(2, 4)
root_node = 1
result = CalcolaProfondita(tree, root_node, 1, 0)
print("Risultato dell'algoritmo MaxRosso:", result)

# Visualizza l'albero binario
visualizza_albero(tree)

# Esegui l'algoritmo max_rosso partendo dalla radice



