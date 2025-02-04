def solution(my_string, queries):
    for s, e in queries:
        inverse = my_string[s:e+1]
        my_string = my_string[:s] + inverse[::-1] + my_string[e+1:]        
    return my_string

print(solution("rermgorpsam", [[2, 3], [0, 7], [5, 9], [6, 10]]))