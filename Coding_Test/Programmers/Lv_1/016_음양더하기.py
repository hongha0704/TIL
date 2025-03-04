def solution(absolutes, signs):
    answer = 0
    for i, n in enumerate(absolutes):
        if signs[i]:
            answer += n
        else:
            answer -= n
    return answer