package coins

import (
	"testing"
)

func BenchmarkTest01(c *testing.B) {
	minCoins2(32, make([]int, 0))
	// minCoins(32, make([]int, 0))
}
