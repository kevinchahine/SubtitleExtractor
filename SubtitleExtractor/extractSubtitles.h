#pragma once

#include "Header.h"

#include <boost/filesystem/path.hpp>

// Calls mkvextract to generate a Bluray format (PGS) subtitle files
// .sup file is written to same directory as .mkv file
// Returns path to the .sup file that is generated
template<typename T_ITER>
void extractSubtitles(const fs::path& mkvPath, T_ITER begin, T_ITER endz);

//void extractSubtitles(, T_ITER dst)
//{
//	for (begin; begin != end; begin++) {
//		fs::path subtitlePath = extractSubtitles(mkvPath, *begin);
//
//		dst->pathToPGS = subtitlePath;
//		
//		++dst;
//	}
//}

template<typename T_ITER>
void extractSubtitles(const fs::path& mkvPath, T_ITER begin, T_ITER end)
{
	fs::path outPath = fs::current_path(); ///mkvPath.parent_path();
	fs::path mkvextractPath = boost::process::search_path("mkvextract");

	if (mkvextractPath.empty()) {
		cout << "mkvextract app not found" << endl;
	}
	else {
		cout << mkvextractPath << endl;
		// mkvextract The\ Phantom\ Menace.mkv tracks 11:11_eng.sup
		// Determine filename and extension
		stringstream ss;
		ss << mkvextractPath << ' ' << mkvPath << " tracks "; 
		
		while (begin != end) {
			SubtitleTrack& track = *begin;

			track.pathToPGS = outPath / string(track.trackID + "_" + track.language + ".sup");

			ss << track.trackID << ':' << track.pathToPGS << ' ';

			begin++;
		}
		outPath.append(ss.str());

		// Call mkvextraxt
		boost::process::system(ss.str());
	}
}
