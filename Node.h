// Node.h

#pragma once
#include <iostream>

#include "Course.h"

using namespace std;

struct Node
{
    Course course;
    Node* left;
    Node* right;

    Node() 
    {
        left = nullptr;
        right = nullptr;
    }

    Node(const string& id, const string& name, const vector<string> prerequisites) : Node()
    {
        course.id = id;
        course.name = name;
        course.prerequisites = prerequisites;
    }
};