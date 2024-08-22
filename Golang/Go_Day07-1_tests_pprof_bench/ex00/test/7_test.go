package coins

import (
	w "ex00"
	"testing"
)

func Test07(c *testing.T) {
	coins := make([]int, 100)
	for i := 0; i < 100; i++ {
		coins[i] = i + 1
	}
	amount := 666666
	new_coins := w.MinCoins(amount, coins)
	if len(new_coins) != 6667 {
		c.Fail()
	}
}
