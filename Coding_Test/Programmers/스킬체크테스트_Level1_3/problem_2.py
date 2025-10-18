def solution(players, callings):
    for c in callings:
        idx = players.index(c)
        players[idx-1], players[idx] = players[idx], players[idx-1]
    return players 