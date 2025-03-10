def solution(quiz):
    answer = []
    for q in quiz:
        n_list = q.split()
        if n_list[1] == '+':
            if int(n_list[0]) + int(n_list[2]) == int(n_list[4]):
                answer.append("O")
            else:
                answer.append("X")
        elif n_list[1] == '-':
            if int(n_list[0]) - int(n_list[2]) == int(n_list[4]):
                answer.append("O")
            else:
                answer.append("X")
    return answer