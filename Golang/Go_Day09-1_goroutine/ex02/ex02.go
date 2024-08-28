package multiplex

//package main

import (
	"sync"
)

// func main() {
// 	one := make(chan interface{}, 5)
// 	two := make(chan interface{}, 1)
// 	one <- 5
// 	one <- 5.44
// 	one <- "dsdadddd"
// 	two <- "dasd"
// 	close(one)
// 	close(two)
// 	result := Multiplex(one, two)
// 	slice := make([]interface{}, 0)
// 	for value := range result {
// 		slice = append(slice, value)
// 	}
// 	fmt.Println(slice)
// }

func Multiplex(args ...<-chan interface{}) <-chan interface{} {
	result := make(chan interface{})
	var wg sync.WaitGroup
	for _, value := range args {
		res := value
		wg.Add(1)
		go func() {
			for d := range res {
				result <- d
			}
			wg.Done()
		}()
	}
	go func() {
		wg.Wait()
		close(result)
	}()
	return result
}
