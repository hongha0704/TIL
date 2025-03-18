def solution(strArr):
    count = [0 for _ in range(30)]
    for s in strArr:
        count[len(s)-1] += 1
    return max(count)