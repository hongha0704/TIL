def solution(arr, queries):
    for q in queries:
        arr[q[0]], arr[q[1]] = arr[q[1]], arr[q[0]]
    return arr

solution([0, 1, 2, 3, 4], [[0, 3],[1, 2],[1, 4]])