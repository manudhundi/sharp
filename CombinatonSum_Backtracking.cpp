/******************************************************************************
 * Given a set of candidate numbers (C) and a target number (T),
 * find all unique combinations in C where the candidate numbers sums to T. 
 * The same repeated number may be chosen from C unlimited number of times.
 *
 * Note:
 * All numbers (including target) will be positive integers.
 * Elements in a combination (a1, a2, … , ak) must be in non-descending order.
 * (ie, a1 = a2 = … = ak).
 * The solution set must not contain duplicate combinations.
 * For example, given candidate set 2,3,6,7 and target 7, 
 * A solution set is: 
 * [7] 
 * [2, 2, 3] 
 *
 * The solution uses backtracking algorithm. We go through all potential
 * solution subtrees until we get a combination or we rule out the subtree
 * finding that possible combination can arise from that subtree.
 * RUNTIME: O((n+m)!) where n is num elements in candidates and
 *          m is possible repetitions of the smallest candidate
 * MEMORY: O(s) where is s is solution size. We store only possible 
 *         combinations
 *
 * Compiled and tested on Leetcode online Judge
 * 
 * Note: A dynamic programming approach is also possible, but it would consume
 *       a lot of space. A straightforward dynamic programming solution that
 *       I can think of would consume MEMORY of O(target*s) where is s is
 *       solution size and have a RUNTIME of O(target*n)
 *****************************************************************************/
class Solution {
private:
    void combinationSumRec(vector<int> &candidates, int target,
                           vector<vector<int> > &res, vector<int> &currVec,
						   int idx)
    {
        if (target < 0) {
            /* Prune out this sub tree and backtrack */
            return;
        }
        
        if (target == 0) {
            /* We have got one of the combinations */
            res.push_back(currVec);
        } else {
            while ((idx < candidates.size()) && (candidates[idx] <= target)) {
                /* Go to a subtree with the hope of a possible combination and 
                   include it in the currVec */
                currVec.push_back(candidates[idx]);
                /* Recursive in a subtree */
                combinationSumRec(candidates, target-candidates[idx], res,
								  currVec, idx);
                idx++;
                /* Move to another potential subtree where a combination
				   can be found */
                currVec.pop_back();
            }
        }
    }
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        vector<vector<int> > res;
        
        if (candidates.size() == 0) { return res; }
        
        sort(candidates.begin(), candidates.end());
        
        /* Current possible result in the potential solution tree */
        vector<int> currVec;
        /* Use recursion with backtracking */
        combinationSumRec(candidates, target, res, currVec, 0);
        
        return res;
    }
};
