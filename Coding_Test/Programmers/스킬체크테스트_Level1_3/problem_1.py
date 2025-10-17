def solution(sizes):
    answer = 0
    sizes_new = []
    
    for size in sizes:
        if size[0] >= size[1]:
            sizes_new.append([size[0], size[1]])
        else:
            sizes_new.append([size[1], size[0]])
            
    max_x = max([i[0] for i in sizes_new])
    max_y = max([i[1] for i in sizes_new])
    
    return max_x * max_y