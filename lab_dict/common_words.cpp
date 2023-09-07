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
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        [](int c) {return std::ispunct(c);});
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */
        for(auto iter : words){
            file_word_maps[i][iter] += 1;
        }
    }
}

void CommonWords::init_common()
{
    /* Your code goes here! */
    for(size_t i = 0; i < file_word_maps.size(); i++){
        for (std::pair<string, unsigned int> key_val : file_word_maps[i]){
            map<string, unsigned int>::iterator find = common.find(key_val.first);
            if(find == common.end()){
                common[key_val.first] = 1;
                }
            else{
                find->second++;
            }
        }
    }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */
    for(auto& iter : common){
        if(iter.second == file_word_maps.size()){

            unsigned counter = 0;
            for(auto& iter1 : file_word_maps){
                auto iter2 = iter1.find(iter.first);
                size_t counter1 = iter2->second;
                if(counter1 >= n){
                    counter++;
                }
            }
            if(counter == iter.second){
                out.push_back(iter.first);
            }
        }
    }

    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
