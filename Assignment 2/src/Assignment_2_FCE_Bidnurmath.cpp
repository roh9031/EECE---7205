#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;

// using class instead of struct with oop approach
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

// helper class to manage tree operations using oop
class BinaryTreeHandler {
public:
    TreeNode* buildTreeLevelOrder(const vector<int>& arr) {
        if (arr.empty()) return nullptr;
        vector<TreeNode*> nodes(arr.size(), nullptr);
        for (size_t i = 0; i < arr.size(); ++i) {
            nodes[i] = new TreeNode(arr[i]);
        }
        for (size_t i = 0; i < arr.size(); ++i) {
            size_t leftIdx = 2 * i + 1;
            size_t rightIdx = 2 * i + 2;
            if (leftIdx < arr.size()) nodes[i]->left = nodes[leftIdx];
            if (rightIdx < arr.size()) nodes[i]->right = nodes[rightIdx];
        }
        return nodes[0];
    }

    // insert from the lecture: new node goes in the first free position in level order
    TreeNode* insertNode(TreeNode* root, int val) {
        TreeNode* newNode = new TreeNode(val);
        if (!root) return newNode;
        queue<TreeNode*> helper;
        helper.push(root);
        while (!helper.empty()) {
            TreeNode* curr = helper.front();
            helper.pop();
            if (!curr->left) { // first missing left child gets the new node
                curr->left = newNode;
                return root;
            }
            helper.push(curr->left);
            if (!curr->right) { // first missing right child gets the new node
                curr->right = newNode;
                return root;
            }
            helper.push(curr->right);
        }
        return root;
    }

    // helper print functions used to check the rebuilt tree in question 11
    void printLevelOrder(TreeNode* node) {
        if (!node) return;
        queue<TreeNode*> helper;
        helper.push(node);
        while (!helper.empty()) {
            TreeNode* curr = helper.front();
            helper.pop();
            cout << curr->val << " ";
            if (curr->left) helper.push(curr->left);
            if (curr->right) helper.push(curr->right);
        }
        cout << "\n";
    }

    void printPostorderHelper(TreeNode* node) {
        if (!node) return;
        printPostorderHelper(node->left);
        printPostorderHelper(node->right);
        cout << node->val << " ";
    }
    void printPostorder(TreeNode* node) {
        printPostorderHelper(node);
        cout << "\n";
    }

    // question 1 - maximum depth of a binary tree
    int maxDepth(TreeNode* node) {
       
        if (node == nullptr) return -1;
        int leftDepth = maxDepth(node->left);
        int rightDepth = maxDepth(node->right);
        return 1 + max(leftDepth, rightDepth);
  }
    /* for a single chain of 7 nodes the frequency count does not change (still 6n + 2 = 44 because it 
    only depends on n) but the recursion depth goes from 2 to 6 so the stack space goes from o(log n) to o(n) */




    // question 2: sum of all nodes
    int sumRecursive(TreeNode* node) {
        if (!node) return 0; //curr node value + all left node values + all right node values
        return node->val + sumRecursive(node->left) + sumRecursive(node->right); // sum = me + left + right
    }

    int sumQueue(TreeNode* node) {
        /*for ref initialize a queue helper and sum = 0 and push the root/first node value into it while the queue
         isnt empty catch the curr front value in the queue pop the value and sum the curr value push the remaining 
         left and right children into the queue if they exist and return the sum */
        if (!node) return 0;
        int sum = 0;
        queue<TreeNode*> helper;
        helper.push(node);
        while (!helper.empty()) {
            TreeNode* curr = helper.front();
            helper.pop();
            sum += curr->val;
            if (curr->left) helper.push(curr->left);
            if (curr->right) helper.push(curr->right);
        }
        return sum;
    }
    /* recursive uses o(h) stack space queue uses o(w) width space both visit each 
    node once so o(n) time (recursive 4n + 2 steps vs queue 6n + 5 steps) */




    // question 3: count nodes with exactly one child
    /*for ref: intialiaze count to 0 count left (or right) child only if they dont have right(or left) child */
    int countOneChild(TreeNode* node) {
        if (!node) return 0;
        int count = 0;
        if ((node->left && !node->right) || (!node->left && node->right)) {
            count = 1; // has only one child
        }
        return count + countOneChild(node->left) + countOneChild(node->right);
    }
    /* complete tree filled left to right means when n is even the last parent has one left child, 
    when n is odd it has two so zero single child nodes */




    // question 4: are two trees identical
    bool isIdentical(TreeNode* p, TreeNode* q) {
        /*for ref: check if curr values and the right and left child values are equal using recursion*/
        if (!p && !q) return true;
        if (!p || !q) return false;
        return (p->val == q->val) && isIdentical(p->left, q->left) && isIdentical(p->right, q->right);
    }
    /*for trees a and c it finds the diff at the very last leaf value 9 vs 10 best case o(1)
     worst case o(n) */




    // question 5: minimum value in a binary tree
    int minValue(TreeNode* node) {
        /* for ref: individually find the min value in root left and right and update the m variable*/
        if (!node) return INT_MAX;
        int m = node->val;
        m = min(m, minValue(node->left));
        m = min(m, minValue(node->right));
        return m;
    }
    /* if bst we just go left all the way in o(log n) instead of scanning every node */




    // question 6: invert (mirror) a binary tree
    TreeNode* invertTree(TreeNode* node) {
        /*for ref: traverse left traverse right and then recursively swap values/pointers
        inverTree(node->left);
        invertTree(node->right);
        swap(invertTree(node->left), inverTree(node->right));*/

        if (!node) return nullptr;
        TreeNode* temp = node->left;
        node->left = node->right;
        node->right = temp;
        invertTree(node->left);
        invertTree(node->right);
        return node;
    }
    /* inorder before is 21 12 3 5 17 8 9 and after is completely reversed because left and right 
    subtrees swap everywhere */





    // question 7: print each level and right side view
    void levelAndRightView(TreeNode* node) {
        if (!node) return;
        queue<TreeNode*> helper;
        helper.push(node);
        cout << "levels:\n";
        vector<int> rightView;
        while (!helper.empty()) {
            int size = helper.size();
            cout << "[";
            vector<int> levelVals;
            for (int i = 0; i < size; ++i) {
                TreeNode* curr = helper.front();
                helper.pop();
                levelVals.push_back(curr->val);
                if (i == size - 1) rightView.push_back(curr->val);
                if (curr->left) helper.push(curr->left);
                if (curr->right) helper.push(curr->right);
            }
            for (size_t i = 0; i < levelVals.size(); ++i) {
                cout << levelVals[i] << (i + 1 == levelVals.size() ? "" : ", ");
            }
            cout << "]\n";
        }
        cout << "right side view: ";
        for (size_t i = 0; i < rightView.size(); ++i) {
            cout << rightView[i] << (i + 1 == rightView.size() ? "" : ", ");
        }
        cout << "\n";
    }
    /*complexity depends on total n nodes and h+1 levels since we push/pop everything and print row by row */





    // question 8: zigzag level order traversal
    vector<int> zigzagLevelOrder(TreeNode* node) {
        vector<int> result;
        if (!node) return result;
        queue<TreeNode*> helper;
        helper.push(node);
        bool leftToRight = true;
        while (!helper.empty()) {
            int size = helper.size();
            vector<int> level(size);
            for (int i = 0; i < size; ++i) {
                TreeNode* curr = helper.front();
                helper.pop();
                int index = leftToRight ? i : (size - 1 - i);
                level[index] = curr->val;
                if (curr->left) helper.push(curr->left);
                if (curr->right) helper.push(curr->right);
            }
            leftToRight = !leftToRight;
            result.insert(result.end(), level.begin(), level.end());
        }
        return result;
    }
    /* queue plus indexing avoids extra stack overhead and keeps extra work low while hitting o(n). 
    counted on the example index filling 87 steps queue + reverse 85 two stacks 67 so two stacks 
    has the fewest steps but needs two containers */





    // question 9: is the tree complete
    bool isCompleteTree(TreeNode* node) {
        if (!node) return true;
        queue<TreeNode*> helper;
        helper.push(node);
        bool nullSeen = false;
        while (!helper.empty()) {
            TreeNode* curr = helper.front();
            helper.pop();
            if (!curr) {
                nullSeen = true; // once null is seen no real nodes allowed after
            } else {
                if (nullSeen) return false;
                helper.push(curr->left);
                helper.push(curr->right);
            }
        }
        return true;
    }
    /* insert and delete keep trees complete by filling left to right so gaps arent allowed */





    // question 10: lowest common ancestor
    TreeNode* lowestCommonAncestor(TreeNode* node, int pVal, int qVal) {
        if (!node || node->val == pVal || node->val == qVal) return node;
        TreeNode* leftLCA = lowestCommonAncestor(node->left, pVal, qVal);
        TreeNode* rightLCA = lowestCommonAncestor(node->right, pVal, qVal);
        if (leftLCA && rightLCA) return node;
        return leftLCA ? leftLCA : rightLCA;
    }
    /* single recursive pass visits each node once o(n) better than storing full paths */

    // question 10 twist, method 1: find both root to node paths and compare them
    bool findPath(TreeNode* node, int target, vector<int>& path) {
        if (!node) return false;
        path.push_back(node->val);
        if (node->val == target) return true;
        if (findPath(node->left, target, path) || findPath(node->right, target, path)) return true;
        path.pop_back(); // target is not below this node so remove it from the path
        return false;
    }
    int lcaByPaths(TreeNode* node, int pVal, int qVal) {
        vector<int> pathA, pathB;
        findPath(node, pVal, pathA);
        findPath(node, qVal, pathB);
        size_t i = 0;
        while (i < pathA.size() && i < pathB.size() && pathA[i] == pathB[i]) ++i;
        return pathA[i - 1]; // last value the two paths share
    }
    /* method 1 runs two full searches plus a compare and stores both paths method 2 does one pass 
    (example lca(21 3): 48 steps vs 41 steps) */





    // question 11: build tree from preorder and inorder
    TreeNode* buildTreeHelper(vector<int>& preorder, int preStart, int preEnd, vector<int>& inorder, int inStart, int inEnd, unordered_map<int, int>& inMap) {
        if (preStart > preEnd || inStart > inEnd) return nullptr;
        TreeNode* root = new TreeNode(preorder[preStart]);
        int inRoot = inMap[root->val];
        int numsLeft = inRoot - inStart;
        root->left = buildTreeHelper(preorder, preStart + 1, preStart + numsLeft, inorder, inStart, inRoot - 1, inMap);
        root->right = buildTreeHelper(preorder, preStart + numsLeft + 1, preEnd, inorder, inRoot + 1, inEnd, inMap);
        return root;
    }
    TreeNode* buildTreeFromPreIn(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inMap;
        for (size_t i = 0; i < inorder.size(); ++i) inMap[inorder[i]] = i;
        return buildTreeHelper(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, inMap);
    }
    /* linear search takes o(n^2) worst case hash map lookup drops it to theta(n) */





    // question 12: diameter of a binary tree
    int heightAndDiameter(TreeNode* node, int& diameter) {
        if (!node) return -1;
        int leftH = heightAndDiameter(node->left, diameter);
        int rightH = heightAndDiameter(node->right, diameter);
        diameter = max(diameter, leftH + rightH + 2);
        return 1 + max(leftH, rightH);
    }
    int diameterOfBinaryTree(TreeNode* node) {
        int diameter = 0;
        heightAndDiameter(node, diameter);
        return diameter;
    }
    /* calling height at every node gives theta(n^2) doing it in one pass gives theta(n) */





    // question 13: serialize and deserialize
    void serializeHelper(TreeNode* node, string& str) {
        if (!node) {
            str += "N ";
            return;
        }
        str += to_string(node->val) + " ";
        serializeHelper(node->left, str);
        serializeHelper(node->right, str);
    }
    string serialize(TreeNode* node) {
        string res = "";
        serializeHelper(node, res);
        return res;
    }
    TreeNode* deserializeHelper(stringstream& ss) {
        string valStr;
        ss >> valStr;
        if (valStr == "N") return nullptr;
        TreeNode* node = new TreeNode(stoi(valStr));
        node->left = deserializeHelper(ss);
        node->right = deserializeHelper(ss);
        return node;
    }
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        return deserializeHelper(ss);
    }
    /* n+1 null markers plus n values gives exactly 2n + 1 tokens in stream */





    // question 14: is valid bst
    bool isValidBSTHelper(TreeNode* node, long long minVal, long long maxVal) {
        if (!node) return true;
        if (node->val <= minVal || node->val >= maxVal) return false;
        return isValidBSTHelper(node->left, minVal, node->val) && isValidBSTHelper(node->right, node->val, maxVal);
    }
    bool isValidBST(TreeNode* node) {
        return isValidBSTHelper(node, LLONG_MIN, LLONG_MAX);
    }
    /* range passing validates top-down efficiently alternative uses inorder traversal check */

    // question 14 twist: second solution using inorder traversal (values must be strictly increasing)
    bool isValidBSTInorder(TreeNode* node, long long& prev) {
        if (!node) return true;
        if (!isValidBSTInorder(node->left, prev)) return false;
        if (node->val <= prev) return false; // not bigger than the value visited before it
        prev = node->val;
        return isValidBSTInorder(node->right, prev);
    }
    /* range method 5n + 3 steps vs inorder 7n + 2 steps best case range o(1) and inorder o(h) because 
    it has to reach the leftmost node first */





    // question 15: vertical order traversal
    void verticalTraversal(TreeNode* node) {
        if (!node) return;
        map<int, vector<int>> m;
        queue<pair<TreeNode*, int>> helper;
        helper.push({node, 0});
        while (!helper.empty()) {
            auto p = helper.front();
            helper.pop();
            TreeNode* curr = p.first;
            int hd = p.second;
            m[hd].push_back(curr->val);
            if (curr->left) helper.push({curr->left, hd - 1});
            if (curr->right) helper.push({curr->right, hd + 1});
        }
        cout << "vertical order:\n";
        for (auto it = m.begin(); it != m.end(); ++it) {
            cout << "distance " << it->first << ": ";
            for (size_t i = 0; i < it->second.size(); ++i) {
                cout << it->second[i] << (i + 1 == it->second.size() ? "" : ", ");
            }
            cout << "\n";
        }
    }
    /* map groups nodes by horizontal distance tree of n nodes can have up to 2h+1 columns */
};




int main() {
    vector<int> arr = {5, 12, 8, 21, 3, 17, 9};
    BinaryTreeHandler treeHandler;
    TreeNode* root = treeHandler.buildTreeLevelOrder(arr);

    cout << "q1: max depth \n" << treeHandler.maxDepth(root) << "\n\n";
    cout << "q2: sum of nodes \nrecursive: " << treeHandler.sumRecursive(root) << ", queue: " << treeHandler.sumQueue(root) << "\n\n";
    
    TreeNode* rootQ3 = treeHandler.buildTreeLevelOrder(arr);
    rootQ3 = treeHandler.insertNode(rootQ3, 4); // insert(root, 4) puts 4 as the left child of 21
    cout << "q3: one child count \n" << treeHandler.countOneChild(rootQ3) << "\n\n";

    TreeNode* rootB = treeHandler.buildTreeLevelOrder(arr);
    TreeNode* rootC = treeHandler.buildTreeLevelOrder({5, 12, 8, 21, 3, 17, 10});
    cout << "q4: identical trees\n" 
         << "identical(a, b) = " << (treeHandler.isIdentical(root, rootB) ? "true" : "false") << "\n"
         << "identical(a, c) = " << (treeHandler.isIdentical(root, rootC) ? "true" : "false") << "\n\n";

    cout << "q5: minimum value \n" << treeHandler.minValue(root) << "\n\n";

    cout << "q6: invert tree \n";
    TreeNode* inverted = treeHandler.invertTree(treeHandler.buildTreeLevelOrder(arr));
    queue<TreeNode*> qInv; qInv.push(inverted);
    while(!qInv.empty()){
        TreeNode* curr = qInv.front(); qInv.pop();
        cout << curr->val << " ";
        if(curr->left) qInv.push(curr->left);
        if(curr->right) qInv.push(curr->right);
    }
    cout << "\n\n";

    cout << "q7: levels & right view \n";
    treeHandler.levelAndRightView(root);
    cout << "\n";

    cout << "q8: zigzag traversal\n";
    vector<int> zz = treeHandler.zigzagLevelOrder(root);
    for (int v : zz) cout << v << " ";
    cout << "\n\n";

    // tree q = {5, 12, 8, null, 3, 17, 9}: same as arr but 12 has no left child
    TreeNode* rootQ9 = treeHandler.buildTreeLevelOrder(arr);
    rootQ9->left->left = nullptr;
    cout << "q9: complete tree \n" 
         << "complete(p) = " << (treeHandler.isCompleteTree(root) ? "true" : "false") << "\n"
         << "complete(q) = " << (treeHandler.isCompleteTree(rootQ9) ? "true" : "false") << "\n\n";

    cout << "q10: lowest common ancestor \n"
         << "lca(21, 3) = " << treeHandler.lowestCommonAncestor(root, 21, 3)->val << "\n"
         << "lca(21, 9) = " << treeHandler.lowestCommonAncestor(root, 21, 9)->val << "\n"
         << "lca(17, 8) = " << treeHandler.lowestCommonAncestor(root, 17, 8)->val << "\n"
         << "by paths: " << treeHandler.lcaByPaths(root, 21, 3) << ", "
         << treeHandler.lcaByPaths(root, 21, 9) << ", "
         << treeHandler.lcaByPaths(root, 17, 8) << "\n\n";

    cout << "q11: build from preorder & inorder \n";
    vector<int> preorder = {5, 12, 21, 3, 8, 17, 9};
    vector<int> inorder = {21, 12, 3, 5, 17, 8, 9};
    TreeNode* rebuilt = treeHandler.buildTreeFromPreIn(preorder, inorder);
    cout << "rebuilt root value: " << rebuilt->val << "\n";
    cout << "level order: ";
    treeHandler.printLevelOrder(rebuilt);
    cout << "postorder: ";
    treeHandler.printPostorder(rebuilt);
    cout << "\n";

    cout << "q12: diameter \n" << treeHandler.diameterOfBinaryTree(root) << "\n\n";

    cout << "q13: serialize & deserialize \n";
    string serializedStr = treeHandler.serialize(root);
    cout << "serialized: " << serializedStr << "\n";
    TreeNode* deserialized = treeHandler.deserialize(serializedStr);
    cout << "deserialized root value: " << deserialized->val << "\n\n";

    TreeNode* rootS = treeHandler.buildTreeLevelOrder({9, 5, 17, 3, 8, 12, 21});
    long long prevP = LLONG_MIN, prevS = LLONG_MIN;
    cout << "q14: is valid bst \n"
         << "isbst(p) = " << (treeHandler.isValidBST(root) ? "true" : "false") << "\n"
         << "isbst(s) = " << (treeHandler.isValidBST(rootS) ? "true" : "false") << "\n"
         << "inorder isbst(p) = " << (treeHandler.isValidBSTInorder(root, prevP) ? "true" : "false") << "\n"
         << "inorder isbst(s) = " << (treeHandler.isValidBSTInorder(rootS, prevS) ? "true" : "false") << "\n\n";

    cout << "q15: vertical order traversal \n";
    treeHandler.verticalTraversal(root);

    return 0;
}