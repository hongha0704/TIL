def solution(myString, pat):
    for i in range(len(myString)-len(pat)+1):
        if pat == myString[-len(pat):]:
            return myString
        myString = myString[:-1]