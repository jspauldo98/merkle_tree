#include "bTREE.h"
#include <string>
using namespace std;
#include <iostream>
#include <queue>
#include <algorithm>

//look at descriptions in pMT.h for guidance on what you might need for these function to actually do
bTREE::bTREE()
{
    root = NULL;
    counterInsert = 0;
    counterFind = 0;
}

bTREE::~bTREE()
{
	destroy( root );
}

int bTREE::dataInserted()
{
    //return the number of operations needed to do the insert, -1 if out of memory
    return counterInsert;
}

int bTREE::dataFound()
{
    // returns the number of oferations needed to do find
    return counterFind;
}

int bTREE::numberOfNodesH(treeNode * subtree)
{
	if (subtree == NULL)
		return 0;
	else {
		return numberOfNodesH(subtree->leftptr) + 1 + numberOfNodesH(subtree->rightptr);
	}
}

int bTREE::numberOfNodes()
{
    //return nodeCount;
	return numberOfNodesH(root);
}

bool bTREE::insert(string data, int timeStamp)
{
    queue<struct treeNode*> q;
    counterInsert+=1;

    // used refernce from geeksforgeeks.com
    if (numberOfNodes() > 0)
    {
        q.push(root);
        counterInsert+=1;
        // Do level order traversal until we find
        // an empty place.
        while (!q.empty()) {
            treeNode * temp = q.front();
            q.pop();
            counterInsert+=2;

            if (!temp->leftptr) {
                // create two new nodes
                // prev_node copys temp node
                // new_node makes new node in right ptr
                treeNode * prev_node = new treeNode();
                treeNode * new_node = new treeNode();

                // copy temp info to prev_node
                prev_node->data = temp->data;
                prev_node->time = temp->time;
                prev_node->isleaf = true;
                prev_node->leftptr = NULL;
                prev_node->rightptr = NULL;

                // add info to new_node
                new_node->data = data;
                new_node->time = timeStamp;
                new_node->leftptr = NULL;
                new_node->rightptr = NULL;
                new_node->isleaf = true;

                // make temp node parent of new_node and prev_node
                // this will be the hash of both
                temp-> data = "parent";
                temp->time = 666;
                temp->leftptr = prev_node;
                temp->rightptr = new_node;
                temp->isleaf = false;
                counterInsert+=17;
                break;
            } else
            {
                counterInsert+=2;
                q.push(temp->leftptr);
                q.push(temp->rightptr);
            }
        }
    }
    else
    {
        counterInsert+=7;
        // create root node
        treeNode * new_node = new treeNode();
        new_node->data = data;
        new_node->time = timeStamp;
        new_node->leftptr = NULL;
        new_node->rightptr = NULL;
        new_node->isleaf = true;
        root = new_node;
    }

    return true;
}

bool bTREE::inorderSearch(treeNode * & subtree, string s, bool &found)
{
    if (subtree != NULL)
    {
        inorderSearch(subtree->leftptr, s, found);
        counterFind++;
        if (subtree->data.compare(s) == 0)
        {
            counterFind++;
            found = true;
        }
        inorderSearch(subtree->rightptr, s, found);
    }

    return found;
}

bool bTREE::find(string s)
{
    // returns true if exists false if not
    bool found = false;
    counterFind++;
    return inorderSearch(root, s, found);

}
bool bTREE::preorderLocate(treeNode * & subtree, string s, string &map)
{
    if (subtree == NULL)
        return false;

    // map += subtree->data;

    if (subtree->data.compare(s) == 0)
        return true;

    if (preorderLocate(subtree->leftptr, s, map)) {
        map += "L";
        return true;
    }

    if (preorderLocate(subtree->rightptr, s, map)) {
        map += "R";
        return true;
    }

    if (map.length() > 0) {
        map = map.erase(map.length()-1);    
    }
    
    return false; 
}
string bTREE::locate(string s)
{
  string map = "";
  // bool found = false;
  preorderLocate(root, s, map);
  if ( map.compare ("") == 0)
  {
    return ".";
  }
  else
  {
    
    // string reversal NOT EFFICICENT
    string map2 = map;
    int j = 0;
    for (int i = map.length(); i > 0; i--)
    {
        map2.at(j) = map.at(i - 1);
        j++;
    }

    return map2;
  }
}

bool operator ==(const bTREE& lhs, const bTREE& rhs)
{
    // if left tree == right tree return true
    // Return true if both trees are empty
    if (lhs.root == NULL  && rhs.root == NULL) return true;

    // Return false if one is empty and other is not
    if (lhs.root == NULL || rhs.root == NULL)  return false;

    // return true if root data is the same AND time is the same
    if(lhs.root->data.compare(rhs.root->data) == 0
        && lhs.root->time == rhs.root->time)
        return true;
    else
        return false;

}

bool operator !=(const bTREE& lhs, const bTREE& rhs)
{
    // if left tree != right tree return true
    // Return false if both trees are empty
    if (lhs.root == NULL  && rhs.root == NULL) return false;

    // Return true if one is empty and other is not
    if (lhs.root == NULL || rhs.root == NULL)  return true;

    // return false if root data is the same AND time is the same
    if(lhs.root->data.compare(rhs.root->data) == 0
        && lhs.root->time == rhs.root->time)
        return false;
    else
        return true;
}

ostream & operator <<(ostream & out, const bTREE & p)
{
    p.print(out);
    return out;
}

void bTREE::print(ostream & outfile) const
{
    if (root == NULL)
        outfile << "-" << endl;
    else
    {
        displayLeft(outfile, root->leftptr, "    ");
        outfile << "---" << root->data << endl;
        displayRight(outfile, root->rightptr, "    ");
    }
}

void bTREE::displayLeft(ostream & outfile, treeNode * subtree, std::string prefix) const
{
    if (subtree == NULL)
    {
        outfile << prefix + "                              /" << endl;
    }
    else
    {
        displayLeft(outfile, subtree->leftptr, prefix + "                   ");
        outfile << prefix + "               /---" << subtree->data << endl;
        displayRight(outfile, subtree->rightptr, prefix + "              |    ");
    }
}

void bTREE::displayRight(ostream & outfile, treeNode * subtree, std::string prefix) const
{
    if (subtree == NULL)
    {
        outfile << prefix + "                              \\" << endl;
    }
    else
    {
        displayLeft(outfile, subtree->leftptr, prefix + "              |    ");
        outfile << prefix + "               \\---" << subtree->data << endl;
        displayRight(outfile, subtree->rightptr, prefix + "                   ");
    }
}

void bTREE::destroy( treeNode * & subtree)
{
	if( subtree != NULL )
   	{
      destroy( subtree->leftptr );
      destroy( subtree->rightptr );
      delete subtree;
      subtree = NULL;
   	}
}

bTREE::treeNode* bTREE::getRoot()
{
    return root;
}
