 /******************************************************************
 * Binary Tree into LL (done IN PLACE)
 *
 *
 *         1                         
 *        / \
 *       2   5
 *      / \   \
 *     3   4   6
 *
 *       to
 *   1
 *    \
 *     2
 *      \
 *       3
 *        \
 *         4
 *          \
 *           5
 *            \
 *             6
 ******************************************************************/
 
 
/**
 * Definition for binary tree
 * /
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void flatten(TreeNode *root) {
  TreeNode *curNode = root;
  TreeNode *leftNode = NULL;
  TreeNode *rightNode = NULL;
  while (curNode) {
    leftNode = curNode->left;
    /* If there is no left node then we just continue to right sub tree */
    if (leftNode) {
      if (curNode->right) {
        /* Make the rightmost node in the left subtree point to right node
        Because as per our need we go the right child only after we are done
        with all elements in the left subtree */
        rightNode = leftNode;
        while (rightNode->right) {
          rightNode = rightNode->right;
        }
        rightNode->right = curNode->right;
      }
      /* Make the left child the right child */
      curNode->right = leftNode;
      curNode->left = NULL;
    }
    /* We no longer have left subtree */
    curNode = curNode->right;
  }
}
