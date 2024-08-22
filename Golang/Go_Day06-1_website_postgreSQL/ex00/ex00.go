package main

import (
	"image"
	"image/color"
	"image/png"
	"log"
	"os"
)

type Square struct {
	x int
	y int
}

func main() {
	width := 300
	height := 300

	upLeft := image.Point{0, 0}
	lowRight := image.Point{width, height}
	img := image.NewRGBA(image.Rectangle{upLeft, lowRight})
	purpleSquare := []Square{{37, 62}, {72, 62}, {107, 62}, {142, 97}, {107, 132}, {72, 132}, {37, 167}, {72, 202}, {107, 202}, {142, 202}, {193, 62}, {228, 97}, {228, 132}, {228, 167}, {228, 202}}
	cyan := color.RGBA{100, 200, 200, 0xff}
	purpl := color.RGBA{128, 0, 255, 0xff}
	for x := 0; x < width; x++ {
		for y := 0; y < height; y++ {
			switch {
			case x < 5 || y < 5 || x > 294 || y > 294:
				img.Set(x, y, color.Black)
			default:
				img.Set(x, y, cyan)
			}
		}
	}
	for _, square := range purpleSquare {
		for x := square.x; x < square.x+35; x++ {
			for y := square.y; y < square.y+35; y++ {
				img.Set(x, y, purpl)
			}
		}
	}

	f, err := os.Create("../image.png")
	if err != nil {
		log.Fatal(err)
	}
	png.Encode(f, img)
}
