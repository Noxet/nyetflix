#include "Test.h"

#include <iostream>
#include <libtorrent/session.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/magnet_uri.hpp>
#include <libtorrent/alert_types.hpp>

#include <format>
#include <thread>
#include <chrono>

using namespace lt;
using namespace std;


char const* state(torrent_status::state_t s)
{
	switch (s)
	{
	case lt::torrent_status::checking_files: return "checking";
	case lt::torrent_status::downloading_metadata: return "dl metadata";
	case lt::torrent_status::downloading: return "downloading";
	case lt::torrent_status::finished: return "finished";
	case lt::torrent_status::seeding: return "seeding";
	case lt::torrent_status::checking_resume_data: return "checking resume";
	default: return "<>";
	}
}


void Test::run(std::string uri)
{
	try
	{
		settings_pack p;

		p.set_int(settings_pack::alert_mask, alert_category::status | alert_category::error);
		session sess(std::move(p));

		add_torrent_params atp = parse_magnet_uri(uri);
		atp.save_path = ".";
		torrent_handle h = sess.add_torrent(std::move(atp));

		bool active{ true };
		bool newAlerts{ false };
		sess.set_alert_notify([&newAlerts]() { newAlerts = true; });

		while (active)
		{
			std::vector<alert*> alerts;
			sess.pop_alerts(&alerts);

			for (const auto &a : alerts)
			{
				switch (a->type())
				{
				case torrent_added_alert::alert_type:
				case file_completed_alert::alert_type:
				case torrent_finished_alert::alert_type:
					cout << std::format("Alert: [CAT: ] [TYPE: {}] - {}\n\t{}", a->type(), a->message(),
					                    a->what()) << endl;
					break;
				case udp_error_alert::alert_type:
					cout << "UDP error" << endl;
				//auto *p = static_cast<udp_error_alert*>(a);
				//cout << p->message() << "\t" << p->error << ", " << operation_name(p->operation) << endl;
					break;
				}

				if (const auto st = alert_cast<state_update_alert>(a))
				{
					if (st->status.empty()) continue;

					for (const auto &ts : st->status)
					{
						cout << std::format("{}\t{} kB/s\t{} kB\t{}% downloaded\t({} peers)\x1b[K", state(ts.state),
						                    ts.download_payload_rate / 1000, ts.total_done / 1000,
						                    ts.progress_ppm / 10000, ts.num_peers) << endl;
					}
				}

				if (alert_cast<torrent_finished_alert>(a))
				{
					active = false;
				}

				sess.post_torrent_updates();

				//while (!newAlerts) {}
				//newAlerts = false;

				std::this_thread::sleep_for(std::chrono::milliseconds(200));
			}
		}

		cout << "Torrent finished" << endl;
	}
	catch (lt::system_error &e)
	{
		cout << e.what() << endl;
	}
}
