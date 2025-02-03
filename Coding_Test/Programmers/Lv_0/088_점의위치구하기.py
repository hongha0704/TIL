def solution(dot):
    if dot[1] > 0:
        if dot[0] > 0:
            answer = 1
        else:
            answer = 2
    else:
        if dot[0] < 0:
            answer = 3
        else:
            answer = 4
    return answer