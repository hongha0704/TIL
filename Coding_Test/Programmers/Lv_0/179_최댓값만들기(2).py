def solution(numbers):
    n = sorted(numbers)
    return max(n[0]*n[1], n[-1]*n[-2])