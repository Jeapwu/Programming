#include<iostream>
using namespace std;
int main()
{
    long long sum=1,i,x,n;
    cin>>x>>n;
    for(i=1;i<=n;i++)
        sum=sum+sum*x;
    cout<<sum;
    return 0;
}
