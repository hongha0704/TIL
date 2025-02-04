def solution(num_list):
    mul = 1
    for i in num_list:
        mul *= i
    sum_square = sum(num_list) ** 2
    
    return 1 if mul < sum_square else 0