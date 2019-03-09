#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>
// HELPER FUNCTIONS HERE...
template <class T>
BST<T>::BST(){
	root = NULL;
}

template <class T>
BST<T>:: ~BST(){
    // your destructor code goes here
	clear(root);
    //root will be deleted using post-order traversal
	//setting the root = to NULL now
	root = NULL;
}

template <class T>
int BST<T> :: height (node<T>* p){
   // your find height code goes here
   int h = -1;
	 if(p!=NULL)
	 {
		 int height_left = height(p->left);
		 int height_right = height(p->right);
		 int max_height = max(height_left,height_right);
		 h = max_height+1;
	 }
	 return h;

}

template <class T>
int BST<T> :: balanceFactor(node<T>* p){
    // you can use this to find balance factor.
		//balance factor is difference of height of left subtree-height of right subtree

			return (height(p->left)-height(p->right));


}

template <class T>
void BST<T> :: fixHeight(node<T>* p){
    // use this function to fix height of a node after insertion or deletion.
		if(p!=NULL)
		{
			p->height = height(p);
		}

    return;
}

// ROTATING HELPERS
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* p){
    // Rotate left code goes here.
		node<T>*temp = p->left;
		p->left = temp->right;
		temp->right = p;
    return temp;
}

template <class T>
node<T>* BST<T> :: rotateright(node<T>* p){
    // Rotate right code goes here
		node<T>*temp = p->right;
		p->right = temp->left;
		temp->left = p;
    return temp;
}

template <class T>
node<T>* BST<T> :: balance(node<T>* p){
	// Entered balance for p->key"<<p->key<<endl;
	// Entered balance  
	int bf = balanceFactor(p);
	// Calculated bfactor"<<bf<<endl;
	if(bf>1)//meaning heavy on the left side
	{
		if(balanceFactor(p->left)>0)
		{
			// Enter rotate left  
			p = rotateleft(p);
		}
		else
		{
			// Enter lr rotate  
            //first do the left rotate and then will do the right rotate
	        node<T>*temp = p->left;
        	p->left = rotateright(temp);
	        p = rotateleft(p);
		}
	}
	else if(bf<-1)//heavy on the right side
		{
			if(balanceFactor(p->right)>0)//heavy on left side
			{
				// Enter rl rotate  
				node<T>*temp = p->right;
        	    p->right = rotateleft(temp);
	            p = rotateright(p);
			}
			else
			{
				// Enter right rotate  
				p = rotateright(p);
			}
		}
	    fixHeight(p);
		//Returning from balance
    return p;
    // Balancing code goes here. You might need to find balance factor and call appropriate rotations.
}
// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: insert(string value,T k){
    root = insertHelper(value,k,root);
		// Root"<<root<<endl;
}
// insertion helpe  r
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) { // note we need a helper because we need recursive calls
    // Insertion code goes here.
		//looking for the Null case first
		if(p==NULL)
		{
			p = new node<T>(k,value);
		}
		else if(k>p->key)
		{
			p->right = insertHelper(value,k,p->right);
		}
		else if(k<p->key)
		{
			p->left = insertHelper(value,k,p->left);
		}
    return balance(p);
    //return p;
}
template<class T>
node<T>* BST<T> :: search(T key){

		node<T>*result = search(root,key);
		if(!result)
		{
			//key not found
			return NULL;
		}
		else
		{
			return result;
		}
    // Search code goes here.
}
// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p){
    // This function finds the min node of the tree.
		if(p==NULL)
		{
			return NULL;
		}
		else if(p->left==NULL)
		{
			return p;
		}
		else
		{
			return findmin(p->left);
		}
}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) {
	node<T>*t;
	if(p!=NULL)
    {
        while(p->left->left!=NULL)
        {
            p = p->left;
        }
        if(p->left->right)
        {
            t = p->left;
            p->left = p->left->right;
            delete t;
        }
        else
        {
            t = t->left->left;
            delete t;
            t->left = NULL;
        }
    }
    return balance(p);
    // This function recursively finds the min node and deletes it.
}

template<class T>
void BST<T>::delete_node(T k){
    root = remove(root, k);
}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{
	node<T>*t;
	if(p==NULL)
	{
		//first conditional;
		return NULL;
	}
	else if(k>p->key)
	{
		//2nd condition
		p->right = remove(p->right,k);

	}
	else if(k<p->key)
	{
	    p->left = remove(p->left,k);
			//3rd condition
	}
	else if(p->right&&p->left)
	{
		//4th condition
		t = findmin(p->right);
		p->key = t->key;
		p->value = t->value;
		p->right = remove(p->right,p->key);
//		p->right = removemin(p->right);
        //removemin(p->right);
	}
	else
	{
		//5th condition
		t = p;
		if(p->right==NULL)
		{
			p = p->left;
		}
		else if(p->left==NULL)
		{
			p = p->right;
		}
		delete t;
	}
	if(p)
    {
        return balance(p);
    }
    else
    {
        return NULL;
    }

    // This function uses findmin and deletemin to delete arbitrary node in the tree.
}
template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}
template<class T>
//extra functions to help in search and de-allocation of memory
node<T>*BST<T>::search(node<T>*p,T key)
{
    if(!p)
    {
        return NULL;
    }
	else if(p->key==key)
	{
		return p;
	}
	else if(key>p->key)
	{
		return search(p->right,key);
	}
	else if(key<p->key)
	{
		return search(p->left,key);
	}

}
template<class T>
void BST<T>::clear(node<T>*p)
{
	if(p!=NULL)
	{
		clear(p->left);
		clear(p->right);
		delete p;
	}
}
#endif
