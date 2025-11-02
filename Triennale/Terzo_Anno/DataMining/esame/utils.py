import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from IPython.display import display
from sklearn.metrics import ConfusionMatrixDisplay

def plot_shape(X: np.ndarray, y: np.ndarray, labels: list[str]):
    """
    Mostra una shape rappresentativa per ciascuna classe presente in y.

    Args:
        X (list of np.ndarray): lista di array (uno per forma) di shape (n_punti, 2)
        y (np.ndarray): array di interi con le etichette corrispondenti alle forme
        labels (list of str): nomi delle etichette per le forme
    """
    classi = np.unique(y)
    num_classi = len(classi)

    fig, axs = plt.subplots(1, num_classi, figsize=(4 * num_classi, 4))

    if num_classi == 1:
        axs = [axs]  # Assicura che axs sia sempre iterabile

    for i, etichetta in enumerate(classi):
        idx = np.where(y == etichetta)[0][0]  # Primo esempio con quell'etichetta
        shape = X[idx]
        ax = axs[i]

        ax.plot(shape[:, 0], shape[:, 1], color="C" + str(etichetta))
        ax.set_title(f"Classe {etichetta}: {labels[etichetta].capitalize()}")
        ax.set_xlabel("X")
        ax.set_ylabel("Y")
        ax.axis("equal")
        ax.grid(True)

    plt.tight_layout()
    plt.suptitle("Una forma per ciascuna classe", fontsize=16, y=1.05)
    plt.show()


def print_grid_search_results_table(name: str, grid, scoring: dict):
    """
    Stampa i risultati di una Grid Search (metriche di valutazione e parametri ottimali)
    in un formato tabellare più esteticamente gradevole.

    Args:
        name (str): Il nome del modello o dell'esperimento.
        grid: L'oggetto GridSearchCV o un oggetto simile con gli attributi
              'cv_results_' e 'best_index_'.
        scoring (dict): Un dizionario con i nomi delle metriche utilizzate per lo scoring.
    """
    print(f"\n--- Risultati per: {name} ---")

    metrics_data = []
    for metric in scoring.keys():
        mean = grid.cv_results_[f"mean_test_{metric}"][grid.best_index_]
        metrics_data.append({"Metrica": metric.capitalize(), "Valore Medio": f"{mean:.2%}"})

    metrics_df = pd.DataFrame(metrics_data)
    print("\n  Metriche di Valutazione:")
    display(metrics_df)

    params_data = []
    for param, value in grid.best_params_.items():
        params_data.append({"Parametro": param, "Valore Ottimale": value})

    params_df = pd.DataFrame(params_data)
    print("\n  Parametri Ottimali:")
    display(params_df)

    print("-----------------------------------\n")


def plot_confusion_matrices(
    best_models: dict,
    X_test_sets: dict,
    y_test_sets: dict,
    labels: list[str],
    title_suffix: str = "",
    figsize: tuple[int, int] = (12, 5),
    cmap: str = "Blues",
):
    """
    Genera e visualizza matrici di confusione per più modelli in un'unica figura.

    Args:
        best_models (dict): Un dizionario dove le chiavi sono i nomi dei modelli
                            (es. 'RF_Model_1') e i valori sono gli oggetti modello
                            addestrati (es. un'istanza di RandomForestClassifier).
        X_test_sets (dict): Un dizionario dove le chiavi sono gli stessi nomi dei modelli
                            e i valori sono i set di test delle feature (X_test)
                            corrispondenti.
        y_test_sets (dict): Un dizionario dove le chiavi sono gli stessi nomi dei modelli
                            e i valori sono i set di test delle etichette (y_test)
                            corrispondenti.
        labels (list[str]): Una lista di stringhe che rappresentano i nomi delle classi,
                             nell'ordine corretto delle etichette numeriche (es. [0, 1, 2]).
        title_suffix (str, optional): Un suffisso da aggiungere al titolo generale della figura.
                                      Utile per specificare il contesto (es. "Risultati Finali").
                                      Default è "".
        figsize (tuple[int, int], optional): La dimensione della figura (larghezza, altezza).
                                             Default è (12, 5).
        cmap (str, optional): La mappa colori da usare per le matrici di confusione.
                              Default è "Blues".
    """

    num_models = len(best_models)

    fig, axes = plt.subplots(1, num_models, figsize=figsize)

    if num_models == 1:
        axes = np.array([axes])

    display_labels_capitalized = [label.capitalize() for label in labels]

    for ax, name in zip(axes.flatten(), best_models.keys()):
        ax.set_xticks([])
        ax.set_yticks([])
        ax.grid(False)
          
        y_test_set = y_test_sets[name]
        y_pred = best_models[name].predict(X_test_sets[name])

        ConfusionMatrixDisplay.from_predictions(
            y_test_set, y_pred, display_labels=display_labels_capitalized, cmap=cmap, ax=ax
        )
        ax.set_title(f"{name}")

    plt.subplots_adjust(
        wspace=0.4, left=0.05, right=0.95, top=0.9
    )  # Aggiusto margini per titolo principale

    # Aggiungi un titolo generale alla figura, se specificato
    if title_suffix:
        plt.suptitle(
            f"Matrici di Confusione {title_suffix}", fontsize=16, y=0.98
        )  # y=0.98 per posizionamento sopra i subplot

    plt.show()

def print_risultati(results_sel, results_pca):
    print("[INFO]: Risultati modello feature selection:\n")

    for keys, values in results_sel.items():
        print("Tipo di dataset:", keys)
        for val in values:
            print(val["accuracy"], val["parametri"])

    print("\n---------------------------------------------\n")

    print("\n[INFO]: Risultati modello PCA:\n")
    for keys, values in results_pca.items():
        print("Tipo di dataset:", keys)
        for val in values:
            print(val["accuracy"], val["parametri"])

def plot_test_results(variazione, results, title, ax=None):
    """
    Plotta l'andamento di più metriche (accuracy, precision, recall, f1)
    al variare di un parametro del dataset.

    Args:
        variazione (str): Nome del parametro variato ("punti", "forme", "rumore").
        results (dict): Dizionario dei risultati, con chiave uguale a variazione.
        titolo_modello (str): Titolo aggiuntivo per il grafico.
        ax (matplotlib.axes._subplots.AxesSubplot): Asse su cui disegnare il grafico (opzionale).
    """
    risultati = results[variazione]
    valori_x = [res["parametri"][variazione] for res in risultati]

    # Estrazione delle metriche
    metriche = {
        "Accuracy": [res["accuracy"] for res in risultati],
        "Precision": [res["precision"] for res in risultati],
    }

    if ax is None:
        fig, ax = plt.subplots()

    # Tracciamento di ciascuna metrica
    for nome_metrica, valori_y in metriche.items():
        ax.plot(valori_x, valori_y, marker="o", linestyle="-", label=nome_metrica)

    # Etichette asse X
    if variazione == "rumore":
        ax.set_xlabel("Livello di rumore")
    elif variazione == "punti":
        ax.set_xlabel("Numero di punti per forma")
    elif variazione == "forme":
        ax.set_xlabel("Numero di forme")
    else:
        ax.set_xlabel(variazione.capitalize())

    # Etichette e titolo
    ax.set_ylabel("Valore metrica")
    ax.set_title(f"Andamento metriche vs {variazione.capitalize()} ({title})")
    ax.grid(True)
    ax.legend()


def plot_figure(results, title):
    fig, axs = plt.subplots(1, 3, figsize=(18, 5))

    for i, var in enumerate(["punti", "forme", "rumore"]):
        plot_test_results(var, results=results, ax=axs[i], title=title)

    plt.tight_layout()
    plt.show()