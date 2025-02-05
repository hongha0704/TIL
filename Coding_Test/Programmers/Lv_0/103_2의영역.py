def solution(arr):
    if 2 not in arr:
        return [-1]
    for i in range(len(arr)):
        if arr[i] == 2:
            a = i
            break
    for i in range(len(arr)-1, 0, -1):
        if arr[i] == 2:
            b = i
            break
    return arr[a:b+1]