#include "RPCServer.h"

#include <iostream>
#include <string>

#include "Log.h"

using std::string;


Status NyetFlixRPCImpl::SayHello(grpc::ServerContext *context, const HelloRequest *request, HelloReply *response)
{
	const string prefix("Hello ");
	NF_CORE_INFO("Got message from client: {}", request->name());

	response->set_message(prefix + request->name());
	return Status::OK;
}


NyetFlixServer::NyetFlixServer(const std::string &address)
{
	m_builder.AddListeningPort(address, grpc::InsecureServerCredentials());
	m_builder.RegisterService(&m_service);
	m_server = m_builder.BuildAndStart();
}


void NyetFlixServer::run()
{
	NF_CORE_INFO("NyetFlix RPC server started");
	m_server->Wait();
}
