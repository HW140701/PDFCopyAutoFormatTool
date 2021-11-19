#ifndef PROJECT_HEADER_H
#define PROJECT_HEADER_H

#include <SDKDDKVer.h>
#include <afxwin.h>

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
#include <windows.h>


// duilib
#include "UIlib.h"
using namespace DuiLib;

//#ifdef _DEBUG  
//#   ifdef _UNICODE  
//#   pragma comment(lib,"DuiLib_ud.lib")  
//#   else  
//#   pragma comment(lib,"DuiLib_d.lib")  
//#   endif  
//#else  
//# ifdef _UNICODE  
//#   pragma comment(lib,"DuiLib_u.lib")  
//#   else  
//#   pragma comment(lib,"DuiLib.lib")  
//#   endif  
//#endif 



// std��׼��
#include <regex>


// �Զ��幤��
#include "ProjectUtils/PathUtils.h"
#include "ProjectUtils/ProjectUtils.h"
#include "ProjectUtils/DuilibAddFont.h"

#endif // !PROJECT_HEADER_H
