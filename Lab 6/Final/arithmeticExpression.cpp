#include "arithmeticExpression.h"
#include <stack>
#include <ostream>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//Returns a integar based on priority of operation - given by zybooks
int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    } else if(op == '*' || op == '/'){
        priority = 2;
    } else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

//Turns the user inputed infix expression to postfix - given by zybooks
string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            } else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            } else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        } else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

//Outputs the tree using visualize tree function - given by zybooks 
//Professor says we do not need to implement Graphviz
void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

//creates an arithmetic expression tree after using infix_to_postfix function
void arithmeticExpression::buildTree(){
    //initialize stack to store subtree nodes
    stack<TreeNode*> nodeStack;
    //change user infix input to postfix
    string postfixExpression = infix_to_postfix();
    //loop through each character to make new nodes add to tree/stack
    for(unsigned i = 0; i< postfixExpression.size();++i){
        char c = postfixExpression.at(i);
        //if character is not an operation, add to the stack
        if (priority(c) == 0){
            TreeNode* newNode = new TreeNode(c, c);
            nodeStack.push(newNode);
        } else {
            //if the character is an operation, make top two stack elements it's children
            //and add the new tree that was created to the stack
            TreeNode* newNode = new TreeNode(c, c);
            newNode -> right = nodeStack.top();
            nodeStack.pop();
            newNode -> left = nodeStack.top();
            nodeStack.pop();
            nodeStack.push(newNode);
        }

    }
    //assign the final tree that is on the stack as the root and delete the last element in the stack
    root = nodeStack.top();
    nodeStack.pop();
}

//Calls the recursive infix function.
void arithmeticExpression::infix(){
    infix(root);
}

//Calls the recursive prefix function.
void arithmeticExpression::prefix(){
    prefix(root);
}

//Calls the recursive postfix function.
void arithmeticExpression::postfix(){
    postfix(root);
}

//Outputs the infix notation of the arithmetic expression 
//tree with appropriate parenthesis around expression (inorder traversal)
void arithmeticExpression::infix(TreeNode *tree){
    TreeNode* curr = tree;
    //base case
    if (curr == nullptr){
        return;
    }
    //if a child node, the chracter is a value and msut add beginning parenthesis
    if (curr->right!=nullptr and curr->left !=nullptr){
        cout<<"(";
    }
    infix(curr->left);
    cout<< curr->key;
    infix(curr->right);
    //if a child node, the chracter is a value and msut add ending parenthesis
    if (curr->right!=nullptr and curr->left !=nullptr){
        cout<<")";
    }
}

//Outputs the prefix notation of the arithmetic expression tree (preorder traversal)
void arithmeticExpression::prefix(TreeNode *tree){
    TreeNode* curr = tree;
    //base case
    if (curr == nullptr){
        return;
    }
    cout<< curr->key;
    prefix(curr->left);
    prefix(curr->right);
}

//Outputs the postfix notation of the arithmetic expression tree (postorder traversal)
void arithmeticExpression::postfix(TreeNode *tree){
    TreeNode* curr = tree;
    //base case
    if (curr == nullptr){
        return;
    }
    postfix(curr->left);
    postfix(curr->right);
    cout<< curr->key;
}

//Helper function for generating the dotty file.
//Professor says we do not need to implement Graphviz
void arithmeticExpression::visualizeTree(ofstream &, TreeNode *tree){}
