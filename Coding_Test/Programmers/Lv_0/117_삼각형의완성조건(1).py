def solution(sides):
    max_len = max(sides)
    sides.remove(max_len)
    if sum(sides) > max_len:
        return 1
    else:
        return 2