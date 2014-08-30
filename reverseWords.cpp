/****************************************************************
 * Given an input string, reverse the string word by word.
 * For example, given s = "the sky is blue",
 *              return "blue is sky the"
 *
 * Additional constraints: 
 * 1)reversed string should not contain leading or trailing spaces
 * 2)multiple spaces between two words in input string to be 
 *   reduced to a single space in the reversed string
 *
 * Implementation Logic:
 * 1) Reverse all characters:
 *    "the sky is blue" ---> "eulb si yks eht" -- O(n) time
 * 2) Reverse each word
 *    "eulb si yks eht" ---> "blue is sky the" -- O(n) time
 ****************************************************************/

#include <string>
using namespace std;

class Solution {
private:
    /* Reverse a portion of the string from start pos to
       end pos */
    void reverse(string &s, int start, int end)
    {
        for (int i = start, j = end-1; i < j; i++, j--)
        {
            /* Swap */
            char temp = s[i];
            s[i] = s[j];
            s[j] = temp;
        }
    }
    /* Reverse every word in the string */
    void reverseEachWord(string &s)
    {
        int startIdx = 0, endIdx = 0;
        
        while (startIdx < s.size()) {
            /* Words are seperated by white space */
            endIdx = s.find(' ', startIdx);
            if (endIdx == -1) { /* last word */
                endIdx = s.size();
            }
            /* Reverse a word */
            reverse(s, startIdx, endIdx);
            startIdx = endIdx + 1;
            /* Delete trailing white space */
            while ((startIdx < s.size()) &&
                    (s[startIdx] == ' ')) {
                s.erase(startIdx, 1);
            }
        }
        /* Erase last space */
        if (s[s.size()-1] == ' ') { s.erase(s.size()-1, 1); }
    }
public:
    void reverseWords(string &s) {
        int i = s.size() - 1;
        /* Erase trailing spaces characters */
        while ((i > 0) && (s[i] == ' ')) {
            s.erase(i, 1);
            i--;
        }
        /* First the reverse the all characters */
        reverse(s, 0, s.size());
        
        /* Reverse each word in the string */
        reverseEachWord(s);
    }
};
