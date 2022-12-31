#include <iostream>
#include <future>

#include "Log.h"
#include "TorrentManager.h"
#include "NyetFlixServer.h"

#include "Test.h"

using namespace std;


int main(int argc, char *argv[])
{
	//NyetFlix::Log::init();
	//NF_CORE_TRACE("Testing log");

	//NyetFlixServer server("0.0.0.0:50051");
	//server.run();


	//TorrentManager tm;
	//auto f = async(&TorrentManager::run, &tm);
	//cout << "started run() async" << endl;

	//cout << "Try to add yet another torrent" << endl;
	//tm.addTorrent(argv[1]);
	//tm.addTorrent(argv[2]);
	//cout << "Torrent added" << endl;


	//NF_CORE_WARN("Testing warning");

	//cout << "Torrent info:" << endl;
	//cout << "name: " << atp.name << endl;
	//cout << "tracker id: " << atp.trackerid << endl;

	//cout << "Seeds:" << endl;
	//for (const auto &seed : handle.http_seeds())
	//{
	//	cout << seed << endl;
	//}

	Test t;
	t.run(
		{
			"magnet:?xt=urn:btih:dd8255ecdc7ca55fb0bbf81323d87062db1f6d1c&dn=Big+Buck+Bunny&tr=udp%3A%2F%2Fexplodie.org%3A6969&tr=udp%3A%2F%2Ftracker.coppersurfer.tk%3A6969&tr=udp%3A%2F%2Ftracker.empire-js.us%3A1337&tr=udp%3A%2F%2Ftracker.leechers-paradise.org%3A6969&tr=udp%3A%2F%2Ftracker.opentrackr.org%3A1337&tr=wss%3A%2F%2Ftracker.btorrent.xyz&tr=wss%3A%2F%2Ftracker.fastcast.nz&tr=wss%3A%2F%2Ftracker.openwebtorrent.com&ws=https%3A%2F%2Fwebtorrent.io%2Ftorrents%2F&xs=https%3A%2F%2Fwebtorrent.io%2Ftorrents%2Fbig-buck-bunny.torrent",
			"magnet:?xt=urn:btih:c9e15763f722f23e98a29decdfae341b98d53056&dn=Cosmos+Laundromat&tr=udp%3A%2F%2Fexplodie.org%3A6969&tr=udp%3A%2F%2Ftracker.coppersurfer.tk%3A6969&tr=udp%3A%2F%2Ftracker.empire-js.us%3A1337&tr=udp%3A%2F%2Ftracker.leechers-paradise.org%3A6969&tr=udp%3A%2F%2Ftracker.opentrackr.org%3A1337&tr=wss%3A%2F%2Ftracker.btorrent.xyz&tr=wss%3A%2F%2Ftracker.fastcast.nz&tr=wss%3A%2F%2Ftracker.openwebtorrent.com&ws=https%3A%2F%2Fwebtorrent.io%2Ftorrents%2F&xs=https%3A%2F%2Fwebtorrent.io%2Ftorrents%2Fcosmos-laundromat.torrent"
		});
}
