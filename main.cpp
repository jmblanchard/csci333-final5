#include <iostream>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>

bool compare_pairs(std::pair<std::string, int> first,
        std::pair<std::string, int> second) {
    if (first.second > second.second) return true;

    return false;
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        char *in_filename = argv[1];
        int total_word_count = 0;
        int unique_word_count = 1;
        std::string line;
        std::ifstream in_file(in_filename);

        std::map<std::string, int> unique_word_list;
        std::list<std::pair<std::string, int> > sorted_words;

        if (in_file.is_open()) {
            while (in_file.good()) {
                std::getline(in_file, line);
                std::istringstream iss(line);
                std::string word;

                while (iss >> word) {
                    std::transform(word.begin(), word.end(),
                            word.begin(), ::tolower);
                    total_word_count++;

                    if (unique_word_list.count(word) == 1) {
                        unique_word_list[word] = unique_word_list[word]
                            + 1;
                    } else {
                        unique_word_list[word] = 1;
                    }
                }
            }
        }

        in_file.close();
        unique_word_count = unique_word_list.size();

        std::ofstream out_analysis("analysis");
        if (out_analysis.is_open()) {
            double lexical_diversity = 
                (double)total_word_count / unique_word_count;
            out_analysis << "Unique words: " << unique_word_count << "\n";
            out_analysis << "Lexical diversity: " << lexical_diversity 
                << "\n";
        }

        out_analysis.close();

        std::map<std::string, int>::iterator it;
        for (it = unique_word_list.begin(); it != unique_word_list.end();
                ++it) {
            sorted_words.push_back(*it);
        }
        sorted_words.sort(compare_pairs);

        std::ofstream out_wordlist("unique-word-list");
        if (out_wordlist.is_open()) {
            std::list<std::pair<std::string, int> >::iterator it2;
            for (it2 = sorted_words.begin(); it2 != sorted_words.end();
                    ++it2) {
                out_wordlist << (*it2).first << " => " << (*it2).second;
                out_wordlist << "\n";
            }
        }

        out_wordlist.close();
    }

    return 0;
}
