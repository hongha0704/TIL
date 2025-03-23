def solution(rank, attendance):
    a, b, c = -1, -1, -1
    
    for i in range(1, len(rank)+1):
        if attendance[rank.index(i)]:
            if a == -1:
                a = rank.index(i)
            elif b == -1:
                b = rank.index(i)
            elif c == -1:
                c = rank.index(i)
                break
    print(a, b, c)
    return 10000*a + 100*b + c
            