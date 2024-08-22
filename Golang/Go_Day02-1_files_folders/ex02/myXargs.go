package main

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var input []string
	for scanner.Scan() {
		input = append(input, scanner.Text())
	}
	args := os.Args
	if len(args) > 1 {
		final := append(args[2:], input...)
		cmd := exec.Command(args[1], final...)
		var out strings.Builder
		cmd.Stdout = &out
		err := cmd.Run()
		if err != nil {
			fmt.Println("ERROR: ", err)
		} else {
			fmt.Printf("%s", out.String())
		}
	} else {
		fmt.Println("ERROR: The input is wrong")
	}
}
