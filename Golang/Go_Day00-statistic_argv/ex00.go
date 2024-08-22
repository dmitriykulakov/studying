package main

import (
	"fmt"
	"io"
	"math"
	"os"
	"slices"
	"sort"
	"strconv"
)

type digit []int

func input() []int {
	var str_number string
	var digits digit
	for {
		fmt.Print("Write a digit between -100000 and 100000 or 'ctrl+d' to stop:\n ")
		_, err1 := fmt.Scanf("%s\n", &str_number)
		if err1 == io.EOF {
			break
		}
		number, err := strconv.Atoi(str_number)
		if err != nil {
			fmt.Printf("ERROR: %s\n", err)
		} else if number >= -100000 && number <= 100000 {
			digits = append(digits, number)
		} else {
			fmt.Println("ERROR: The digit is not between -100000 and 100000")
		}
	}
	sort.Slice(digits, func(i, j int) bool {
		return digits[i] < digits[j]
	})
	return digits
}

func (d digit) countMean() {
	fmt.Printf("Mean = %.2f\n", count_mean(d))
}

func count_mean(d digit) float64 {
	var mean float64 = 0
	for _, value := range d {
		mean = mean + float64(value)
	}
	mean = mean / float64(len(d))
	return mean
}

func (d digit) countMedian() {
	len_d := len(d)
	if len_d == 0 {
		fmt.Println("Median = NaN")
	} else if len_d%2 == 1 {
		fmt.Println("Median = ", d[len_d/2])
	} else {
		fmt.Printf("Median = %.2f\n", float32((d[len_d/2]+d[len_d/2-1])/2))
	}
}

func (d digit) countMode() {
	if len(d) == 0 {
		fmt.Println("Mode = NaN")
	} else {
		var (
			mode           int = d[0]
			mode_count     int = 0
			mode_tmp       int = d[0]
			mode_tmp_count int = 0
		)
		for i := 0; i < len(d); i++ {
			if d[i] == mode_tmp {
				mode_tmp_count++
				if mode_tmp_count > mode_count {
					mode = d[i]
					mode_count = mode_tmp_count
				}
			} else {
				mode_tmp = d[i]
				mode_tmp_count = 0
				i--
			}
		}
		fmt.Printf("Mode = %d\n", mode)
	}
}

func (d digit) countSD() {
	mean := count_mean(d)
	var SD float64 = 0
	for i := 0; i < len(d); i++ {
		SD = SD + math.Pow(float64(d[i])-mean, 2)
	}
	SD = math.Sqrt(SD / float64(len(d)))
	fmt.Printf("SD = %.2f\n", SD)
}

func output(d digit, args []string) {
	print_mode := true
	fmt.Printf("\n")
	if slices.Contains(args, "Mean") || slices.Contains(args, "Average") {
		d.countMean()
		print_mode = false
	}
	if slices.Contains(args, "Median") {
		d.countMedian()
		print_mode = false
	}
	if slices.Contains(args, "Mode") {
		d.countMode()
		print_mode = false
	}
	if slices.Contains(args, "SD") {
		d.countSD()
		print_mode = false
	}
	if print_mode {
		d.countMean()
		d.countMedian()
		d.countMode()
		d.countSD()
	}
}

func main() {
	args := os.Args[1:]
	digits := input()
	output(digits, args)
}
