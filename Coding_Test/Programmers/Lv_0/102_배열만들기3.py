def solution(arr, intervals):
    a, b = intervals
    answer = arr[a[0]:a[1]+1]
    answer.extend(arr[b[0]:b[1]+1])
    return answer