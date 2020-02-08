#pragma once


class MyInt
{
public:
	MyInt();
	~MyInt();

	int getVal() { return value; }
	void setVal(int newVal) { value = newVal; }
	

private:
	int value;
};

