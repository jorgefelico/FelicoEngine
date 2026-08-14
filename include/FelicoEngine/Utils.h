#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

namespace FelicoEngine {
	class Utils {
	public:
		static std::string readFile(const char* filePath);
	};
}