#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "nyetflix.grpc.pb.h"


using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using nyetflix::NyetFlixRPC;
using nyetflix::torrentURI;
using nyetflix::status;
using nyetflix::empty;

class NyetFlixClient
{
public:
	NyetFlixClient(std::shared_ptr<Channel> channel)
		: stub_(NyetFlixRPC::NewStub(channel))
	{
	}


	// Assembles the client's payload, sends it and presents the response back
	// from the server.
	std::string addTorrent(const std::string &torrent)
	{
		// Data we are sending to the server.
		torrentURI request;
		request.set_torrent(torrent);

		// Container for the data we expect from the server.
		empty reply;

		// Context for the client. It could be used to convey extra information to
		// the server and/or tweak certain RPC behaviors.
		ClientContext context;

		// The actual RPC.
		Status status = stub_->addTorrent(&context, request, &reply);

		// Act upon its status.
		if (status.ok())
		{
			return "Status ok!";
		}
		else
		{
			std::cout << status.error_code() << ": " << status.error_message()
				<< std::endl;
			return "RPC addTorrent failed";
		}
	}


	std::string getStatus()
	{
		empty req;
		status reply;

		ClientContext context;
		Status status = stub_->getStatus(&context, req, &reply);

		if (status.ok())
		{
			return reply.msg();
		}

		return "RPC getStatus failed";
	}


private:
	std::unique_ptr<NyetFlixRPC::Stub> stub_;
};


int main(int argc, char **argv)
{
	// Instantiate the client. It requires a channel, out of which the actual RPCs
	// are created. This channel models a connection to an endpoint specified by
	// the argument "--target=" which is the only expected argument.
	// We indicate that the channel isn't authenticated (use of
	// InsecureChannelCredentials()).
	std::string target_str = "localhost:50051";

	NyetFlixClient nfClient(
		grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
	std::string torrent("magnet:?xt=urn:abcdefg");
	std::string reply = nfClient.addTorrent(torrent);
	std::string status = nfClient.getStatus();
	std::cout << "Torrent status: " << status << std::endl;

	return 0;
}
