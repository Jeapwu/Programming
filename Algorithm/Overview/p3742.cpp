//#include<bits/stdc++.h>
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string x,z;
	int n;
	cin>>n;
	cin>>x>>z;
	for(int i=0;i<n;i++)
		if(x[i]<z[i])
		{
			cout<<"-1"<<endl;
			return 0;
		}
	cout<<z<<endl;
	return 0;		
}
