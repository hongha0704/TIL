def solution(code):
    answer = ''
    mode = 0
    for idx in range(len(code)):
        if code[idx] == "1":
            mode = (mode + 1) % 2
            continue
        if mode == 0:
            if idx % 2 == 0:
                answer += code[idx]
        else:
            if idx % 2:
                answer += code[idx]
    return answer if answer else "EMPTY"

print(solution("abc1abc1abc")) # acbac