#include <iostream>

#include "Log.h"

#include <libtorrent/session.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/magnet_uri.hpp>


using namespace std;


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "Usage: nyetflix <magnet url>" << endl;
	}

	lt::session sess;

	lt::add_torrent_params atp = lt::parse_magnet_uri(argv[1]);
	atp.save_path = ".";
	lt::torrent_handle handle = sess.add_torrent(atp);

	NyetFlix::Log::init();
	NF_CORE_TRACE("Testing log");

	NF_CORE_WARN("Testing warning");

	cout << "Torrent info:" << endl;
	cout << "name: " << atp.name << endl;
	cout << "tracker id: " << atp.trackerid << endl;

	cout << "Seeds:" << endl;
	for (const auto &seed : handle.http_seeds())
	{
		cout << seed << endl;
	}
}
