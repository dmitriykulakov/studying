package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	input := []int{27, 5, 100, 28, 23, 10, 1, 45, 11, 29, 26, 25, 24, 22}
	ch := make(chan (int))
	sleepSort(input, ch)
	for value := range ch {
		fmt.Println(value)
	}
}

func sleepSort(input []int, ch chan (int)) {
	var wg sync.WaitGroup
	for _, number := range input {
		wg.Add(1)
		go func(number int) {
			defer wg.Done()
			time.Sleep((time.Duration)(number) * 2 * time.Millisecond)
			ch <- number
		}(number)
	}
	go func() {
		wg.Wait()
		close(ch)
	}()
}
