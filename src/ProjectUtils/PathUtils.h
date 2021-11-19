#ifndef PATH_UTILS_H
#define PATH_UTILS_H

#include <string>

#define WINDOWS


class PathUtils
{
public:
	// �õ���ǰ��Exe��·��
	static std::string GetCurrentExeDirectory();

	// �õ���Դ·��
	static std::string GetResourceDirectory();

	// �õ�Duilib��Ƥ���ļ�·��
	static std::string GetSkinDirectory();

	// �õ�Duilib������·��
	static std::string GetFontDirectory();

};


#endif // !PATH_UTILS_H
