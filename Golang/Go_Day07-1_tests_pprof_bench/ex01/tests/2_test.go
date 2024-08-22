package coins

import (
	"testing"
)

func BenchmarkTest02(c *testing.B) {
	minCoins2(0, []int{6, 10, 2, 3, 4, 5, 6, 7, 500, 20, 10, 45, 1, 100, 1000})
	// minCoins(0, []int{6, 10, 2, 3, 4, 5, 6, 7, 500, 20, 10, 45, 1, 100, 1000})
}
