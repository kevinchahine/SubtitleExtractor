#pragma once

#include "Track.h"

#include <iostream>
#include <string>
#include <vector>
#include <deque>

#include <boost/process.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem/path.hpp>

namespace pt = boost::property_tree;
namespace fs = boost::filesystem;

using namespace std;

inline void pause()
{
	cout << "Press any key...";
	cin.get();
}