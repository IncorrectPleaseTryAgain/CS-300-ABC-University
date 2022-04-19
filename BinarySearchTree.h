// BinarySearchtree.h

#pragma once
#include <iostream>

#include "Node.h"

using namespace std;

class BinarySearchTree
{
public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void insertCourse(const string& id, const string& name, const vector<string>& prerequisites);
	void printCourseList();
	void printCourse(const string& id);
	void displayCourse(Node*& node) const;
	void displayPrereq(Node*& node) const;

private:
	Node* root;

	void addCourse(Node* node, const string& id, const string& name, const vector<string>& prerequisites);
	void inOrder(Node* node);
	void removeSubtree(Node* node);
};