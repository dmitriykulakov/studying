package coins

import (
	"testing"
)

func BenchmarkTest08(c *testing.B) {
	// minCoins2(6, []int{1, 3, 4})
	minCoins(6, []int{1, 3, 4})
}
