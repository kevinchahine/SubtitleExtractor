#pragma once

#include "Header.h"

#include <iostream>
#include <string>
#include <vector>

#include <boost/filesystem/path.hpp>

using namespace std;

class Track
{
public:

public:
	string codec;
	string trackID;
	boost::filesystem::path sourceFile;
};

class SubtitleTrack : public Track
{
public:

public:
	string language;
	string number;
	boost::filesystem::path pathToPGS;
	boost::filesystem::path pathToIDX;
};
