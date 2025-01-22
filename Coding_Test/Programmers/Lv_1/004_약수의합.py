# 시간 효율 감소소
def solution(n):
    answer = 0
    for i in range(1, n+1):
        for j in range(1, n+1):
            if i * j == n:
                answer += i
                break
    return answer

# 시간 효율 증가가
def solution(n):
    return sum([i for i in range(1, n+1) if n % i == 0])