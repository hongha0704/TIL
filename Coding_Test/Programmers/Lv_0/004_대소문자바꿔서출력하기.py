str = input()
temp = ''

for i in str:
    if i.isupper():
        i = i.lower()
    else:
        i = i.upper()
    temp += i
str = temp

print(str)