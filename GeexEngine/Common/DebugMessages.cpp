//suppress "vsnprintf is insecure"-whines from MSVC - this is just debugging stuff. have fun exploiting this...
#define _CRT_SECURE_NO_WARNINGS

#include <Common/DebugMessages.h>
#include <Windows.h>
#include <stdio.h>

void ErrorExit(const char* err, ...)
{
	va_list args;
	char msg[4096];

	va_start(args, err);
	vsnprintf(msg, sizeof(msg), err, args);
	va_end(args);

	printf(msg);

#if defined(_WIN32) || defined(_WIN64)
    MessageBox(NULL, msg, "GeexEngine Error", MB_OK | MB_ICONERROR | MB_TOPMOST);
#endif

	//TODO: Cleanup video shit
	exit(1);
}

void DebugMsg(const char* err, ...)
{
	va_list args;
	char msg[4096];

	va_start(args, err);
	vsnprintf(msg, sizeof(msg), err, args);
	va_end(args);

	printf(msg);

#if defined(_WIN32) || defined(_WIN64)
	OutputDebugString(msg);
#endif
}
