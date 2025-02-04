def solution(num_list):
    odd_num = 0
    even_num = 0
    for n in num_list:
        if n % 2:
            odd_num += 1
        else:
            even_num += 1
    return[even_num, odd_num]