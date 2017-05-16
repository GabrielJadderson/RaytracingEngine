#include "Mouse.h"

std::pair<int, int> Mouse::GetPos() const
{
	return{x,y};
}

int Mouse::GetPosX() const
{
	return x;
}

int Mouse::GetPosY() const
{
	return y;
}

bool Mouse::LeftIsPressed() const
{
	return leftIsPressed;
}

bool Mouse::RightIsPressed() const
{
	return rightIsPressed;
}

bool Mouse::IsInWindow() const
{
	return isInWindow;
}

Mouse::Event Mouse::Read()
{
	if (buffer.size() > 0u)
	{
		Mouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	else
	{
		return Mouse::Event();
	}
}

void Mouse::Flush()
{
	buffer = std::queue<Event>();
}

void Mouse::OnMouseLeave()
{
	isInWindow = false;
}

void Mouse::OnMouseEnter()
{
	isInWindow = true;
}

void Mouse::OnMouseMove(int newx, int newy)
{
	x = newx;
	y = newy;

	buffer.push(Mouse::Event(Mouse::Event::Move, *this));
	TrimBuffer();
}

void Mouse::OnLeftPressed(int x, int y)
{
	leftIsPressed = true;

	buffer.push(Mouse::Event(Mouse::Event::LPress, *this));
	TrimBuffer();
}

void Mouse::OnLeftReleased(int x, int y)
{
	leftIsPressed = false;

	buffer.push(Mouse::Event(Mouse::Event::LRelease, *this));
	TrimBuffer();
}

void Mouse::OnRightPressed(int x, int y)
{
	rightIsPressed = true;

	buffer.push(Mouse::Event(Mouse::Event::RPress, *this));
	TrimBuffer();
}

void Mouse::OnRightReleased(int x, int y)
{
	rightIsPressed = false;

	buffer.push(Mouse::Event(Mouse::Event::RRelease, *this));
	TrimBuffer();
}

void Mouse::OnWheelUp(int x, int y)
{
	buffer.push(Mouse::Event(Mouse::Event::WheelUp, *this));
	TrimBuffer();
}

void Mouse::OnWheelDown(int x, int y)
{
	buffer.push(Mouse::Event(Mouse::Event::WheelDown, *this));
	TrimBuffer();
}

void Mouse::TrimBuffer()
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}