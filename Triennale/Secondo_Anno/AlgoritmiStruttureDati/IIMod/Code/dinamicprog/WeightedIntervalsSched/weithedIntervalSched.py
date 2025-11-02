# Classe Job, ciascun job ha un tempo di inizio, di fine e un peso
class Job:
    def __init__(self, start, finish, weight: int) -> None:
        self.start = start
        self.finish = finish
        self.weight = weight

    def is_compatible(self, job) -> bool:
        return self.start >= job.finish

    def to_string(self) -> None:
        return f"(s: {self.start}, f: {self.finish}, w: {self.weight})"

def print_intervals(intervals: list[Job]) -> None:
    n = len(intervals)
    for j in range(n - 1):
        print(intervals[j].to_string(), end=", ")
    print(intervals[n - 1].to_string())

def binary_search(arr: list[Job], job_index: int, s, f: int) -> int:
    if s > f:
        return -1

    m = (s + f) // 2
    if arr[job_index].is_compatible(arr[m]): # if arr[m].finish <= arr[job_index].start
        next_index = binary_search(arr, job_index, m + 1, f)
        return m if next_index == -1 else next_index
    else:
        return binary_search(arr, job_index, s, m - 1)

def compute_p(arr: list[Job]) -> list[int]:
    # p[j] = l'indice più grande i tale che: i < j e tale che il job i è compatibile con il job j 
    p = []
    n = len(arr)
    for i in range(n):
        j = binary_search(arr, i, 0, i - 1)
        p.append(j)
    return p

def compute_opt(intervals: list[Job], p: list[int]) -> tuple[list[int]]:
    n = len(intervals)
    OPT = [0] * n

    OPT[0] = intervals[0].weight
    for i in range(1, n):
        OPT[i] = max(OPT[i - 1], intervals[i].weight + (OPT[p[i]] if p[i] != -1 else 0))

    return OPT

def find_solution(OPT: list[int], p: list[int], intervals: list[Job]) -> list[list[int, Job]]:
    n = len(intervals)
    sol = []
    i = n - 1
    while i >= 0:
        if intervals[i].weight + (OPT[p[i]] if p[i] != -1 else 0) > OPT[i - 1]:
            sol.append([i, intervals[i]])
            i = p[i]
        else:
            i -= 1
    sol.reverse()
    return sol

def weighted_intervals_sched(intervals: list[Job]) -> tuple[list[int], list[Job], list[int]]:

    intervals = sorted(intervals, key=lambda x: x.finish)

    p = compute_p(intervals)
    
    OPT = compute_opt(intervals, p)
    SOL = find_solution(OPT, p, intervals)
    
    indexes = []
    sol = []
    for i in SOL:
        indexes.append(i[0])
        sol.append(i[1])
    
    return OPT, sol, indexes

# Test with predefined intervals
intervals = [
    Job(1, 4, 1),
    Job(4, 7, 4),
    Job(3, 5, 2),
    Job(4, 11, 8),
    Job(5, 9, 6),
    Job(3, 8, 5),
    Job(0, 6, 3),
    Job(6, 10, 7)
]

OPT, SOL, indx = weighted_intervals_sched(intervals)
print("[INFO]: Il valore della soluzione ottima è:", OPT[-1])
print("[INFO]: La soluzione ottima è:", indx)
print("[INFO]: Gli intervalli nella soluzione ottima sono:", end=" ")
print_intervals(SOL)
