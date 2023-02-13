#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int n;
	cin >> n;
	do
	{
		if (n==-1)
		{
			cout << "bye";
			break;
		}
		
		if (n>0 && n%5==0)
			cout << n/5 << endl;
		else cout << -1 << endl;
		cin >> n;
		
		if (n==-1)
		{
			cout << "bye";
			break;
		}
	}
	while(n!=-1);
}
