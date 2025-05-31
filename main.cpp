#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include <unordered_map>
#include <set>
#include <regex>


std::string s_zodis(const std::string& zodis) {
    std::string result;
    for (char c : zodis) {
        if (std::isalpha(c) || std::isdigit(c)) {
            result += std::tolower(c);
        }
    }
    return result;
}

void pasikartojantys(const std::string& file) {
    std::ifstream input(file);
    if (!input) {
        std::cerr << "Klaida: Nepavyko atidaryti '" << file << "'\n";
        return;
    }

    std::ofstream rf("rez/svarus_zodziai.txt");
    if (!rf) {
        std::cerr << "Klaida: Nepavyko sukurti 'rez/svarus_zodziai.txt'\n";
        return;
    }

    std::unordered_map<std::string, int> word_count;
    std::string word;

    std::string line;
while (std::getline(input, line)) {
    std::istringstream iss(line);
    std::string word;

    while (iss >> word) {
        std::string svarus_z = s_zodis(word);
        if (!svarus_z.empty()) {
            word_count[svarus_z]++;
            rf << svarus_z << " ";
        }
    }

    rf << "\n";
}
    std::cout << "Zodziai isvalyti ir isvesti i 'rez/svarus_zodziai.txt'\n";
    input.close();
    rf.close();

    std::ofstream output("rez/pasikartojantys.txt");
    if (!output) {
        std::cerr << "Klaida: Nepavyko sukurti 'rez/pasikartojantys.txt'\n";
        return;
    }

    for (const auto& [word, count] : word_count) {
        if (count > 1) {
            output << word << ": " << count << "\n";
        }
    }
    std::cout << "Rezultatai isvesti i 'rez/pasikartojantys.txt'\n";
    output.close();
}

void cross_reference(const std::string& failas) {
    std::ifstream input(failas);
    if (!input) {
        std::cerr << "Klaida: Nepavyko atidaryti '" << failas << "'\n";
        return;
    }

    std::unordered_map<std::string, std::set<int>> word_lines;
    std::unordered_map<std::string, int> word_count;
    std::string line;
    int line_number = 0;

    while (std::getline(input, line)) {
        ++line_number;
        std::istringstream iss(line);
        std::string word;

        while (iss >> word) {
            std::string svarus = s_zodis(word);
            if (!svarus.empty()) {
                word_lines[svarus].insert(line_number);
                word_count[svarus]++;
            }
        }
    }

    input.close();

    std::ofstream output("rez/crossref.txt");
    if (!output) {
        std::cerr << "Klaida: Nepavyko sukurti 'rez/crossref.txt'\n";
        return;
    }

    for (const auto& [word, lines] : word_lines) {
        if (word_count[word] > 1) {
            output << word << ": ";
            for (int line : lines) {
                output << line << " ";
            }
            output << "\n";
        }
    }

    output.close();
    std::cout << "Cross-reference lentelė sukurta: rez/crossref.txt\n";
}

void find_url(const std::string& file)
{
    std::ifstream input(file);
    if (!input) {
        std::cerr << "Klaida: Nepavyko atidaryti '" << file << "'\n";
        return;
    }
    std::ofstream output("rez/url.txt");
    if (!output) {
        std::cerr << "Klaida: Nepavyko sukurti 'rez/url.txt'\n";
        return;
    }
     std::regex url_regex(R"((https?://[^\s]+|www\.[^\s]+|\b[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}\b))");

    std::string line;
    std::set<std::string> found_urls;

    while (std::getline(input, line)) {
        auto begin = std::sregex_iterator(line.begin(), line.end(), url_regex);
        auto end = std::sregex_iterator();

        for (auto it = begin; it != end; ++it) {
            found_urls.insert(it->str());
        }
    }

    for (const auto& url : found_urls) {
        output << url << "\n";
    }

    input.close();
    output.close();

    std::cout << "Rezultatai pateikti rez/url.txt'\n";
}
int main() {
    pasikartojantys("duom.txt");
    cross_reference("rez/svarus_zodziai.txt");
    find_url("duom.txt");
    return 0;
}
