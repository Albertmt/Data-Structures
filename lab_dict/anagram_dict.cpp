/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>
using std::string;
using std::vector;
using std::ifstream;

/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename){
	ifstream wordsFile(filename);
	string word;
	if(wordsFile.is_open()){
		while(getline(wordsFile, word)){
			string wordCopy = word;
			sort(word.begin(), word.end());
			auto lookup = dict.find(word);
			if(lookup == dict.end())
				dict[word].push_back(wordCopy);
			else{
				if(find(dict[word].begin(), dict[word].end(), wordCopy) != dict[word].end())
					continue;
				else
					dict[word].push_back(wordCopy);
			}	
		}
	}
}

/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words){
	for(unsigned int i = 0; i < words.size(); i++){
		string word = words[i];
		string wordCopy = word;
		std::sort(word.begin(), word.end());
		auto lookup = dict.find(word);
		if(lookup == dict.end()){
			dict[word] = vector<string>();
			dict[word].push_back(wordCopy);
		}
		else{
			if(std::find(dict[word].begin(), dict[word].end(), word) != dict[word].end())
				continue;
			else
				dict[word].push_back(wordCopy);

		}	
	}
}


/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const{
	
	string wordCopy = word;	
	sort(wordCopy.begin(), wordCopy.end());
	auto lookup = dict.find(wordCopy);
	if(lookup == dict.end())
		return vector< string >();	
	else
		return lookup->second;
}       

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const{
	
	vector< vector< string > > ret;
	for(auto it:dict){
		if ((it.second).size()!=1)
			ret.push_back(it.second);
	}
    return ret;
}


