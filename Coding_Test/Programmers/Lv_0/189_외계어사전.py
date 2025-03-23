def solution(spell, dic):
    for d in dic:
        len_d = len(d)
        for s in spell:
            if s in d:
                d = d.replace(s, '', 1)
        if not d and len(spell) == len_d:
            return 1
    return 2
