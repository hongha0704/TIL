def solution(arr, k):
    answer = []
    for idx, num in enumerate(arr):
        if num not in answer:
            answer.append(num)
        if len(answer) == k:
            break
    if len(answer) < k:
        for _ in range(k - len(answer)):
            answer.append(-1)
    return answer