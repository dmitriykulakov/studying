package coins

import (
	w "ex00"
	"testing"
)

func Test01(c *testing.T) {
	coins := make([]int, 0)
	amount := 32
	new_coins := w.MinCoins(amount, coins)
	if len(new_coins) != 0 {
		c.Fail()
	}
}
