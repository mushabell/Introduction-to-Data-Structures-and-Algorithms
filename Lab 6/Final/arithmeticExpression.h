#pragma once
#include <iostream>
#include <cstdlib>

using namespace std;
//struct for TreeNode for the arithmetic expression tree
struct TreeNode{
   char data;
   char key;
   TreeNode* left;
   TreeNode* right;
   TreeNode(char data, char key):data(data),key(key),left(0),right(0){}
};

//Arithmetic expression class
class arithmeticExpression{
   string infixExpression;
   TreeNode* root;

  public:
   //Initializes an empty tree and sets the infixExpression to the value of parameter passed in.
   arithmeticExpression(const string &expression){
      root = nullptr;
      infixExpression = expression;
   }

   //deconstructor, copy-constructor, and assignment operator
   ~arithmeticExpression() {
      // The Node struct recursively deletes its children
      delete root;
   }
   arithmeticExpression(const arithmeticExpression&) = delete;
   arithmeticExpression& operator=(const arithmeticExpression&) = delete;

   //creates an arithmetic expression tree after using infix_to_postfix function
   void buildTree();

   //Calls the recursive infix function
   void infix();

   //Calls the recursive prefix function
   void prefix();

   //Calls the recursive postfix function
   void postfix();

   //Outputs the tree using visualize tree function - given by zybooks 
   //Professor says we do not need to implement Graphviz 
   void visualizeTree(const string &);

 private:
   //Returns a integar based on priority of operation - given by zybooks
   int priority(char op);

   //Turns the user inputed infix expression to postfix - given by zybooks
   string infix_to_postfix();

   //Outputs the infix notation of the arithmetic expression 
   //tree with appropriate parenthesis around expression (inorder traversal)
   void infix(TreeNode *tree);

   //Outputs the prefix notation of the arithmetic expression tree (preorder traversal)
   void prefix(TreeNode *tree);

   //Outputs the postfix notation of the arithmetic expression tree (postorder traversal)
   void postfix(TreeNode *tree);

   //Helper function for generating the dotty file.
   //Professor says we do not need to implement Graphviz
   void visualizeTree(ofstream &, TreeNode *tree);
};