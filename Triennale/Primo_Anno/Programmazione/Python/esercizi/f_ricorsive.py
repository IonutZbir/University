import os
from colorama import Fore
from colorama import Style


def max_list_ric(l):
    if len(l) == 1:
        return l[0]
    else:
        l[1] = l[0] if l[0] > l[1] else l[1]
        return max_list_ric(l[1:])


def max_list_ric2(l):
    if len(l) == 1:
        return l[0]
    else:
        m = max_list_ric(l[1:])
        if l[0] > m:
            return l[0]
        else:
            return m


def count_int(l: list[int]):
    """Conta gli interi contenenti in un lista e nelle sottoliste usando la ricorsione
    [1, [0, 1], 2]
    Args:
        l (list): list of integers or list of lists with integers
    """

    if l == []:
        return 0
    if type(l[0]) in (int, float, bool, str, type(None)):
        return 1 + count_int(l[1:])
    elif type(l[0]) == list:
        return 0 + count_int(l[0]) + count_int(l[1:])


def deep_clone(l):
    b = []
    for x in l:
        if type(x) == list:
            b.append(deep_clone(x))
        else:
            b.append(x)
    return b


def explore(dir):
    content = os.listdir(dir)
    output = ""
    for c in content:
        full_path = os.path.join(dir, c)
        if os.path.isfile(full_path):
            output += f"{Fore.BLUE}FILE:{Style.RESET_ALL} {full_path}\n"
        elif os.path.isdir(full_path):
            output += f"{Fore.RED}DIR :{Style.RESET_ALL} {full_path}\n"
    return output


def explore_dir(dir):
    content = os.listdir(dir)
    output = ""
    for c in content:
        full_path = os.path.join(dir, c)
        if os.path.isfile(full_path):
            output += f"{Fore.BLUE}FILE:{Style.RESET_ALL} {full_path}\n"
        elif os.path.isdir(full_path):
            output += explore_dir(full_path)
    return output


def find_file(dir, extension="txt"):
    content = os.listdir(dir)
    output = []
    for c in content:
        full_path = os.path.join(dir, c)
        if os.path.isfile(full_path) and type(c) == str and c.endswith(extension):
            output.append(full_path)
        elif os.path.isdir(full_path):
            output.extend(find_file(full_path, extension))
    return output

# def check(arr: list, m: list[list], n: int) -> str:
#     scorrere una matrice per diagonali
#     k = 0
#     for i in range(n):
#         for j in range(i + 1):
#             if arr[k] != m[i - j][j]:
#                 return "NO"
#             k += 1
            
#     for i in range(1, n):
#         for j in range(n - i):
#             if arr[k] != m[n - 1 - j][i + j]:
#                 return "NO"
#             k += 1
    
#     return "YES"

x = find_file("D:\\Università\\Programmazione", "py")
