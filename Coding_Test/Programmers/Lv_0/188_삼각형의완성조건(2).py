def solution(sides):
    return sum([1 for i in range(1, sum(sides)) if max(sides) < i + min(sides)])