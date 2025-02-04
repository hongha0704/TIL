def solution(a, d, included):
    sum_list = []
    for i in range(len(included)):
        sum_list.append(a + d * i)
    return sum([sum_list[i] for i in range(len(included)) if included[i]])