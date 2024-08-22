package main
package main

import (
	"bytes"
	"crypto/tls"
	"encoding/json"
	"flag"
	"fmt"
	"net/http"
)

func GetClient() *http.Client {
	

	tlsConfig := &tls.Config{
	}

	client := &http.Client{
		Transport: &http.Transport{
			TLSClientConfig: tlsConfig,
		},
	}
	return client
}

type InlineResponse201 struct {
	Change int32 `json:"change"`

	Thanks string `json:"thanks,omitempty"`
}

type InlineResponse400 struct {
	Error_ string `json:"error,omitempty"`
}

type Order struct {

	// amount of money put into vending machine
	Money int `json:"money"`

	// kind of candy
	CandyType string `json:"candyType"`

	// number of candy
	CandyCount int `json:"candyCount"`
}

func main() {
	var order Order
	flag.StringVar(&order.CandyType, "k", "empty", "a string var")
	flag.IntVar(&order.CandyCount, "c", 0, "a count")
	flag.IntVar(&order.Money, "m", 0, "money")
	flag.Parse()
	client := GetClient()

	bodyJson, _ := json.Marshal(order)
	bodyPost := bytes.NewReader(bodyJson)
	response, err := client.Post("http://localhost:3333/buy_candy", "application/json", bodyPost)
	if err == nil {
		defer response.Body.Close()
		var result InlineResponse201
		json.NewDecoder(response.Body).Decode(&result)
		fmt.Printf("%s Your change is %d!\n", result.Thanks, result.Change)
	}
}

