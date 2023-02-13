#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int a[5];
	int sum=0;
	for (int i=0; i<5; i++)
	{
		cin >> a[i];
		sum=sum+a[i];
	}
	double mean=double(sum)/5;
	double b[5];
	for (int i=0; i<5; i++)
	{
		b[i]=abs(double(a[i])-mean);
	}
	double min = b[0];
	int k=0;
	for (int i=0; i<5; i++)
	{
		if (b[i]<min)
		{
			min = b[i];
			k=i;
		}
	}
	cout << a[k];
}
