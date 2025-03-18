def solution(dots):
    x_min = min([i[0] for i in dots])
    y_min = min([i[1] for i in dots])
    x_max = max([i[0] for i in dots])
    y_max = max([i[1] for i in dots])
    return (x_max-x_min)*(y_max-y_min)