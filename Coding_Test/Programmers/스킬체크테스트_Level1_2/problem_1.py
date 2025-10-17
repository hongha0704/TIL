def solution(n):
    answer = ""
    result = 0
    
    # 3진법으로 변환
    count = 0
    while n >= 3**(count+1):
        count += 1
        
    for i in range(count, -1, -1):
        answer += str(n // 3**i)
        n -= 3**i * (n // 3**i)
        
    # 10진법으로 변환
    for idx, num in enumerate(answer):
        result += int(num) * 3**idx
        
    return result