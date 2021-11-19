#ifndef PATH_UTILS_H
#define PATH_UTILS_H

#include <string>

#define WINDOWS


class PathUtils
{
public:
	// 得到当前的Exe的路径
	static std::string GetCurrentExeDirectory();

	// 得到资源路径
	static std::string GetResourceDirectory();

	// 得到Duilib的皮肤文件路径
	static std::string GetSkinDirectory();

	// 得到Duilib的字体路径
	static std::string GetFontDirectory();

};


#endif // !PATH_UTILS_H
