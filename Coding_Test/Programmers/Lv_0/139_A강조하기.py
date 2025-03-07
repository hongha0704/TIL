def solution(myString):
    return "".join([i.upper() if i.lower() == 'a' else i.lower() for i in myString])