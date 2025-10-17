def solution(nums):
    answer = 0
    num = 0
    l = [1, 2, 3]
    for i in range(4, max(nums)*3):
        for j in range(2, i//2+1):
            if not i % j:
                break
            if j == i//2:
                l.append(i)
        
    for i in range(len(nums)-2):
        j_s = i + 1
        for j in range(j_s, len(nums)-1):
            k_s = j + 1
            for k in range(k_s, len(nums)):
                num = nums[i] + nums[j] + nums[k]
                if num in l:
                    answer += 1
    return answer