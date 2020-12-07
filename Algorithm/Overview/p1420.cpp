#include<iostream>
using namespace std;
int a[10000+5];
int main()
{
    int n,sum=1,max=1;
    bool flag=0;
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>a[i];
    for(int i=0;i<n;i++)
        if(a[i+1]==a[i]+1)
        {
			sum++;
			if(max<sum)
				max=sum;
		}
		else
			sum=1;
    cout<<max<<endl;
    return 0;
}
