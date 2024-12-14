#include "WordsLayer.h"

WordsLayer::WordsLayer(std::string fileName)
{
	srand((unsigned int)time(NULL));
	loadWordsFromFile(fileName);
}
WordsLayer::~WordsLayer()
{
	m_words.clear();
}
std::string WordsLayer::getRandomWordsLine()
{
	return m_words[rand() % m_words.size()];
}
int WordsLayer::getLinesCount()
{
	return m_words.size();
}

void WordsLayer::loadWordsFromFile(std::string fileName)
{
	std::ifstream fis(fileName);
	std::string line;
	while (getline(fis, line))
	{
		if (line.length() == 0)
			continue;
		m_words.push_back(line);
	}
	fis.close();
}