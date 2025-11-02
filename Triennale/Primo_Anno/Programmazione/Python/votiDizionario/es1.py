def f(list_string):
    '''
    Si scriva una funzione che prenda in input una lista di stringhe a e restituisca
    un dizionario che abbia per chiavi le iniziali delle stringhe in a
    e ad ogni chiave k associ come valore la lista di stringhe in a che cominciano con k
    '''
    output = {} # O(1)
    for string in list_string: # O(len(list_string))
        if string == '':
            continue # O(1)
        k = string[0] # O(1)
        if k in output:  # O(1)
                output[k].append(string) # O(1) lettura del dizionario + O(1)
        else:
            output[k] = [string] # O(1) costo per creare la lista + O(1) per scrittura del dizionario
    return output
    # costo computazionale: O(len(list_string))
a = ['python', '', 'codice', 'codice']
print(f(a))