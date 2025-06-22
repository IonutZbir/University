import numpy as np
from scipy.spatial import ConvexHull
import pandas as pd
import os
import csv

X = np.array(
    [
        [
            [-2.16129309, 1.48012075],
            [-2.4591423, 1.14660214],
            [-2.59253808, 0.63828907],
            [-2.54702492, 0.01026515],
            [-2.32753489, -0.66941348],
            [-1.95785314, -1.3270931],
            [-1.47804041, -1.89150392],
            [-0.94009186, -2.30148326],
            [-0.40230256, -2.51260351],
            [0.07704966, -2.5019865],
            [0.44601956, -2.27078277],
            [0.66462353, -1.8440468],
            [0.70917244, -1.26802208],
            [0.57483871, -0.60512982],
            [0.27617949, 0.07279532],
            [-0.15444085, 0.69228963],
            [-0.67035793, 1.1862213],
            [-1.21566412, 1.50106515],
            [-1.73126703, 1.60270298],
            [-2.16129309, 1.48012075],
        ],
        [
            [4.62796476, 2.24351854],
            [4.50361353, 2.66404501],
            [4.36581803, 3.07272066],
            [3.98895846, 3.37597512],
            [3.42322825, 3.63879137],
            [2.89832263, 3.68615186],
            [2.36162751, 3.58488113],
            [1.86229742, 3.48353259],
            [1.48612377, 3.10283882],
            [1.29503815, 2.7219732],
            [1.2967058, 2.30502749],
            [1.41119916, 1.89505395],
            [1.7562995, 1.62213866],
            [2.10908255, 1.35157675],
            [2.6750831, 1.1231915],
            [3.15910945, 1.14605908],
            [3.73146702, 1.2716204],
            [4.18348103, 1.5263114],
            [4.49773552, 1.90067435],
            [4.53386551, 2.14047857],
        ],
        [
            [3.31862541, 2.10347003],
            [3.36289286, 2.07422944],
            [3.40716031, 2.04498885],
            [3.45142777, 2.01574826],
            [3.49569522, 1.98650768],
            [3.53996267, 1.95726709],
            [3.58423012, 1.9280265],
            [3.62849757, 1.89878591],
            [3.67276503, 1.86954532],
            [3.71703248, 1.84030473],
            [3.76129993, 1.81106414],
            [3.80556738, 1.78182355],
            [3.84983484, 1.75258296],
            [3.89410229, 1.72334237],
            [3.93836974, 1.69410178],
            [3.98263719, 1.66486119],
            [4.02690464, 1.6356206],
            [4.0711721, 1.60638001],
            [4.11543955, 1.57713942],
            [4.159707, 1.54789883],
        ],
        [
            [-3.18759921, -4.24889309],
            [-3.11570813, -4.17266226],
            [-2.92963173, -4.25390855],
            [-2.78381789, -4.24384752],
            [-2.58847103, -4.27571002],
            [-2.41942617, -4.19887343],
            [-2.3178249, -4.168037],
            [-2.22075457, -4.25722223],
            [-1.98475571, -4.30736054],
            [-1.85558777, -4.28467949],
            [-1.72531833, -4.30619599],
            [-1.54391683, -4.35104363],
            [-1.43248654, -4.3016988],
            [-1.24367661, -4.34072447],
            [-1.06681925, -4.31289037],
            [-0.89977145, -4.35303898],
            [-0.68773955, -4.39261271],
            [-0.56098871, -4.38655649],
            [-0.40871229, -4.45362673],
            [-0.30152858, -4.46294577],
        ],
        [
            [1.72516175, 5.33912309],
            [1.65696157, 4.98901256],
            [1.75231272, 4.60402332],
            [2.00088243, 4.22587493],
            [2.37573431, 3.89554564],
            [2.83624734, 3.64883175],
            [3.33251779, 3.51246854],
            [3.81076706, 3.50123308],
            [4.21916941, 3.61634291],
            [4.51346813, 3.84532409],
            [4.66177136, 4.16336295],
            [4.64800816, 4.53599506],
            [4.47366999, 4.92283993],
            [4.15764908, 5.28197693],
            [3.73419121, 5.57448799],
            [3.24918461, 5.768675],
            [2.75518727, 5.84349477],
            [2.30573147, 5.79083944],
            [1.94952271, 5.61641501],
            [1.72516175, 5.33912309],
        ],
    ]
)

x = np.array(
    [
        [-2.16129309, 1.48012075],
        [-2.4591423, 1.14660214],
        [-2.59253808, 0.63828907],
        [-2.54702492, 0.01026515],
        [-2.32753489, -0.66941348],
        [-1.95785314, -1.3270931],
        [-1.47804041, -1.89150392],
        [-0.94009186, -2.30148326],
        [-0.40230256, -2.51260351],
        [0.07704966, -2.5019865],
        [0.44601956, -2.27078277],
        [0.66462353, -1.8440468],
        [0.70917244, -1.26802208],
        [0.57483871, -0.60512982],
        [0.27617949, 0.07279532],
        [-0.15444085, 0.69228963],
        [-0.67035793, 1.1862213],
        [-1.21566412, 1.50106515],
        [-1.73126703, 1.60270298],
        [-2.16129309, 1.48012075],
    ],
)

k = np.array(
    [
        [-2.16129309, 1.48012075],
    ],
)

square = np.array(
    [
        [
            [0, 0],
            [2, 0],
            [2, 2],
            [0, 2],
        ], # quadrato
        [
            [0, 0],
            [0, 2],
            [2, 2],
            [0, 4],
        ], # trapezio
    ]
)

# # Get elements of the first column
# first_col = square[:, 0]
# # Get elements of the second column
# second_col = square[:, 1]

# print("First column:", first_col)
# print("Second column:", second_col)


def calcola_centroidi(X):

    centroidi = []

    for xi in X:
        # print("\n", xi, "\n")
        # print("\n", xi[0], "\n")
        centroidi.append(xi.mean(axis=0))

    return np.array(centroidi)


def calcola_distanza_centroide(X):
    distanze = []
    centroidi = calcola_centroidi(X)

    for xi, ci in zip(X, centroidi):
        distanze.append(np.linalg.norm(xi - ci, axis=1))

    return np.array(distanze)


def calcola_aree(X):
    aree = []

    for xi in X:
        x = xi[:, 0]
        y = xi[:, 1]

        a = 0.5 * np.abs(np.dot(x, np.roll(y, 1)) - np.dot(y, np.roll(x, 1)))
        aree.append(a)

    return np.array(aree)


def calcola_area_convessa(X):
    aree = []

    for xi in X:
        hull = ConvexHull(xi)
        area_convessa = hull.volume
        aree.append(area_convessa)

    return np.array(aree)


def calcola_perimetro(X):
    perimetro = []
    for xi in X:
        p = np.sum(np.linalg.norm(np.diff(xi, axis=0, append=[xi[0]]), axis=1))
        perimetro.append(p)
    
    return np.array(perimetro)

import numpy as np
import pandas as pd

def esporta_dataset(filename, X, y, labels):
    """
    Esporta le forme in un CSV con stringhe coordinate formattate e label testuali.

    Formato:
        x0,y0;x1,y1;x2,y2,...,etichetta

    Args:
        filename (str): Nome del file CSV di output.
        X (np.ndarray): Array di shape (n_forme, n_punti, 2).
        y (np.ndarray): Etichette numeriche.
        labels (list or dict): Mappa da indice a stringa.
    """
    righe = []
    for forma, etichetta in zip(X, y):
        stringa_coord = ";".join(f"{x:.8f},{y:.8f}" for x, y in forma)
        righe.append({
            "coordinate": stringa_coord,
            "label": labels[etichetta]
        })
    
    df = pd.DataFrame(righe, columns=["coordinate", "label"])
    

    
    df.to_csv(filename, index=False)
    print(f"[INFO]: Dataset esportato con successo in '{filename}' con {len(df)} righe.")

def importa_dataset(filename, labels):
    df = pd.read_csv(filename)

    y = []
    X = []
    for _, row in df.iterrows():
        label = row['label']
        raw_coords = row['coordinate']

        print(raw_coords)
    
        # Lista di tuple (x, y)
        points = [tuple(map(float, point.split(','))) for point in raw_coords.split(';')]
        X.append(points)
        
        y.append(labels[label])
    
    return np.array(X), np.array(y)

def esporta_piatto():


    # Supponiamo che il tuo array si chiami `shapes`
    shapes = np.array([...])  # il tuo array appiattito

    with open("forme.csv", "w", newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["coordinate"])  # intestazione facoltativa

        for shape in shapes:
            # forma la stringa "x1,y1;x2,y2;..." per ogni riga
            coord_string = ";".join(f"{x:.6f},{y:.6f}" for x, y in shape.reshape(-1, 2))
            writer.writerow([coord_string])


def calcola_statistiche_centroide(distanze):
    """
    Calcola per ciascuna forma, la media, deviazione standard e massimo e minimo delle distanze.
    
    Parametri:
        distanze (np.ndarray): Array di shape, per ogni forma il relativo array delle distanze dal centroide
    
    Restituisce:
        stats (np.ndarray): Array di shape
    """
    
    print(distanze)
    
    mean = np.mean(distanze, axis=1).reshape(-1 ,1)
    std = np.std(distanze, axis=1).reshape(-1 ,1)
    M = np.max(distanze, axis=1).reshape(-1 ,1)
    m = np.min(distanze, axis=1).reshape(-1 ,1)
    
    
    print(mean, "\n")
    print(std, "\n")
    print(M, "\n")
    print(m, "\n")
    
    stats = np.hstack([mean, std, M, m])
    
    print(stats)

def bounding_box(X):
    """
    Calcola la bounding box di una forma 2D.

    Parametri:
    - X: array di forma (n_punti, 2), contenente coordinate x, y

    Ritorna:
    - aspect_ratio: rapporto larghezza/altezza
    """
    
    bb = []
    for xi in X:
        min_x = np.min(xi[:, 0])
        max_x = np.max(xi[:, 0])
        min_y = np.min(xi[:, 1])
        max_y = np.max(xi[:, 1])
    
        width = max_x - min_x
        height = max_y - min_y
        aspect_ratio = width / height if height != 0 else 0
        bb.append(aspect_ratio)

    return np.array(bb)

# labels_idx = {'ellisse': 0, 'rettangolo': 1, 'segmento': 2, 'croce': 3}
# labels = ['ellisse', 'rettangolo', 'segmento', 'croce']
# y = np.array([0, 1, 1, 2, 3])

# current_file_path = os.path.abspath(__file__)
# dir_path = os.path.dirname(current_file_path)
# filename = os.path.join(dir_path, "data.csv")

# esporta_dataset(filename, X, y, labels)
# X_i, y = importa_dataset(filename, labels_idx)

# print(X_i)
# print(y)

# print(X)


# esporta_piatto(os.path.join(dir_path, "data_piatto.csv"))

distanze = np.linalg.norm(X[:, -1] - X[:, 0], axis=1)
print(distanze)
aspect_ratio = bounding_box(X)
print(aspect_ratio)

# dX = calcola_distanza_centroide(X)

# stats = calcola_statistiche_centroide(dX)

# X_f = np.array([list(x.flatten()) for x in X])
# X_f = np.hstack([X_f, dX])




# aree = calcola_aree(square)
# areeC = calcola_area_convessa(square)
# rapporto = aree / areeC
# perimetro = calcola_perimetro(square)

# print("Aree: ", aree)
# print("Aree Convesse:", areeC)
# print("Rapporto: ", rapporto)
# print("Perimetro: ", perimetro)

# print("[INFO]: Array di forme originario:")
# for xi in X:
#     print(xi)
# print("---")
# print("[INFO]: Array di forme con distanze centroide:")
# for xi in X_f:
#     print(xi)
# print("---")
# print("[INFO]: Array distanze centroide")
# for xi in dX:
#     print(xi)
