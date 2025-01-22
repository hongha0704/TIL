def solution(name, yearning, photo):
    answer = []
    for p in photo:
        score = 0
        for people in p:
            if people in name:
                index = name.index(people)
                score += yearning[index]
        answer.append(score)
    return answer

name= ["may", "kein", "kain", "radi"]
yearning = [5, 10, 1, 3]
photo = [["may", "kein", "kain", "radi"],["may", "kein", "brin", "deny"], ["kon", "kain", "may", "coni"]]

print(solution(name, yearning, photo))
# result: [19, 15, 6]