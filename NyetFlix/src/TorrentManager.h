#pragma once

#include <libtorrent/session.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/magnet_uri.hpp>
#include <libtorrent/alert_types.hpp>

class TorrentManager
{
public:
	TorrentManager();
	/**
	 * @brief Adds a new torrent to the current session, to be downloaded.
	 * @param torrent A magnet URI for the torrent. TODO: make it handle torrent files too
	 */
	void addTorrent(const std::string &torrent);

	/**
	 * @brief Starts the main (infinite) loop of the torrent manager.
	 *
	 * The loop handles everything torrent-related.
	 * It responds to added torrent, prints status information and so on.
	*/
	void run();

private:
	lt::session m_session{};
};
