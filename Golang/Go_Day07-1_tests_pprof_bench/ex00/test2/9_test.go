package coins

import (
	w "ex00"
	"testing"
)

func Test09(c *testing.T) {
	coins := []int{1, 2, 5, 10, 15, 20, 25, 35, 50}
	amount := 111
	new_coins := w.MinCoins2(amount, coins)
	if len(new_coins) != 4 {
		c.Fail()
	}
}
