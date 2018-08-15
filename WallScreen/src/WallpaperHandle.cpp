#include "WallpaperHandle.h"

#include <iostream>

#include "WallScreenException.h"

#define PROGMAN_NAME "Progman"
#define PROGMAN_MESSAGE 0x052c
#define SHELLDLL_DEFVIEW_NAME "SHELLDLL_DefView"
#define WORKER_W_NAME "WorkerW"
#define WORKER_W_FLAG 0x403

HWND SpawnWorkerWBehindIcons()
{
	HWND progman = FindWindow(PROGMAN_NAME, NULL);
	if (progman == NULL)
	{
		std::cout << "ERROR: Could not find Program Manager Handle!" << std::endl;
		return NULL;
	}

	LRESULT msgResult = SendMessageTimeout(progman, PROGMAN_MESSAGE, NULL, NULL, SMTO_NORMAL, 1000, NULL);
	if (msgResult == NULL)
	{
		std::cout << "ERROR: Could not send message to Program Manager Handle!" << std::endl;
		return NULL;
	}

	static HWND workerw = NULL;
	EnumWindows([](HWND topHandle, LPARAM topParamHandle) {
		HWND shelldllDefview = FindWindowEx(topHandle, NULL, SHELLDLL_DEFVIEW_NAME, NULL);

		if (shelldllDefview != NULL)
		{
			workerw = FindWindowEx(NULL, topHandle, WORKER_W_NAME, NULL);
		}

		return TRUE;
	}, NULL);

	return workerw;
}

WallpaperHandle::WallpaperHandle()
{
	m_Window = SpawnWorkerWBehindIcons();
	if (m_Window == NULL)
		throw WallScreenException("Could not spawn WorkerW!");

	m_DeviceContext = GetDCEx(m_Window, NULL, WORKER_W_FLAG);
}

WallpaperHandle::~WallpaperHandle()
{
	ReleaseDC(HWND_DESKTOP, m_DeviceContext);
}
