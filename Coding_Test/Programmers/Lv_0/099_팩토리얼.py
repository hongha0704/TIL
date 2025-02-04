def solution(n):
    num = 1
    answer = 1
    
    while num <= n:
        answer += 1
        num = num * answer
        
    return answer - 1