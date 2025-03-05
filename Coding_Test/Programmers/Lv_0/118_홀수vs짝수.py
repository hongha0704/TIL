def solution(num_list):
    even = sum(num_list[1::2])
    odd = sum(num_list[::2])
    return even if even > odd else odd