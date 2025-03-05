def solution(array, n):
    array.sort()
    sub = [abs(n-i) for i in array]
    return array[sub.index(min(sub))]