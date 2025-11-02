people = [
    {"name": "John", "age": 25},
    {"name": "Alice", "age": 30},
    {"name": "Bob", "age": 20}
]
people.sort(key=lambda person: person['age'], reverse=True) 
#print(people)
a = sorted((2, 1, 6, 4, 11, 3))
#print(a)

m = [1, 2, 3, 4]
x, y, *z = m

def x(n):
    a = list(range(n))
    print(a)
    a.append(list(range(n, 2*n)))
    print(a)
    a+= list(range(2*n, 3*n))
    print(a)
    return a[n]*a[n+1]


def enigma(x):
    if x == '':
        return 1
    else:
        return 1 + enigma(x[1:])

a = [1, 'string', 3.5, 4, 'ciao', 6.6, -2, -1, 7, 8, 0, 'casa', 10]
print(a[:-1])


def c(x):
    if type(x) == type(0):
        return x
    else:
        return -1
    
a = sorted(a, key=c)
print(a)