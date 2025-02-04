def solution(box, n):
    a = max(range(0,box[0]+1,n)) / n
    b = max(range(0,box[1]+1,n)) / n
    c = max(range(0,box[2]+1,n)) / n
    return a*b*c