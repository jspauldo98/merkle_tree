#include <iomanip>
#include "bTREE.h"
#include "pMT.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;
pMT::pMT(int hashSelect)
/**
 * @brief
 * @param hashSelect a number corresponding to the hashfunction to use for this pMT
 * @return
 */
{
	myMerkle = bTREE();
	selectedHash = hashSelect;
  counterFind = 0;
}

pMT::~pMT()
/**
 * @brief destructor
 * @return nada
 */
{
}

int pMT::insert(string vote, int time)
/**
 * @brief insert a vote and time into a leaf node of tree
 * @param vote - a string
 * @param time - an int representing the time
 * @return the number of operations needed to do the insert, -1 if out of memory
 */

{

	myMerkle.insert(vote, time);

	if (myMerkle.numberOfNodes() > 2)
		rehash(myMerkle.getRoot());

	return myMerkle.dataInserted();
}

void pMT::rehash(bTREE::treeNode * tree)
{

	if (tree != NULL && !(tree->isleaf))
	{
		rehash(tree->leftptr);
        rehash(tree->rightptr);

        switch (selectedHash)
    	{
    		case 1:
    		      tree->data = hash_1(tree->leftptr->data + tree->rightptr->data);
                  break;
    		case 2:
    		      tree->data = hash_2(tree->leftptr->data + tree->rightptr->data);
    		      break;
    		case 3:
    		      tree->data = hash_3(tree->leftptr->data + tree->rightptr->data);
    		      break;
    	}

	}
}

bool pMT::inorderSearch(bTREE::treeNode * subtree, string s, int time, bool &found)
{
  if (subtree != NULL)
    {
        inorderSearch(subtree->leftptr, s, time, found);
        counterFind++;
        if (subtree->data.compare(s) == 0 && subtree->time == time)
        {
            counterFind+=3;
            found = true;
        }
        inorderSearch(subtree->rightptr, s, time, found);
    }

    return found;
}

int pMT::find(string vote, int time, int hashSelect)
/**
 * @brief given a vote, timestamp, and hash function, does this vote exist in the tree?
 * @param vote, a string
 * @param time, an int
 * @param hashSelect, an int corresponding to the hash functions _1, _2, and _3
 * @return 0 if not found, else number of opperations required to find the matching vote
 */
{
  // if leaf nodes are "raw strings" why are we given hashSelect as a parameter?
  bool found = false;
  if (inorderSearch(myMerkle.getRoot(), vote, time, found))
    return counterFind;
  else
	 return 0;
}

int pMT::findHash(string mhash)
/**
 * @brief does this hash exist in the tree?
 * @param mhash, a string to search for in the tree
 * @return 0 if not found, else number of opperations required to find the matching hash
 */
{
  if (myMerkle.find(mhash))
    return myMerkle.dataFound();
  else
    return 0;
}


string pMT::locateData(string vote)
/**
 * @brief Function takes a hash of Vote and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root.
 * @param vote, the data to search for
 * @return sequence of L's and R's comprising the movement to the leaf node; else return a dot '.'
 */

{
	string map = myMerkle.locate(vote);
	return map;
}

string pMT::locateHash(string mhash)
/**
 * @brief Function takes a hash and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root.
 * @param mhash, the hash to search for
 * @return sequence of L's and R's comprising the movement to the hash node, ; else return a dot '.'
 */
{
	string map = myMerkle.locate(mhash);
	return map;
}



string pMT::hash_1(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 * creator: Sam
 */
{
    char charKey[64];

    // put the key in a char array of length 32 (maximum output length)
    for (int i = 0, j = 0; i < 64; i++, j++) {
        if (j == key.length()) {
            j = 0;
        }

        charKey[i] = (char) key.at(j);
    }


    string hash;

    // max unsigned long 4294967295
    // max prime in range: 4294967291
    unsigned long myPrime = 4294967291;

    // mod 95 then plus 33 to avoid unwanted characters

    // do the operation on the first character
    hash = (char) ((((((int) charKey[0] + (int) charKey[1])) % myPrime) % 94) + 33);

    // do the operation on the rest
    for (int i = 2; i < 63; i += 2) {

        hash += (char) ((((((int) charKey[i] + (int) charKey[i + 1]) * i) % myPrime) % 94) + 33);
    }


    return hash;


}

string pMT::hash_2(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 * ETHAN'S HASH
 */
 {
    int prime = 2147483647;
    int hash = 5381; //"5381 is just a number that, in testing, resulted in fewer collisions and better avalanching." - stackoverflow user Mahmoud Al-Qudsi
 	 int a = 378551;
 	 int b = 63689;
 	 // a and b pulled from lab 9
    for (int i=0; i < key.length(); i++)
    {
       hash += ((unsigned char)key[i] % prime) * a;
 			a = a * b;
    }
 	 //string s = to_string(hash);
 	 ostringstream str1;
 	 str1 << hash;
 	 string s = str1.str();
	 srand(NULL);
 	 while(s.length() < 32)
 	 {
 		 int digit = rand() % 10;
 		 ostringstream str2;
 		 str2 << digit;
 		 string temp = str2.str();
 		 s += temp;
 	 }
 	 while(s.length() > 32)
 	 {
 		 s.erase(s.length()-1);
 	 }
 	 return s;
  }
//Jared's Hash
string pMT::hash_3(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */

{
	// initialize prime constants
	const int A = 15607;
	const int B = 38303;

	// initialize new string and length
	string new_key = "";
	int length = key.length();

	// if length is < 32 make it 32 by cycling through
	// the key and adding more characters
	// if the length is > 32  make it 32 by putting the last chacters first
	if (length < 32) {
		int i = 0;
		while (key.length() < 32)
		{
			key += key.at(i);
			i++;
		}
		length = key.length();
	}
	else if (length > 32) {
		int j = 0;
		while (key.length() > 32)
		{
			key.at(j) = key.at(length - (j + 1));
			key.erase(length - (j + 1));
			j++;
		}
		length = key.length();
	}

	// make hash
	for (int i = 0; i < length; i++)
	{
		int ascii = (unsigned char)key.at(i);
		new_key += (((((ascii * A) ^ (ascii * B) * i) ) % 93) + 33);
	}

	return new_key;

}

bool operator ==(const pMT& lhs, const pMT& rhs)
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if equal, false otherwise
 */
{
	// return (lhs.myMerkle.getRoot()->data.compare(rhs.myMerkle.getRoot()->data) == 0) ? true : false;
	return lhs.myMerkle == rhs.myMerkle;
}

bool operator !=(const pMT& lhs, const pMT& rhs)
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if not equal, false otherwise
 */
{
	// return (lhs.myMerkle.getRoot()->data.compare(rhs.myMerkle.getRoot()->data) != 0) ? true : false;
	return lhs.myMerkle != rhs.myMerkle;
}

// friend pMT pMT::operator ^=(const pMT& lhs, const pMT& rhs)
// /**
//  * @brief XOR between two merkle trees
//  * @param lhs, the left hand side of the equality statment
//  * @param rhs, the right hand side of the equality statement
//  * @return true if not equal, false otherwise
//  */
// {
// }


ostream& operator <<(ostream& out, const pMT& p)
/**
 * @brief Print out a tree
 * @param out
 * @param p
 * @return a tree to the screen
 */
{
	out << p.myMerkle;
	return out;
}


void pMT::overloadedCaratHelper(pMT& lhs, bTREE::treeNode * rRoot, pMT& rightSide) {
	// preorder traversal

	if (rRoot) {
		if (lhs.find(rRoot->data, rRoot->time, 1) == 0) {
			rightSide.insert(rRoot->data, rRoot->time);
		}
		overloadedCaratHelper(lhs, rRoot->leftptr, rightSide);
		overloadedCaratHelper(lhs, rRoot->rightptr, rightSide);
	}
}

void pMT::helper2(pMT& lhs, pMT& rhs, pMT& rightSide) {
	overloadedCaratHelper(lhs, rhs.myMerkle.getRoot(), rightSide);
	if (rightSide.myMerkle.getRoot() == NULL) {
		rightSide.insert("validated", 0);
	}
}

// int pMT::numberOfNodes() {
// 	return myMerkle.numberOfNodes();
// }

pMT operator ^(pMT& lhs, pMT& rhs)
/**
 * @brief Where do two trees differ
 * @param lhs
 * @param rhs
 * @return a tree comprised of the right hand side tree nodes that are different from the left
 */
{
	pMT rightSide(1);
	rightSide.helper2(lhs, rhs, rightSide);
	return rightSide;
}
