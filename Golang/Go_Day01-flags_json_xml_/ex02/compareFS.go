package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"os"
)

func input(filename string) (lines map[string]int, flag bool) {
	lines = make(map[string]int)
	File, err := os.Open(filename)
	if err != nil {
		fmt.Println("ERROR:", err)
		return lines, false
	}
	defer File.Close()
	reader := bufio.NewReader(File)
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			if err == io.EOF {
				break
			} else {
				fmt.Println("ERROR: ", err)
				break
			}
		}
		lines[line] = 1
	}
	return lines, true
}

func compare(contain_old map[string]int, new_file string) {
	File, err := os.Open(new_file)
	if err != nil {
		fmt.Println("ERROR:", err)
		return
	}
	defer File.Close()
	reader := bufio.NewReader(File)
	for {
		new, err := reader.ReadString('\n')
		if err != nil {
			if err == io.EOF {
				break
			} else {
				fmt.Println("ERROR: ", err)
				break
			}
		}
		if contain_old[new] == 1 {
			delete(contain_old, new)
		} else {
			fmt.Printf("ADDED %s", new)
		}
	}
	for key := range contain_old {
		fmt.Printf("REMOVED %s", key)
	}

}

func main() {
	var old_file string
	var new_file string
	flag.StringVar(&old_file, "old", "empty", "a string var")
	flag.StringVar(&new_file, "new", "empty", "a string var")
	flag.Parse()
	contain_old, flag_old := input(old_file)
	if flag_old {
		compare(contain_old, new_file)
	}
}
