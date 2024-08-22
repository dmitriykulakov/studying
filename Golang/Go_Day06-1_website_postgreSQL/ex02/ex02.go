package main

import (
	"fmt"
	"log"
	"net/http"
	"os/exec"
	"regexp"
	"strings"
	"text/template"
	"time"

	database "ex02/database"

	"github.com/gorilla/mux"
	"golang.org/x/time/rate"
)

type Article struct {
	Id          int
	Title       string
	ArticleText string
}

var adminStatus int = 0
var page uint = 1
var limitConnect = rate.NewLimiter(rate.Every(time.Second), 100)

func homePage(w http.ResponseWriter, r *http.Request) {
	if !limitConnect.Allow() {
		http.Error(w, "429 "+http.StatusText(http.StatusTooManyRequests), http.StatusTooManyRequests)
		return
	}
	t, err := template.ParseFiles("html/main.html", "html/header.html", "html/footer.html")
	if err != nil {
		log.Fatal(err)
	}
	var articles []Article
	db := database.ConnectDatabase()
	defer db.Close()
	count, _ := db.Query("select count(*) from articles")
	defer count.Close()
	count.Next()
	var databaseCount uint
	count.Scan(&databaseCount)
	for (page-1)*3 >= databaseCount {
		page--
	}
	rows, err := db.Query("SELECT* FROM articles")
	if err != nil {
		log.Fatal(err)
	}
	defer rows.Close()
	for currentArticle := 0; rows.Next(); currentArticle++ {
		var article Article
		rows.Scan(&article.Id, &article.Title, &article.ArticleText)
		if (uint)(currentArticle) >= (page-1)*3 && (uint)(currentArticle) < (page)*3 {
			articles = append(articles, article)
		}
	}
	t.ExecuteTemplate(w, "main", &articles)
}

func adminPage(w http.ResponseWriter, r *http.Request) {
	t, err := template.ParseFiles("html/admin.html", "html/header.html", "html/footer.html")
	if err != nil {
		log.Fatal(err)
	}
	t.ExecuteTemplate(w, "admin", adminStatus)
}

func saveArticle(w http.ResponseWriter, r *http.Request) {
	login := r.FormValue("login")
	password := r.FormValue("password")
	title := r.FormValue("title")
	text := r.FormValue("text")
	admin := database.ParseAdmin()
	if login == admin.Login && password == admin.Password {
		http.Redirect(w, r, "/admin", http.StatusSeeOther)
		adminStatus = 1
		db := database.ConnectDatabase()
		defer db.Close()
		_, err := db.Exec(fmt.Sprintf("INSERT into articles values (default, '%s', '%s')", title, text))
		if err != nil {
			log.Println("ERROR", err)
		}
	} else {
		http.Redirect(w, r, "/admin", http.StatusSeeOther)
		adminStatus = 2
	}
}

func changeMain(w http.ResponseWriter, r *http.Request) {
	var pageStr = r.FormValue("button")
	if pageStr == "0" {
		page = 1
	}
	if pageStr == "1" {
		page++
	}
	http.Redirect(w, r, "/", http.StatusSeeOther)
}

func openArticle(w http.ResponseWriter, r *http.Request) {
	t, err := template.ParseFiles("html/article.html", "html/header.html", "html/footer.html")
	if err != nil {
		log.Fatal(err)
	}
	db := database.ConnectDatabase()
	defer db.Close()
	id := (mux.Vars(r))["article_id"]
	rows, err := db.Query(fmt.Sprintf("SELECT * FROM articles WHERE id = %s", id))
	if err != nil {
		log.Fatal(err)
	}
	defer rows.Close()
	var article Article
	rows.Next()
	rows.Scan(&article.Id, &article.Title, &article.ArticleText)
	article.ArticleText = markdownConvert(article.ArticleText)

	t.ExecuteTemplate(w, "article", &article)
}

func markdownConvert(article string) string {
	var articleMarkdown string
	lines := strings.SplitAfter(article, "\n")
	for _, i := range lines {
		if strings.Contains(i, "###") {
			i = fmt.Sprintln(strings.Replace(i, "###", "<h3>", 10), "</h3>")
		}
		if strings.Contains(i, "](") {
			reName := regexp.MustCompile(`\[([^\[\]\(\)]*)\]\(`)
			nameLink := reName.FindAllStringSubmatch(i, -1)
			reLink := regexp.MustCompile(`\]\(([^\[\]\(\)]*)\)`)
			link := reLink.FindAllStringSubmatch(i, -1)
			for n := 0; n < len(nameLink); n++ {
				i = strings.ReplaceAll(i, fmt.Sprintf("[%s](%s)", nameLink[n][1], link[n][1]), fmt.Sprintf("<a href=\"%s\" class=\"link\">%s</a>", link[n][1], nameLink[n][1]))
			}
		}
		articleMarkdown += i
	}
	articleMarkdown = strings.ReplaceAll(articleMarkdown, "\n", "<br>")
	return articleMarkdown
}

func Handle() {
	router := mux.NewRouter()
	router.HandleFunc("/", homePage).Methods("GET")
	router.HandleFunc("/admin", adminPage).Methods("GET")
	router.HandleFunc("/admin/", adminPage).Methods("GET")
	router.HandleFunc("/save_article", saveArticle).Methods("POST")
	router.HandleFunc("/change_main", changeMain).Methods("POST")
	router.HandleFunc("/open_article/{article_id:[0-9]+}", openArticle).Methods("GET")
	http.Handle("/", router)
	http.Handle("/html/statics/", http.StripPrefix("/html/statics/", http.FileServer((http.Dir("./html/statics/")))))
	log.Printf("Server started")
	http.ListenAndServe(":8888", nil)
}

func Unzip() {
	cmd := exec.Command("unzip", "-o", "./html/statics.zip", "-d", "./html/")
	err := cmd.Run()
	if err != nil {
		log.Println(err)
	}
}

func main() {
	Unzip()
	database.CreateDatabase()
	Handle()
}
