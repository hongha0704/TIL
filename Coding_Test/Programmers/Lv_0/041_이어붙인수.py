def solution(num_list):
    return int("".join([str(i) for i in num_list if i % 2])) + int("".join([str(i) for i in num_list if i % 2 == 0]))

print(solution([5, 7, 8, 3]))