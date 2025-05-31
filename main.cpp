#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include <unordered_map>

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

int main() {
    pasikartojantys("duom.txt");
    return 0;
}
