#ifndef _WORDS_LAYER_H_
#define _WORDS_LAYER_H_

#include<fstream>
#include<iostream>
#include<string>
#include<deque>

#include<cstdlib>
#include<ctime>


class WordsLayer
{
public:
	WordsLayer(std::string fileName);
	~WordsLayer();
	std::string getRandomWordsLine();
	int getLinesCount();
private:
	void loadWordsFromFile(std::string fileName);
	std::deque<std::string> m_words;
};

#endif // _WORDS_LAYER_H_