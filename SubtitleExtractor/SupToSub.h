#pragma once

#include "Header.h"

void supToSub(SubtitleTrack& subTrack);

// Returns paths to (VOB) subtitles
template<typename T_ITER>
void supToSub(T_ITER begin, T_ITER end);

template<typename T_ITER>
void supToSub(T_ITER begin, T_ITER end)
{
	while (begin != end) {
		SubtitleTrack & track = *begin;

		supToSub(track);

		++begin;
	}
}
