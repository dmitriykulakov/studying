package coins

import (
	"testing"
)

func BenchmarkTest04(c *testing.B) {
	// minCoins2(32, []int{1, 10, 10, 15, 20, 100, 1000})
	minCoins(32, []int{1, 10, 10, 15, 20, 100, 1000})
}
