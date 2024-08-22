package main

import (
	"bufio"
	"bytes"
	"errors"
	"fmt"
	"io"
	"os"
	"slices"
	"strconv"
)

func input(args []string) (Mode string, Files []string, err error) {
	if len(args) > 0 {
		i := 1
		if args[0] == "-l" {
			if slices.Contains(args, "-w") || slices.Contains(args, "-m") {
				return Mode, Files, errors.New("ERROR: Too many flags")
			}
			Mode = "lines"
		} else if args[0] == "-m" {
			if slices.Contains(args, "-w") || slices.Contains(args, "-l") {
				return Mode, Files, errors.New("ERROR: Too many flags")
			}
			Mode = "chars"
		} else if args[0] == "-w" {
			if slices.Contains(args, "-m") || slices.Contains(args, "-l") {
				return Mode, Files, errors.New("ERROR: Too many flags")
			}
			Mode = "words"
		} else {
			Mode = "words"
			i = 0
		}
		for j := 0; i < len(args); i++ {
			Files = append(Files, args[i])
			j++
		}
	}
	return Mode, Files, nil
}

func resultCount(Mode string, File string, c chan string) {
	file, err := os.Open(File)
	if err != nil {
		fmt.Printf("ERROR: %s\n", err)
		c <- ""
	} else {
		fileScanner := bufio.NewScanner(file)
		if Mode == "lines" {
			lineCount := 0
			for fileScanner.Scan() {
				lineCount++
			}
			c <- strconv.Itoa(lineCount) + "\t" + File + "\n"
		}
		if Mode == "words" {
			byteValue, _ := io.ReadAll(file)
			wordCount := 0
			for range bytes.Fields(byteValue) {
				wordCount++
			}
			c <- strconv.Itoa(wordCount) + "\t" + File + "\n"
		} else if Mode == "chars" {
			byteValue, _ := io.ReadAll(file)
			charCount := 0
			for _, word := range bytes.Fields(byteValue) {
				for range string(word) {
					charCount++
				}
			}
			c <- strconv.Itoa(charCount) + "\t" + File + "\n"
		}
	}
	defer file.Close()
}

func main() {
	args := os.Args
	Mode, Files, err := input(args[1:])
	if err == nil {
		c := make(chan string)
		for _, File := range Files {
			go resultCount(Mode, File, c)
		}
		for range Files {
			fmt.Printf("%s", <-c)
		}
	} else {
		fmt.Println(err)
	}
}
