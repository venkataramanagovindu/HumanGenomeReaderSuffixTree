#pragma once

#include <string>
using namespace std;


struct TreeNode {
	string data;
	TreeNode* A = NULL;
	TreeNode* C = NULL;
	TreeNode* G = NULL;
	TreeNode* T = NULL;
	TreeNode* N = NULL;
	TreeNode* DS = NULL;
};

class SuffixTree
{
	private:
		char* genomeArray;
		long long int totalGenomeLength = 0;
		char* genomeSubStr;
		TreeNode* treeRoot;
		long long int queriesSize; // Number of queries to be picked from the 50k segment, 5k, 50k etc
		long long int segmentLength; // The length of the segment from the Subject Genome - 50K
		int queryLength; // Length of each query - 36
		long long int nodeCount;

	public:
		void readHumanGenomes(string genomeFilePath);
		void getSegmentFromSubject();
		SuffixTree();
		SuffixTree(long long int qSize);
		TreeNode* makeTreeNode(string str = "\0");
		void buildTheSuffixTree();
		void createChild(TreeNode* p, TreeNode* c, char ch);

};

