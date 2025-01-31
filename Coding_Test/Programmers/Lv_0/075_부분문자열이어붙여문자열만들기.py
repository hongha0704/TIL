def solution(my_strings, parts):
    answer = ""
    for i, s in zip(my_strings, parts):
        answer += i[s[0]:s[1]+1]
    return answer

print(solution(["progressive", "hamburger", "hammer", "ahocorasick"],
               [[0, 4], [1, 2], [3, 5], [7, 7]]	))