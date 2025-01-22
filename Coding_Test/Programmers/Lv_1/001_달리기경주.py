def solution(players, callings):
    for call in callings:
        index = players.index(call)
        players[index], players[index - 1] = players[index - 1], players[index]
    answer = players
    return answer