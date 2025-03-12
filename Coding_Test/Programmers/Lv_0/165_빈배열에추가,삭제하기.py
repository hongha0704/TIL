def solution(arr, flag):
    answer = []
    for idx, num in enumerate(arr):
        if flag[idx]:
            for _ in range(num*2):
                answer.append(num)
        else:
            for _ in range(num):
                answer.pop()
    return answer