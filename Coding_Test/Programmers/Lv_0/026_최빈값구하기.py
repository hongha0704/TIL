def solution(array):
    max_count = max([array.count(i) for i in array])
    max_list = [i for i in array if array.count(i) == max_count]
    for i in range(1, len(max_list)):
        if max_list[0] != max_list[i]:
            return -1
    return max_list[0]