package coins

import (
	"testing"
)

func BenchmarkTest05(c *testing.B) {
	// minCoins(31, []int{6, 10, 500, 1, 100, 1000})
	minCoins2(31, []int{6, 10, 500, 1, 100, 1000})
}
