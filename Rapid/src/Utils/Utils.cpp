#include "Utils.h"

namespace Rapid
{
	namespace Utils
	{
		
		std::string ReadFile(const char* fileLocation)
		{
			std::string content;
			std::ifstream fileStream(fileLocation, std::ios::in);

			if(!fileStream.is_open())
			{
				std::cout << "Failed to read" << fileLocation << "! File does not exist. - Dosya Okunamadi!" << std::endl;
				return "";
			}
			std::string line = "";
			while(!fileStream.eof())
			{
				std::getline(fileStream, line);
				content.append(line + "\n");
			}

			fileStream.close();
			return content;
		}

	}
}