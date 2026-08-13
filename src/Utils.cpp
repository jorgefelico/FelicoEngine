#include "Utils.h"

namespace FelicoEngine {
	std::string Utils::readFile(const char* filePath) {
		std::ifstream file(filePath);
		if (!file.is_open()) {
			printf("There was an error opening file: %s", filePath);
			return "";
		}

		std::stringstream buffer;
		buffer << file.rdbuf();

		std::string file_contents = buffer.str();
		return file_contents;
	}
}