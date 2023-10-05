def coins(n, arr, dp):
    min_depth = n
    
    if dp[n] > 0: return dp[n]

    cont = 0

    for e in arr:
        n_e = n - e

        if n_e < 0: 
            cont += 1
            continue

        if n_e == 0: 
            dp[n] = 1
            return 1

        dp[n_e] = coins(n_e, arr, dp)
        if dp[n_e] < min_depth:
            min_depth = dp[n_e]

    if cont >= 3:
        dp[n] = -1
        return -1
    
    dp[n] = min_depth + 1
    return dp[n]

n = int(input())

arr = [20, 5, 30]

dp = []

for i in range(n+1):
    dp.append(-1)

print(coins(n, arr, dp))