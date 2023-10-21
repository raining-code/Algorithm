#include <iostream>
#include <stack>
using std::cout;
using std::endl;
using std::stack;
// 二叉树非递归进行前/中/后序遍历
class Code12_TreeOrder {
private:
    struct TreeNode {
        TreeNode(int val = 0) {
            this->val = val;
        }
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
        int val;
    };
    static void PrevOrder(TreeNode* root) {
        // 中 左 右
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            auto node = st.top();
            st.pop();
            cout << node->val << ' ';
            if (node->right) {
                st.push(node->right);
            }
            if (node->left) {
                st.push(node->left);
            }
        }
        cout << endl;
    }
    static void InOrder(TreeNode* root) {
        // 左 中 右
        stack<TreeNode*> st;
        TreeNode* cur = root;
        while (cur || !st.empty()) {
            while (cur) {
                st.push(cur);
                cur = cur->left;
            }
            cout << st.top()->val << ' ';
            cur = st.top()->right;
            st.pop();
        }
        cout << endl;
    }
    static void PostOrderUse2Stack(TreeNode* root) {
        // 使用2个栈版本的后续遍历
        // 左 右 中
        // 先序：中 左 右
        // 中 右 左
        stack<TreeNode*> st;
        stack<TreeNode*> collect;
        st.push(root);
        while (!st.empty()) {
            auto node = st.top();
            st.pop();
            collect.push(node);
            if (node->left) {
                st.push(node->left);
            }
            if (node->right) {
                st.push(node->right);
            }
        }
        while (!collect.empty()) {
            cout << collect.top()->val << ' ';
            collect.pop();
        }
        cout << endl;
    }
    static void PostOrderUse1Stack(TreeNode* root) {
        // 使用1个栈版本的后续遍历
        // 左 右 中
        stack<TreeNode*> st;
        st.push(root);
        TreeNode* last = nullptr; // last表示前一个遍历的树
        while (!st.empty()) {
            TreeNode* cur = st.top();              // cur表示当前遍历到的树
            if (!cur->left || cur->left == last) { // 左为空或左树已经完成遍历
                if (!cur->right) {
                    cout << cur->val << ' ';
                    st.pop();
                    last = cur;
                } else { // 右不为空
                    if (cur->right == last) {
                        cout << cur->val << ' ';
                        st.pop();
                        last = cur;
                    } else {
                        st.push(cur->right);
                    }
                }
            } else if (cur->right && cur->right == last) {
                cout << cur->val << ' ';
                st.pop();
                last = cur;
            } else {
                st.push(cur->left);
            }
        }
        cout << endl;
    }

public:
    static void Run() {
        TreeNode root1;
        root1.val = 1;
        TreeNode root2;
        root2.val = 2;
        TreeNode root3;
        root3.val = 3;
        TreeNode root4;
        root4.val = 4;
        TreeNode root5;
        root5.val = 5;
        TreeNode root6;
        root6.val = 6;
        TreeNode root7;
        root7.val = 7;
        root1.left = &root2;
        root1.right = &root3;
        root2.left = &root4;
        root2.right = &root5;
        root3.left = &root6;
        root3.right = &root7;
        PrevOrder(&root1);
        InOrder(&root1);
        PostOrderUse2Stack(&root1);
        PostOrderUse1Stack(&root1);
    }
};