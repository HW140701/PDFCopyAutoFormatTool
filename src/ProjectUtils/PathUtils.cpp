#include "PathUtils.h"

#ifdef WINDOWS

#include<Windows.h>

#elif LINUX

#include <dlfcn.h>

#endif // WINDOWS



#ifdef WINDOWS
	static HMODULE GetSelfModuleHandle()
	{
		MEMORY_BASIC_INFORMATION mbi;
		return (
			(::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0)
			? (HMODULE)mbi.AllocationBase : NULL
			);
	}

	std::string PathUtils::GetCurrentExeDirectory()
	{
		std::string strCurrentPath = "";
		char curDirector[260] = { 0 };
		GetModuleFileName(GetSelfModuleHandle(), curDirector, 260);
		strCurrentPath = curDirector;

		size_t nameStart = strCurrentPath.rfind("\\");
		strCurrentPath = strCurrentPath.substr(0, nameStart + 1);
		return strCurrentPath;
	}
#elif LINUX
	static std::string GetSoCurrentPath()
	{
		std::string strCurrentPath = "";
		Dl_info info;
		int rc;

		rc = dladdr((void*)GetSoCurrentPath, &info);

		if (!rc)
		{
			return strCurrentPath;
		}

		strCurrentPath = info.dli_fname;
		return strCurrentPath;
	}

	std::string PathUtils::GetCurrentExeDirectory()
	{
		std::string strCurrentPath = "";
		Dl_info info;
		int rc;

		rc = dladdr((void*)GetSoCurrentPath, &info);

		if (!rc)
		{
			return strCurrentPath;
		}

		strCurrentPath = info.dli_fname;

		size_t nameStart = strCurrentPath.rfind("/");
		strCurrentPath = strCurrentPath.substr(0, nameStart + 1);
		return strCurrentPath;
	}
#endif

	std::string PathUtils::GetResourceDirectory()
	{
#ifdef _DEBUG
		return GetCurrentExeDirectory() + "../../../../resource/";
#else
		return GetCurrentExeDirectory() + "./resource/";
#endif // DEBUG	
	}
	std::string PathUtils::GetSkinDirectory()
	{
#ifdef _DEBUG
		return "../../../.././resource/skin/";
#else
		return "./resource/skin/";
#endif // DEBUG	
	}

