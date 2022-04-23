#include "NyetFlixServer.h"

#include <iostream>
#include <string>

#include "Log.h"

using std::string;

/**
 * @brief The actual implementation of the RPC functions.
 *
 * The user is not meant to see this, rather they should just create
 * a NetFlixServer object to initialize everything and then call run on it.
 */
class NyetFlixRPCImpl final : public NyetFlixRPC::Service
{
	Status SayHello(grpc::ServerContext *context, const HelloRequest *request,
	                HelloReply *response) override
	{
		const string prefix("Hello ");
		NF_CORE_INFO("Got message from client: {}", request->name());

		response->set_message(prefix + request->name());
		return Status::OK;
	}
};


NyetFlixServer::NyetFlixServer(const std::string &address) : m_service(new NyetFlixRPCImpl())
{
	m_builder.AddListeningPort(address, grpc::InsecureServerCredentials())
	         .RegisterService(m_service);
	m_server = m_builder.BuildAndStart();
}


NyetFlixServer::~NyetFlixServer()
{
	delete m_service;
}


void NyetFlixServer::run()
{
	NF_CORE_INFO("NyetFlix RPC server started");
	m_server->Wait();
}
