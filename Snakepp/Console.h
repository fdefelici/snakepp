#ifndef CONSOLE_H 
#define CONSOLE_H

#include <iostream>
#include <Windows.h>

class Console 
{
public:
	Console(unsigned width, unsigned height) :
		width(width),
		height(height),
		bufferSize(width* height),
		buffer(new wchar_t[width * height])
	{
		SMALL_RECT r;
		COORD      c;
		//hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
		hConOut = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		if (!GetConsoleScreenBufferInfo(hConOut, &csbi))
			throw std::runtime_error("You must be attached to a human.");
		SetConsoleActiveScreenBuffer(hConOut);

		r.Left =
			r.Top = 0;
		r.Right = width - 1;
		r.Bottom = height - 1;
		SetConsoleWindowInfo(hConOut, TRUE, &r);

		c.X = width;
		c.Y = height;
		SetConsoleScreenBufferSize(hConOut, c);


	}

	~Console()
	{
		SetConsoleTextAttribute(hConOut, csbi.wAttributes);
		SetConsoleScreenBufferSize(hConOut, csbi.dwSize);
		SetConsoleWindowInfo(hConOut, TRUE, &csbi.srWindow);
		delete[] this->buffer;
	}

	void color(WORD color = 0x07)
	{
		SetConsoleTextAttribute(hConOut, color);
	}

	void setTile(const wchar_t string[], ...) {
		va_list args;
		va_start(args, string);
		wchar_t title[100];
		vswprintf(title, 100, string, args);
		va_end(args);

		SetConsoleTitle(title);
	}

	void write(wchar_t* screen) {
		DWORD dwBytesWritten;
		WriteConsoleOutputCharacter(hConOut, screen, width * height, { 0,0 }, &dwBytesWritten);
	}

	void putLine(unsigned int lineIndex, const wchar_t string[], ...) {
		va_list args;
		va_start(args, string);
		vswprintf(this->buffer, this->width, string, args);
		va_end(args);
		//TODO: scrivere a una certa linea nel buffer
	}

	void put(unsigned int x, unsigned int y, wchar_t value) {
		buffer[y * this->width + x] = value;
	}

	void flush() {
		this->write(this->buffer);
	}

	unsigned int getWidth() {
		return this->width;
	}
	unsigned int getHeight() {
		return this->height;
	}

private:
	HANDLE                     hConOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	unsigned int width;
	unsigned int height;
	unsigned int bufferSize;
	wchar_t* buffer;
};


#endif