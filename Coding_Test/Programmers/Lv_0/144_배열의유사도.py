def solution(s1, s2):
    count = 0
    for s in s1:
        if s in s2:
            count += 1
    return count