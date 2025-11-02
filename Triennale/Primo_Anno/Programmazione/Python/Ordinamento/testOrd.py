from mergeSort import *
from bubbleSort import *
import random
import matplotlib.pyplot as plt


def randomList(f=0, to=500, step=100):
    a = []
    lenght = random.randint(0, 1000)
    for i in range(lenght):
        a.append(int(random.randint(0, 10000)))
    return a

def compare(list_input):
    m = list_input[:]
    b = list_input[:]
    mSteps = mergeSort(m)
    b, bSteps = BubbleSort(b, inplace=False)
    return {'Merge': mSteps, 'Bubble': bSteps}

def mediaSteps(filePath):
    file = open(filePath)
    bubbleData, mergeData, media = {}, {}, {}
    row = file.readline()
    while row != '':
        LEN, BUBBLE, MERGE = row.split(',')
        bubbleData[LEN] = bubbleData.get(LEN, [])
        bubbleData[LEN].append(int(BUBBLE))
        mergeData[LEN] = mergeData.get(LEN, [])
        mergeData[LEN].append(int(MERGE))
        row = file.readline()
    file.close()
    for key in bubbleData.keys():
        media[key] = sum(bubbleData[key])/len(bubbleData[key]), sum(mergeData[key])/len(mergeData[key])
    return media

def insertCSV(list_input, filePath):
    data = compare(list_input)
    file = open(filePath, 'a')
    line = f"{len(list_input)},{data['Bubble']},{data['Merge']}\n"
    file.write(line)
    file.close()
    m = mediaSteps(filePath)
    return m

def graph():    
    input_list = randomList()
    media = insertCSV(input_list, 'dataOrd.csv')
    values = list(zip(*media.values()))
    X = media.keys()
    YB, YM = values
    plt.plot(X, YB, label = 'Bubble-Sort')
    plt.plot(X, YM, label = 'Merge-Sort')
    plt.legend()
    plt.xlabel('Dimensione Lista')
    plt.ylabel('Numero Confronti')
    plt.show()

graph()