#include "Test.h"

#include <iostream>
#include <libtorrent/session.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/magnet_uri.hpp>
#include <libtorrent/alert_types.hpp>

using namespace lt;
using namespace std;


void Test::run(std::string uri)
{
	session sess;

	try
	{
		add_torrent_params atp = parse_magnet_uri(uri);
		atp.save_path = ".";
		torrent_handle h = sess.add_torrent(std::move(atp));
		atp.save_path = "..";
	}
	catch (lt::system_error &e)
	{
		cout << e.what() << endl;
	}


	/*
	 * Instead of sleeping for a time when querying alerts, use
	 * void set_alert_notify(std::function<void()> const& fun);
	 * See row 1016 in "session_handle.hpp"
	 */
}
