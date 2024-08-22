package main

import (
	"fmt"
	"reflect"
)

type UnknownPlant struct {
	FlowerType int `color_type:"int"`
	LeafTypef  string
	Color      int `color_scheme:"rgb"`
}

type AnotherUnknownPlant struct {
	FlowerColor int
	LeafType    string
	Height      int `unit:"inches"`
}

func describePlant(v interface{}) {
	Value := reflect.ValueOf(v)
	for i := 0; i < Value.NumField(); i++ {
		fmt.Printf("%s", Value.Type().Field(i).Name)
		if Value.Type().Field(i).Tag != "" {
			fmt.Printf("(%s)", Value.Type().Field(i).Tag)
		}
		fmt.Printf(":%v\n", Value.Field(i))
	}
}

func main() {
	var plant = UnknownPlant{20, "fgh", 10}
	var plant2 = AnotherUnknownPlant{10, "lanceolate", 15}
	describePlant(plant)
	describePlant(plant2)
}
