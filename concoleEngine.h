#pragma once
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define ADVANCE (DWORD)45
#define _WIN32_WINNT

class concoleEngine
{
	private:
		bool isError = true;
		bool loopState = true;
		clock_t fpsTime = 0;
		bool advancedBuffer = false;
		HANDLE concoleIn, concoleOut,oConcoleOut;
		CONSOLE_SCREEN_BUFFER_INFO concoleInfo,oConcoleInfo;
		CONSOLE_FONT_INFOEX font,oFont;
		char *buffer = new char[256];
		DWORD cRead, cWritten, concoleMode, oConcoleMode;
	public:
		concoleEngine();
		concoleEngine(DWORD flag);
		~concoleEngine();
		bool textAttrib(WORD attrib);
		bool mode(DWORD modes);
		bool write(char *text);
		bool read(char *text,int buffer,bool addLast = true);
		bool point(int x, int y);
		bool windowSize(int w,int h);
		bool bufferSize(int w,int h);
		bool concoleLayout(int wW,int wH,int bW,int bH);
		bool draw(int x, int y, short character = 0x0042, short theme = 0x000F);
		void fpsStart();
		void fpsStop(float fps);
		bool fontLayout(int x, int y);
		virtual void init();
		virtual void loop();
		void start();
		void stop();
};
