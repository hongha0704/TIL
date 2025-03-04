def solution(s):
    num_list = s.split(' ')
    print(num_list)
    answer = 0
    for i, n in enumerate(num_list):
        if n == "Z":
            answer -= int(num_list[i-1])
        else:
            answer += int(n)
    return answer