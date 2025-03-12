def solution(myStr):
    answer = []
    Str = ''
    for i in myStr:
        if i not in 'abc':
            Str += i
        else:
            if Str:
                answer.append(Str)
            Str = ''
    answer.append(Str)
    return answer if answer[0] else ["EMPTY"]