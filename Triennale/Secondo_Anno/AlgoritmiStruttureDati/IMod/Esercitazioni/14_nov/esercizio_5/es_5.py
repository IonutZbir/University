import networkx as nx
import matplotlib.pyplot as plt
from networkx.drawing.nx_pydot import graphviz_layout

def crea_albero_binario(n):
    G = nx.Graph()

    G.add_node(1, value=1, colore="R")
    for i in range(2, n + 1):
        if i == 2:
            G.add_node(i, value=i)
        else:
            G.add_node(i, value=i)

    G.add_edge(1, 2)
    G.add_edge(1, 3)

    G.add_edge(2, 4)

    G.add_edge(3, 5)
    G.add_edge(3, 6)

    G.add_edge(6, 7)
    G.add_edge(6, 8)

    G.add_edge(7, 9)
    G.add_edge(7, 10)

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
def MinProf(graph, current_node, h, visited=None):
    # Mediante l'utilizzo di un set, tengo conto dei nodi visitati, principalmente dei padri,
    # cosi la dfs verrà effettuta solo sui figli sinistri e destri

    if visited is None:
        visited = set()

    if current_node is None or current_node in visited: ## se il nodo attuale è None oppure è gia stato visitato
        return (0, 0, h)

    visited.add(current_node)
    node = graph.nodes[current_node]
    val = node['value']

    neighbors = list(graph.neighbors(current_node))
    
    result = [MinProf(graph, neighbor, h + 1, visited) for neighbor in neighbors]
    
    print(result)

    if len(result) == 3:
        sx = result[1]
        dx = result[2]
    else:
        sx = result[0]
        dx = result[1] if len(result) > 1 else (0, 0, h)

    disc = sx[0] + dx[0] + 1
    nodo_sx = sx[1]
    nodo_dx = dx[1]
    h_sx = sx[2]
    h_dx = dx[2]

    
    print(f'Node {current_node} - Value: {val} - Height: {h} - Disc: {disc}')
    if h >= disc:
        return (disc, current_node, h)
    elif h_sx < h_dx:
        return (disc, nodo_sx, h_sx)
    else:
        return (disc, nodo_dx, h_dx)

def CalcMinNodoProf(graph, current_node):
    disc, nodo, h =  MinProf(graph, current_node, 0)
    return nodo

# Specifica il numero di nodi nell'albero binario
nodi = 10

# Crea l'albero binario
albero_binario = crea_albero_binario(nodi)
root_node = 1
result = CalcMinNodoProf(albero_binario, root_node)
print("Risultato dell'algoritmo CalcBilanciati:", result)

# Visualizza l'albero binario
visualizza_albero(albero_binario)

# Esegui l'algoritmo max_rosso partendo dalla radice

