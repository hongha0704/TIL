def solution(my_string):
    sum = 0
    num = ''
    for i in my_string:
        if i.isnumeric():
            num += i
        else:
            if num:
                sum += int(num)
            num = ''
    if num:
        sum += int(num)
    return sum