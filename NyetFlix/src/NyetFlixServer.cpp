#include "NyetFlixServer.h"

#include <iostream>
#include <string>
#include <future>

#include "Log.h"
#include "TorrentManager.h"

using std::string;

/**
 * @brief The actual implementation of the RPC functions.
 *
 * The user is not meant to see this, rather they should just create
 * a NetFlixServer object to initialize everything and then call run on it.
 */
class NyetFlixRPCImpl final : public NyetFlixRPC::Service
{
	TorrentManager m_torrentManager;
	std::future<void> torrentAsync;

public:
	void run()
	{
		torrentAsync = std::async(std::launch::async, &TorrentManager::run, &m_torrentManager);
	}


	void wait() const
	{
		torrentAsync.wait();
	}


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
	m_service->run();
	// wait for threads to close.
	m_server->Wait();
	m_service->wait();
}
