#include "DiaryStore.h"
#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) { //argc(argument count) is the number of command-line arguments.
    // Check if the correct number of command-line arguments is provided.
    if (argc != 2) {
        std::cerr << "Usage: pdadd <YYYYMMDD>\n";
        return 1;
    }

    int date;

    // Parse the date from the command-line argument. If the date is not in the correct format, print an error message and exit.
    try { date = DiaryStore::parseDate(argv[1]); }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    std::string line, content;
    bool first = true;
    // Read lines of input from the user until a line containing only a single period (".") is entered.
    while (std::getline(std::cin, line)) {
        if (line == ".") break;
        if (!first) content += "\n";
        content += line;
        first = false;
    }

    DiaryStore store;
    store.add(date, content);
    store.save();
    std::cout << "Saved " << DiaryStore::formatDate(date) << "\n";
    return 0;
}
