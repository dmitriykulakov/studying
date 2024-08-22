package coins

import (
	"testing"
)

func BenchmarkTest06(c *testing.B) {
	minCoins2(32, []int{1, 6, 10, 500, 1000})
	// minCoins(32, []int{1, 6, 10, 500, 1000})
}
