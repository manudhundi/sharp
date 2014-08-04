/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
private:
    void splitList(ListNode *head, ListNode **list1, ListNode **list2)
    {
        ListNode *hare = head;
        ListNode *tortoise = head;
        if (!list1 || !list2)
            return;
            
        if (!head) {
            *list1 = NULL;
            *list2 = NULL;
        }
        *list1 = head;
        
        while (hare->next) {
            hare = hare->next->next;
            if (!hare) {
                break;
            }
            tortoise = tortoise->next;
        }
        *list2 = tortoise->next;
        tortoise->next = NULL; /* Important, don't miss this */
        return;
    }

    /* Move from head of a list1 to head of list2 */
    void moveNode(ListNode **dst, ListNode **src)
    {
        ListNode *node = *src;
        
        /* Update head of src list */
        *src = (*src)->next;
        
        /* Add node at head of dst list */
        node->next = *dst;
        *dst = node; /* Update head of dst list */
    }

    /* Merge 2 sorted lists */
    ListNode* mergeSortedLists(ListNode *list1, ListNode *list2)
    {
        ListNode* result = NULL;
        ListNode** currRef = &result;
        
        while (1) {
            if (!list1) {
                *currRef = list2;
                break;
            } else if (!list2) {
                *currRef = list1;
                break;
            } else {
                if (list1->val < list2->val) {
                    moveNode (currRef, &list1);
                } else {
                    moveNode (currRef, &list2);
                }
                currRef = &((*currRef)->next);
            }
        }
        return result;
    }
    
    /* IN PLACE merge sort */
    ListNode *mergeSortList(ListNode *head)
    {
        ListNode *list1 = NULL, *list2 = NULL;
        if (!head || !(head->next)) { /* base cases */
            return head;
        }
        /* Divide the list into 2 */
        splitList(head, &list1, &list2);
        
        /* Recursively merge left half and right half */
        list1 = mergeSortList(list1);
        list2 = mergeSortList(list2);
        
        /* Merge the result */
        return (mergeSortedLists(list1, list2));
    }
public:
    ListNode *sortList(ListNode *head) {
        return (mergeSortList(head));
    }
};
