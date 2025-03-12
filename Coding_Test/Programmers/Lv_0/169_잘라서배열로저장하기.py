def solution(my_str, n):
    return [my_str[i:i+n] if i+n < len(my_str) else my_str[i:] for i in range(0, len(my_str), n)]