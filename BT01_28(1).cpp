#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int d;
	cout << 12 << " midnight\n";
	for (int i=1; i<24; i++)
	{
		if (1<=i && i<=11)
		{
			cout << i << " am\n";
			d=1;
		}
		else
		{
			if (i==12)
			{
				cout << 12 << " noon\n";
				d=0;	
			}
			else
			cout << i-12 << " pm\n";
		}
	}
}
