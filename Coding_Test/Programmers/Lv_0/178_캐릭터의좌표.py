def solution(keyinput, board):
    p = [0, 0]
    for k in keyinput:
        if k == "left":
            if p[0]-1 >= -(board[0]/2):
                p[0] -= 1
        elif k == "right":
            if p[0]+1 <= board[0]/2:
                p[0] += 1
        elif k == "down":
            if p[1]-1 >= -(board[1]/2):
                p[1] -= 1
        elif k == "up":
            if p[1]+1 <= board[1]/2:
                p[1] += 1
    return p