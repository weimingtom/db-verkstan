#pragma once

class Demo
{
public:
	Demo();

	~Demo();

	void init(HWND *hwnd);

	void load();

	void run();

	int getTick();

	void setTick(int tick);
protected:

};