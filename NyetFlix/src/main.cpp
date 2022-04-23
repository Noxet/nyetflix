#include <iostream>
#include <future>

#include "Log.h"
#include "TorrentManager.h"
#include "RPCServer.h"


using namespace std;


int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "Usage: nyetflix <magnet url>" << endl;
	}

	NyetFlix::Log::init();
	NF_CORE_TRACE("Testing log");

	NyetFlixServer server("0.0.0.0:50051");
	server.run();


	/*
	TorrentManager tm;
	auto f = async(&TorrentManager::run, &tm);
	cout << "started run() async" << endl;

	cout << "Try to add yet another torrent" << endl;
	tm.addTorrent(argv[1]);
	tm.addTorrent(argv[2]);
	cout << "Torrent added" << endl;
	*/

	/*
	NF_CORE_WARN("Testing warning");

	cout << "Torrent info:" << endl;
	cout << "name: " << atp.name << endl;
	cout << "tracker id: " << atp.trackerid << endl;

	cout << "Seeds:" << endl;
	for (const auto &seed : handle.http_seeds())
	{
		cout << seed << endl;
	}
	*/
}
