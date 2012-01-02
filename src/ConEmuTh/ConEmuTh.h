
/*
Copyright (c) 2009-2012 Maximus5
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#pragma once

#include "../common/common.hpp"
#include "../Common/WinObjects.h"
#include "ConEmuTh_Lang.h"

#define SafeCloseHandle(h) { if ((h)!=NULL) { HANDLE hh = (h); (h) = NULL; if (hh!=INVALID_HANDLE_VALUE) CloseHandle(hh); } }

#ifdef _DEBUG
	#define OUTPUTDEBUGSTRING(m) OutputDebugString(m)
	#define SHOWDBGINFO(x) OutputDebugStringW(x)

	//#define CONEMU_LOG_FILES
	#undef CONEMU_LOG_FILES
#else
	#define OUTPUTDEBUGSTRING(m)
	#define SHOWDBGINFO(x)

	//#define CONEMU_LOG_FILES
	#undef CONEMU_LOG_FILES
#endif


#define ISALPHA(c) ((((c) >= (BYTE)'c') && ((c) <= (BYTE)'z')) || (((c) >= (BYTE)'C') && ((c) <= (BYTE)'Z')))
#define isPressed(inp) ((GetKeyState(inp) & 0x8000) == 0x8000)
//#define countof(array) (sizeof(array)/sizeof(*array))

// X - �������, Y - �������
#define FAR_X_VER 995
#define FAR_Y_VER 1900
#define FUNC_X(fn) fn##995
#define FUNC_Y(fn) fn##1900


#define ConEmuTh_SysID 0x43455568 // 'CETh'


//#define EVENT_TYPE_REDRAW 250
#define TH_ENVVAR_NAME L"FarThumbnails"
#define TH_ENVVAR_ACTIVE L"Active"
#define TH_ENVVAR_SCROLL L"Scrolling"



//typedef struct tag_FarVersion {
//	union {
//		DWORD dwVer;
//		struct {
//			WORD dwVerMinor;
//			WORD dwVerMajor;
//		};
//	};
//	DWORD dwBuild;
//} FarVersion;

struct CEFAR_FIND_DATA
{
	//FILETIME ftCreationTime;
	//FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	union
	{
		struct
		{
			DWORD nFileSizeHigh;
			DWORD nFileSizeLow;
		};
		unsigned __int64 nFileSize;
	};
	const wchar_t *lpwszFileName;
	const wchar_t *lpwszFileNamePart;
	const wchar_t *lpwszFileExt;
	//const wchar_t *lpwszAlternateFileName;
	DWORD    dwFileAttributes; // Decrease 32bit structure size by rearrange
};

struct CePluginPanelItem
{
	DWORD			 cbSize;
	CEFAR_FIND_DATA  FindData;
	BOOL             bVirtualItem;
	DWORD_PTR        UserData;
	UINT             PreviewLoaded; // �������� �� ��� ��������� ��������� (|1-��������� Shell, |2-��������� Preview, |4-Thumbnail ��� ������� ��������, � �� ������ ��������� ����������)
	const wchar_t*   pszFullName; // ��� ��������� ��������� - ������ �� ��������� �����
	const wchar_t*   pszDescription; // ������ �� ������ � ���� CePluginPanelItem
	unsigned __int64 Flags;
	DWORD            NumberOfLinks;
	BOOL             bIsCurrent; // ������ �������������, ��������������� �� ��� ���� ������, ��� ����� ���� �����������
	//BOOL           bItemColorLoaded;
	//COLORREF       crFore, crBack;
};

struct CePluginPanelItemColor
{
	BOOL            bItemColorLoaded;
	COLORREF        crFore, crBack;
};

enum CEPANELINFOFLAGS
{
	CEPFLAGS_SHOWHIDDEN         = 0x00000001,
	CEPFLAGS_HIGHLIGHT          = 0x00000002,
	CEPFLAGS_REVERSESORTORDER   = 0x00000004,
	CEPFLAGS_USESORTGROUPS      = 0x00000008,
	CEPFLAGS_SELECTEDFIRST      = 0x00000010,
	CEPFLAGS_REALNAMES          = 0x00000020,
	CEPFLAGS_NUMERICSORT        = 0x00000040,
	CEPFLAGS_PANELLEFT          = 0x00000080,
};


#include "Display.h"



//struct ThumbnailSettings
//{
//	TODO("nWidth & nHeight - deprecated");
//	// �������� �������� �� WholeWidth() & WholeHeight()
//	int nWidth, nHeight; // 98x98
//
//	int nThumbSize; // 96
//	int nIconSize; // 48
//	DWORD crBackground; // 0xFFFFFF (RGB) ��� 0xFF000000 (Index)
//
//	int nThumbFrame; // 1 (����� ����� ������ ���������
//	DWORD crThumbFrame; // 0xFFFFFF (RGB) ��� 0xFF000000 (Index)
//	int nSelectFrame; // 1 (����� ������ �������� ��������)
//	DWORD crSelectFrame; // 0xFFFFFF (RGB) ��� 0xFF000000 (Index)
//	int nHSpacing, nVSpacing; // 5, 25 - ���������� ����� ����� �������
//
//	TODO("����� �� ����� - �������� ������ nSelectFrame? ��� ����� �����?");
//	int nHPadding, nVPadding; // 1, 1 - ���������������� ������
//
//	int nFontHeight; // 14
//	wchar_t sFontName[32]; // Tahoma
//	BOOL bLoadPreviews, bLoadFolders;
//	int nLoadTimeout; // 15 sec
//
//	int nMaxZoom;
//	BOOL bUsePicView2;
//
//	wchar_t sCacheFolder[MAX_PATH];
//
//
//	void Load() {
//		TODO("nWidth & nHeight - deprecated");
//		nWidth = nHeight = 98;
//
//		nThumbSize = 96; // ����� ������� ����� 96. ����� ����� ���� 500% �� 16�16 ���������
//		nIconSize = 32;
//
//		nThumbFrame = 1;
//		nSelectFrame = 1;
//
//		nHSpacing = 5; nVSpacing = 25;
//		nHPadding = 1; nVPadding = 1;
//
//		nFontHeight = 14;
//		lstrcpy(sFontName, L"Tahoma");
//
//		bLoadPreviews = TRUE;
//		bLoadFolders = TRUE;
//		nLoadTimeout = 15;
//		nMaxZoom = 500; // �� �� ������ ������� ��������� :)
//		bUsePicView2 = TRUE;
//        sCacheFolder[0] = 0;
//	};
//};
BOOL LoadThSet(DWORD anGuiPid=-1);
extern PanelViewSetMapping gThSet;
extern BOOL gbCancelAll;



extern HWND ghConEmuRoot;
extern HWND ghConEmuWnd;
extern HMODULE ghPluginModule; // ConEmuTh.dll - ��� ������
extern DWORD gnSelfPID, gnMainThreadId;
//extern int lastModifiedStateW;
//extern bool gbHandleOneRedraw; //, gbHandleOneRedrawCh;
//extern WCHAR gszDir1[CONEMUTABMAX], gszDir2[CONEMUTABMAX],
//extern wchar_t* gszRootKey;
//extern int maxTabCount, lastWindowCount;
//extern CESERVER_REQ* tabs; //(ConEmuTab*) calloc(maxTabCount, sizeof(ConEmuTab));
//extern CESERVER_REQ* gpCmdRet;
//extern HWND ConEmuHwnd;
//extern HWND FarHwnd;
extern FarVersion gFarVersion;
//extern int lastModifiedStateW;
////extern HANDLE hEventCmd[MAXCMDCOUNT];
//extern HANDLE hThread;
////extern WCHAR gcPlugKey;
////WARNING("������, �������� ghConIn �� GetStdHandle()"); // ����� � Win7 ����� ����� �����������
////extern HANDLE ghConIn;
//extern BOOL gbNeedPostTabSend;
//extern HANDLE ghServerTerminateEvent;
//extern CESERVER_CONSOLE_MAPPING_HDR *gpConsoleInfo;
//extern DWORD gnSelfPID;
extern CeFullPanelInfo pviLeft, pviRight;
extern HANDLE ghDisplayThread; extern DWORD gnDisplayThreadId;
//extern HWND ghLeftView, ghRightView;
//extern bool gbWaitForKeySequenceEnd;
extern DWORD gnWaitForKeySeqTick;
extern DWORD gnFarPanelSettings, gnFarInterfaceSettings;
//class CRgnDetect;
//extern CRgnDetect *gpRgnDetect;

// *** lng resources begin ***
extern wchar_t gsFolder[64], /*gsHardLink[64],*/ gsSymLink[64], gsJunction[64], gsTitleThumbs[64], gsTitleTiles[64];
// *** lng resources end ***

extern COLORREF /*gcrActiveColors[16], gcrFadeColors[16],*/ *gcrCurColors;
extern bool gbFadeColors;
extern bool gbFarPanelsReady;

class CRgnDetect;
extern CRgnDetect *gpRgnDetect;
extern CEFAR_INFO_MAPPING gFarInfo;
extern DWORD gnRgnDetectFlags;


//typedef struct tag_SynchroArg {
//	enum {
//		eCommand,
//		eInput
//	} SynchroType;
//	HANDLE hEvent;
//	LPARAM Result;
//	LPARAM Param1, Param2;
//	BOOL Obsolete;
//	//BOOL Processed;
//} SynchroArg;

void FUNC_X(GetPluginInfoW)(void* piv);
void FUNC_Y(GetPluginInfoW)(void* piv);

HANDLE OpenPluginWcmn(int OpenFrom,INT_PTR Item);
HANDLE WINAPI OpenPluginW1(int OpenFrom,INT_PTR Item);
HANDLE WINAPI OpenPluginW2(int OpenFrom,const GUID* Guid,INT_PTR Data);

BOOL SettingsLoad(LPCWSTR pszName, DWORD* pValue);
BOOL SettingsLoadReg(LPCWSTR pszRegKey, LPCWSTR pszName, DWORD* pValue);
BOOL SettingsLoadA(LPCWSTR pszName, DWORD* pValue);
BOOL FUNC_X(SettingsLoadW)(LPCWSTR pszName, DWORD* pValue);
BOOL FUNC_Y(SettingsLoadW)(LPCWSTR pszName, DWORD* pValue);
void SettingsLoadOther(LPCWSTR pszRegKey);
void SettingsLoadOtherA();
void FUNC_X(SettingsLoadOtherW)();
void FUNC_Y(SettingsLoadOtherW)();
void SettingsSave(LPCWSTR pszName, DWORD* pValue);
void SettingsSaveReg(LPCWSTR pszRegKey, LPCWSTR pszName, DWORD* pValue);
void SettingsSaveA(LPCWSTR pszName, DWORD* pValue);
void FUNC_X(SettingsSaveW)(LPCWSTR pszName, DWORD* pValue);
void FUNC_Y(SettingsSaveW)(LPCWSTR pszName, DWORD* pValue);
void SavePanelViewState(BOOL bLeftPanel, DWORD dwMode);

bool isPreloadByDefault();

void EntryPoint(int OpenFrom,INT_PTR Item);
BOOL LoadFarVersion();
void StartPlugin(BOOL abManual);
void ExitPlugin(void);
void FUNC_X(ExitFARW)(void);
void FUNC_Y(ExitFARW)(void);
void FUNC_X(SetStartupInfoW)(void *aInfo);
void FUNC_Y(SetStartupInfoW)(void *aInfo);
int ShowMessage(int aiMsg, int aiButtons);
int ShowMessageA(int aiMsg, int aiButtons);
int FUNC_X(ShowMessageW)(int aiMsg, int aiButtons);
int FUNC_Y(ShowMessageW)(int aiMsg, int aiButtons);
int ShowMessageA(LPCSTR asMsg, int aiButtons);
int FUNC_X(ShowMessageW)(LPCWSTR asMsg, int aiButtons);
int FUNC_Y(ShowMessageW)(LPCWSTR asMsg, int aiButtons);
void PostMacro(wchar_t* asMacro);
void PostMacroA(char* asMacro);
void FUNC_X(PostMacroW)(wchar_t* asMacro);
void FUNC_Y(PostMacroW)(wchar_t* asMacro);
LPCWSTR GetMsgW(int aiMsg);
const wchar_t* GetMsgA(int aiMsg, wchar_t* rsMsg/*MAX_PATH*/);
LPCWSTR FUNC_Y(GetMsgW)(int aiMsg);
LPCWSTR FUNC_X(GetMsgW)(int aiMsg);
int ShowPluginMenu();
int ShowPluginMenuA();
int FUNC_Y(ShowPluginMenuW)();
int FUNC_X(ShowPluginMenuW)();
BOOL IsMacroActive();
BOOL IsMacroActiveA();
BOOL FUNC_X(IsMacroActiveW)();
BOOL FUNC_Y(IsMacroActiveW)();
//CeFullPanelInfo* LoadPanelInfo(BOOL abActive);
CeFullPanelInfo* GetActivePanel();
BOOL LoadPanelInfoA(BOOL abActive);
BOOL FUNC_X(LoadPanelInfoW)(BOOL abActive);
BOOL FUNC_Y(LoadPanelInfoW)(BOOL abActive);
void ReloadPanelsInfo();
void ReloadPanelsInfoA();
void FUNC_X(ReloadPanelsInfoW)();
void FUNC_Y(ReloadPanelsInfoW)();
//BOOL IsLeftPanelActive();
//BOOL IsLeftPanelActiveA();
//BOOL FUNC_X(IsLeftPanelActive)();
//BOOL FUNC_Y(IsLeftPanelActive)();
void LoadPanelItemInfo(CeFullPanelInfo* pi, INT_PTR nItem);
void LoadPanelItemInfoA(CeFullPanelInfo* pi, INT_PTR nItem);
void FUNC_X(LoadPanelItemInfoW)(CeFullPanelInfo* pi, INT_PTR nItem);
void FUNC_Y(LoadPanelItemInfoW)(CeFullPanelInfo* pi, INT_PTR nItem);
bool CheckWindows();
//bool CheckWindowsA();
//bool FUNC_X(CheckWindows)();
//bool FUNC_Y(CheckWindows)();
bool CheckFarPanelsA();
bool FUNC_X(CheckFarPanelsW)();
bool FUNC_Y(CheckFarPanelsW)();

// ��� "����������" ������� ���������� �� �������� ����, ��� ����� ������� FAR Api
//void DisplayReloadPanel(CeFullPanelInfo* pi);

extern int gnCreateViewError;
extern DWORD gnWin32Error;
//HWND CreateView(CeFullPanelInfo* pi);
void UpdateEnvVar(BOOL abForceRedraw);
CeFullPanelInfo* IsThumbnailsActive(BOOL abFocusRequired);
BOOL CheckPanelSettings(BOOL abSilence);
BOOL CheckPanelSettingsA(BOOL abSilence);
BOOL FUNC_X(CheckPanelSettingsW)(BOOL abSilence);
BOOL FUNC_Y(CheckPanelSettingsW)(BOOL abSilence);

BOOL GetFarRect(SMALL_RECT* prcFarRect);
void FUNC_X(GetFarRectW)(SMALL_RECT* prcFarRect);
void FUNC_Y(GetFarRectW)(SMALL_RECT* prcFarRect);

typedef struct
{
	int bValid; // Must be ==1
	int bExpired; // Must be ==0, if !=0 - ������ ���������� ������
	enum
	{
		eExecuteMacro = 0,
	} nCommand;
	WORD Data[1]; // variable array
} ConEmuThSynchroArg;
extern bool gbSynchoRedrawPanelRequested;
extern ConEmuThSynchroArg* gpLastSynchroArg;
void ExecuteInMainThread(ConEmuThSynchroArg* pCmd);
void FUNC_X(ExecuteInMainThreadW)(ConEmuThSynchroArg* pCmd);
void FUNC_Y(ExecuteInMainThreadW)(ConEmuThSynchroArg* pCmd);
//int WINAPI ProcessSynchroEventW(int Event, void *Param);

#define SYNCHRO_REDRAW_PANEL ((ConEmuThSynchroArg*)1)
void SetCurrentPanelItemA(BOOL abLeftPanel, INT_PTR anTopItem, INT_PTR anCurItem);
void FUNC_X(SetCurrentPanelItemW)(BOOL bLeftPanel, INT_PTR anTopItem, INT_PTR anCurItem);
void FUNC_Y(SetCurrentPanelItemW)(BOOL bLeftPanel, INT_PTR anTopItem, INT_PTR anCurItem);

#define SYNCHRO_RELOAD_PANELS ((ConEmuThSynchroArg*)2)


// ConEmu.dll
typedef int (WINAPI *RegisterPanelView_t)(PanelViewInit *ppvi);
typedef HWND (WINAPI *GetFarHWND2_t)(BOOL abConEmuOnly);
extern RegisterPanelView_t gfRegisterPanelView;
extern GetFarHWND2_t gfGetFarHWND2;
BOOL CheckConEmu(BOOL abSilence=FALSE);
BOOL WINAPI OnPrePeekConsole(HANDLE hInput, PINPUT_RECORD lpBuffer, DWORD nBufSize, LPDWORD lpNumberOfEventsRead, BOOL* pbResult);
BOOL WINAPI OnPostPeekConsole(HANDLE hInput, PINPUT_RECORD lpBuffer, DWORD nBufSize, LPDWORD lpNumberOfEventsRead, BOOL* pbResult);
BOOL WINAPI OnPreReadConsole(HANDLE hInput, PINPUT_RECORD lpBuffer, DWORD nBufSize, LPDWORD lpNumberOfEventsRead, BOOL* pbResult);
BOOL WINAPI OnPostReadConsole(HANDLE hInput, PINPUT_RECORD lpBuffer, DWORD nBufSize, LPDWORD lpNumberOfEventsRead, BOOL* pbResult);
BOOL WINAPI OnPreWriteConsoleOutput(HANDLE hOutput,const CHAR_INFO *lpBuffer,COORD dwBufferSize,COORD dwBufferCoord,PSMALL_RECT lpWriteRegion);


/* Other plugin integrations */
#define IMPEX_MAGIC 0x78456D49 // 'ImEx'
struct ImpExPanelItem
{
	DWORD nMagic;			// IMPEX_MAGIC
	DWORD cbSizeOfStruct;	// 1196 � ���� ������
	DWORD nBinarySize;		// ������
	LPBYTE pBinaryData;		// � ���������� �������� ������
	// ��������� ���� �� ����������
};
#define PBFAR_MAGIC 0x50624672 // 'PbFr'
struct PbFarPanelItem
{
	DWORD nMagic;			// PBFAR_MAGIC
	DWORD cbSizeOfStruct;	//
	DWORD_PTR pPlugin;      // CPBPlugin*
};
typedef int (WINAPI* GetPbFarFileData_t)(DWORD_PTR pPlugin, LPCWSTR asFile, LPVOID* ppData, DWORD* pDataSize);

#define REGEDIT_MAGIC 0x52674564 // 'RgEd'
