package main

import (
	"context"
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"os/signal"
	"sync"
)

func main() {
	urlChan := make(chan string, 301)
	for i := 0; i < 300; i++ {
		urlChan <- "https://edu.21-school.ru/project"
	}
	urlChan <- "https://edu.21-school.rufdsf/project"
	close(urlChan)
	ctx, stop := signal.NotifyContext(context.Background(), os.Interrupt)
	defer stop()
	response := crawlWeb(ctx, urlChan)
	i := 1
	for value := range response {
		fmt.Println(i, " answer:", value)
		i++
	}
	fmt.Println("Program stopped")
}

func crawlWeb(ctx context.Context, in chan string) chan *string {
	var wg sync.WaitGroup
	response := make(chan *string, len(in))
	maxRoutine := make(chan struct{}, 8)
	//count := 0
	for url := range in {
		maxRoutine <- struct{}{}
		wg.Add(1)
		go func(url string) {
			//count++
			//fmt.Println(count)
			defer wg.Done()
			select {
			case <-ctx.Done():
				<-maxRoutine
				//count--
				log.Println("Stop the programm goroutine.....")
				return
			default:
				resp, err := http.Get(url)
				if err != nil {
					log.Println(err)
				} else {
					defer resp.Body.Close()
					reader, err := io.ReadAll(resp.Body)
					if err != nil {
						log.Println(err)
					} else {
						res := string(reader)
						response <- &res
					}
				}
				//count--
				<-maxRoutine
			}
		}(url)
	}
	go func() {
		wg.Wait()
		close(response)
	}()
	return response
}
