package coins

import (
	"testing"
)

func BenchmarkTest0(c *testing.B) {
	minCoins2(15, []int{1})
	//minCoins(15, []int{1})
}
