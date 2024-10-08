/*
 * Candy Server
 *
 * No description provided (generated by Swagger Codegen https://github.com/swagger-api/swagger-codegen)
 *
 * API version: 1.0.0
 * Generated by: Swagger Codegen (https://github.com/swagger-api/swagger-codegen.git)
 */

package main

import (
	"crypto/tls"
	"fmt"
	"log"
	sw "main/go"
	"net/http"
)

func getServer() *http.Server {
	// data, _ := ioutil.ReadFile("minica.pem")
	// cp, _ := x509.SystemCertPool()
	// cp.AppendCertsFromPEM(data)

	tls := &tls.Config{
		// ClientCAs:      cp,
		// ClientAuth:     tls.RequireAndVerifyClientCert,
		// GetCertificate: utils.CertReqFunc("cert.pem", "key.pem"),
	}
	server := &http.Server{
		Addr:      ":3333",
		TLSConfig: tls,
	}
	return server
}

func main() {

	server := getServer()
	http.HandleFunc("/buy_candy", sw.BuyCandy)
	log.Printf("Server started")
	err := server.ListenAndServe()
	//err := server.ListenAndServeTLS("", "")
	if err != nil {
		fmt.Println(err)
	}
}
