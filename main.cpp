#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>

std::string s_zodis(const std::string& zodis) {
    std::string result;
    for (char c : zodis) {
        if (std::isalpha(c) || std::isdigit(c)) {
            result += std::tolower(c);
        }
    }
    return result;
}

int main() {

    std::ofstream rf("rez/svarus_zodziai.txt");
    std::ifstream df("duom.txt");
    if (!df) {
        std::cerr << "Nepavyko atidaryti failo 'duom.txt'" << std::endl;
        return 1;
    }
    std::string eil;

    while (std::getline(df, eil)) {
        std::istringstream iss(eil);
        std::string zodzis;
        while (iss >> zodzis) {
            std::string svarus_zodis = s_zodis(zodzis);
            if (!svarus_zodis.empty()) {
                rf << svarus_zodis << " ";
            }
        }
        rf<< std::endl;
        
    }

}