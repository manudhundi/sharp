/******************************************************************************
 * Given s1, s2, s3, find whether s3 is formed by the
 * interleaving of s1 and s2.
 * https://oj.leetcode.com/problems/interleaving-string/
 *
 * The solution uses dynamic programming approach. We go through all possible
 * ways through which input strings can be interleaved and see if they
 * produce a target string finally
 *
 * RUNTIME: O(mn) 
 * MEMORY: O(mn) where m and n are lengths of the input strings
 *
 * Compiled and tested on Leetcode online Judge
 *****************************************************************************/
#include <string>
using namespace std;

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if ((s1.length() + s2.length()) != s3.length()) {
            return false;
        }
        /* 2D table for DP solution */
        bool **table = new bool*[s1.length() + 1];
        int i = 0, j = 0;
        for (i = 0; i <= s1.length(); i++) {
            table[i] = new bool[s2.length() + 1];
        }
        
        /* Initialize the table */
        table[0][0] = true;
        for (i = 1; i <= s1.length(); i++) {
            if (s1[i-1] == s3[i-1]) {
                table[i][0] = true;
            } else {
                for (; i <= s1.length(); i++) {
                    table[i][0] = false;
                }
            }
        }
        for (j = 1; j <= s2.length(); j++) {
            if (s2[j-1] == s3[j-1]) {
                table[0][j] = true;
            } else {
                for (; j <= s2.length(); j++) {
                    table[0][j] = false;
                }
            }
        }
        /* Build the table */
        for (i = 1; i <= s1.length(); i++) {
            for (j = 1; j <= s2.length(); j++) {
                table[i][j] = ((table[i-1][j] && (s1[i-1] == s3[i+j-1]))
                               || (table[i][j-1] && (s2[j-1] == s3[i+j-1])));
            }
        }
        return table[s1.length()][s2.length()];
    }
};
