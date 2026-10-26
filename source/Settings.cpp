#include "Settings.h"

#include <windows.h>

namespace settings
{
	namespace
	{
		std::string ReadString(const char* a_section, const char* a_key, const std::string& a_path)
		{
			char buf[128]{};
			GetPrivateProfileStringA(a_section, a_key, "", buf, static_cast<DWORD>(sizeof(buf)), a_path.c_str());
			return buf;
		}

		bool ReadBool(const char* a_section, const char* a_key, const std::string& a_path, bool a_default)
		{
			std::string str = ReadString(a_section, a_key, a_path);
			std::transform(str.begin(), str.end(), str.begin(), ::tolower);
			if (str == "1" || str == "true")
				return true;
			if (str == "0" || str == "false")
				return false;
			return a_default;
		}

		float ReadFloat(const char* a_section, const char* a_key, const std::string& a_path, float a_default)
		{
			const std::string str = ReadString(a_section, a_key, a_path);
			if (str.empty())
				return a_default;
			char* end = nullptr;
			const float value = std::strtof(str.c_str(), &end);
			return end != str.c_str() ? value : a_default;
		}

		std::uint32_t ReadUInt(const char* a_section, const char* a_key, const std::string& a_path, std::uint32_t a_default)
		{
			const std::string str = ReadString(a_section, a_key, a_path);
			if (str.empty())
				return a_default;
			char* end = nullptr;
			const unsigned long value = std::strtoul(str.c_str(), &end, 10);
			return end != str.c_str() ? static_cast<std::uint32_t>(value) : a_default;
		}
	}

	void Init(const std::string& a_iniFileName)
	{
		const std::string path = "Data\\SKSE\\Plugins\\" + a_iniFileName;

		{
			using namespace debug;
			logLevel = static_cast<logger::level>(ReadUInt("Debug", "uLogLevel", path, static_cast<std::uint32_t>(logLevel)));
		}

		{
			using namespace mapmenu;
			localMapColor = ReadBool("MapMenu", "bMapLocalColor", path, localMapColor);
			localMapFogOfWar = ReadBool("MapMenu", "bMapLocalFogOfWar", path, localMapFogOfWar);
			localMapKeyboardPanSpeed = ReadFloat("MapMenu", "fMapLocalKeyboardPanSpeed", path, localMapKeyboardPanSpeed);
			localMapShowEnemyActors = ReadBool("MapMenu", "bMapLocalShowEnemyActors", path, localMapShowEnemyActors);
			localMapShowHostileActors = ReadBool("MapMenu", "bMapLocalShowHostileActors", path, localMapShowHostileActors);
			localMapShowGuardActors = ReadBool("MapMenu", "bMapLocalShowGuardActors", path, localMapShowGuardActors);
			localMapShowDeadActors = ReadBool("MapMenu", "bMapLocalShowDeadActors", path, localMapShowDeadActors);
			localMapShowTeammateActors = ReadBool("MapMenu", "bMapLocalShowTeammateActors", path, localMapShowTeammateActors);
			localMapShowNeutralActors = ReadBool("MapMenu", "bMapLocalShowNeutralActors", path, localMapShowNeutralActors);
			localMapShowActorsOnlyWithDetectSpell = ReadBool("MapMenu", "bImmersiveMode", path, localMapShowActorsOnlyWithDetectSpell);
		}
	}
}