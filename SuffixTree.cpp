#include "SuffixTree.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <cstring>

using namespace std;

SuffixTree::SuffixTree() {
    //trieRoot = makeTrieNode(NULL);
    //trieRootWithError = makeTrieNode(NULL);
    queryLength = 36;
    //randomQuery = new char[queryLength + 1];
    nodeCount = 0;
    treeRoot = makeTreeNode();
}

SuffixTree::SuffixTree(long long int qSize):SuffixTree() {
    this->queriesSize = qSize;
    //this->segmentLength = 50000;
    this->segmentLength = 50;
 }

void SuffixTree::readHumanGenomes(string genomeFilePath) {
    // read file char by char
    char ch;
    fstream fin(genomeFilePath, fstream::in);
    char* headerCharArray;

    /* Time function returns the time since the
    Epoch(jan 1 1970). Returned time is in seconds. */
    time_t start, end;
    std::time(&start);
    std::ios_base::sync_with_stdio(false);

    // Calculating the size of the file
    fin.seekg(0, std::ios::end);
    long long int size = fin.tellg();
    fin.seekg(0, std::ios::beg);

    // Dynamically allocating memory for the array
    genomeArray = new char[size];
    bool isHeader = false;
    long long int charArridx = 0;
    long long int headerCharidx = 0;
    //long long int genomeLength = 0;

    while (fin >> noskipws >> ch) {

        // 62 = >
        if (ch == 62) {
            isHeader = true;

            /*totalGenomeLength += genomeLength;
            genomeLength = 0;*/
        }

        if (isHeader) {
            if (ch == 10) {
                isHeader = false;
            }
        }
        else if (ch != 10)
        {
            genomeArray[charArridx++] = ch;
            totalGenomeLength++;
        }
    }
    fin.close();

    genomeArray[charArridx] = '\0';

    std::ios_base::sync_with_stdio(false);
    time(&end);

    // Calculating total time taken by the program.
    double time_taken = double(end - start);
    cout << "Time taken to read the genome file : " << fixed
        << time_taken;
    cout << " sec " << endl;
}

void SuffixTree::getSegmentFromSubject() {
    genomeSubStr = new char[this->segmentLength + 1];

    long long int startIndex = rand() % (this->totalGenomeLength - this->segmentLength - this->queryLength);

    strncpy(genomeSubStr, genomeArray + startIndex, this->segmentLength);

    genomeSubStr[this->segmentLength] = '\0';
}

TreeNode* SuffixTree::makeTreeNode(string str) {
    // Allocate memory for node
    TreeNode* node = new TreeNode;

    node->A = NULL;
    node->C = NULL;
    node->G = NULL;
    node->T = NULL;
    node->N = NULL;
    node->DS = NULL;
    node->data = str;

    return node;
}

void SuffixTree::createChild(TreeNode* p, TreeNode* c, char ch) {

}

void SuffixTree::buildTheSuffixTree() {
    nodeCount = 0;
    char* suffixTreeSubStr = new char[this->segmentLength + 1];
    long long int len = 0;
    long long int nodeDatalen = 0;


    TreeNode* current = treeRoot;

    for (long long int i = 0; i < this->segmentLength; i++)
    {
        strncpy(suffixTreeSubStr, this->genomeSubStr + i, this->segmentLength - i);
        suffixTreeSubStr[this->segmentLength - i] = '\0';
        len = strlen(suffixTreeSubStr);
        TreeNode *tempNode1, *tempNode2;

        for (long long int j = 0; j < len; j++)
        {

            switch (suffixTreeSubStr[j])
            {
            case 'A':
                if (current->A == NULL) {
                    current->A = makeTreeNode(suffixTreeSubStr);
                    nodeDatalen = sizeof(current->A->data) / sizeof(current->A->data);
                }
                else {
                    nodeDatalen = current->A->data.length();
                    for (long long int k = 0; k < nodeDatalen && k < len; k++)
                    {
                        if (current->A->data[k] != suffixTreeSubStr[k]) {
                            
                            string s = current->A->data.substr(k, nodeDatalen - k);
                            current->A->data = current->A->data.substr(0, k);
                            tempNode1 = makeTreeNode(s);
                            tempNode2 = makeTreeNode(suffixTreeSubStr);
                            createChild(current->A, tempNode1, suffixTreeSubStr[k]);
                        }
                    }
                }
                break;
            case 'C':
                if (current->C == NULL) {
                    current->C = makeTreeNode(suffixTreeSubStr);
                }
                break;
            case 'G':
                if (current->G == NULL) {
                    current->G = makeTreeNode(suffixTreeSubStr);
                }
                break;
            case 'T':
                if (current->T == NULL) {
                    makeTreeNode(suffixTreeSubStr);
                }
                break;
            case 'N':
                if (current->N == NULL) {
                    current->N = makeTreeNode(suffixTreeSubStr);
                }
                break;
            default:
                break;
            }
            break;
        }
    }
}