def solution(arr, queries):
    answer = []
    for s, e, k in queries:
        a = []
        for i in range(s, e+1):
            if arr[i] > k:
                a.append(arr[i])
        if a == []:
            answer.append(-1)
        else:
            answer.append(min(a))
    return answer

print(solution([0, 1, 2, 4, 3], [[0, 4, 2],[0, 3, 2],[0, 2, 2]]))