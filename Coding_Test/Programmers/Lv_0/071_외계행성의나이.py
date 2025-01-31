def solution(age):
    alpha = "abcdefghij"
    return "".join(alpha[int(i)] for i in str(age))