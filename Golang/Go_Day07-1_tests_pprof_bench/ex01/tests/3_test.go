package coins

import (
	"testing"
)

func BenchmarkTest03(c *testing.B) {
	minCoins2(320, []int{1, 10, 15, 20, 100, 1000})
	// minCoins(320, []int{1, 10, 15, 20, 100, 1000})
}
