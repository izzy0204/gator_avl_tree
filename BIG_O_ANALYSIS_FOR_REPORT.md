# Big O Complexity Analysis Template for Report.pdf

## Instructions
Copy this analysis into your Report.pdf. Make sure to include:
1. Variable definition (what is n?)
2. Time complexity justification
3. Space complexity justification

---

## Variable Definition

**n** = the number of nodes (student records) currently in the AVL tree

---

## Time and Space Complexity Analysis

### 1. insert(name, id)

**Time Complexity:** O(log n)

**Justification:** 
- The insertion follows a binary search tree path from root to a leaf, which takes O(log n) time in a balanced tree
- After insertion, we traverse back up the path updating heights and checking balance, which is also O(log n) since the height of an AVL tree is guaranteed to be O(log n)
- If rebalancing is needed, rotations take O(1) time
- Total: O(log n) for search path + O(log n) for rebalance path = O(log n)

**Space Complexity:** O(log n)

**Justification:**
- The recursive call stack depth equals the height of the tree
- In an AVL tree, height is guaranteed to be O(log n)
- Each recursive call uses O(1) space
- Total recursion depth: O(log n)

---

### 2. remove(id)

**Time Complexity:** O(log n)

**Justification:**
- Finding the node to delete requires traversing the BST, which takes O(log n) time
- If the node has two children, finding the inorder successor (leftmost node in right subtree) takes O(log n) time in the worst case
- After deletion, we traverse back up rebalancing, which takes O(log n) time
- Rotations take O(1) time
- Total: O(log n)

**Space Complexity:** O(log n)

**Justification:**
- The recursive call stack depth equals the height of the tree
- Height is O(log n) for an AVL tree
- Each recursive call uses O(1) space

---

### 3. search(id) - Search by ID

**Time Complexity:** O(log n)

**Justification:**
- This is a standard BST search operation
- At each node, we compare the target ID with the current node's ID and go either left or right
- In an AVL tree with height O(log n), we traverse at most O(log n) nodes
- Each comparison takes O(1) time

**Space Complexity:** O(log n)

**Justification:**
- The recursive call stack depth equals the search path length
- In an AVL tree, the maximum path length is the height, which is O(log n)

---

### 4. search(name) - Search by Name

**Time Complexity:** O(n)

**Justification:**
- Unlike searching by ID, searching by name cannot use the BST property (tree is sorted by ID, not name)
- We must visit every node in the tree to find all matches
- We use preorder traversal which visits each node exactly once
- Total: O(n) nodes × O(1) per node = O(n)

**Space Complexity:** O(k) where k is the number of matching names, or O(n) in worst case

**Justification:**
- We store all matching IDs in a vector
- In the best case (few matches), this is O(k) where k << n
- In the worst case (all nodes have the same name), this is O(n)
- Recursion depth is O(log n) but the vector storage dominates

---

### 5. printInorder()

**Time Complexity:** O(n)

**Justification:**
- Inorder traversal visits every node in the tree exactly once
- At each node, we perform O(1) work (add name to vector)
- After traversal, printing the names with commas takes O(n) time
- Total: O(n)

**Space Complexity:** O(n)

**Justification:**
- We store all n names in a vector before printing
- The recursion call stack has depth O(log n), but the vector storage dominates
- Total: O(n)

---

### 6. printPreorder()

**Time Complexity:** O(n)

**Justification:**
- Preorder traversal visits every node exactly once
- At each node, we perform O(1) work (add name to vector)
- Printing takes O(n) time
- Total: O(n)

**Space Complexity:** O(n)

**Justification:**
- We store all n names in a vector
- Recursion depth is O(log n), but vector storage dominates
- Total: O(n)

---

### 7. printPostorder()

**Time Complexity:** O(n)

**Justification:**
- Postorder traversal visits every node exactly once
- At each node, we perform O(1) work (add name to vector)
- Printing takes O(n) time
- Total: O(n)

**Space Complexity:** O(n)

**Justification:**
- We store all n names in a vector
- Recursion depth is O(log n), but vector storage dominates
- Total: O(n)

---

### 8. printLevelCount()

**Time Complexity:** O(1)

**Justification:**
- We simply return the height stored in the root node
- This is a single member variable access
- No traversal or computation required
- Total: O(1)

**Space Complexity:** O(1)

**Justification:**
- No additional data structures used
- No recursion
- Only accessing a single integer value

---

### 9. removeInorder(N)

**Time Complexity:** O(n)

**Justification:**
- First, we perform a full inorder traversal to collect all IDs, which takes O(n) time
- Then, we remove the Nth ID, which takes O(log n) time
- The inorder traversal dominates: O(n) + O(log n) = O(n)

**Space Complexity:** O(n)

**Justification:**
- We store all n node IDs in a vector during the inorder collection
- The remove operation uses O(log n) space for recursion
- The vector storage dominates: O(n)

---

## Summary Table

| Operation | Time Complexity | Space Complexity | Primary Factor |
|-----------|-----------------|------------------|----------------|
| insert | O(log n) | O(log n) | AVL tree height |
| remove | O(log n) | O(log n) | AVL tree height |
| search (by ID) | O(log n) | O(log n) | BST search |
| search (by name) | O(n) | O(k) to O(n) | Full traversal needed |
| printInorder | O(n) | O(n) | Visit all nodes |
| printPreorder | O(n) | O(n) | Visit all nodes |
| printPostorder | O(n) | O(n) | Visit all nodes |
| printLevelCount | O(1) | O(1) | Direct access |
| removeInorder | O(n) | O(n) | Full inorder + remove |

---

## Key Points for Report

1. **AVL Tree Height Guarantee:** 
   - The height of an AVL tree with n nodes is always O(log n)
   - This is maintained by the balance factor constraint (±1)
   - This guarantee is crucial for the efficiency of insert, remove, and search by ID

2. **Trade-offs:**
   - Operations that use the BST property (search by ID) are efficient: O(log n)
   - Operations that require visiting all nodes (search by name, traversals) are O(n)
   - We chose to sort by ID for efficient ID lookups, accepting O(n) for name searches

3. **Space Considerations:**
   - Recursive implementations use O(log n) stack space
   - Operations that collect results use O(n) or O(k) space for storage
   - This is a trade-off between code simplicity and memory usage

4. **Rotation Complexity:**
   - All four rotation types (left, right, left-right, right-left) take O(1) time
   - This is because rotations only involve pointer reassignments
   - No nodes are visited beyond the rotation point
