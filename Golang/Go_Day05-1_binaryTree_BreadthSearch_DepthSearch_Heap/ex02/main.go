package main

import (
	"container/heap"
	"errors"
	"fmt"
)

type Present struct {
	Value int
	Size  int
}

type PresentHeap struct {
	value int
	size  int
}

func getNCoolestPresents(old []Present, n int) ([]Present, error) {
	var new []Present
	if n > len(old) {
		return nil, errors.New("n is larger than the size of the slice")
	} else if n < 0 {
		return nil, errors.New("n is negative")
	} else {
		pq := make(PresentHeapQueue, len(old))
		for i := 0; i < len(old); i++ {
			pq[i] = &PresentHeap{
				value: old[i].Value,
				size:  old[i].Size,
			}
		}
		heap.Init(&pq)
		for ; n > 0; n-- {
			item := heap.Pop(&pq).(*PresentHeap)
			new = append(new, Present{item.value, item.size})
		}
		return new, nil
	}
}

type PresentHeapQueue []*PresentHeap

func (pq PresentHeapQueue) Len() int { return len(pq) }

func (pq PresentHeapQueue) Less(i, j int) bool {
	if pq[i].value != pq[j].value {
		return pq[i].value > pq[j].value
	} else {
		return pq[i].size < pq[j].size
	}
}

func (pq PresentHeapQueue) Swap(i, j int) {
	pq[i], pq[j] = pq[j], pq[i]
}

func (pq *PresentHeapQueue) Push(x interface{}) {
	item := x.(*PresentHeap)
	*pq = append(*pq, item)
}

func (pq *PresentHeapQueue) Pop() interface{} {
	old := *pq
	n := len(old)
	item := old[n-1]
	old[n-1] = nil
	*pq = old[0 : n-1]
	return item
}

func main() {
	var presents []Present = []Present{{5, 1}, {4, 5}, {3, 1}, {5, 2}, {6, 4}, {4, 10}}
	new_present, err := getNCoolestPresents(presents, 5)
	if err == nil {
		fmt.Println(new_present)
	} else {
		fmt.Println("ERROR:", err)
	}
}
