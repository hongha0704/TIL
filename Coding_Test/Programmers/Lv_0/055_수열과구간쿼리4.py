def solution(arr, queries):
    for s, e, k in queries:
        for i in range(len(arr)):
            if s <= i <= e:
                if i % k == 0:
                    arr[i] += 1
    return arr