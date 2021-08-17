#include "SupToSub.h"
#include "Globals.h"

#include "LanguageMap.h"

void supToSub(SubtitleTrack & subTrack)
{
	fs::path javaPath = boost::process::search_path("java");
	if (javaPath.empty()) {
		cout << "Could not find path to java executable. Make sure its in system PATH\n";
		return;
	}
	else {
		//cout << javaPath << endl;
	}

	fs::path bdsup2subPath(R"dil(C:\Program Files\BDSup2Sub\BDSup2Sub512.jar)dil");
	if (!fs::exists(bdsup2subPath)) {
		cout << "Could not find "
			<< bdsup2subPath.filename()
			<< " Make sure it is in " << bdsup2subPath.parent_path() << endl;
		return;
	}
	else {
		//cout << bdsup2subPath << endl;
	}

	string lang;
	auto it = g_languageMap.right.find(subTrack.language);
	if (it == g_languageMap.right.end()) {
		cout << "Could not find ISO language for " << subTrack.language
			<< ". Defaulting to english. "
			<< "See LanguageMap.cpp for a list of supported languages" << endl;

		lang = "eng";
	}
	else {
		lang = it->get_left();
	}

	subTrack.pathToIDX = subTrack.pathToPGS;
	subTrack.pathToIDX.replace_extension(".idx");

	//cout << "Input file: " << subTrack.pathToPGS << endl;

	// ex:
	//	java -jar BDSup2Sub.jar --language <lang> -o <output> <input>
	boost::process::child java(javaPath, "-jar", bdsup2subPath, 
		"--language", lang, 
		"-o", subTrack.pathToIDX, subTrack.pathToPGS);
	
	while (java.running()) {
	}
}
