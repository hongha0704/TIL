def solution(n):
    x = 1
    while x ** 2 <= n:
        if x ** 2 == n:
            return (x+1) ** 2
        x += 1
    return -1

##################################3

def solution(n):
    sqrt = n ** (1/2)
    if sqrt % 1 == 0:
        return (sqrt+1) ** 2
    return -1