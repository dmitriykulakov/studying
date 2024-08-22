package main

import (
	dataRead "ex02/dataRead"
	"fmt"
	"html/template"
	"log"
	"net/http"
)

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		var data dataRead.ViewData
		data.DataRead()
		tmpl, err := template.ParseFiles("./docs/index.html")
		if err != nil {
			log.Fatal(err)
		}
		tmpl.Execute(w, data)
	})

	fmt.Println("Server is listening...")
	http.ListenAndServe(":8080", nil)
}
