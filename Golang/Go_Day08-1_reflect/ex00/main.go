package main

import (
	"errors"
	"fmt"
	"unsafe"
)

func getElement(arr []int, idx int) (int, error) {
	if len(arr) == 0 {
		return 0, errors.New("the slice is empty")
	}
	if idx < 0 {
		return 0, errors.New("the index is negative")
	}
	if idx >= len(arr) {
		return 0, errors.New("the index is out of bounds")
	}
	step := unsafe.Sizeof(arr[0])
	address := (uintptr)(unsafe.Pointer(&arr[0]))
	new_address := address + step*uintptr(idx)
	result := ((*int)(unsafe.Pointer(new_address)))
	return *result, nil
}

func main() {
	arr := []int{10, 11, 12, 13, 14, 15}
	// arr := make([]int, 0)
	result, err := getElement(arr, 6)
	fmt.Println(result)
	fmt.Println(err)
}
