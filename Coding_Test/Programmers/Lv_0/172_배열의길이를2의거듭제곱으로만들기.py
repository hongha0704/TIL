def solution(arr):
    i = 0
    while len(arr) > 2**i:
        i += 1
    if len(arr) != 2**i:
        for _ in range(2**i - len(arr)):
            arr.append(0)
    return arr