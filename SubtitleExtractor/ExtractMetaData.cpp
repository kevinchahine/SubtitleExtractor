#include "ExtractMetaData.h"
#include "ExtractTracks.h"

#include <boost/property_tree/json_parser.hpp>

vector<SubtitleTrack> extractMetaData(const fs::path& videoPath)
{
	fs::path mkvmergePath = boost::process::search_path("mkvmerge");
	cout << mkvmergePath << '\n';

	cout << "Extracting metadata from: " << endl
		<< "\t" << videoPath.string() << endl;

	boost::process::ipstream is;
	boost::process::child mkvChild(mkvmergePath, "-i", "--identification-format", "json", videoPath, boost::process::std_out > is);

	string line;
	stringstream ss;
	while (mkvChild.running() && getline(is, line)/* && !line.empty()*/)
	{
		///cout << line << endl;
		ss << line << endl;
	}

	mkvChild.wait();

	do {
		getline(is, line);
		ss << line << endl;
	} while (!line.empty());

	boost::property_tree::ptree tree;
	boost::property_tree::read_json(ss, tree);
	///boost::property_tree::write_json(cout, tree);

	vector<SubtitleTrack> subtitleTracks = extractSubtitleTracks(tree);

	for (auto& track : subtitleTracks) {
		if (track.language == "eng") {
			track.sourceFile = videoPath;
		}
	}

	cout << subtitleTracks.size() << " subtitles extracted\n";

	return subtitleTracks;
}
