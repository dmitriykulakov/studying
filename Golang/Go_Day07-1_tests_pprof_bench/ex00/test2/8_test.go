package coins

import (
	w "ex00"
	"testing"
)

func Test08(c *testing.T) {
	coins := []int{1, 3, 4, 4, 4, 1, 1}
	amount := 6
	new_coins := w.MinCoins2(amount, coins)
	if len(new_coins) != 2 {
		c.Fail()
	}
}
