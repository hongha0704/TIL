def solution(s):
    answer = ''
    for idx, string in enumerate(s):
        if string not in s[:idx]+s[idx+1:]:
            answer += string
    return ''.join(sorted(answer))