import os

# Versione 1

def analizza_test(path):
    data = {}
    if os.path.isdir(path):
        os.chdir(path)
        folder = os.listdir()
        for fileName in folder:
            if os.path.isfile(fileName) and fileName.split('.')[-1] == 'txt':
                file = open(os.path.join(path,fileName))
                for row in file:
                    email, voto = row.split(';')
                    voto = int(voto)
                    data[email] = data.get(email, [])
                    data[email].append(voto)
                file.close()
    return data                    

# Versione 2

def analizza_test_voto(path):
    voti = {i: 0 for i in range(6)}
    voti.update({6: 0.3, 7: 0.4, 8: 0.6, 9: 1, 10: 1.5})
    data = {}
    if os.path.isdir(path):
        os.chdir(path)
        folder = os.listdir()
        for fileName in folder:
            if os.path.isfile(fileName) and fileName.split('.')[-1] == 'txt':
                file = open(fileName)
                for row in file:
                    email, punto = row.split(';')
                    punto = int(punto)
                    for voto in voti:
                        if punto == voto:
                            punto = voti[voto]
                    data[email] = data.get(email, [])
                    data[email].append(punto)
                file.close()
    
    for key in data:
        data[key] = sum(data[key])
    return data

# Versione 3

def analizza_test_voto_get(path):
    mappa_voti = {6: 0.3, 7: 0.4, 8: 0.6, 9: 1, 10: 1.5}
    data = {}
    if os.path.isdir(path):
        os.chdir(path)
        folder = os.listdir()
        for fileName in folder:
            if os.path.isfile(fileName) and fileName.split('.')[-1] == 'txt':
                file = open(fileName)
                for row in file:
                    email, punto = row.split(';')
                    punto = int(punto)
                    data[email] = data.get(email, 0) + mappa_voti.get(punto, 0)
                file.close()
    
    return data



               
path = os.path.join(os.getcwd(), 'voti')
data = analizza_test_voto_get(path)
for keys in data.keys():
    print(keys, ': ', data.get(keys))