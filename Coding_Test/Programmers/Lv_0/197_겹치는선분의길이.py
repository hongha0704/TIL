def solution(lines):
    answer = 0
    l0 = [i+0.5 for i in range(lines[0][0], lines[0][1])]
    l1 = [i+0.5 for i in range(lines[1][0], lines[1][1])]
    l2 = [i+0.5 for i in range(lines[2][0], lines[2][1])]
    minimum = min([i[0]+0.5 for i in lines])
    maximum = max([i[1]+0.5 for i in lines])
    
    i = minimum
    while i < maximum:
        if (i in l0 and i in l1 and i in l2):
            answer += 1
        elif (i in l0 and i in l1) or (i in l0 and i in l2) or (i in l1 and i in l2):
            answer += 1
        i += 1
    return answer