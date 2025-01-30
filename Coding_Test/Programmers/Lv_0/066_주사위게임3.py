def solution(a, b, c, d):
    if a == b == c == d:
        answer = 1111 * a
        
    elif a == b == c != d:
        answer = (10 * a + d) ** 2
    elif d == a == b != c:
        answer = (10 * a + c) ** 2
    elif c == d == a != b:
        answer = (10 * a + b) ** 2
    elif b == c == d != a:
        answer = (10 * d + a) ** 2
    
    elif a == b != c == d:
        answer = (a + c) * abs(a - c)
    elif a == c != b == d:
        answer = (a + b) * abs(a - b)
    elif a == d != c == b:
        answer = (a + c) * abs(a - c)
    
    elif (a == b != c != d) and (a != d):
        answer = c * d
    elif (a == c != b != d) and (a != d):
        answer = b * d
    elif (a == d != c != b) and (a != b):
        answer = c * b
    elif (b == c != a != d) and (b != d):
        answer = a * d
    elif (b == d != a != c) and (b != c):
        answer = a * c
    elif (c == d != a != b) and (c != b):
        answer = a * b
        
    elif (a != b != c != d) and (a != c) and (b != d) and (a != d):
        answer = min(a, b, c, d)
        
    return answer