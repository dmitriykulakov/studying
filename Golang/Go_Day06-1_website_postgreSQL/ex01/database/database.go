package database

import (
	"database/sql"
	"encoding/json"
	"fmt"
	"log"
	"os"

	_ "github.com/lib/pq"
)

type parseAdmin struct {
	Login    string `json:"login"`
	Password string `json:"password"`
}

type parseDatabase struct {
	DatabaseLogin    string `json:"login_database"`
	DatabasePassword string `json:"password_database"`
	DatabaseName     string `json:"name_database"`
	DatabaseCreate   string `json:"database_create"`
	DatabaseSelect   string `json:"database_select"`
}

func CreateDatabase() *sql.DB {
	db := ConnectDatabase()
	database := ParseDatabase()
	defer db.Close()
	_, err := db.Query(fmt.Sprintf(database.DatabaseSelect))
	if err != nil {
		log.Println(err)
		_, err := db.Exec(database.DatabaseCreate)
		if err != nil {
			log.Println("ERROR", err)
		}
	}
	return db
}

func ConnectDatabase() *sql.DB {
	database := ParseDatabase()
	connStr := fmt.Sprintf("user=%s password=%s dbname=%s sslmode=disable", database.DatabaseLogin, database.DatabasePassword, database.DatabaseName)
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		log.Fatal("ERROR", err)
	}
	return db
}

func ParseAdmin() parseAdmin {
	var admin parseAdmin
	conf, err := os.ReadFile("./database/admin_credentials.txt")
	if err != nil {
		log.Fatalf("file not found: %v", err)
	}
	err = json.Unmarshal(conf, &admin)
	if err != nil {
		log.Fatal(err)
	}
	return admin
}

func ParseDatabase() parseDatabase {
	var database parseDatabase

	conf, err := os.ReadFile("./database/admin_credentials.txt")
	if err != nil {
		log.Fatalf("file not found: %v", err)
	}
	err = json.Unmarshal(conf, &database)
	if err != nil {
		log.Fatal(err)
	}
	return database
}
