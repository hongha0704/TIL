def solution(my_string):
    answer = [0 for i in range(52)]
    for i in my_string:
        if ord(i) >= 97:
            index = ord(i) - 71
        else:
            index = ord(i) - 65
        answer[index] += 1
    return answer

print(solution("Programmers"))