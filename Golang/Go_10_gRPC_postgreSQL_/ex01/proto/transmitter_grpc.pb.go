// Code generated by protoc-gen-go-grpc. DO NOT EDIT.
// versions:
// - protoc-gen-go-grpc v1.2.0
// - protoc             v4.25.1
// source: transmitter.proto

package proto

import (
	context "context"
	grpc "google.golang.org/grpc"
	codes "google.golang.org/grpc/codes"
	status "google.golang.org/grpc/status"
)

// This is a compile-time assertion to ensure that this generated file
// is compatible with the grpc package it is being compiled against.
// Requires gRPC-Go v1.32.0 or later.
const _ = grpc.SupportPackageIsVersion7

// TransmitterClient is the client API for Transmitter service.
//
// For semantics around ctx use and closing/ending streaming RPCs, please refer to https://pkg.go.dev/google.golang.org/grpc/?tab=doc#ClientConn.NewStream.
type TransmitterClient interface {
	Transmit(ctx context.Context, in *Request, opts ...grpc.CallOption) (Transmitter_TransmitClient, error)
}

type transmitterClient struct {
	cc grpc.ClientConnInterface
}

func NewTransmitterClient(cc grpc.ClientConnInterface) TransmitterClient {
	return &transmitterClient{cc}
}

func (c *transmitterClient) Transmit(ctx context.Context, in *Request, opts ...grpc.CallOption) (Transmitter_TransmitClient, error) {
	stream, err := c.cc.NewStream(ctx, &Transmitter_ServiceDesc.Streams[0], "/transmitter.Transmitter/Transmit", opts...)
	if err != nil {
		return nil, err
	}
	x := &transmitterTransmitClient{stream}
	if err := x.ClientStream.SendMsg(in); err != nil {
		return nil, err
	}
	if err := x.ClientStream.CloseSend(); err != nil {
		return nil, err
	}
	return x, nil
}

type Transmitter_TransmitClient interface {
	Recv() (*Response, error)
	grpc.ClientStream
}

type transmitterTransmitClient struct {
	grpc.ClientStream
}

func (x *transmitterTransmitClient) Recv() (*Response, error) {
	m := new(Response)
	if err := x.ClientStream.RecvMsg(m); err != nil {
		return nil, err
	}
	return m, nil
}

// TransmitterServer is the server API for Transmitter service.
// All implementations must embed UnimplementedTransmitterServer
// for forward compatibility
type TransmitterServer interface {
	Transmit(*Request, Transmitter_TransmitServer) error
	mustEmbedUnimplementedTransmitterServer()
}

// UnimplementedTransmitterServer must be embedded to have forward compatible implementations.
type UnimplementedTransmitterServer struct {
}

func (UnimplementedTransmitterServer) Transmit(*Request, Transmitter_TransmitServer) error {
	return status.Errorf(codes.Unimplemented, "method Transmit not implemented")
}
func (UnimplementedTransmitterServer) mustEmbedUnimplementedTransmitterServer() {}

// UnsafeTransmitterServer may be embedded to opt out of forward compatibility for this service.
// Use of this interface is not recommended, as added methods to TransmitterServer will
// result in compilation errors.
type UnsafeTransmitterServer interface {
	mustEmbedUnimplementedTransmitterServer()
}

func RegisterTransmitterServer(s grpc.ServiceRegistrar, srv TransmitterServer) {
	s.RegisterService(&Transmitter_ServiceDesc, srv)
}

func _Transmitter_Transmit_Handler(srv interface{}, stream grpc.ServerStream) error {
	m := new(Request)
	if err := stream.RecvMsg(m); err != nil {
		return err
	}
	return srv.(TransmitterServer).Transmit(m, &transmitterTransmitServer{stream})
}

type Transmitter_TransmitServer interface {
	Send(*Response) error
	grpc.ServerStream
}

type transmitterTransmitServer struct {
	grpc.ServerStream
}

func (x *transmitterTransmitServer) Send(m *Response) error {
	return x.ServerStream.SendMsg(m)
}

// Transmitter_ServiceDesc is the grpc.ServiceDesc for Transmitter service.
// It's only intended for direct use with grpc.RegisterService,
// and not to be introspected or modified (even as a copy)
var Transmitter_ServiceDesc = grpc.ServiceDesc{
	ServiceName: "transmitter.Transmitter",
	HandlerType: (*TransmitterServer)(nil),
	Methods:     []grpc.MethodDesc{},
	Streams: []grpc.StreamDesc{
		{
			StreamName:    "Transmit",
			Handler:       _Transmitter_Transmit_Handler,
			ServerStreams: true,
		},
	},
	Metadata: "transmitter.proto",
}
