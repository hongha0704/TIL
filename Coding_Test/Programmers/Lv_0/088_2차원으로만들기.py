def solution(num_list, n):
    temp = []
    answer = []
    for i in num_list:
        if len(temp) == n:
            answer.append(temp)
            temp = []
        temp.append(i)
    answer.append(temp)
    return answer