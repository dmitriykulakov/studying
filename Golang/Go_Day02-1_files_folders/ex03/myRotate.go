package main

import (
	"errors"
	"fmt"
	"os"
	"os/exec"
	"strconv"
	"strings"
	"time"
)

type Input struct {
	time   string
	folder string
}

func input(args []string) (input Input, files []string, err error) {
	input.time = strconv.FormatInt(time.Now().Unix(), 10)
	if len(args) > 0 {
		if args[0] == "-a" {
			if len(args) > 1 {
				input.folder = args[1]
				if len(args[2:]) > 0 {
					return input, args[2:], nil
				} else {
					return input, files, errors.New("ERROR: the input is wrong, there is no files")
				}
			} else {
				return input, files, errors.New("ERROR: the input is wrong, there is no information about folder")
			}
		} else {
			input.folder = "."
			if len(args) == 0 {
				return input, files, errors.New("ERROR: the input is wrong, there is no files")
			}
			return input, args, nil
		}
	}
	return input, files, errors.New("ERROR: the input is empty")
}

func makeArchive(input Input, file string, c chan bool) {
	application, result := strings.CutSuffix(file, ".log")
	if !result {
		fmt.Printf("ERROR: %s has wrong format\n", file)
	} else {
		file2, err := os.Open(file)
		if err != nil {
			fmt.Printf("ERROR: %s\n", err)
		} else {
			cmd := exec.Command("tar", "-cf", input.folder+"/"+application+"_"+input.time+".tar.gz", file)
			var out strings.Builder
			cmd.Stdout = &out
			err := cmd.Run()
			if err != nil {
				fmt.Println("ERROR: ", err, "the input is wrong")
			}
		}
		defer file2.Close()
	}
	c <- true
}

func main() {
	args := os.Args
	input, files, err := input(args[1:])
	if err != nil {
		fmt.Println("ERROR: ", err)
	} else {
		c := make(chan bool)
		for _, filename := range files {
			go makeArchive(input, filename, c)
		}
		for range files {
			<-c
		}
	}
}
