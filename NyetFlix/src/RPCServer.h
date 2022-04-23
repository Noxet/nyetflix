#pragma once

#include <grpc++/grpc++.h>

#include "nyetflix.grpc.pb.h"

using grpc::Status;
using grpc::Server;
using grpc::ServerBuilder;
using nyetflix::NyetFlixRPC;
using nyetflix::HelloReply;
using nyetflix::HelloRequest;

class NyetFlixRPCImpl final : public NyetFlixRPC::Service
{
	Status SayHello(grpc::ServerContext *context, const HelloRequest *request,
	                HelloReply *response) override;
};


class NyetFlixServer
{
	NyetFlixRPCImpl m_service;
	ServerBuilder m_builder;
	std::unique_ptr<Server> m_server;

public:
	NyetFlixServer(const std::string &address);

	void run();
};
