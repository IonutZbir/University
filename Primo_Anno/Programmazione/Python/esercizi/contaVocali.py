str = input('Digita una stringa: ')


def contaVocaliBase(str):
    numVoc, i = 0, 0
    vocali = 'aeiouAeiou'

    while i < len(str):
        if str[i] in vocali:
            numVoc += 1
        i += 1
    return numVoc

def contaVocaliPari(str):
    numVoc, i = 0, 0
    vocali = 'aeiouAeiou'

    while i < len(str):
        if i % 2 == 0 and str[i] in vocali:
            numVoc += 1
        i += 1
    return numVoc

def contaVocaliFor(str):
    numVoc = 0
    vocali = 'aeiouAeiou'

    for i in str:
        if i in vocali:
            numVoc += 1
    return numVoc

def contaVocaliRircosiva(str, numVoc):
    vocali = 'aeiouAeiou'
    if len(str) < 1:
        return numVoc
    if str[0] in vocali:
        numVoc += 1
    return contaVocaliRircosiva(str[1: ], numVoc)



print('Il numero di vocali è: ', contaVocaliRircosiva(str, 0))
