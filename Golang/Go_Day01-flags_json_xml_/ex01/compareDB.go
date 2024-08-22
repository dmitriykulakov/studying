package main

import (
	"encoding/json"
	"encoding/xml"
	"flag"
	"fmt"
	"io"
	"os"
	"strings"
)

type DBReader interface {
	reading(byteValue []byte) cakes
}

type Cake_j struct{}
type Cake_x struct{}

type cakes struct {
	Cake []struct {
		Name        string       `json:"name" xml:"name"`
		Time        string       `json:"time" xml:"stovetime"`
		Ingredients []Ingredient `json:"ingredients" xml:"ingredients>item"`
	} `json:"cake" xml:"cake"`
}

type Ingredient struct {
	Ingredient_name  string `json:"ingredient_name" xml:"itemname"`
	Ingredient_count string `json:"ingredient_count" xml:"itemcount"`
	Ingredient_unit  string `json:"ingredient_unit,omitempty" xml:"itemunit"`
}

func input(filename string) (byteValue []byte, flag bool) {
	File, err := os.Open(filename)
	if err != nil {
		fmt.Println("ERROR:", err)
		return byteValue, false
	}
	defer File.Close()
	byteValue, _ = io.ReadAll(File)
	return byteValue, true
}

func (c Cake_j) reading(byteValue []byte) cakes {
	var Cakes cakes
	json.Unmarshal(byteValue, &Cakes)
	return Cakes
}

func (c Cake_x) reading(byteValue []byte) cakes {
	var Cakes cakes
	xml.Unmarshal(byteValue, &Cakes)
	return Cakes
}

func compare(old cakes, new cakes) {
	for i := 0; i < len(new.Cake); i++ {
		flag_ADD := true
		for j := 0; j < len(old.Cake); j++ {
			if old.Cake[i].Name == new.Cake[j].Name {
				flag_ADD = false
			}
		}
		if flag_ADD {
			fmt.Printf("ADDED cake \"%s\"\n", new.Cake[i].Name)
		}
	}
	for i := 0; i < len(old.Cake); i++ {
		flag_REMOVE := true
		for j := 0; j < len(new.Cake); j++ {
			if old.Cake[i].Name == new.Cake[j].Name {
				if old.Cake[i].Time != new.Cake[j].Time {
					fmt.Printf("CHANGED cooking time for cake \"%s\" - \"%s\" instead of \"%s\"\n", old.Cake[i].Name, new.Cake[i].Time, old.Cake[i].Time)
				}
				compare_ingredients(old.Cake[i].Ingredients, new.Cake[j].Ingredients, old.Cake[i].Name)
				flag_REMOVE = false
			}
		}
		if flag_REMOVE {
			fmt.Printf("REMOVED cake \"%s\"\n", old.Cake[i].Name)
		}
	}
}

func compare_ingredients(old []Ingredient, new []Ingredient, cake_name string) {
	for i := 0; i < len(new); i++ {
		flag_ADD := true
		for j := 0; j < len(old); j++ {
			if new[i].Ingredient_name == old[j].Ingredient_name {
				flag_ADD = false
			}
		}
		if flag_ADD {
			fmt.Printf("ADDED ingredient \"%s\" for cake \"%s\"\n", new[i].Ingredient_name, cake_name)
		}
	}
	for i := 0; i < len(old); i++ {
		flag_REMOVE := true
		for j := 0; j < len(new); j++ {
			if old[i].Ingredient_name == new[j].Ingredient_name {
				flag_REMOVE = false
				if old[i].Ingredient_count != new[j].Ingredient_count {
					fmt.Printf("CHANGED unit count for ingredient \"%s\" for cake \"%s\" - \"%s\" instead of \"%s\"\n", old[i].Ingredient_name, cake_name, new[j].Ingredient_count, old[i].Ingredient_count)
				}
				if old[i].Ingredient_unit != new[j].Ingredient_unit && new[i].Ingredient_unit == "" {
					fmt.Printf("REMOVED unit \"%s\" for ingredient \"%s\" for cake \"%s\"\n", old[i].Ingredient_unit, old[i].Ingredient_name, cake_name)
				} else if old[i].Ingredient_unit != new[j].Ingredient_unit && old[i].Ingredient_unit == "" {
					fmt.Printf("ADDED unit \"%s\" for ingredient \"%s\" for cake \"%s\"\n", new[j].Ingredient_unit, old[i].Ingredient_name, cake_name)
				} else if old[i].Ingredient_unit != new[j].Ingredient_unit {
					fmt.Printf("CHANGED unit for ingredient \"%s\" for cake \"%s\" - \"%s\" instead of \"%s\"\n", old[i].Ingredient_name, cake_name, new[j].Ingredient_unit, old[i].Ingredient_unit)
				}
			}
		}
		if flag_REMOVE {
			fmt.Printf("REMOVED ingredient \"%s\" for cake \"%s\"\n", old[i].Ingredient_name, cake_name)
		}
	}
}

func main() {
	var old_file string
	var new_file string
	flag.StringVar(&old_file, "old", "empty", "a string var")
	flag.StringVar(&new_file, "new", "empty", "a string var")
	flag.Parse()
	byteValue_old, flag_old := input(old_file)
	byteValue_new, flag_new := input(new_file)
	if flag_new && flag_old {
		var (
			cakes_new DBReader
			cakes_old DBReader
			flag      bool = true
			old       cakes
			new       cakes
		)
		if strings.Contains(old_file, ".json") {
			cakes_old = Cake_j{}
			old = cakes_old.reading(byteValue_old)
		} else if strings.Contains(old_file, ".xml") {
			cakes_old = Cake_x{}
			old = cakes_old.reading(byteValue_old)
		} else {
			fmt.Printf("ERROR: the old file has wrong format\n")
			flag = false
		}
		if strings.Contains(new_file, ".json") {
			cakes_new = Cake_j{}
			new = cakes_new.reading(byteValue_new)
		} else if strings.Contains(new_file, ".xml") {
			cakes_new = Cake_x{}
			new = cakes_new.reading(byteValue_new)
		} else {
			fmt.Printf("ERROR: the file has wrong format\n")
			flag = false
		}
		if flag {
			compare(old, new)
		}
	}
}
