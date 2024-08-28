package main

import (
	w "ex02"
	"slices"
	"testing"
)

func Test(t *testing.T) {
	inputData := []interface{}{5, 5.44, "asd", "dasd"}
	one := make(chan interface{}, len(inputData))
	two := make(chan interface{}, len(inputData))
	one <- inputData[0]
	one <- inputData[1]
	one <- inputData[2]
	two <- inputData[3]
	close(one)
	close(two)
	result := w.Multiplex(one, two)
	sliceOut := make([]interface{}, 0)
	for value := range result {
		sliceOut = append(sliceOut, value)
	}
	for _, res := range sliceOut {
		if !slices.Contains(sliceOut, res) {
			t.Errorf("MISTAKE!! There are no the element: %v\n", res)
		}
	}
	if slices.Contains(sliceOut, "elem") {
		t.Errorf("MISTAKE!! There are no the element: %v\n", "asd")
	}
}
