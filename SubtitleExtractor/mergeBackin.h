#pragma once

#include "Header.h"

template<typename ITER_T>
void mergeBackin(ITER_T begin, ITER_T end, const fs::path & sourceVideo, const fs::path & destVideo);

template<typename ITER_T>
void mergeBackin(ITER_T begin, ITER_T end, const fs::path& sourceVideo, const fs::path& destVideo)
{
	fs::path mkvmergePath = boost::process::search_path("mkvmerge");

	stringstream ss;

	ss << mkvmergePath << " -o " << destVideo << ' ' << sourceVideo << ' ';

	while (begin != end)
	{
		const SubtitleTrack& sub = *begin;
	
		ss << " --language 0:" << sub.language << ' ' << sub.pathToIDX << ' ';
		
		++begin;
	}

	//cout << "Should I call:\n\t" << ss.str() << "\n";
	//pause();

	// mkvmerge -o title_t02.new.mkv title_t02.mkv 
	//		--language 0:eng 4_en.idx 
	//		--language 0:eng 5_en.idx 
	//		--language 0:spa 6_sp.idx
	boost::process::system(ss.str());

	//while (mkvmerge.running()) {}
}