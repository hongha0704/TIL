def solution(n, m):
    n_min, n_max = min(n, m), max(n, m)
    while n_max:
        n_min, n_max = n_max, n_min % n_max
    a = n_min
    b = (min(n, m) * max(n, m) // a)
    return [a, b]