/******************************************************************************
 * Given a string s and a dictionary of words dict, add spaces in s to
 * construct a sentence where each word is a valid dictionary word.
 *
 * Return all such possible sentences.
 *
 * For example, given
 * s = "catsanddog",
 * dict = ["cat", "cats", "and", "sand", "dog"].
 *
 * A solution is ["cats and dog", "cat sand dog"]
 *
 * Solution:
 * The solution uses combination of Dynamic Programming approach
 * and recursion with backtracking.
 *
 * Solution using only DP consumes a lot of memory as we need to
 * cache all potential solutions.
 * A solution with recursion and backtracking has a high runtime
 * as we do not backtrack early in recursion tree
 *
 * The solution below builds a table using DP approach maintains
 * if the string can be broken into words upto a particular char
 * in the string. This helps to backtrack very early in the recursion
 * tree and thereby reduce the runtime.
 *
 * Compiled and tested on Leetcode online Judge
******************************************************************************/
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

class Solution {
private:
	  /* Check if a word s is found in the dict */
    bool wordFound(string s, unordered_set<string> &dict)
    {
        if (dict.count(s)) { return true;}
        return false;
    }
	  /* Recursively find the all solutions. (like DFS)
		Note: string potentialResult should not be a reference as we
	        we do not want the potentialResult subsequent recurvise
			    calls in the recursion tree */
    void findAllSentences(string &s, unordered_set<string> &dict,
                          bool *wordTable, string potentialResult,
						  vector<string> &res, int start, int end)
    {
        if (end < start) { /* We have found a sentence */
            /* Delete the last extra space */
            potentialResult.erase(potentialResult.length()-1, 1);
            /* Add to result */
            res.push_back(potentialResult);
        }
        
        for (int i = end; i >= start; i--) {
            if ((!i || wordTable[i-1]) &&
        		wordFound(s.substr(i, end-i+1), dict)) {
                /* Prepend to the potentialResult*/
                potentialResult.insert(0, " ");
                potentialResult.insert(0, s.substr(i, end-i+1));
                findAllSentences(s, dict, wordTable, potentialResult, res,
                    			 start, i-1);
				        /* No explicit backtracking here. If a solution is found we
				           would have added it to res, else we just continue */
                potentialResult.erase(0, s.substr(i, end-i+1).length() + 1);
            }
        }
    }
public:
    vector<string> wordBreak(string s, unordered_set<string> &dict) {
        vector<string> res;
        string potentialResult;
        bool *wordTable = new bool[s.length()];
        if (!dict.size()) { return res; }
        
        for (int i = 0; i < s.length(); i++) {
            wordTable[i] = false;
        }
        /* Build the table which indicates if upto a point string can be
		       broken into words */
        for (int i = 0; i < s.length(); i++) {
            if (!wordTable[i] && wordFound(s.substr(0, i+1), dict)) { 
                wordTable[i] = true;
            }
            if (!wordTable[i]) { continue; }
            
            for (int j = i+1; j < s.length(); j++) {
                if (wordFound(s.substr(i+1, j-(i+1)+1), dict)) {
                    wordTable[j] = true;
                }
            }
        }
        
        int end = s.length()-1;
		    /* Return here itself no solution is possible */
        if (!wordTable[end]) {
            return res;
        }
        /* Starting from last try to find valid word breaks,
    	   backtrack when needed */
        findAllSentences(s, dict, wordTable, potentialResult, res, 0,
                    	 s.length()-1);
        return res;
    }
};
