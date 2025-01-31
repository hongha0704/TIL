def solution(my_string, is_suffix):
    for i in range(len(my_string)):
        if is_suffix == my_string[i:]:
            return 1
    return 0

# def solution(m, s):
#     if m[-len(s):]==s: return 1
#     return 0

print(solution("banana", "ana"))