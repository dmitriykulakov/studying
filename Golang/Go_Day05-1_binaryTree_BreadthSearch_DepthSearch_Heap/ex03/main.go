package main

import (
	"fmt"
	"math"
)

type Present struct {
	Value int
	Size  int
}

func grabPresents(old []Present, capacity int) []Present {
	var new []Present
	if capacity < 0 {
		return new
	}
	n := len(old)
	maximum := make([][]int, n+1)
	for j := range maximum {
		maximum[j] = make([]int, capacity+1)
	}
	for i := 0; i < n+1; i++ {
		for j := 0; j < capacity+1; j++ {
			if i == 0 || j == 0 {
				maximum[i][j] = 0
			} else if old[i-1].Size > j {
				maximum[i][j] = maximum[i-1][j]
			} else {
				maximum[i][j] = int(math.Max(float64(maximum[i-1][j]), float64(maximum[i-1][j-old[i-1].Size]+old[i-1].Value)))
			}
		}
	}
	findPresents(old, &new, maximum, n, capacity)
	return new
}

func findPresents(old []Present, new *[]Present, maximum [][]int, k int, s int) {
	if maximum[k][s] == 0 {
		return
	}
	if maximum[k-1][s] == maximum[k][s] {
		findPresents(old, new, maximum, k-1, s)
	} else {
		findPresents(old, new, maximum, k-1, s-old[k-1].Size)
		*new = append(*new, old[k-1])
	}
}

func main() {
	var presents []Present = []Present{{3, 1}, {4, 5}, {3, 1}, {5, 2}, {6, 4}, {6, 3}}
	new_present := grabPresents(presents, 10)
	fmt.Println(new_present)
}
