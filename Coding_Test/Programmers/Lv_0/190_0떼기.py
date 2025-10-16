def solution(n_str):
    i = 0
    while not int(n_str[i]):
        i += 1
    return n_str[i:]