def solution(arr):
    arr_before = arr.copy()
    arr_list = []
    x = 0
    while True:
        for i in arr_before:
            if i >= 50 and not i % 2:
                arr_list.append(i//2)
            elif i < 50 and i % 2:
                arr_list.append(i*2+1)
            else:
                arr_list.append(i)
                
        if arr_before == arr_list:
            return x
        
        x += 1
        arr_before = arr_list.copy()
        arr_list = []