#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


struct BST
{
    // Data reprezinta valoarea din retinuta in nod. Din ea avem pointeri ce arata in stanga sau dreapta catre alte noduri. In stanga mai se arata catre valori mai mici, iar in dreapta valori mai mari.
    long long int data;
    BST *left, *right;
    int leftCount;

};

int verificatorPred=0;
int verificatorSuc=0;
int verificator=0;

// Default Constructor definitie.
BST* newBST(long long int data) {
    BST* node=new BST();
    node->data=data;
    node->left=NULL;
    node->right=NULL;
    node->leftCount=0;

    return node;
}

// Functia Insert definitie.
BST* Insert(BST* root, long long int value)
{
    if (!root)
    {
        // Daca nu avem nod, introducem un nou nod.
        return newBST(value);
    }
    // Comparam valorea dorita cu nodul
    // Insert data.
    if (value > root->data)
    {
        // Insert right node data, if the 'value'
        // to be inserted is greater than 'root' node data.
        // Daca este mai mare, coboram valorea de introdus spre dreapta

        // Process right nodes.
        root->right = Insert(root->right, value);
    }
    else
    {
        // Insert left node data, if the 'value'
        // to be inserted is greater than 'root' node data.
        // Daca este mai mica, coboram valorea de introdus spre stanga

        // Process left nodes.
        root->left = Insert(root->left, value);
        root->leftCount++;
    }

    // Return 'root' node, after insertion.
    return root;
}

// Inorder traversal function. Ordonarea elementelor crescator
// This gives data in sorted order.
void Inorder(BST* root)
{
    if (!root) {
        return;
    }
    Inorder(root->left);
    cout << root->data << endl;
    Inorder(root->right);
}

long long minim(BST* root)
{
  // Coboram la stanga pana cand ajungem la final
  if(root->left!=NULL)
    minim(root->left);
  else
    return root->data;
}

long long maxim(BST* root)
{
  // Coboram de dreapta pana cand ajungem la final
  if(root->right!=NULL)
    maxim(root->right);
  else
    return root->data;
}

int isIn(BST* root, long long int num)
{
    // Verificam daca num este egal cu valoarea nodului
    if(num == root->data)
    return 1;

    // Verificam daca se poate cobora la stanga sau la dreapta si daca se poate efectuam coborarea
    else if(num < root->data and root->left!= NULL)
    return isIn(root->left, num);

    else if(num > root->data and root->right!= NULL)
    return isIn(root->right, num);

    // Daca nu se gaseste valorea, aceasta nu exista si intoarcem 0.
    return 0;

}

//int BST:: succesor(BST* root, )

BST* stergeElem(BST* root, long long int k)
{
    verificator=1;
    // Cazul de baza
    if (root == NULL)
        return root;

    // Apelam recursiv stramosi nodului de sters.
    if (root->data > k) {
        root->left = stergeElem(root->left, k);
        return root;
    }
    else if (root->data < k) {
        root->right = stergeElem(root->right, k);
        return root;
    }

    // Cautam nodul si in functie de el avem 2 cazuri diferite.

    //Daca nodul are 1 copil
    if (root->left == NULL) {
        BST* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL) {
        BST* temp = root->left;
        delete root;
        return temp;
    }

    // Daca nodul are 2 copii
    else {

        BST* succParent = root;

        // Gasim succesorul
        BST* succ = root->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        root->data = succ->data;

        delete succ;
        return root;
    }
}

void predecessor1(BST* root, BST*& pre, long long int key) {
    verificatorPred=0;
	if(root==NULL)
    {return;}
    if(root->data==key)
    {
        verificatorPred=1;
        if(root->left!=NULL) {
            BST* tmp=root->left;
            while(tmp->right){
                tmp=tmp->right;
            }
            pre=tmp;
        }
        return;
    }
    if(root->data>key) {
        predecessor1(root->left, pre, key);
    }
    else {
        pre=root;
        predecessor1(root->right, pre, key);
    }
}

void predecessor(BST* root, long long key) {
    BST *pre;
    predecessor1(root, pre, key);
    if(pre&&verificatorPred==1)
        cout<<"predecesorul lui "<<key<<" este "<<pre->data<<endl;
    else
        cout<<key<<" nu are predecesor\n";
    verificatorPred=0;
}

void succesor1(BST* root, BST*& suc, long long int key) {
    verificatorSuc=0;
    if(root==NULL) return;
    if(root->data==key) {
        verificatorSuc=1;
        if(root->right!=NULL) {
            BST* tmp=root->right;
            while(tmp->left)
                tmp=tmp->left;
            suc=tmp;
        }
        return;
    }
    if(root->data>key) {
        suc=root;
        succesor1(root->left, suc, key);
    }
    else {
        succesor1(root->right, suc, key);
    }
}

void succesor(BST* root, long long key) {
    BST *suc;
    succesor1(root, suc, key);
    if(suc&&verificatorSuc==1)
        cout<<"succesorul lui "<<key<<" este "<<suc->data<<endl;
    else
        cout<<key<<" nu are succesor\n";
    verificatorSuc=0;
}

BST* elementKaugumentat(BST* root, int k) {
  if(verificator==1) {
    cout<<"nu putem apela elementKaugumentat";
    return root;
  }
  else{
  if(root==NULL)
    return NULL;
  int count=root->leftCount+1;

  if(count==k)
    return root;
  if(count>k)
    return elementKaugumentat(root->left, k);
  else
    return elementKaugumentat(root->right, k-count);
  }
}

BST* elementK(BST* root, int& k)
{
    // base case
    if (root == NULL)
        return NULL;

    // search in left subtree
    BST* left = elementK(root->left, k);

    // if k'th smallest is found in left subtree, return it
    if (left != NULL)
        return left;

    // if current element is k'th smallest, return it
    k--;
    if (k == 0)
        return root;

    // else search in right subtree
    return elementK(root->right, k);
}

int numberOfElements(BST *root) {
    if (root) {
        return 1 + numberOfElements(root->left) + numberOfElements(root->right);
    } else {
        return 0;
    }
}


// Driver code
int main()
{

	BST b, *root=NULL;
    cout << "PreOrder Traversal of constructed BST \n";

	ifstream f("balanced2.txt");
    long long int x;
    x=x;
    f>>x;
    root = Insert(root, x);
    while(f>>x)
    {
        Insert(root, x);
    }
    f.close();

    long long int mini=minim(root);
    stergeElem(root, 200);
    cout<<mini<<endl;
    cout<<maxim(root)<<endl;
    succesor(root, mini);
    predecessor(root, 100000);
    int k=3;
    cout<<elementK(root, k)->data<<endl;
    cout<<numberOfElements(root)<<endl;
    cout<<isIn(root, mini);

  return 0;
}
