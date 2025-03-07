def solution(my_string):
    num_list = my_string.split()
    answer = int(num_list[0])
    print(num_list)
    for i, n in enumerate(num_list):
        if n == '+':
            answer += int(num_list[i+1])
        elif n == '-':
            answer -= int(num_list[i+1])
    return answer