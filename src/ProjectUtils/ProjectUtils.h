#ifndef PROJECT_UTILS_H
#define PROJECT_UTILS_H

#include "ProjectHeader.h"

static std::string CDuiStringToString(const CDuiString& duistring) {
    LPCTSTR str = duistring.GetData();
#ifdef _UNICODE
    int size_str = WideCharToMultiByte(CP_UTF8, 0, str, -1, 0, 0, NULL, NULL);

    char* point_new_array = new char[size_str];

    WideCharToMultiByte(CP_UTF8, 0, str, -1, point_new_array, size_str, NULL, NULL);

    std::string return_string(point_new_array);
    delete[] point_new_array;
    point_new_array = NULL;
    return return_string;
#else
    return std::string(str);
#endif
}


#endif // !PROJECT_UTILS_H
