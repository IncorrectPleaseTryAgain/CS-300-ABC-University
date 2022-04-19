// Course.h

#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct Course
{
	string id;
	string name;
	vector<string>prerequisites;

	Course() { id = "", name = "", prerequisites = {}; }
};