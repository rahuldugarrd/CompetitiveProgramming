#include <bits/stdc++.h>
#define IO ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define endl '\n'
typedef long long ll;
using namespace std;
int a[65536];
vector<int> ho[16],preho[16];
int main()
{
	IO;
	int n;
	cin>>n;
	int z=0;
	while(n!=-1)
	{
		z++;
		int te;
		for(int i=0; i<n; i++) {
			cin>>te;
			a[te]++;
		}
		for(int i=0; i<16; i++)
		{
			ho[i].clear();
			ho[i].resize((1<<i)*2);
			preho[i].clear();
			preho[i].resize((1<<i)*2);
		}
		for(int i=0; i<(1<<16); i++)
		{
			for(int j=0; j<16; j++)
				ho[j][i&((1<<(j+1))-1)]+=a[i];
			a[i]=0;
		}
		for(int j=0; j<16; j++)
		{
			preho[j][0]=ho[j][0];
			for(int i=1; i<(1<<(j+1)); i++)
				preho[j][i]=ho[j][i]+preho[j][i-1];
		}
		char tem;
		int c;
		int counter=0;
		ll ans=0;
		cin>>tem;
		while(tem!='E')
		{
			cin>>c;
			if(tem=='C')
				counter=(counter-c+(1<<16))&((1<<16)-1);
			else
			{
				int te=((1<<(c+1))-1+counter)&((1<<(1+c))-1);
				if(te>=(1<<c))
					ans+=preho[c][te]-preho[c][te-(1<<c)];
				else
					ans+=preho[c][te]+preho[c][(1<<(c+1))-1]-preho[c][te+(1<<c)];
			}
			cin>>tem;
		}
		cout<<"Case "<<z<<": "<<ans<<endl;
		cin>>n;
	}
}
