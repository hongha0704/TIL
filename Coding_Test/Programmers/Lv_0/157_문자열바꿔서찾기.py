def solution(myString, pat):
    myString = myString.replace("A", 'b')
    myString = myString.replace("B", "a")
    myString = myString.upper()
    return 1 if pat in myString else 0