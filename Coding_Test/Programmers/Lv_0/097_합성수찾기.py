def solution(n):
    count = 0
    answer = 0
    
    for i in range(1, n+1):
        for j in range(1, i+1):
            if i % j == 0:
                count += 1
            if count >= 3:
                answer += 1
                break
        count = 0
    return answer