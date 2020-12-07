#include<bits/stdc++.h>
using namespace std;
bool a[240+5][240+5];

void ex(int x,int y,int s,int t)
{
	for(int j=x;j<=s;j++)
		for(int k=y;k<=t;k++)
			a[j][k]=1;
}

int main()
{
	int m,n,c,x,y,s,t,count=0;
	memset(a,0,sizeof(a));
	cin>>m>>n;
	cin>>c;
	for(int i=0;i<c;i++)
	{
		cin>>x>>y>>s>>t;
		ex(x,y,s,t);	 
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(a[i][j])
				count++;
		}
	}			
	cout<<count<<endl;
	return 0;		
}
