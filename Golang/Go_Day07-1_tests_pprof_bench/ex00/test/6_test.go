package coins

import (
	w "ex00"
	"testing"
)

func Test06(c *testing.T) {
	coins := []int{1, 6, 10, 500, 1000}
	amount := 32
	new_coins2 := w.MinCoins(amount, coins)
	if len(new_coins2) != 4 {
		c.Fail()
	}
}
