#include <iostream>
#include "Card.h"
using namespace std;

class BST {    
    struct node {
        Card data;
        int count;
        node* left;
        node* right;
    };
    int* deck = new int[13];
    node* root;
    node* makeEmpty(node* t) {
        if(t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }
    node* insert(Card x, node* t){
        if(t == NULL)
        {
            t = new node;
            t->count = 1;
            t->data = x;
            t->left = t->right = NULL;
        }else if(x.getValue() == t->data.getValue()){
            t->count++;
            return t;
        }
        else if(x.getValue() < t->data.getValue())
            t->left = insert(x, t->left);
        else if(x.getValue() > t->data.getValue())
            t->right = insert(x, t->right);
        return t;
    }
    node* findMin(node* t){
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }
    node* findMax(node* t) {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }
    node* remove(Card x, node* t) {
        node* temp;
        if(t == NULL)
            return NULL;
        else if(x.getValue() < t->data.getValue())
            t->left = remove(x, t->left);
        else if(x.getValue() > t->data.getValue())
            t->right = remove(x, t->right);
        else if(t->left && t->right){
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            if(t->count > 1){
                t->count--;
                return t;
            }            
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        return t;
    }
    void inorder(node* t) {
        if(t == NULL)
            return;
        inorder(t->left);
        deck[t->data.getValue() - 1] = t->count;
        inorder(t->right);
    }
    node* find(node* t, Card x) {
        if(t == NULL)
            return NULL;
        else if(x.getValue() < t->data.getValue())
            return find(t->left, x);
        else if(x.getValue() > t->data.getValue())
            return find(t->right, x);
        else
            return t;
    }
public:
    BST() {
        root = NULL;
    }
    void empty() {
        root = makeEmpty(root);
    }
    void insert(Card x) {
        root = insert(x, root);
    }
    void remove(Card x) {
        root = remove(x, root);
    }
    void search(Card x) {
        root = find(root, x);
    }
    int* getData(){
        inorder(root);
        return deck;
    }

};