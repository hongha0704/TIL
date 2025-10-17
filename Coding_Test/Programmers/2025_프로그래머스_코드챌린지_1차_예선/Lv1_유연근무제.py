def solution(schedules, timelogs, startday):
    answer = 0
    schedules_new = []
    workday = {1:[1, 1, 1, 1, 1, 0, 0],
               2:[1, 1, 1, 1, 0, 0, 1],
               3:[1, 1, 1, 0, 0, 1, 1],
               4:[1, 1, 0, 0, 1, 1, 1],
               5:[1, 0, 0, 1, 1, 1, 1],
               6:[0, 0, 1, 1, 1, 1, 1],
               7:[0, 1, 1, 1, 1, 1, 0],}
    
    for s in schedules:
        schedule = 0
        if (s + 10) % 100 >= 60:
            schedule += ((s + 10) // 100 + 1) * 100
            schedule += (s + 10) % 100 - 60
        else:
            schedule = s + 10
        schedules_new.append(schedule)
    
    for i, times in enumerate(timelogs):
        count = 0
        for j, time in enumerate(times):
            if workday[startday][j] and time > schedules_new[i]:
                break
            count += 1
        if count == 7:
            answer += 1
        
    return answer