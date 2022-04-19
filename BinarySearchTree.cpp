// BinarySearchtree.cpp

#include <thread>

#include "BinarySearchTree.h"

//number of seconds to sleep
#define NUM_SECONDS_PAUSE 1

/*
* Initialize housekeeping variables.
*
* @return N/A
* Parameters: N/A
*/
BinarySearchTree::BinarySearchTree()
{
    // initialize housekeeping variables
    root = nullptr;
}

/*
* Delete tree one node at a time.
*
* @return N/A
* Parameters: N/A
*/
BinarySearchTree::~BinarySearchTree()
{
    // recurse from root deleting every node
    removeSubtree(root);
}

/*
* Recursevely delete every node in each subtree
* from a starting node.
*
* @return N/A
* Parameters: Node*
*/
void BinarySearchTree::removeSubtree(Node* node)
{
    // If node is not nullptr
    if (node)
    {
        // If node has left child
        if (node->left)
        {
            // Go left
            removeSubtree(node->left);
        }

        // If node has right child
        if (node->right)
        {
            // Go right
            removeSubtree(node->right);
        }

        // Free node
        free(node);
    }
}

/*
* Insert course into tree 
*
* @return N/A
* Parameters: const string&
*             const string&
*             const vector<string>&
*/
void BinarySearchTree::insertCourse(const string& id, const string& name, const vector<string>& prerequisites)
{
    // If tree is empty
    if (root == nullptr)
    {
        // Create new node as root
        root = new Node(id, name, prerequisites);
    }
    else
    {
        // Traverse tree and insert
        addCourse(root, id, name, prerequisites);
    }
}

/*
* Print list of all courses in alphabetical order
* according to course ID
*
* @return N/A
* Parameters: N/A
*/
void BinarySearchTree::printCourseList()
{
    cout << "Printing Courses...\n" << endl;

    // Pause 1 second
    this_thread::sleep_for(chrono::seconds(NUM_SECONDS_PAUSE));

    // Calling Function to print in alphabetical order
	inOrder(root);
}

/*
* Print specific course and their respected prerequisites.
*
* @return N/A
* Parameters: const string&
*/
void BinarySearchTree::printCourse(const string& id)
{
    // Used to traverse tree
    Node* current = root;

    // While not at end of tree
    while (current != nullptr)
    {
        // If at course node
        if (current->course.id == id)
        {
            displayCourse(current);
            displayPrereq(current);

            return;
        }

        // If id is less than node id
        // Go into left subtree
        if (id < current->course.id)
        {
            current = current->left;
        }
        // Go into right subtree
        else
        {
            current = current->right;
        }

    }

    // Not Found
    cout << "Error: Course Not Found" << endl;
}

/*
* Print course ID and Name
*
* @return N/A
* Parameters: Node*&
*/
void BinarySearchTree::displayCourse(Node*& node) const
{
    cout << node->course.id << ", " << node->course.name << endl;
}

/*
* Print all prerequisites of course
*
* @return N/A
* Parameters: Node*&
*/
void BinarySearchTree::displayPrereq(Node*& node) const
{
    // Number of prerequisites for course
    const int NUM_PREREQ = node->course.prerequisites.size();

    cout << "Prerequisites: ";

    // If course has at least one prerecuisite
    if (NUM_PREREQ > 0)
    {
        // Print all prerequisites of course
        for (int i = 0; i < NUM_PREREQ; i++)
        {
            if (i == NUM_PREREQ - 1)
            {
                cout << node->course.prerequisites[i] << endl;
            }
            else
            {
                cout << node->course.prerequisites[i] << ", ";
            }
        }
    }
    else
    {
        cout << "N/A" << endl;
    }
}

/*
* Traverse tree and add new course
*
* @return N/A
* Parameters: Node*
*             const string&
*             const string&
*             const vector<string>&
*/
void BinarySearchTree::addCourse(Node* node, const string& id, const string& name, const vector<string>& prerequisites)
{
    // Implement inserting a course into the tree
    // If id is less than node id
    // Go into left subtree
    if (id < node->course.id)
    {
        // If node is leaf
        if (node->left == nullptr)
        {
            node->left = new Node(id, name, prerequisites);
        }
        else
        {
            // Traferse into left subtree
            addCourse(node->left, id, name, prerequisites);
        }
    }
    // Go into right subtree
    else
    {
        // If node is leaf
        if (node->right == nullptr)
        {
            node->right = new Node(id, name, prerequisites);
        }
        else
        {
            // Traferse into right subtree
            addCourse(node->right, id, name, prerequisites);
        }
    }
}

/*
* Recurselvely print courses in alphabetical order
*
* @return N/A
* Parameters: Node*
*/
void BinarySearchTree::inOrder(Node* node)
{
    // If not at end of tree
    if (node)
    {
        inOrder(node->left);
        displayCourse(node);
        inOrder(node->right);
    }
}