#ifndef WALSHCODE_H
#define WALSHCODE_H
#include <vector>
#include <string>

using namespace std;

class WalshCode
{
public:
	WalshCode();
	vector<int> reverseVector(vector<int> vect);
	vector<int> toBinary(int n);
	int toInteger(vector<int> binary);
	vector<int> getCode(int child);
	vector<int> encode(int val, int child);
	vector<int> encode(int val, int child, vector<int> signal);
	int decode(vector<int> signal, vector<int> code);
	void print(vector<int> code);
	string toString(vector<int> code);
	vector<int> toVect(string s);
private:
	vector<vector<int> > _H;
};

#endif
