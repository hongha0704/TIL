def solution(a, b):
    a_list = {i for i in range(1, a+1) if a % i == 0}
    b_list = {i for i in range(1, b+1) if b % i == 0}
    maximum = max(a_list & b_list)
    b_new = b // maximum

    list_2_5 = []
    
    for i in range(10):
        for j in range(5):
            x = 2**i * 5**j
            if x > 1000:
                break
            list_2_5.append(x)
    list_2_5.sort()
    
    for i in range(1, b_new+1):
        if i in list_2_5:
            continue
        if not b_new%i:
            return 2
    return 1