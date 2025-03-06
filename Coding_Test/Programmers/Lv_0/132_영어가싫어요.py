def solution(numbers):
    answer = ''
    while numbers:
        if numbers[:4] == 'zero':
            numbers = numbers[4:]
            answer += '0'
        elif numbers[:3] == 'one':
            numbers = numbers[3:]
            answer += '1'
        elif numbers[:3] == 'two':
            numbers = numbers[3:]
            answer += '2'
        elif numbers[:5] == 'three':
            numbers = numbers[5:]
            answer += '3'
        elif numbers[:4] == 'four':
            numbers = numbers[4:]
            answer += '4'
        elif numbers[:4] == 'five':
            numbers = numbers[4:]
            answer += '5'
        elif numbers[:3] == 'six':
            numbers = numbers[3:]
            answer += '6'
        elif numbers[:5] == 'seven':
            numbers = numbers[5:]
            answer += '7'
        elif numbers[:5] == 'eight':
            numbers = numbers[5:]
            answer += '8'
        elif numbers[:4] == 'nine':
            numbers = numbers[4:]
            answer += '9'
            
    return int(answer)