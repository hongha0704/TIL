def solution(my_string):
    for n in 'aeiou':
        my_string = my_string.replace(n, '')
    return my_string