#include <list>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

const int table_size = 250;

int hash_func(string str)
{
	int h = 0;
	for (int i = 0; i < str.length(); i++)
	{
		h += (int)(str[i]) / (i + 1);
	}
	return h;
}

string* split(string str, int index)
{
	assert(index >= 0 && index < str.length());
	string* res = new string[2];
	int i = 0;
	while (i < str.length())
	{
		if (i < index)
		{
			res[0] += str[i];
		}
		if (i > index)
		{
			res[1] += str[i];
		}
		i++;
	}
	return res;
}

string uploadBufferFromFile(const char* path)
{
#pragma warning(disable : 4996)
	FILE* f = fopen(path, "r");
	fseek(f, 0, SEEK_END);
	int len = ftell(f);
	rewind(f);
	char* cbuffer = new char[len];
	size_t p = fread(cbuffer, 1, len, f);
	fclose(f);
	string buffer = split(string(cbuffer), p)[0];
	delete[] cbuffer;
	return buffer;
}

size_t split(const std::string& txt, std::vector<std::string>& strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}


int main()
{
	vector<list<string>> table(table_size);
	vector<string> words;
	string text = uploadBufferFromFile("D:\\Проги\\hamlet.txt");
	split(text, words, ' ');
	//cout << text << "   " << words[0];
	for (int i = 0; i < words.size(); i++)
		table[hash_func(words[i]) % table_size].push_front(words[i]);
	for (int i = 0; i < table_size; i++)
		cout << i + 1 << " " << table[i].size() << endl;
	return 0;
}

