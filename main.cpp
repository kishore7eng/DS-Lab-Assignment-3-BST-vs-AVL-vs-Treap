#include <iostream>
#include<fstream>
#include<string.h>
#include<time.h>
#include<cstdio>
#include <climits>
#include <cstdlib>
#include <stack>
#include <vector>
#include<bits/stdc++.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
static int n=250,k=1;
static int BSTComp,AVLComp,AVLBfComp,TreapComp,TreapPComp;
static int AVLRot,TreapRot ;
static int c=0,d=0,e=0;

	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
                                     /////////////////////////////////**********BST*********//////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
class BSTNode
{
    int data;
    BSTNode *left, *right;
public:
    BSTNode()
    {
    
    }
    BSTNode(int value)
    {
        data = value;
    left = right = NULL;
    }

    ~BSTNode(){
		delete left;
		delete right;
	}
	friend class BST;
};

class BST{
    BSTNode*root;
    public:
        BST()
        {
            root=NULL;
        }
    void BST_Insert(int);
	void BST_Delete(int);
	int Height(BSTNode* );
	int HeightBST();
	int BSTnodeHeight(BSTNode*);
	int countnodes(BSTNode*);
	double nodeHeight();
};


void BST ::BST_Insert(int value)
{
	BSTNode*temp=root;
	BSTNode*parent=NULL;
	
	if (temp==NULL)
    {
        // Insert the first BST, if root is NULL.
       
        temp=new BSTNode(value);
        root=temp;
		return ;
		
    }
  
	while(temp!=NULL)
   {
   	    parent=temp;
   	    BSTComp++;
       if (value > temp->data)
       {

			temp=temp->right;
       }
       else
       {
            temp=temp->left;
       }
    }

    BSTNode*n=new BSTNode(value);
    BSTComp++;
    if(parent->data>value)
    {
    	parent->left=n;
	}
	else
	{
		parent->right=n;
	}
    return ;
}


void BST:: BST_Delete( int key)
{
  	BSTNode* curr = root;
    BSTNode* prev = NULL;
    while (curr != NULL && curr->data != key)
	{
        prev = curr;
         BSTComp+=2;
        if (key < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if(curr==NULL)
    return;
 
    if (curr->left == NULL || curr->right == NULL)
	{
         BSTNode* newCurr;
        if (curr->left == NULL)
            newCurr = curr->right;
        else
            newCurr = curr->left;
        if (prev == NULL)
            return ;
        if (curr == prev->left)
            prev->left = newCurr;
        else
            prev->right = newCurr;
        free(curr);
    }
    else 
	{
        BSTNode* p = NULL;
        BSTNode* temp;
 
        //  inorder successor
        temp = curr->right;
        while (temp->left != NULL) {
            p = temp;
            temp = temp->left;
        }
 
        if (p != NULL)
            p->left = temp->right;

        else
            curr->right = temp->right;
 
        curr->data = temp->data;
        free(temp);
    }
    return ;
}

int BST:: Height(BSTNode* node)
{
    if (node == NULL)
        return 0;
    else
    {
        int lh = Height(node->left);
        int rh = Height(node->right);

        if (lh > rh)
            return(lh + 1);
        else 
		    return(rh + 1);
    }
}


int BST:: countnodes( BSTNode *root)
{
    if(root != NULL)
    {
        countnodes(root->left);
        c++;
        countnodes(root->right);
    }
    return c;
}


int BST::HeightBST()
{
	int h=Height(root);
	return h;
}
int BST::BSTnodeHeight(BSTNode* root)
{
	if (root == NULL)
        return 0;
 
    return BSTnodeHeight(root->left) +
           Height(root) +
           BSTnodeHeight(root->right);
    

	
}
double BST::nodeHeight()

{
	int x= BSTnodeHeight(root);
	int y=countnodes(root);
    double z=double(x)/double(y);
    
    return z;
}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
                                     /////////////////////////////////**********AVL*********//////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	
class AVL_Node
{
public:
   int key;
   int bf; // balance factor bf = height(LChild subtree) – height(RChild subtree)
   AVL_Node *LChild, *RChild;
   AVL_Node(){
    LChild=NULL;
    RChild=NULL;}
   AVL_Node(int k)
   {
       LChild=NULL;
       key=k;
       RChild=NULL;
       bf=0;
   }
   ~AVL_Node()
   {
       delete LChild;
       delete RChild;
   }
   friend class AVL_Tree;
};
class AVL_Tree
{
private:
    AVL_Node *h;
 void write_to_file(AVL_Node*, ofstream&);
public:
    AVL_Tree()
    {
        h=new AVL_Node(0);
    }
    AVL_Tree(const AVL_Tree &T);
    AVL_Tree &operator=(const AVL_Tree &T);
    void AVL_Insert(int k);
    void AVL_Delete(int k);
    int Height(AVL_Node*);
    int HeightAVL();
    int countnodes(AVL_Node*);
    int AVLnodeHeight(AVL_Node*);
	double nodeHeight();

    

    ~AVL_Tree(){delete h;}
};


void AVL_Tree::AVL_Insert(int k)
{
    AVL_Node *pbp=h;
    //pbp refers to parent of balance pointer that might affect the balancing property
    AVL_Node *iterate;
    iterate=h->RChild;
    //bp refers to balance pointer from which bf will be affected
    AVL_Node *bp=h->RChild;
    //pos refers to positon of the node to be inserted
    AVL_Node *pos,*random;
    AVL_Node *BST= new AVL_Node(k);

    if(iterate==NULL)
    {
        h->RChild=BST;
        return;
    }
    while(1)
    {
    	AVLComp++;
    	AVLBfComp++;
        if(k<iterate->key)
        {

            pos=iterate->LChild;
            if(pos==NULL)
            {
                iterate->LChild=BST;
                pos=iterate->LChild;

                break;
            }
            else
            {
                if(pos->bf!=0)
                {
                    pbp=iterate;
                    bp=pos;
                }
                iterate=pos;
            }
        }
        else if(k>iterate->key)
        {
            pos=iterate->RChild;
            if(pos==NULL)
            {
                iterate->RChild=BST;
                pos=iterate->RChild;
                break;
            }
            else
            {
            	AVLBfComp++;
                if(pos->bf!=0)
                {
                    pbp=iterate;
                    bp=pos;
                }
                iterate=pos;
            }
        }
        else
          return;
 

    }
    AVLComp++;
    AVLBfComp++;
    int b=k<bp->key?1:-1;
    AVLBfComp++;
    if(b==1)
    {
        random=bp->LChild;
        iterate=bp->LChild;
    }
    else
    {
        random=bp->RChild;
        iterate=bp->RChild;
    }
    while(iterate!=pos)
    {
    	AVLComp++;
    	AVLBfComp++;
        if(k<iterate->key)
        {
            iterate->bf=1;
            iterate=iterate->LChild;
        }
        else
        {
            iterate->bf=-1;
            iterate=iterate->RChild;
        }
    }
   AVLBfComp++;
    if(bp->bf==0)
    {
        bp->bf=b;
        return;
    }
    else if(bp->bf==-1*b)
    {
        bp->bf=0;
        return;
    }
    else
    {
    	AVLBfComp++;
    	//left left rotation
       if(random->bf==1 && b==1)
       {
       	   AVLRot++;
           iterate=random;
           bp->LChild=random->RChild;
           random->RChild=bp;
           random->bf=0;
           bp->bf=0;
       }
       //right right rotation
       else if(random->bf==-1 && b==-1)
       {
       	   AVLRot++;
           iterate=random;
           bp->RChild=random->LChild;
           random->LChild=bp;
           random->bf=0;
           bp->bf=0;
       }
       //right left rotation
       else if(random->bf==-1*b && b==1)
       {
       	   AVLRot+=2;
           iterate=random->RChild;
           random->RChild=iterate->LChild;
           iterate->LChild=random;
           bp->LChild=iterate->RChild;
           iterate->RChild=bp;
           AVLBfComp++;
           if(iterate->bf==0)
           {
               bp->bf=0;
               random->bf=0;
           }
           else if(iterate->bf==1)
           {
               bp->bf=-1;
               random->bf=0;
           }
           else
           {
               bp->bf=0;
               random->bf=1;
           }
           iterate->bf=0;
       }
       //left right rotation
       else if(random->bf==-1*b && b==-1)
       {
       	   AVLRot+=2;
           iterate=random->LChild;
           random->LChild=iterate->RChild;
           iterate->RChild=random;
           AVLBfComp++;
           bp->RChild=iterate->LChild;
           iterate->LChild=bp;
           if(iterate->bf==0)
           {
               bp->bf=0;
               random->bf=0;
           }
           else if(iterate->bf==1)
           {
               bp->bf=0;
               random->bf=-1;
           }
           else
           {
               bp->bf=1;
               random->bf=0;
           }
           iterate->bf=0;
       }

    }
    if(bp==pbp->RChild)
        pbp->RChild=iterate;
    else
        pbp->LChild=iterate;

}

void AVL_Tree::AVL_Delete(int x)
{
	AVL_Node *iterate = h->RChild; 
	AVL_Node *bp, *pbp, *random;
	stack<AVL_Node*> s;
	s.push(h); 
    int flag=0;
	if(iterate == NULL) 
	return;

	while(iterate)
	{
		AVLComp++;
		AVLBfComp++;
		if(x < iterate->key)
		{
			s.push(iterate);
			iterate = iterate->LChild;
		}
		else if(x > iterate->key)
		{
			s.push(iterate);
			iterate = iterate->RChild;
		}
		else
		{
			flag = 1;
			break;
		}
	}
	if(flag==0) 
		return;
	else
	{
		
		if(!iterate->LChild || !iterate->RChild)
		{
			AVL_Node *temp = iterate->LChild ? iterate->LChild : iterate->RChild;
			AVL_Node *parent = s.top();

			if(!temp)
			{
				temp = iterate;
				if(iterate == parent->LChild)
					parent->LChild = NULL;
				else 
				    parent->RChild = NULL;
				iterate = NULL;
			}
			else
			{
				iterate->key = temp->key;
				iterate->bf = temp->bf;
				iterate->LChild = temp->LChild;
				iterate->RChild = temp->RChild;
			}
			delete temp;
		}
		// Node to be deleted has two the children
		else
		{
			s.push(iterate);
			AVL_Node *InSuccessor = iterate->RChild; 
			while(InSuccessor->LChild)
			{
				s.push(InSuccessor);
			 	InSuccessor = InSuccessor->LChild;
			}
			iterate->key = InSuccessor->key;
			x = InSuccessor->key; 
			AVL_Node *temp = InSuccessor->LChild ? InSuccessor->LChild : InSuccessor->RChild;
			AVL_Node *parent = s.top();

			if(!temp)
			{
				temp = InSuccessor;
				if(InSuccessor == parent->LChild)
					parent->LChild = NULL;
				else
				    parent->RChild = NULL;
				InSuccessor = NULL;
			}
			else
			{
				InSuccessor->key = temp->key;
				InSuccessor->bf = temp->bf;
				InSuccessor->LChild = temp->LChild;
				InSuccessor->RChild = temp->RChild;
			}
			delete temp;
		}
	}


	while(s.top() != h)
	{
		bp= s.top();
		AVLComp++;
		AVLBfComp++;
		int a = x < bp->key ? 1 : -1;
		s.pop();
		pbp = s.top();
        AVLBfComp++;
		if(bp->bf == a)
		{
			
			bp->bf = 0;
			continue;
		}
		else if(bp->bf == 0)
		{
			bp->bf = -1*a;
			return;
		}
		else
		{
		    AVLBfComp++;
		    AVLBfComp++;
			if(bp->bf==1)
			random=bp->LChild;
			else
			random=bp->RChild;
		
			
			if(random->bf == -1*a)
			{
					//left left rotation
				if(a == 1)
				{
					AVLRot++;
					AVLBfComp++;
					iterate = random;
					bp->RChild = random->LChild;
					random->LChild = bp;
					bp->bf = 0;
					random->bf = 0;
				
				}
				//right right rotation
				else if(a == -1)
				{
					AVLRot++;
					AVLBfComp++;
					iterate = random;
					bp->LChild = random->RChild;
					random->RChild = bp;
					bp->bf = 0;
					random->bf = 0; 
					
				}
			}
			//single rotation
			else if(random->bf == 0)
			{
				if(a == 1)
				{
					AVLRot++;
				AVLBfComp++;
					iterate = random;
					bp->RChild = random->LChild;
					random->LChild = bp;
					random->bf = a;
					
				}
				else if(a == -1)
				{
					AVLRot++;
					AVLBfComp++;
					iterate = random;
					bp->LChild = random->RChild;
					random->RChild = bp;
					random->bf = a; 
				
				}
			}
			
			else if(random->bf == a)
			{
				//right left rotation
				if(a == 1)
				{
					AVLRot+=2;
					AVLBfComp++;
					iterate = random->LChild;
					random->LChild = iterate->RChild;
					iterate->RChild = random;
					bp->RChild = iterate->LChild;
					iterate->LChild = bp;
					AVLBfComp++;
				    if(iterate->bf==0)
                	{
                    	bp->bf=0;
                    	random->bf=0;
                	}
                	else if(iterate->bf==1)
                	{
                   		bp->bf=0;
                   		random->bf=-1;
                	}
                	else
               		{
                  		bp->bf=1;
                  		random->bf=0;
               		}
               	iterate->bf=0;
				}
				//left right rotation
				else if(a ==- 1)
				{
					AVLRot+=2;
					AVLBfComp++;
					iterate = random->RChild;
					random->RChild = iterate->LChild;
					iterate->LChild = random;
					bp->LChild = iterate->RChild;
					iterate->RChild = bp;
				    AVLBfComp++;
					if(iterate->bf==0)
             	    {
                		bp->bf=0;
                	    random->bf=0;
                	}
                	else if(iterate->bf==1)
                	{
                   		bp->bf=-1;
                   		random->bf=0;
                	}
                	else
                	{
                  		bp->bf=0;
                  		random->bf=1;
                	}

					iterate->bf = 0;
				}
			}
			AVLBfComp++;
			if(iterate->bf == 1 || iterate->bf == -1)
			{
				if(bp == pbp->RChild) 
					pbp->RChild = iterate;
				else 
					pbp->LChild = iterate;
				return;
			}
		}
		if(bp == pbp->RChild)
			pbp->RChild = iterate;
		else 
			pbp->LChild = iterate;		
	}

}

int AVL_Tree:: Height(AVL_Node* node)
{
    if (node == NULL)
        return 0;
    else
    {
        int lh = Height(node->LChild);
        int rh = Height(node->RChild);
        if (lh > rh)
            return(lh + 1);
        else 
		    return(rh + 1);
    }
}

int AVL_Tree::HeightAVL()
{
	int x=Height(h->RChild);
	return x;
}
	
int AVL_Tree:: countnodes( AVL_Node *root)
{
    if(root != NULL)
    {
        countnodes(root->LChild);
        d++;
        countnodes(root->RChild);
    }
    return d;
}

int AVL_Tree::AVLnodeHeight(AVL_Node* root)
{
	if (root == NULL)
        return 0;
 
    return AVLnodeHeight(root->LChild) +
           Height(root) +
           AVLnodeHeight(root->RChild);
    

	
}
double AVL_Tree::nodeHeight()

{
	int x= AVLnodeHeight(h->RChild);
	int y=countnodes(h->RChild);
    double z= double(x)/double(y);
    return z;
}

	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		                                 
									 /////////////////////////////////**********TREAPS*********//////////////////////
                                     
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	


class Treap_node
{
	int key;
	int priority;
	Treap_node *left;
	Treap_node *right;
public:
	Treap_node()
	{
	}
	Treap_node(int x)
	{
		key=x;
		priority=rand()%100000;
		left=right=NULL;
	}
	~Treap_node()
	{
		delete left;
		delete right;
	}
	friend class Treap;
};
class Treap
{
	Treap_node*root;
public:
	Treap()
	{
		root=NULL;
		
	}
	
	void Treap_Insert(int);
	void Treap_Delete(int);
	void Treap_InsHelp(Treap_node*&,int);
	void Treap_RotateLeft(Treap_node*&);
	void Treap_RotateRight(Treap_node*& root);
	void Treap_DelHelp(Treap_node*&,int);
	int Height(Treap_node*);
	int HeightTreap();
	int TreapnodeHeight(Treap_node*);
	int countnodes(Treap_node*);
	double nodeHeight();
};
void Treap:: Treap_RotateLeft(Treap_node*& root)
{
    Treap_node* R = root->right;
    Treap_node* X = root->right->left;
    R->left = root;
    root->right = X;
    root = R;
}

void Treap:: Treap_RotateRight(Treap_node*& root)
{
    Treap_node* L = root->left;
    Treap_node* Y = root->left->right;
    L->right = root;
    root->left = Y; 
    root = L;
}
 
void Treap:: Treap_InsHelp(Treap_node*&root,int x)
{
	if (root == NULL)
    {
        root = new Treap_node(x);
        return;
    }
    TreapComp++;
    TreapPComp++;
    if (x < root->key)
    {
        Treap_InsHelp(root->left, x);
        TreapPComp++;
        if (root->left != NULL && root->left->priority > root->priority) 
		{
			TreapRot++;
            Treap_RotateRight(root);
        }
    }
    else 
	{
        Treap_InsHelp(root->right, x);
        TreapPComp++;
        if (root->right != NULL && root->right->priority > root->priority) 
		{
			TreapRot++;
            Treap_RotateLeft(root);
        }
    }
	return ;
}

void Treap::Treap_Insert(int x)
{
	Treap_InsHelp(root,x);
	return ;
}
	

void Treap::Treap_DelHelp(Treap_node*&root,int x)
{
	TreapComp++;
	TreapPComp++;
	if (root == NULL)
      return;
   if (x < root->key)
      Treap_DelHelp(root->left, x);
   else if (x > root->key)
      Treap_DelHelp(root->right, x);
      
   else {
      if (root->left ==NULL && root->right == NULL) 
	  {
         delete root;
         root = NULL;
      }
      else if (root->left && root->right) 
	  {
	  TreapPComp++;
         if (root->left->priority < root->right->priority) 
		 {
		 	TreapRot++;
            Treap_RotateLeft(root);
            Treap_DelHelp(root->left, x);
         }
		else 
		 {
		 	TreapRot++;
            Treap_RotateRight(root);
            Treap_DelHelp(root->right, x);
         }
      }
      else {
         Treap_node* child = (root->left)? root->left: root->right;
         Treap_node* curr = root;
         root = child;
		 
	  }

   }
}
void Treap:: Treap_Delete(int x)
{
	Treap_DelHelp(root,x);
	return;
}
int Treap:: Height(Treap_node* node)
{
    if (node == NULL)
        return 0;
    else
    {
       
        int lh = Height(node->left);
        int rh = Height(node->right);
        if (lh > rh)
            return(lh + 1);
        else 
		    return(rh + 1);
    }
}

int Treap::HeightTreap()
{
	int x=Height(root);
	return x;
}
int Treap:: countnodes( Treap_node *root)
{
    if(root != NULL)
    {
        countnodes(root->left);
        e++;
        countnodes(root->right);
    }
    return e;
}


int Treap::TreapnodeHeight(Treap_node* root)
{
	if (root == NULL)
        return 0;
 
    return TreapnodeHeight(root->left) +
           Height(root) +
           TreapnodeHeight(root->right);
    

	
}
double Treap::nodeHeight()

{
	int x= TreapnodeHeight(root);
	int y=countnodes(root);
    double z=double(x)/double(y);
    return z;
}




	    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		///////////////////////////////////////////////////////////****DRIVER CODE****/////////////////////////////////////////////////////////////////////
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void generate_file(ofstream&fout)
{
	//n=100;
	vector<int> v;
	int flag=1,m=0;
	n*=k;
	k++;
	fout<<n<<"\n";
	for(int i=0;i<n;i++)
	{
		int ele=rand()%100000;
		int operation=1+rand()%3;
		if(operation%2==0)
		{
			if(flag==0)
			fout<<"Delete "<<v[m++]<<"\n";
			else
			fout<<"Delete "<<ele<<"\n";
		}
		else
		{
			fout<<"Insert "<<ele<<"\n";
			v.push_back(ele);
			flag=0;
		}
	}

	return;

}



int main(int argc, char** argv) {

	ofstream fout;
	ifstream fin;
	ifstream f;
	int l=0;
	char p[100];
	while(1){
	cout<<"\n\n";
	cout<<"Do you want to generate file and exectue or run with your own file \n";
	cout<<"1)If you need to generate file and do analysis\n";
	cout<<"2)If you have your own file for which analysis is to be done\n";
	cout<<"3)Choose 3 to exit\n";
	cout<<"Give your choice (1/2): ";
    int ch;
	cin>>ch;
	
	
	switch(ch)
	{
		case 1:for(int i=1;i<=5;i++)
				{
					
					char fname[50];
					sprintf(fname, "file%d.txt",i);
					fout.open(fname);
					generate_file(fout);
					fout.close();
					fin.open(fname);
					BST BSTobj;
					AVL_Tree AVLobj;
					Treap Treapobj;
					string op;
					int ele,n;
					c=0;
					d=0;
					e=0;
					TreapComp=0;
					TreapPComp=0;
					AVLComp=0;
					AVLBfComp=0;
					BSTComp=0;
					AVLRot=0;
					TreapRot=0;
					fin>>n;
					cout<<"----------------------------------------------------------------------------------------------------\n\n";
					cout<<"File generated conatining "<<n<<" operations\n";
					cout<<"Displaying parameters for file "<<i<<endl;
					cout<<endl;
					while(n!=0)
					{
						fin>>op;
						fin>>ele;
						n--;
						if(op=="Insert")
						{
							BSTobj.BST_Insert(ele);
							AVLobj.AVL_Insert(ele);
							Treapobj.Treap_Insert(ele);
						}
						else
						{
							BSTobj.BST_Delete(ele);
							AVLobj.AVL_Delete(ele);
							Treapobj.Treap_Delete(ele);	
						}
						
					}	
					
					cout<<"Average height of Nodes \n\n";
					cout<<"BST: ";
					cout<<BSTobj.nodeHeight()<<"\n";
					cout<<"AVL: ";
				    cout<<AVLobj.nodeHeight()<<"\n";
					cout<<"Treaps: ";
					cout<<Treapobj.nodeHeight()<<"\n";
					cout<<"\nHeight of the tree\n\n";
					cout<<"BST Height: "<<BSTobj.HeightBST()<<"\n";
					cout<<"AVL Height: "<<AVLobj.HeightAVL()<<"\n";
					cout<<"Treaps Height: "<<Treapobj.HeightTreap()<<endl;
					cout<<"\nComparisions\n \n";	
					cout<<"BST Comparisions: "<<BSTComp<<endl;
					cout<<"AVL Comparisions: "<<AVLComp<<endl;
					cout<<"AVL Comparisions including Balance Factor comparisions: "<<AVLBfComp<<endl;
					cout<<"Treap Comparisions: "<<TreapComp<<endl;
					cout<<"Treap Comparisions including Priority Comparisions: "<<TreapPComp<<endl;
					cout<<"\nRotations \n\n";
					cout<<"AVL Rotations: "<<AVLRot<<endl;
					cout<<"Treap Rotations: "<<TreapRot<<endl;
					cout<<endl;
					cout<<"----------------------------------------------------------------------------------------------------\n";
					fin.close();
				}
				k=250;
				n=1;
				break;
				
		case 2: cout<<"Enter the number of files: ";
		        cin>>l;
		        for(int i=0;i<l;i++)
				{
		            cout<<"Enter the name of the file: "<<i+1<<"\t";
		            cin>>p;
		            f.open(p);
					BST BSTobj;
					AVL_Tree AVLobj;
					Treap Treapobj;
					string op;
					int ele,n;
					c=0;
					d=0;
					e=0;
					TreapComp=0;
					TreapPComp=0;
					AVLComp=0;
					AVLBfComp=0;
					BSTComp=0;
					AVLRot=0;
					TreapRot=0;
					
					f>>n;
					cout<<"----------------------------------------------------------------------------------------------------\n\n";
					cout<<"File opened containing "<<n<<" operations\n";
					cout<<"Displaying parameters for file "<<i+1<<endl;
					cout<<endl;
					while(n!=0)
					{
						f>>op;
						f>>ele;
						n--;
						if(op=="Insert")
						{
							BSTobj.BST_Insert(ele);
							AVLobj.AVL_Insert(ele);
							Treapobj.Treap_Insert(ele);
						}
						else
						{
							BSTobj.BST_Delete(ele);
							AVLobj.AVL_Delete(ele);
							Treapobj.Treap_Delete(ele);	
						}
						
					}	
					
					cout<<"Average height of Nodes \n\n";
					cout<<"BST: ";
					cout<<BSTobj.nodeHeight()<<"\n";
					cout<<"AVL: ";
				    cout<<AVLobj.nodeHeight()<<"\n";
					cout<<"Treaps: ";
					cout<<Treapobj.nodeHeight()<<"\n";
					cout<<"\nHeight of the tree\n\n";
					cout<<"BST Height: "<<BSTobj.HeightBST()<<"\n";
					cout<<"AVL Height: "<<AVLobj.HeightAVL()<<"\n";
					cout<<"Treaps Height: "<<Treapobj.HeightTreap()<<endl;
					cout<<"\nComparisions \n\n";	
					cout<<"BST Comparisions: "<<BSTComp<<endl;
					cout<<"AVL Comparisions: "<<AVLComp<<endl;
					cout<<"AVL Comparisions including Balance Factor comparisions: "<<AVLBfComp<<endl;
					cout<<"Treap Comparisions: "<<TreapComp<<endl;
					cout<<"Treap Comparisions including Priority Comparisions: "<<TreapPComp<<endl;
					cout<<"\nRotations \n\n";
					cout<<"AVL Rotations: "<<AVLRot<<endl;
					cout<<"Treap Rotations: "<<TreapRot<<endl;
					cout<<endl;
					cout<<"----------------------------------------------------------------------------------------------------\n";
					

					f.close();
		            
		   		} 
		   		break;
	
		case 3: exit(0);
	}
}
	system("PAUSE");
	return 0;
}
