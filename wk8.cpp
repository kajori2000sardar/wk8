//include library
#include<iostream>

using namespace std;

//create class for Node
class Node
{
      public:
	//initialization
	int data;
	Node *lft;
	Node *rgt;
	Node *prt;
	//create constructor
	Node(int val)
	{
		data=val;
		lft=NULL;
		rgt=NULL;
		prt=NULL;
	}
};

//create class for binary searching tree
class BST
{
      public:
	Node *root;
	int count=0;

	//creating constructor
	BST()
	{
		root=NULL;
	}

	//creating function to help in insertion of values in tree
	void inserthpr(int val)
	{
		//if root is null then create a new node as root
		if(root==NULL)
		{
			root=new Node(val);
			count++;
			return;
		}

		insert(root,val);
		count++;
	}

	//creating function to insert value
	void insert(Node *cur,int val)
	{
		//decide to go left or right
		if(val<cur->data)
		//have to go left
		{
			//if left side is null then create a new node and link it
			if(cur->lft==NULL)
			{
				cur->lft=new Node(val);
				cur->lft->prt=cur;
			}
			else
			//move left and insert value there
				insert(cur->lft,val);
		}
		else
		//have to go right									
		{
			//if right is null then create a new node and link it
			if(cur->rgt==NULL)
			{
				cur->rgt=new Node(val);
				cur->rgt->prt=cur;
			}
			else
			//move right and insert value there
				insert(cur->rgt,val);
		}
	}
}

	//creating function to help display
	void displayhpr()
	{
		display(root);
	}

	//creating function to display values of tree
	void display(Node *cur)
	{
		//case for empty tree
		if(cur==NULL)
			return;
		//print left
			display(cur->lft);
		//print data
			cout<<cur->data<<" , ";
		//print right
			display(cur->rgt);
	}

	//creating node to help search of tree
	Node *searchhpr(int val)
	{
		return search(root,val);
	}

	//creating node to search the tree
	Node *search(Node *cur,int val)
	{
		//if it's value or null return current
		if(cur==NULL||cur->data==val)
			return cur;
		else
		//search left or right
		//search left
			if(val<cur->data)
				return search(cur->lft,val);
		//search right
			else
				return search(cur->rgt,val);
	}

	//function to return count
	int count()
	{
		return count;
	}

	//create node to help find minimum value
	Node *minhpr(int val)
	{
		//search the required node
		Node *cur=searchhpr(val);

		//if the node is null, return null
		if(root==NULL||cur==NULL)
			return NULL;

		//else call function to find minimum node
		else
			 min(cur,val);
	}

	//create a node to find minimum
	Node *min(Node *cur,int val)
	{
		//if it is the first element, return the node
		if(cur->lft==NULL)
			return cur;
		//else call function on the left of the current node
		else
			min(cur->lft,val);
	}

	//create function to delete the given value
	void del(int val)
	{
		//search the node with required value as current node
		Node *cur=searchhpr(val);

		//if the node doesn't exists, show output that node doesn't exist
		if(cur==NULL)
			cout<<"This value doesn't exists in the tree"<<endl;
		else
		{
			count--;
			//if the parent has only one child
			if(cur->lft!=NULL&&cur->rgt==NULL||cur->lft==NULL&&cur->rgt!=NULL)
			{
				//if left child exists
				if(cur->lft!=NULL&&cur->rgt==NULL)
				{
					Node *temp=cur->lft;
					//if current is root
					if(cur==root)
						root=temp;
					else
					{
						//whether current is left or the right child
						if((cur->data)<(cur->prt->data))
							cur->prt->lft=temp;
						else
							cur->prt->rgt=temp;
					}
					temp->prt=cur->prt;
				}
				//if right child exists
				else
				{
					Node *temp=cur->rgt;
					//if current is root
					if(cur==root)
						root=temp;
					else
					{
						//whether current is left or right
						if((cur->data)<(cur->prt->data))
							cur->prt->lft=temp;
						else
							cur->prt->rgt=temp;
					}
					temp->prt=cur->prt;
				}
				//delete current
				delete cur;
			}
			//if the parent has two child
			if(cur->lft!=NULL&&cur->rgt!=NULL)
			{
				Node *temp=minhpr(cur->rgt->data);
				cur->data=temp->data;
				//removal of previous links
				if(temp->rgt!=NULL)
				{
					temp->prt->lft=temp->rgt;
					temp->rgt->prt=temp->prt;
				}
				else
				{
					temp->prt->lft=NULL;
				}
				//delete temp
				delete temp;
			}
			//if parent has no child
			if(cur->lft==NULL&&cur->rgt==NULL)
			{
				//if current is root
				if(cur==root)
					root=NULL;
				//removal of previous links
				if((cur->data)<(cur->prt->data))
					cur->prt->lft=NULL;
				else
					cur->prt->rgt=NULL;
				//delete current
				delete cur;
			}
		}
	}

	//create a function to help print all the nodes in the given range
	void rngphpr(int l,int h)
	{
		rngp(root,l,h);
	}

	//create a function to print all the nodes in the given range
	void rngp(Node *cur,int l,int h)
	{
		//base condition
		if(cur==NULL)
			return;

		//display left
		rngp(cur->lft,l,h);

		//display current if within range
		if((cur->data)>=l&&(cur->data)<=h)
			cout<<cur->data<<"'";

		//display right
		rngp(cur->rgt,l,h);
	}
		
	//create function to help count nodes within range
	int rngchpr(int l,int h)
	{
		return rngc(root,l,h);
	}

	//create function to count nodes within range
	int rngc(Node *cur,int l,int h)
	{
		//base case
		if(!cur)
			return 0;
		
		if(cur->data==h&&cur->data==l)	
			return 1;

		//if current node is in range, then include it in count and use recursion for laft and right
		if((cur->data)<=h&&(cur->data)>=l)
			return 1+rngc(cur->lft,l,h)+rngc(cur->rgt,l,h);
	
		//if current is smaller than low, then use recursion for right child
		else
			if((cur->data)<l)
				return rngc(cur->lft,l,h);
			//else use recursion for left child
			else
				return rngc(cur->lft,l,h);
	}

	//create function to help find height of tree
	int hthpr()
	{
		return ht(root);
	}		

	//create function to find height of tree
	int ht(Node *cur)
	{

	}		
};

//creating main
int main()
{
	//create object of the class
	BST b;

	//call for the working of the functions in the class
	b.inserthpr(4);	
	b.inserthpr(2);
	b.inserthpr(5);
	b.inserthpr(3);
	b.inserthpr(9);
	b.inserthpr(6);
	b.displayhpr();
	cout<<endl;
	Node *f=b.searchhpr(5);
	if(f!=NULL)
		cout<<f->data<<endl;
	else
		cout<<"Entered data is not there in the tree"<<endl;
	Node *m=b.minhpr(3);	
	cout<<"The required minimum is "<<m->data<<endl;
	b.displayhpr();
	b.del(9);
	b.displayhpr();
	//terminating main function

	return 0;
}

