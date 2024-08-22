package coins

import (
	"sort"
)

func minCoins(val int, coins []int) []int {
	res := make([]int, 0)
	i := len(coins) - 1
	for i >= 0 {
		for val >= coins[i] {
			val -= coins[i]
			res = append(res, coins[i])
		}
		i -= 1
	}
	return res
}

func minCoins2(val int, coins []int) []int {
	res := make([]int, 0)
	if val <= 0 || len(coins) == 0 {
		return res
	}
	sort.Ints(coins)
	minCoins := make([]int, val+1)
	coinsUsed := make([]int, val+1)
	for cents := 0; cents < val+1; cents++ {
		coinCount := cents
		newCoin := coins[0]
		for j := 0; j < len(coins) && coins[j] <= cents; j++ {
			if minCoins[cents-coins[j]]+coins[0] < coinCount {
				coinCount = minCoins[cents-coins[j]] + coins[0]
				newCoin = coins[j]
			}
			minCoins[cents] = coinCount
			coinsUsed[cents] = newCoin
		}
	}
	for coinsUsed[val] > 0 {
		res = append(res, coinsUsed[val])
		val -= coinsUsed[val]
	}
	return res
}
