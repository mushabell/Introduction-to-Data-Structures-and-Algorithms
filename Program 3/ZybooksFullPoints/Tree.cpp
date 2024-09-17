#include "Tree.h"
#include "iostream"
#include <stdexcept>

void Tree::insert(const string &value){
    Node* curr = root;
    //it is a new tree and root is nullptr
    if (curr == nullptr){
        Node* newNode = new Node(value);
        root = newNode;
        return;
    }
    //if the key is already in the tree throw an error
    if (search(value)){
        throw runtime_error("Value in tree can not be inserted again");
    }
    
    //find the next leaf node for the value
    Node* parent = curr;
    //cout<<"amshu: part 1"<<endl;
    while (curr -> left != nullptr){
        //cout<<"Amshu: entered the while loop"<<endl;
        parent = curr;
        if (curr->keycount == 1){
            if (value < curr->small){
                curr = curr -> left;
            } else {
                curr = curr -> middle;
            }
        } else {
            if (value < curr->small){
                curr = curr -> left;
            } else if (value > curr->small and value < curr->large){
                curr = curr -> middle;
            } else {
                curr = curr -> right;
            }
        }
    }
    //cout<<"Amshu: part 2"<<endl;
    //make sure if the leaf node is the root, the parent is re-assigned to 
    if (curr == root){
        //cout<<"Amshu: I entered the root== curr loop"<<endl;
        parent = nullptr;
    }
    //call split function if leaf is full
    if (curr->keycount == 2){
        split(value, root, curr, parent);
        // if (parent == nullptr){
        //     cout<<"Amshu: parent is nullptr"<<endl;
        // } else {
        //     cout<<"amshu: this is the parent: " << parent -> small<<endl;
        // }
    } else {
        //if the leaf node is not full, intert correctly
        if (value < curr->small){
            curr->large = curr->small;
            curr->small = value;
        } else {
            curr->large = value;
        }
        curr->keycount++;
        //cout<<"amshu: the values in the node are "<<curr->small << " and " << curr->large<<endl;
    }
}

//splits the leaf nodes of the tree to help with insertion of new keys
void Tree::split(const string& value, Node* tree, Node* node, Node* parent){
    //find the values that in order from smallest to largest and assing to correct strings
    string small;
    string medium;
    string large;
    //if the new value is smaller than both nodes
    if (value < node->small){
        small = value;
        medium = node->small;
        large = node->large;
    } else if ( value > node->small and value < node->large){
        //if the new value is inbetween both nodes
        small = node->small;
        medium = value;
        large = node->large;
    } else {
        //if the value is bigger than all nodes
        small = node->small;
        medium = node->large;
        large = value;
    }
    //assign the split children with their own correct children
    Node* splitLeft = new Node(small);
    Node* splitRight = new Node(large);
    //if the node is not the root call a helper function
    if (parent != nullptr) {
        if (parent->keycount == 1){
            //cout<<"Amshu: entered the keycount = 1"<<endl;
            if (medium > parent->small){
                //cout<<"Amshu: entered the loop for "<<endl;
                parent->large = medium;
                parent -> middle = splitLeft;
                parent ->  right = splitRight;
                splitLeft -> parent = parent;
                splitRight -> parent = parent;
                parent -> keycount++;
                if (parent == root){
                    //cout<<"Amshu: entered the parent == root"<<endl;
                    root = parent;
                }
            }
        }
    } else {
        //if the node is the root, then create a new root and assign the pointers correctly
        Node* nodeParent = new Node(medium, splitLeft, splitRight);
        splitLeft -> parent = nodeParent;
        splitRight -> parent = nodeParent;
        root = nodeParent;
    }
    return;
}

//call on recursive preOrder function
void Tree::preOrder() const{
    preOrder(root);
    cout<<endl;
}

//call on recursive inOrder function
void Tree::inOrder() const{
    inOrder(root);
    cout<<endl;
}

//call on recursive postOrder function
void Tree::postOrder( ) const{
    postOrder(root);
    cout<<endl;
}
void Tree::remove(const string &value){
    //check if the value is found in the tree
    Node* curr = root;
    string nodePosition;
    if (curr==nullptr){
        throw runtime_error("attempting to remove node from tree with no values");
    }
    //cout<<"Amshu: positon 1"<<endl;
    while (true){
        if (curr -> small == value or curr -> large == value){
            //cout<<"Amshu: found the value we were looking for"<<endl;
            if (value == curr->small){
                nodePosition = "s";
                //cout<<"amshu: position 3"<<endl;
            } else {
                nodePosition = "l";
            }
            break;
        }
        //cout<<"Amshu: position 2"<<endl;
        if (curr -> keycount == 1){
            //cout<<"amshu: root key count is one"<<endl;
            if (value < curr->small){
                curr = curr -> left;
            } else {
                //cout<<"amshu: position 2"<<endl;
                curr = curr -> middle;
            }
        } else {
            if (value < curr->small) {
                curr = curr -> left;
            } else if (value > curr->small and value > curr->large){
                curr = curr->middle;
            } else {
                curr = curr->right;
            }
        }
        if (curr == nullptr){
            throw runtime_error("The value you want to remove is not found inside the tree");
        } 
    }
    // if (curr->parent == root){
    //     cout<<"amshu: the parent is not null"<<endl;
    // } else if (curr->parent == nullptr){
    //     cout<<"amshu: the parent is null and the curr small is: "<< curr -> small<<endl;
    // }
    //cout<<"amshu: out of while"<<endl;
    //cout<<"Amshu: the parent of the node is: "<<curr->parent->small<<endl;
    if (curr == root){
        //cout<<"Amshu: curr == root"<<endl;
        if(curr->keycount == 1){
            if (curr->left == nullptr and curr->middle == nullptr){
                delete(curr);
                root = nullptr;
            } else {
                // cout<<"amshu: inside the else loop"<<endl;
                // if (curr == root){
                //     cout<<"Amshu: you have the right current node"<<endl;
                //     cout<<"Amshu: the curr left keycount is: "<<curr->left->keycount<<endl;
                // }
                if (curr->left->keycount ==1 and curr->middle->keycount == 1){
                    //cout<<"amshu: inside the if loop"<<endl;
                    curr -> small = curr->left->small;
                    curr -> large = curr->middle->small;
                    // cout<<"Amshu: root large value is: " << root->large<<endl;
                    // cout<<"amshu: assigned the values to root"<<endl;
                    delete(curr->left);
                    delete(curr->middle);
                    //cout<<"amshu: deleted the nodes of chiildren"<<endl;
                    curr->left = nullptr;
                    curr->middle = nullptr;
                    curr->right = nullptr;
                    curr->keycount++;
                    root = curr;
                    //cout<<"amshu: assigned a nullptr"<<endl;
                    return;
                }
            }
        } else {
            if (nodePosition == "s"){
                root ->small = root->large;
            }
            root->large = "";
            root -> keycount--;
            //cout<<"Amshu: the current keycount is: "<<curr->keycount<<endl;
        }
        return;
    }
    //cout<<"Amshu: im in the outside"<<endl;
    if (curr->keycount == 1){
        //cout<<"Amshu: keycount is equal to one loop"<<endl;
        //cout<<"Amshu: the parent of the node is: "<<curr->parent->small<<endl;
        //cout<<"amshu: position 4"<<endl;
        // if (curr->parent == root ){
        //     cout<<"Amshu: correct logic"<<endl;
        // }
        if (curr == curr -> parent -> left){
            //cout<<"amshu: entered the first loop"<<endl;
            if (curr -> parent -> middle -> keycount == 1){
                curr -> parent -> large = curr -> parent -> middle -> small;
                delete(curr->parent->middle);
                curr->parent->middle=nullptr;
            } else {
                //implementation not nessassary for zybooks
                throw runtime_error("not implemented yet");
            }
            curr -> parent -> left = nullptr;
            curr -> parent -> keycount++;
            delete(curr);
        } else if (curr == curr -> parent -> middle){
            if (curr->parent->left->keycount==1){
                curr -> parent -> large = curr -> parent -> small;
                curr -> parent -> small = curr -> parent -> left -> small;
                delete(curr->parent->left);
                curr -> parent -> left = nullptr;
            } else {
                //implementation not nessassary for zybooks
                throw runtime_error("not implemented yet");
            }
            curr -> parent -> middle = nullptr;
            curr -> parent -> keycount++;
            delete(curr);
        }
    } else {
        if (nodePosition == "s"){
            curr -> small = curr -> large;
        }
        curr -> large = "";
        curr -> keycount--;
    }
}

//searches for node with string value and returns a boolean value
bool Tree::search (const string &value) const{
    Node* curr = root;
    //loop through until we reach end of tree
    while (curr != nullptr){
        if (curr -> small == value or curr -> large == value){
            //if value is found return true
            return true;
        }
        if (curr -> keycount == 1){
            if (value < curr->small){
                curr = curr -> left;
            } else {
                curr = curr -> middle;
            }
        } else {
            if (value < curr->small) {
                curr = curr -> left;
            } else if (value > curr->small and value > curr->large){
                curr = curr->middle;
            } else {
                curr = curr->right;
            }
        } 
    }
    //if value is not found, return false
    return false;
}

//traverse through tree by root, left, and right
void Tree::preOrder(Node* tree) const{
    Node* curr = tree;
    //base case
    if (curr == nullptr){
    return;
    }
    cout << curr->small << ", ";
    preOrder(curr->left);
    if (curr -> keycount == 2){
        cout<< curr -> large << ", ";
    }
    preOrder(curr->middle);
    preOrder(curr->right);
}

//traverse through tree by left, root, and right
void Tree::inOrder(Node* tree) const{
    Node* curr = tree;
    //base case
    if (curr == nullptr){
        return;
    }
    inOrder(curr->left);
    cout<< curr->small << ", ";
    inOrder(curr->middle);
    if (curr -> keycount == 2){
        cout<< curr -> large << ", ";
    }
    inOrder(curr->right);
}

//traverse through the tree by left, right, and root
void Tree::postOrder(Node* tree) const{
    Node* curr = tree;
    //base case
    if (curr == nullptr){
    return;
    }
    postOrder(curr->left);
    postOrder(curr->middle);
    cout<< curr->small << ", ";
    postOrder(curr->right);
    if (curr -> keycount == 2){
        cout<< curr -> large << ", ";
    }
}
void Tree::merge(Node* node){

}

void Tree::rotateRight(Node* node){

}

void Tree::rotateLeft(Node* node){

}

void Tree::fusion(Node* node){

}
