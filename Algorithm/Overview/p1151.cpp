#include<iostream>
using namespace std;
int main()
{
    int k,s1,s2,s3;
    bool flag=0;
    cin>>k;
    if(k>0&&k<1000)
    {
    	for(int i=10000;i<=30000;i++)
    	{
	    	s1=i/100;
	    	s2=(i/10)%1000;
	    	s3=i%1000;
	    	if(s1%k==0&&s2%k==0&&s3%k==0)
	    	{
	    		flag=1;
				cout<<i<<endl;
			}		
		}	
	}
	if(!flag)
		cout<<"No"<<endl;
    return 0;
}
