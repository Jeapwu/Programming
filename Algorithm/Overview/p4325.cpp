#include<iostream>
#include<cstring>
using namespace std;
bool a[42];
int main()
{
    int sum=0,x; 
	memset(a,0,sizeof(a));
    for(int i=0;i<10;i++)
    {
    	cin>>x;
    	a[x%42]=1;
	}     
    for(int i=0;i<42;i++)
        if(a[i])
			sum++;
    cout<<sum<<endl;
    return 0;
}
