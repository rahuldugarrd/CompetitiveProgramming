#include <bits/stdc++.h>
#define IO ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define endl '\n'
using namespace std;
struct node
{
	int size;
	node *left,*right;
};
node* arr[500001];
int cursize;
void init(node *a,int level)
{
	if(level>=0)
	{
		a->left=new node();
		a->right=new node();
		init(a->left,level-1);
		init(a->right,level-1);
	}
}
void add(int num)
{
	cursize++;
	arr[cursize]=new node();
	node* ne=arr[cursize];
	node* ol=arr[cursize-1];
	ne->size=ol->size+1;
	for(int i=18; i>=0; i--,ne->size=ol->size+1)
		if((num&(1<<i))!=0)
		{
			ne->left=ol->left;
			ne->right=new node();
			ne=ne->right;
			ol=ol->right;
		}
		else
		{
			ne->right=ol->right;
			ne->left=new node();
			ne=ne->left;
			ol=ol->left;
		}
}
int xormaxquery(int l, int r, int y)
{
	node* sm=arr[l-1];
	node* la=arr[r];
	int val=0;
	for(int i=18; i>=0; i--)
	{
		if(y&(1<<i))
			if((la->left->size)-(sm->left->size)>0)
			{
				la=la->left;
				sm=sm->left;
			}
			else
			{
				la=la->right;
				sm=sm->right;
				val|=1<<i;
			}
		else
			if((la->right->size)-(sm->right->size)>0)
			{
				val|=1<<i;
				la=la->right;
				sm=sm->right;
			}
			else
			{
				la=la->left;
				sm=sm->left;
			}
	}
	return val;
}
int kthquery(int l, int r, int k)
{
	node *sm=arr[l-1];
	node *la=arr[r];
	int val=0;
	for(int i=18; i>=0; i--)
		if(sm->left->size+k<=la->left->size)
		{
			sm=sm->left;
			la=la->left;
		}
		else
		{
			k-=la->left->size-sm->left->size;
			val|=1<<i;
			sm=sm->right;
			la=la->right;
		}
	return val;
}
int lessthanx(int l, int r, int x)
{
	int val=r-l+1;
	node *sm=arr[l-1],*la=arr[r];
	for(int i=18; i>=0; i--)
		if(!(x&(1<<i)))
		{
			val-=la->right->size-sm->right->size;
			la=la->left;
			sm=sm->left;
		}
		else
		{
			la=la->right;
			sm=sm->right;
		}
	return val;
}
int ni()
{
	int te;
	cin>>te;
	return te;
}
int main()
{
	IO;
	int n;
	cin>>n;
	arr[0]=new node();
	init(arr[0],18);
	while(n-->0)
	{
		int te;
		cin>>te;
		int te1,te2,te3;
		if(te==0)
		{
			cin>>te1;
			add(te1);
		}
		else if(te==1)
		{
			cin>>te1>>te2>>te3;
			cout<<xormaxquery(te1,te2,te3)<<endl;
		}
		else if(te==2)
		{
			cin>>te1;
			cursize-=te1;
		}
		else if(te==3)
		{
			cin>>te1>>te2>>te3;
			cout<<lessthanx(te1,te2,te3)<<endl;
		}
		else
		{
			cin>>te1>>te2>>te3;
			cout<<kthquery(te1,te2,te3)<<endl;
		}
	}
}
