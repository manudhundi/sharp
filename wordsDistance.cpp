/******************************************************************************
 * Given two words word1 and word2, find the minimum number of steps required
 * to convert word1 to word2. (each operation is counted as 1 step.)

 * 3 operations permitted on a word:

 * a) Insert a character
 * b) Delete a character
 * c) Replace a character
 *
 * The solution uses dynamic programming paradigm.
 *
 * RUNTIME: O(mn)
 * MEMORY: O(mn) where m and n are lengths of the words
 *
 * Compiled and tested on Leetcode online Judge
 * https://oj.leetcode.com/problems/edit-distance/
 *****************************************************************************/
#include <vector>
#include <string>
using namespace std;

class Solution {
private:
    int findMin(int a, int b, int c) {
        if (a < b) {
            if (a < c) {
                return a;
            } else {
                return c;
            }
        } else {
            if (b < c) {
                return b;
            } else {
                return c;
            }
        }
    }
public:
    int minDistance(string word1, string word2) {
        int **distTable;
        
        if (word1.length() == 0) { 
            return word2.length();
        }
        if (word2.length() == 0) { 
            return word1.length();
        }
        
        /* Create a 2D table */
        distTable = new int*[word1.length() + 1];
        for (int i = 0; i <= word1.length(); i++) {
            distTable[i] = new int[word2.length() + 1];
        }
        
        /* Initialize the table */
        for (int i = 0; i <= word1.length(); i++) {
            distTable[i][0] = i;
        }
        for (int j = 0; j <= word2.length(); j++) {
            distTable[0][j] = j;
        }
        
        /* Bottom up DP approach */
        for (int i = 1; i <= word1.length(); i++) {
            for (int j = 1; j <= word2.length(); j++) {
                /* (i,j) entry in the table is the minimum of 
				   (replacement, insertion, deletion) 
                    Note: Table from (1,1) to (i,j); but word1 and word2
        				  are from 0 to i-1 */
                distTable[i][j] = findMin(distTable[i-1][j-1] + (word1[i-1] != word2[j-1]),
                                          distTable[i][j-1] + 1,
                                          distTable[i-1][j] + 1);
            }
        }
        return distTable[word1.length()][word2.length()];
    }
};
