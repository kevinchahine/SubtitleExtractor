#include "ExtractTracks.h"

#include <typeinfo>

#include <boost/property_tree/json_parser.hpp>

// T - Data type of the entries value
template <typename T>
T extractEntry(const pt::ptree& elem, const string& tag)
{
	auto op = elem.get_optional<T>(tag);
	if (op) {
		return op.get();
	}
	else {
		cout << "Entry does not have a tag named " << tag
			<< " or a value of type " << typeid(T).name() << endl;
		return T();	 // default value
	}
}

vector<SubtitleTrack> extractSubtitleTracks(const pt::ptree& root)
{
	vector<SubtitleTrack> tracks;
	tracks.reserve(50);	// TODO: Count # of tracks in ptree before reserving 

	{ // tracks
		boost::optional<const pt::ptree&> op = root.get_child_optional("tracks");// root.get_child("tracks");
		if (op) {
			const pt::ptree& tracksArray = op.get();

			pt::ptree::const_iterator it = tracksArray.begin();
			while (it != tracksArray.end()) {
				// it->first will be empty because we have an array (I think??)
				const pt::ptree& elem = it->second;

				cout << "element: " << elem.get<string>("id") << '\t';

				// --- Make sure its a subtitle track ---
				auto type = elem.get_optional<string>("type");
				if (type.has_value() && type.get() == "subtitles") {
					tracks.emplace_back();
					SubtitleTrack& track = tracks.back();

					track.codec = extractEntry<string>(elem, "codec");
					track.trackID = extractEntry<string>(elem, "id");

					{ // properties
						const pt::ptree& properties = elem.get_child("properties");

						track.language = extractEntry<string>(properties, "language");
						track.number = extractEntry<string>(properties, "number");
					} // properties
				}
				else {
					cout << "Skipping non subtitle track";
				}

				cout << endl;
				++it;
			}
		}
		else {
			cout << "JSON data did not contain a tracks array" << endl;
			cout << "do you want to see the JSON data (y or n): ";
			char answer;
			cin >> answer;
			answer = tolower(answer);
			if (answer == 'y') {
				pt::write_json(cout, root);
				pause();
			}
		}
	} // end tracks

	return tracks;
}
