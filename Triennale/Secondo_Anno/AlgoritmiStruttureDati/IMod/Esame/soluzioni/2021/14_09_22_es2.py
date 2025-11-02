import networkx as nx
import matplotlib.pyplot as plt
from networkx.drawing.nx_pydot import graphviz_layout

def crea_albero_binario(n):
    G = nx.Graph()

    G.add_node(1, value=2, color="B")
    for i in range(2, n + 1):
        G.add_node(i, value=i * 2, color="G" if i % 2 == 0 else "B")

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
        if 'color' not in nodo[1]:
            nodo[1]['color'] = 'G'
        i += 1

    values = [nodo[1]['value'] for nodo in graph.nodes(data=True)]
    colors = [nodo[1]['color'] for nodo in graph.nodes(data=True)]

    fig, ax = plt.subplots(figsize=(10, 10))
    nx.draw(graph, pos, with_labels=True, font_weight='bold', node_size=700, font_size=8, node_color='lightgray', edge_color="gray", linewidths=0.5, ax=ax)

    # Mostra l'informazione sul colore e il valore accanto ai nodi
    for nodo, val, col in zip(graph.nodes, values, colors):
        x, y = pos[nodo]
        ax.text(x, y, f'Value: {val}\nColor: {col}', ha='center', va='center', bbox=dict(facecolor='white', edgecolor='white', boxstyle='round,pad=0.3'))

    plt.show()

# Implementazione dell'algoritmo Calcola Profondità
def BluGialloAnt(graph, current_node, b, g, n_b, n_g, visited=None):
    # Mediante l'utilizzo di un set, tengo conto dei nodi visitati, principalmente dei padri,
    # cosi la dfs verrà effettuta solo sui figli sinistri e destri

    if visited is None:
         visited = set()

    if current_node is None or current_node in visited: ## se il nodo attuale è None oppure è gia stato visitato
        return 0

    visited.add(current_node)
    node = graph.nodes[current_node]
    val = node['value']
    col = node['color']

    if col == 'B':
        n_b += 1
    else:
        n_g += 1

    neighbors = list(graph.neighbors(current_node))

    print(f'Node {current_node} - Value: {val} - Color: {col} - GialliAnt: {n_g} - BlueAnt: {n_b}')

    if n_b >= b or n_g >= g:
        return sum([BluGialloAnt(graph, neighbor, b, g, n_b, n_g, visited) for neighbor in neighbors]) + 1
    else:
        return sum([BluGialloAnt(graph, neighbor, b, g, n_b, n_g,  visited) for neighbor in neighbors])
# Specifica il numero di nodi nell'albero binario
nodi = 7

# Crea l'albero binario
albero_binario = crea_albero_binario(nodi)
root_node = 1
result = BluGialloAnt(albero_binario, root_node, 3, 2, 0, 0)
print("Risultato dell'algoritmo BluGiallo:", result)

# Visualizza l'albero binario
visualizza_albero(albero_binario)



