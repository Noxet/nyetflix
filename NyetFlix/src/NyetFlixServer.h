#pragma once

#include <grpc++/grpc++.h>

#include "nyetflix.grpc.pb.h"

using grpc::Status;
using grpc::Server;
using grpc::ServerBuilder;
using nyetflix::NyetFlixRPC;
using nyetflix::HelloReply;
using nyetflix::HelloRequest;


class NyetFlixServer
{
	class NyetFlixRPCImpl *m_service;
	ServerBuilder m_builder;
	std::unique_ptr<Server> m_server;

public:
	explicit NyetFlixServer(const std::string &address);
	~NyetFlixServer();

	// We don't want to copy or move this class
	NyetFlixServer(const NyetFlixServer &other) = delete;
	NyetFlixServer(NyetFlixServer &&other) noexcept = delete;
	NyetFlixServer& operator=(const NyetFlixServer &other) = delete;
	NyetFlixServer& operator=(NyetFlixServer &&other) noexcept = delete;

	// Starts the RPC server and the torrent manager thread
	void run();
};
