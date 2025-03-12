def solution(array):
    return sum([1 for num in array for n in str(num) if n == '7'])