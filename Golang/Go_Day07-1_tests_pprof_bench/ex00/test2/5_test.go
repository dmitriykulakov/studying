package coins

import (
	w "ex00"
	"testing"
)

func Test05(c *testing.T) {
	coins := []int{6, 10, 500, 1, 100, 1000}
	amount := 31
	new_coins := w.MinCoins2(amount, coins)
	if len(new_coins) != 4 {
		c.Fail()
	}
}
