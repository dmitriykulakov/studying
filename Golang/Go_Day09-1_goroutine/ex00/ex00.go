package main

import (
	"fmt"
	"time"
)

func main() {
	input := []int{5, 100, 10, 1, 45, 11, 29, 26, 25, 24, 22}
	ch := sleepSort(input)
	defer close(ch)
	for i := 0; i < len(input); i++ {
		fmt.Println(<-ch)
	}
}

func sleepSort(input []int) chan int {

	ch := make(chan int)
	for _, number := range input {
		go func() {
			time.Sleep((time.Duration)(number) * 2 * time.Millisecond)
			ch <- number
		}()
	}
	return ch
}
