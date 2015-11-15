/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str) 
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), 
                        std::back_inserter(ret),
                        std::ptr_fun< int, int >(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

/**
 * Initializes file_word_maps.
 * @param filenames The vector of names of the files that will be used
 */
void CommonWords::init_file_word_maps(const vector<string>& filenames) 
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for(size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current file
        vector<string> words = file_to_vector(filenames[i]);
        map<string, unsigned int> m;
	for(int j = 0; j < (int)words.size(); j++){ 
		auto lookup = m.find(words[j]);
		(lookup != m.end())?(lookup->second)++:m[words[j]] = 1;
	}
	file_word_maps[i] = m;
    }
}

/**
 * Initializes common.
 */
void CommonWords::init_common(){
	for(int i = 0; i < (int)file_word_maps.size(); i++){
		for(auto it = file_word_maps[i].begin(); it != file_word_maps[i].end() ; it++){
			string str = it->first;
			if(common.find(str) == common.end() ){
				common[str] = vector<unsigned int>(file_word_maps.size(), 0);	
			}
			common[str][i] += it->second;
		}
		

	}
    /* Your code goes here! */
}

/**
 * @param n The number of times the word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector< string > CommonWords::get_common_words(unsigned int n) const
{
    /* Your code goes here! */
    vector<string> out;
	vector<unsigned int> m; 
	for(auto it = common.begin(); it != common.end(); it++){
		bool hope = true;
		for(unsigned int i = 0; i<(unsigned int)it->second.size();i++){
			if(it->second[i] < n){
				hope = false;
				break;
			}
			
		}
		if (hope)
			out.push_back(it->first);
			
	}
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector< string > CommonWords::file_to_vector(const string& filename) const {
    ifstream words(filename);
    vector<string> out;

    if(words.is_open()) {
        std::istream_iterator<std::string> word_iter(words);
        while(!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
