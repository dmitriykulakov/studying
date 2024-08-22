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

func print_x(cakes cakes) {
	fmt.Printf("<recipes>\n")
	for i := 0; i < len(cakes.Cake); i++ {
		fmt.Printf("    <cake>\n")
		fmt.Printf("        <name>%s</name>\n", cakes.Cake[i].Name)
		fmt.Printf("        <stovetime>%s</stovetime>\n", cakes.Cake[i].Time)
		fmt.Printf("        <ingredients>\n")
		for j := 0; j < len(cakes.Cake[i].Ingredients); j++ {
			fmt.Printf("            <item>\n")
			fmt.Printf("                <itemname>%s</itemname>\n", cakes.Cake[i].Ingredients[j].Ingredient_name)
			fmt.Printf("                <itemcount>%s</itemcount>\n", cakes.Cake[i].Ingredients[j].Ingredient_count)
			fmt.Printf("                <itemunit>%s</itemunit>\n", cakes.Cake[i].Ingredients[j].Ingredient_unit)
			fmt.Printf("            </item>\n")
		}
		fmt.Printf("        </ingredients>\n")
		fmt.Printf("    </cake>\n")
	}
	fmt.Printf("</recipes>\n")
}

func print_j(cakes cakes) {
	fmt.Printf("{\n")
	for i := 0; i < len(cakes.Cake); i++ {
		fmt.Printf("  \"cake\": [\n    {\n")
		fmt.Printf("      \"name\": \"%s\",\n", cakes.Cake[i].Name)
		fmt.Printf("      \"time\": \"%s\",\n", cakes.Cake[i].Time)
		fmt.Printf("      \"ingredients\": [\n")
		for j := 0; j < len(cakes.Cake[i].Ingredients); j++ {
			fmt.Printf("        {\n")
			fmt.Printf("          \"ingredient_name\": \"%s\",\n", cakes.Cake[i].Ingredients[j].Ingredient_name)
			fmt.Printf("          \"ingredient_count\": \"%s\"", cakes.Cake[i].Ingredients[j].Ingredient_count)
			if cakes.Cake[i].Ingredients[j].Ingredient_unit != "" {
				fmt.Printf(",\n          \"ingredient_unit\": \"%s\"\n", cakes.Cake[i].Ingredients[j].Ingredient_unit)
			}
			fmt.Printf("        }\n")
		}
		fmt.Printf("      ]\n")
		fmt.Printf("    }\n")
	}
	fmt.Printf("}\n")
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

func main() {
	var filename string
	flag.StringVar(&filename, "f", "empty", "a string var")
	flag.Parse()
	byteValue, flag := input(filename)
	if flag {
		if strings.Contains(filename, ".json") {
			var tmp DBReader = Cake_j{}
			cakes := tmp.reading(byteValue)
			print_x(cakes)
		} else if strings.Contains(filename, ".xml") {
			var tmp DBReader = Cake_x{}
			cakes := tmp.reading(byteValue)
			print_j(cakes)
		} else {
			fmt.Printf("ERROR: the file has wrong format\n")
		}
	}
}
