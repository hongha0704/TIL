def solution(board):
    n = len(board)
    x = [[True]*n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if board[i][j]:
                for ii in range(i-1, i+2):
                    for jj in range(j-1, j+2):
                        if (0 <= ii <= n-1) and (0 <= jj <=n-1):
                            x[ii][jj] = False
    return sum([1 for i in range(n) for j in range(n) if x[i][j]])
