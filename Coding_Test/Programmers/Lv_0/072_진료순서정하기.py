def solution(emergency):
    answer = [0 for i in range(len(emergency))]
    for i in range(len(emergency)):
        answer[emergency.index(sorted(emergency, reverse=True)[i])] = i+1
    return answer