def solution(dots):
    answer = 0
    for a, b, c, d in [[0, 1, 2, 3], [0, 2, 1, 3], [0, 3, 1, 2]]:
        dxdy1 = (dots[a][1] - dots[b][1]) / (dots[a][0] - dots[b][0])
        dxdy2 = (dots[c][1] - dots[d][1]) / (dots[c][0] - dots[d][0])
        if dxdy1 == dxdy2:
            answer = 1
    return answer