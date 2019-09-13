//Encodes and decodes based on size 4 WalshCode
//Encoded values are between 0 and 7
#include "WalshCode.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <string.h>

using namespace std;

WalshCode::WalshCode()
{
	_H = { {-1,-1,-1,-1},
	       {-1,1,-1,1},
	       {-1,-1,1,1},
	       {-1,1,1,-1} };

}
vector<int> WalshCode::reverseVector(vector<int> vect)
{
	unsigned int lf = 0, rt = vect.size() - 1, tmp;
	while (lf < rt)
	{
		tmp = vect[lf];
		vect[lf] = vect[rt];
		vect[rt] = tmp;
		lf++; rt--;
	}
	return vect;
}
//sets 1 to 1, 0 to -1
vector<int> WalshCode::toBinary(int n)
{
	vector<int> bin;
	if (n == 0)
		bin.push_back(-1);
		
	//make sure val is represented by 3 bits
	while (n != 0)
	{
		if (n % 2 == 0) 
			bin.push_back(-1);
		else 
			bin.push_back(1);
		n /= 2;
	}
	while (bin.size() < 3)
		bin.push_back(-1);

	//reverse the order;
	return reverseVector(bin);
}

int WalshCode::toInteger(vector<int> binary)
{
	double sum = 0;
	vector<int> newVect = reverseVector(binary);
	for (unsigned int i = 0; i < newVect.size(); i++)
	{
		if(newVect[i]==1)
			sum += pow(2, (double)i);
	}
	return (int)sum;
}

vector<int> WalshCode:: getCode(int child)
{
	return _H[child];
}
//creates a new signal
vector<int> WalshCode::encode(int val, int child)
{
	vector<int> signal;
	vector<int> code = getCode(child);
	vector<int> binVal = toBinary(val);
	for (unsigned int i = 0; i < binVal.size(); i++)
	{
		for (unsigned int j = 0; j < code.size(); j++)
			signal.push_back(code[j] * binVal[i]);
	}
	return signal;
}
//Further encrypts an existing signal
vector<int> WalshCode::encode(int val, int child, vector<int> signal)
{
	vector<int> newSignal = encode(val, child);
	for (unsigned int i = 0; i < signal.size(); i++)
		signal[i] += newSignal[i];
	return signal;
}
int WalshCode::decode(vector<int> signal, vector<int> code)
{
	int codeSize = static_cast<int>(code.size());
	int index = -1;
	vector<int> binary;
	for (unsigned int i = 0; i < signal.size(); i++)
	{
		signal[i] *= code[i%codeSize];
		if (i%codeSize == 0)
		{
			binary.push_back(signal[i]);
			index++;
		}
		else
			binary[index] += signal[i];
	}
	for (unsigned int j = 0; j < binary.size(); j++)
		binary[j] /= codeSize;

	return toInteger(binary);
}
void WalshCode::print(vector<int> code)
{
	for (unsigned int i = 0; i < code.size(); i++)
	{
		cout << code[i];
		if (i == code.size()-1)
			cout << endl;
		else
			cout << " ";
	}
}
string WalshCode::toString(vector<int> code)
{
	string s = "";
        for (unsigned int i = 0; i < code.size(); i++)
	{
		s += to_string(code[i]);
		if (i == code.size()-1)
			s += "\n";
		else
			s += " ";
	}
	return s;
}
vector<int> WalshCode::toVect(string s)
{
	char arr[s.length()];
	strncpy(arr, s.c_str(), sizeof(arr));
	vector<int> v;
	char *endptr, *token; 
	token = strtok(arr, " ");
	while(token != NULL)
	{
		v.push_back(strtol(token, &endptr, 10));
		token = strtok(NULL, " ");
	}
	return v;
}
