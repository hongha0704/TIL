def solution(l, r):
    answer = []
    i = 0
    while True:
        if int(bin(i)[2:])*5 > r:
            break
        if int(bin(i)[2:])*5 >= l:
            answer.append(int(bin(i)[2:])*5)
        i += 1
    if answer == []:
        answer = [-1]
    return answer

print(solution(5, 555))


