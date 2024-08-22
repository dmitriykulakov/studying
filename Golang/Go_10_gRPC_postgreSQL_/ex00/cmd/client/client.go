package main

import (
	"context"
	gRPC "ex00/proto"
	"fmt"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"log"
)

func main() {
	conn, err := grpc.NewClient("localhost:3333", grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		log.Fatalf("error connecting to server: %v", err)
	}
	defer conn.Close()
	client := gRPC.NewTransmitterClient(conn)
	resp, err := client.Transmit(context.Background(), &gRPC.Request{})
	if err != nil {
		log.Fatalf("error sending request: %v", err)
	}
	r, err := resp.Recv()
	if err != nil {
		log.Fatalf("error connecting to server: %v", err)
	}
	fmt.Printf("Session_id: %v\nFrequency: %f\nTimestamp: %v\n", r.SessionId, r.Frequency, r.Timestamp.AsTime())
}
