#pragma once
#include <string>
#include <vector>

#include <libtorrent/session.hpp>

using namespace std;

class Test
{
public:
	Test();
	void run();
	void addTorrent(std::string uri);

private:
	lt::session m_sess;
	std::vector<lt::torrent_handle> thandles{};
};
