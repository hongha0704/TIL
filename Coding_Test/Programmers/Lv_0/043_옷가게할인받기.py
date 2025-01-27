def solution(price):
    if price >= 500000: price_ratio = 0.8
    elif price >= 300000: price_ratio = 0.9
    elif price >= 100000: price_ratio = 0.95
    else: price_ratio = 1
    return int(price * price_ratio)