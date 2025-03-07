def solution(arr1, arr2):
    answer = []
    answer_row = []
    for i, row in enumerate(arr1):
        for j, col in enumerate(row):
            answer_row.append(arr1[i][j]+arr2[i][j])
        answer.append(answer_row)
        answer_row = []
    return answer