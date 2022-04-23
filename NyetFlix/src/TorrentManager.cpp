#include "TorrentManager.h"
#include "Log.h"

#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
using namespace lt;


TorrentManager::TorrentManager()
{
	settings_pack p;
	p.set_int(settings_pack::alert_mask, alert_category::status | alert_category::error);
	m_session.apply_settings(std::move(p));
}


void TorrentManager::addTorrent(const std::string &torrent)
{
	add_torrent_params atp = parse_magnet_uri(torrent);
	atp.save_path = ".";
	m_session.async_add_torrent(std::move(atp));
}


void TorrentManager::run()
{
	NF_CORE_INFO("Torrent manager started");

	torrent_handle handle;
	while (true)
	{
		vector<alert*> alerts;
		m_session.pop_alerts(&alerts);

		for (const auto &alert : alerts)
		{
			if (const auto &at = alert_cast<add_torrent_alert>(alert))
			{
				NF_CORE_INFO("Torrent started downloading");
				handle = at->handle;
			}

			if (alert_cast<torrent_finished_alert>(alert))
			{
				NF_CORE_INFO("Torrent finished");
			}

			if (const auto &st = alert_cast<state_update_alert>(alert))
			{
				if (st->status.empty()) continue;

				// TODO: map status to its handle, and hash for quick lookup, see st->status docs
				for (const auto &status : st->status)
				{
					NF_CORE_INFO("{} - Rate: {} kB/s\tProgress: {}%", status.name, status.download_payload_rate / 1000,
					             status.progress_ppm / 10000);
				}
			}
		}

		this_thread::sleep_for(chrono::milliseconds(500));
		m_session.post_torrent_updates();
	}
}
