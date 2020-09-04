// #include<bits/stdc++.h>
#include <vector>
#include <utility>
#include <exception>
#include <iostream>
#include <stack>
#include <map>
#include <string>
using namespace std;
#pragma once

namespace cop3530 {
    template<typename Key, typename T>

    class bst {
        struct node {
            Key key;  // key
            T value;  // value

            node* left;  // left child
            node* right;  // right child

            node() {}
            node(Key k, T t) {}
        };
        node* root; // root of tree

    public:
        bst();

        ~bst();
        void destructHelper(node* head);

        void insert(const Key& key, const T& t);
        void insertHelper(node*& head, const Key& key, const T& t); // Insert's Helper Function

        void erase(const Key& key);
        node* deleteNode(node* head, const Key& key);
        node* minValueNode(node* head);

        T& at(const Key& key);
        T& atHelper(node* atRoot, const Key& key);

        bool contains(const Key& key) const;
        bool containsHelper(node* head, const Key& key) const;

        bool empty() const;

        size_t size() const;
        size_t sizeHelper(node* sizeNode) const;

        vector<pair<Key, T>> inorder_contents();
        void inorderHelp(vector<pair<Key, T>>& contents, node* head);

        vector<pair<Key, T>> preorder_contents();
        void preorderHelp(vector<pair<Key, T>>& contents, node* head);

    };




// ============ Constructor ==============
    template<typename Key, typename T>
    bst<Key, T>::bst()
    {
        //Constructs a bst object, initializing necessary member variables, etc.
        root = nullptr;
    }





// =========================== Destructor =================
    template<typename Key, typename T>
    bst<Key, T>::~bst()
    {
        //Destructs the bst object. Should free any dynamically allocated memory.
        destructHelper(root);
    }
    
    template<typename Key, typename T>
    void bst<Key, T>::destructHelper(node* head)
    {
        if(head != NULL)
        {
            if(head->left != NULL)
            {
                destructHelper(head->left);
            }
            if(head->right != NULL)
            {
                destructHelper(head->right);
            }

            delete head;
        }
    }





// ==================== Insert Function ========================
    template<typename Key, typename T>
    void bst<Key, T>::insert(const Key& key, const T& t)
    {
        //Inserts a new node into the bst, mapping key to t. If a node with Key key is already present in the bst, t replaces the previously mapped value.
        // node* temp = root;

        insertHelper(root, key, t);
    }

    template<typename Key, typename T>
    void bst<Key, T>::insertHelper(node*& head, const Key& key, const T& t)
    {
        node* newNode = new node;
        newNode->left = nullptr;
        newNode->right = nullptr;

        if (head == nullptr)
        {
            head = newNode;
            head->key = key;
            head->value = t;
        }
        else if(head->key == key)
        {
            head->value = t;
        }

        if (key < head->key)
        {
            insertHelper(head->left, key, t);
        }
        else if(key > head->key)
        {
            insertHelper(head->right, key, t);
        }
    }





// ================== Erase Function ===========================
    template<typename Key, typename T>
    void bst<Key, T>::erase(const Key& key)
    {
        //Removes the node with Key key from the bst. Throws an out_of_range error if a node with Key key is not found in the bst.

        if(root != nullptr)
        {
            root = deleteNode(root, key);
        }
        else
        {
            throw out_of_range("");
        }        
    }

    template<typename Key, typename T>
    typename bst<Key, T>::node* bst<Key, T>::deleteNode(node* root, const Key& key)
    {
        if(root == NULL) // Base case
        {
            throw out_of_range("");
        } 

        else if(key == root->key)
        {
            if(root->left == NULL){
                node* temp = root;
                root = root->right;
                delete temp;
            }
            else if(root->right == NULL){
                node* temp = root;
                root = root->left;
                delete temp;
            }
            

            //Two children
            else
            {
                node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->value = temp->value;
                root->right = deleteNode(root->right, temp->key);
            }
            return root;
        }

        else if (key < root->key)
        {
            root->left = deleteNode(root->left, key);
        }
        else if(key > root->key)
        {
            root->right = deleteNode(root->right, key);
        }
        return root;
    }

    template<typename Key, typename T>
    typename bst<Key, T>::node* bst<Key, T>::minValueNode(node* head)
    {
        node* current = head;
        
        while(current && current->left != NULL)
        {
            current = current->left;
        }
        return current;        
    }








// ==================== At Function =============================
    template<typename Key, typename T>
    T& bst<Key, T>::at(const Key& key)
    {
        //Returns a reference to the value type to which key maps.
        //Throws an out_of_range error if a node with Key key is not found in the bst.

        return atHelper(root, key);
    }

    template<typename Key, typename T>
    T& bst<Key, T>::atHelper(node* head, const Key& key)
    {
        if (root == nullptr)
        {
            throw out_of_range("");
        }
        if(head == nullptr)
        {
            throw out_of_range("");
        }
        if (head->key == key)
        {
            return head->value;
        }
        if (key < head->key)
        {
            atHelper(head->left, key);
        }
        else if(key > head->key)
        {
            atHelper(head->right, key);
        }
        else
        {
            throw out_of_range("");
        } 
    }






// ==================== Contains Function =====================
    template<typename Key, typename T>
    bool bst<Key, T>::contains(const Key& key) const
    {
        //Returns true if a node with Key key is present in the bst and false otherwise.
        if (containsHelper(root, key) == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template<typename Key, typename T>
    bool bst<Key, T>::containsHelper(node* head, const Key& key) const
    {
        if (root == nullptr)
        {
            return false;
        }
        if (head->key == key)
        {
            return true;
        }
        if (key < head->key)
        {
            containsHelper(head->left, key);
        }
        else if (key > head->key)
        {
            containsHelper(head->right, key);
        }
        else 
        {
            return false;
        }
    }







// ======================= Empty Function ========================
    template<typename Key, typename T>
    bool bst<Key, T>::empty() const
    {
        //Returns true if the bst is empty and false otherwise.
        if (root == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }










// ===================== Size Function ============================
    template<typename Key, typename T>
    size_t bst<Key, T>::size() const
    {
        //Returns the number of nodes in the bst.
        return sizeHelper(root);
    }

    template<typename Key, typename T>
    size_t bst<Key, T>::sizeHelper(node* head) const
    {
        size_t countNodes = 1;

        if(head == NULL)
        {
            return 0;
        }
        else
        {
            countNodes += sizeHelper(head->left);
            countNodes += sizeHelper(head->right);
            return countNodes;
        }  
    }









// ==================== In Order Function =========================
    template<typename Key, typename T>
    vector<pair<Key, T>> bst<Key, T>::inorder_contents()
    {
        //Performs an inorder traversal of the bst and returns the contents as a vector of pairs. Each pair’s first element should be the key of the corresponding bst node and the second element should be the value of the corresponding bst node. See the test cases for details on the format expected.

        //Left-Root-Right

        vector<pair<Key, T>> contents;

        inorderHelp(contents, root);
        return contents;
    }

    template<typename Key, typename T>
    void bst<Key, T>::inorderHelp(vector<pair<Key, T>>& contents, node* head)
    {
        if (head == nullptr)
        {
            //Nothing
        }
        else
        {
            inorderHelp(contents, head->left);
            contents.push_back(make_pair(head->key, head->value));
            inorderHelp(contents, head->right);
        }
    }










// ======================= Pre Order Function ==========================
    template<typename Key, typename T>
    vector<pair<Key, T>> bst<Key, T>::preorder_contents()
    {
        //Performs a preorder traversal of the bst and returns the contents as a vector of pairs. Each pair’s first element should be the key of the corresponding bst node and the second element should be the value of the corresponding bst node.

        vector<pair<Key, T>> contents;
        preorderHelp(contents, root);

        return contents;
    }

    template<typename Key, typename T>
    void bst<Key, T>::preorderHelp(vector<pair<Key, T>>& contents, node* head)
    {
        if (head == NULL)
        {
            // Do Nothing
        }
        else
        {
            contents.push_back(make_pair(head->key, head->value));
            preorderHelp(contents, head->left);
            preorderHelp(contents, head->right);
        }        
    }
}
