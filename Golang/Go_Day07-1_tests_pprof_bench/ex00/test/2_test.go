package coins

import (
	w "ex00"
	"testing"
)

func Test02(c *testing.T) {
	coins := []int{1, 10, 15, 20, 100, 1000}
	amount := 0
	new_coins := w.MinCoins(amount, coins)
	if len(new_coins) != 0 {
		c.Fail()
	}
}
