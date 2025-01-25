def solution(a, b):
    sum1 = int(str(a) + str(b))
    sum2 = int(str(b) + str(a))
    return sum1 if sum1 > sum2 else sum2

# ==========

def solution(a, b):
    return max(int(str(a) + str(b)), int(str(b) + str(a)))