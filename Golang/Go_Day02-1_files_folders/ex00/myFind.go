package main

import (
	"errors"
	"fmt"
	"io/fs"
	"os"
	"path/filepath"
	"slices"
	"strings"
)

type Input struct {
	flags string
	path  string
	ext   string
}

func input(args []string) (result Input) {
	if len(args) > 0 {
		result.path = args[len(args)-1]
		args = args[:len(args)-1]
	}
	if slices.Contains(args, "-f") && len(args) > 0 {
		result.flags += "f"
		if slices.Contains(args, "-ext") && args[len(args)-1] != "-f" && args[len(args)-1] != "-ext" {
			result.flags += "e"
			result.ext = "." + args[len(args)-1]
			args = args[:len(args)-1]
		}
	}
	if slices.Contains(args, "-d") {
		result.flags += "d"
	}
	if slices.Contains(args, "-sl") {
		result.flags += "s"
	}
	return result
}

func find(input Input) {
	dir, err := os.Open(input.path)
	if err != nil {
		if !(errors.Is(err, fs.ErrPermission)) { // Проверка на допуск к открытию
			fmt.Println("ERROR: ", err)
		}
		return
	}
	defer dir.Close()
	dirContain, err := dir.Readdir(-2)
	if err != nil {
		fmt.Println("ERROR: ", err)
		return
	}
	for _, file := range dirContain {
		if file.IsDir() {
			if strings.Contains(input.flags, "d") {
				fmt.Println(input.path + "/" + file.Name())
			}
			find(Input{input.flags, input.path + "/" + file.Name(), input.ext})
		} else if file.Mode().IsRegular() {
			filePrint(input, file.Name())
		} else if file.Mode().String()[0] == 'L' {
			if strings.Contains(input.flags, "s") {
				simlink, err := filepath.EvalSymlinks(file.Name())
				if err != nil {
					fmt.Println(input.path + "/" + file.Name() + " -> [broken]")
				} else {
					fmt.Println(input.path + "/" + file.Name() + " -> " + simlink)
				}
			}
		}
	}
}

func filePrint(input Input, fileName string) {
	file, err := os.Open(input.path)
	if err != nil {
		if !(errors.Is(err, fs.ErrPermission)) { // Проверка на допуск к открытию
			fmt.Println("ERROR1: ", err)
		}
		return
	}
	defer file.Close()
	if strings.Contains(input.flags, "f") {
		if strings.Contains(input.flags, "e") {
			if strings.Contains(fileName, input.ext) {
				fmt.Println(input.path + "/" + fileName)
			}
		} else {
			fmt.Println(input.path + "/" + fileName)
		}
	}
}

func main() {
	args := os.Args[1:]
	input := input(args)
	find(input)
}
