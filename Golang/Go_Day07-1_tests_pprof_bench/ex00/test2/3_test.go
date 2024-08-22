package coins

import (
	w "ex00"
	"testing"
)

func Test03(c *testing.T) {
	coins := []int{1, 10, 15, 20, 100, 1000}
	amount := 32
	new_coins := w.MinCoins2(amount, coins)
	if len(new_coins) != 4 {
		c.Fail()
	}
}
