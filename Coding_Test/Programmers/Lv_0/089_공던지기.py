def solution(numbers, k):
    answer = (1 + (k-1) * 2) % len(numbers)
    return numbers[-1] if answer == 0 else answer