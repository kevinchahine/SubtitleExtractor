#include "Header.h"
#include "ExtractMetaData.h"
#include "ExtractTracks.h"
#include "extractSubtitles.h"
#include "SupToSub.h"
#include "mergeBackin.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;

void fixSubs(const fs::path& videoPath, const fs::path & dstPath);

int main()
{
	fs::path srcPath(
		//	R"dil(E:\Video\Revenge of the Sith\Revenge of the Sith_t01.mkv)dil"
		R"dil(D:\Users\kchah\Videos\MKV\Dark Kniught\)dil"
	);
	fs::path dstPath(
		R"dil(D:\Users\kchah\Videos\MKV\Dark Kniught\subtitles)dil"
	);

	if (!fs::exists(dstPath) && fs::is_directory(dstPath)) {
		fs::create_directory(dstPath);
	}

	if (fs::is_directory(srcPath)) {
		auto it = fs::directory_iterator(srcPath);
		auto end = fs::directory_iterator();

		while (it != end) {
			const fs::path & p = it->path();

			if (p.has_extension() && p.extension() == ".mkv") {
				fixSubs(p, dstPath / p.filename());
			}
			else {
				cout << "skipping non mkv " << p << endl;
			}

			it++;
		}
	}
	else if (fs::is_regular_file(srcPath)) {
		if (srcPath.has_extension() && srcPath.extension() == ".mkv") {
			fixSubs(srcPath, dstPath / srcPath.filename());
		}
		else {
			cout << srcPath << " is not an mkv file" << endl;
		}               
	}
	
	cout << "Press any key...";
	cin.get();
	return 0;
}

void fixSubs(const fs::path& videoPath, const fs::path& dstPath)
{
	vector<SubtitleTrack> subtitleTracks = extractMetaData(videoPath);

	extractSubtitles(videoPath, subtitleTracks.begin(), subtitleTracks.end());

	supToSub(subtitleTracks.begin(), subtitleTracks.end());

	mergeBackin(subtitleTracks.begin(), subtitleTracks.end(), videoPath, dstPath);
}