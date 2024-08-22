package coins

import (
	w "ex00"
	"testing"
)

func Test0(c *testing.T) {
	coins := []int{1}
	amount := 15
	new_coins := w.MinCoins2(amount, coins)
	if len(new_coins) != 15 {
		c.Fail()
	}
}
