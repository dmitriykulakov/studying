package coins

import (
	"testing"
)

func BenchmarkTest09(c *testing.B) {
	minCoins2(4567, []int{1, 2, 5, 10, 15, 20, 25, 35, 50})
	// minCoins(4567, []int{1, 2, 5, 10, 15, 20, 25, 35, 50})
}
