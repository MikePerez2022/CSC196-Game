#include "FileIO.h"

namespace Kiko
{
	std::string getFilePath()
	{
		return std::filesystem::current_path().string();
	}
}