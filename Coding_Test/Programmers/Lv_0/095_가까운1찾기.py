def solution(arr, idx):
    try:
        return min([i for i in range(idx, len(arr)) if arr[i] == 1])
    except:
        return -1