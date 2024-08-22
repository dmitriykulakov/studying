package dataRead

import (
	"encoding/json"
	"log"
	"os"
)

type ViewData struct {
	Title                    string     `json:"Title"`
	Function_describe        string     `json:"Function_describe"`
	Variables_describe       []Variable `json:"Variables_describe"`
	Function_return          string     `json:"Function_return"`
	Function_return_describe string     `json:"Function_return_describe"`
	Title_of_changes         string     `json:"Title_of_changes"`
	Changes                  []Change   `json:"Changes "`
	Examples                 []Example  `json:"Examples"`
	Conclusion               string     `json:"Conclusion"`
}

type Variable struct {
	Variable string `json:"Variable"`
}

type Change struct {
	Change string `json:"Change"`
}

type Example struct {
	Example string `json:"Example"`
}

func (data *ViewData) DataRead() (res ViewData) {
	file, err := os.ReadFile("./dataRead/data.json")
	if err != nil {
		log.Fatal(err)
	}
	err = json.Unmarshal(file, &data)
	if err != nil {
		log.Fatal(err)
	}
	return res
}
