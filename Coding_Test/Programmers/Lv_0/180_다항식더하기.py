def solution(polynomial):
    p = polynomial.split(" + ")
    one, num = [], []
    for i in p:
        if i == "x":
            one.append(1)
        elif "x" in i:
            one.append(int(i[:-1]))
        elif i.isdigit():
            num.append(int(i))
    if sum(one) == 1 and sum(num):
        return f"x + {sum(num)}"
    elif sum(one) and sum(num):
        return f"{sum(one)}x + {sum(num)}"
    elif sum(one) == 1:
        return f"x"
    elif sum(one):
        return f"{sum(one)}x"
    elif sum(num):
        return f"{sum(num)}"