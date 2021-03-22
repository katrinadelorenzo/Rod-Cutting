/* Practice cut rod problem & dynamic programming 
 * By: X. Zhang
 * 4/16/2018
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int CutRodHelper (vector<int> p, int n, int r[]);

// Recursive solution: declare the CutRod function
/* return the max. revenue
 */
int CutRod (vector<int> p, int n)
{
   if (n==0) //base case
	   return 0;

   //general case 
   int curMax; //current max. revenue
   curMax = 0; 

   //explore all possible ways to make first
   //cut (i=1...n), and recursive evaluate smaller prob
   // Cut_Rod (n-i)
   int maxRodLength = p.size()-1;
   maxRodLength = min (n, maxRodLength);

   for (int i=1;i<=maxRodLength;i++)
	   curMax = max (curMax, p[i]+ CutRod(p,n-i));

   return curMax;
}


// 2. Recursive with Meomoization:
// declare the MemoizedCutRod function
/* return the max. revenue
 */
int MemoizedCutRod (vector<int> p, int n)
{
	int r[n+1];
	for (int i=0;i<=n;i++)
		r[i]=-1;

	return CutRodHelper (p, n, r);
}

//The recursive helper function called by MemoizedCutRod
int CutRodHelper (vector<int> p, int n, int r[])
{
   if (r[n]>=0)
	return r[n];

   //base case
   if (n==0)
	   return 0;
   int curMax; //current max. revenue
   curMax = 0; 

   //explore all possible ways to make first
   //cut , and recursive evaluate smaller prob 
   int maxRodLength = p.size()-1;
   maxRodLength = min (n, maxRodLength);

   for (int i=1;i<=maxRodLength;i++)
	   curMax = max (curMax, p[i]+CutRodHelper(p,n-i,r));

   r[n] = curMax;
   return curMax;
}


/* 3 Bottom up implementation of Dynamic Programming
 */
int CutRodBottomUp (vector<int> p, int n)
{
   int r[n+1];

   r[0]= 0; 

   for (int i=1; i<=n;i++){
	//calculate max profit for rod length i 
   	int curMax; //current max. revenue
   	curMax = 0; 

   	//explore all possible ways to make first
   	//cut , and recursive evaluate smaller prob 
   	int maxRodLength = p.size()-1;
   	maxRodLength = min (i, maxRodLength);

   	for (int c1=1;c1<=maxRodLength;c1++)
	{
	   	curMax = max (curMax, p[c1]+r[i-c1]);
	}

   	r[i] = curMax;
   }
   //finsih evaluating r1, r2, ..., rn
   return r[n];
}

int main()
{
   vector<int> p {0,1,5,8,9,10,17,17,20,24,30}; 
  	 //p[i] is the price for rod of  length i 
	 //the max. rod length is p.size()-1

    int n,r;
    char ans;
    
    do
    {
	cout <<"Enter the rod length:";
	cin >> n;

	//call your function to find max. revenue 
	//display the result
	r = CutRod (p, n);
	cout <<"Maxi. revenue:"<<r<<endl;

	r = MemoizedCutRod (p,n);
	cout <<"Memoized Maxi. revenue:"<<r<<endl;

	r = CutRodBottomUp (p, n);
	cout <<"Bottom up solution:"<<r<<endl;
	
	//continue?
	cout <<"Continue(y/n)?";
	cin >> ans;
    } while (ans=='y');
}

