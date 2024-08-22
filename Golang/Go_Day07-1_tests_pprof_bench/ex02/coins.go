package main

/*
	Function receives two variables int and slice []int and return an another slice []int
			[]string{"val int: an amount of coins that need to return
			coins []int: a slice of coins, that accept to use in function
	Function result:
		[]int: a slice of coins, that represented minimum set of input coins to describe an amount val

	There are many changes from the func minCoins(val int, coins []int) []int:
		1. add an opportunity to use unsorted slice of coins in the input
		2. add an opportunity to use a slice with duplicates in the input",
		3. the new function works faster in case of empty input slice, val = 0 and if input slice has onle one member
		4. in the new function solved problem of wrong result with input like this:

			minCoins(32, []int{1, 6, 10, 500, 1000}
			result: [10,10,10,1,1] - wrong

			minCoins2(32, []int{1, 6, 10, 500, 1000}
			result: [10,10,6,6]

	Conclusion: The function works right, can work with unsorted slices,
				many problems from the func minCoins(val int, coins []int)[]int are solved,
				but the new function has less speed with big input slices of coins

	The HTML page saved by command curl localhost:8080 > Documentation.html

*/

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
