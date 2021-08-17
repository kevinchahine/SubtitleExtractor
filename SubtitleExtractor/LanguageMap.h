#pragma once

#include "Header.h"

#include <boost/bimap.hpp>

class LanguageMap : public boost::bimap<string, string>
{
public:
	LanguageMap();
	LanguageMap(const LanguageMap&) = default;
	LanguageMap(LanguageMap&&) noexcept = default;
	~LanguageMap() noexcept = default;
	LanguageMap& operator=(const LanguageMap&) = default;
	LanguageMap& operator=(LanguageMap&&) noexcept = default;
	
};

