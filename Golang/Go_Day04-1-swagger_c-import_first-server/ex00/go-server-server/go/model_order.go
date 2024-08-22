/*
 * Candy Server
 *
 * No description provided (generated by Swagger Codegen https://github.com/swagger-api/swagger-codegen)
 *
 * API version: 1.0.0
 * Generated by: Swagger Codegen (https://github.com/swagger-api/swagger-codegen.git)
 */

package goo

type Order struct {

	// amount of money put into vending machine
	Money int32 `json:"money"`

	// kind of candy
	CandyType string `json:"candyType"`

	// number of candy
	CandyCount int32 `json:"candyCount"`
}
