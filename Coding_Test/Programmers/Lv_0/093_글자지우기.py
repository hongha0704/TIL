def solution(my_string, indices):
    indices.sort()
    answer = my_string[:indices[0]]
    temp = indices[0]
    
    for i in range(1, len(indices)):
        answer += my_string[temp+1:indices[i]]
        temp = indices[i]
    
    answer += my_string[temp+1:]
    return answer

print(solution("apporoograpemmemprs", [1, 16, 6, 15, 0, 10, 11, 3]))