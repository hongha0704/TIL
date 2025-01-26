def solution(ineq, eq, n, m):
    if eq == '=' and ineq == '>':
        return int(n >= m)
    elif eq == '=' and ineq == '<':
        return int(n <= m)
    elif eq == '!' and ineq == '>':
        return int(n > m)
    elif eq == '!' and ineq == '<':
        return int(n < m)
