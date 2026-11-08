#include "DiaryStore.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Expect exactly one argument: the date to show
    if (argc != 2) { std::cerr << "Usage: pdshow <YYYYMMDD>\n"; return 1; }

    int date;
    // Parse the date argument, which should be in YYYYMMDD format
    try { date = DiaryStore::parseDate(argv[1]); }
    catch (const std::exception& e) { std::cerr << e.what() << "\n"; return 1; }

    DiaryStore store;
    const DiaryEntry* entry = store.find(date);
    // If no entry exists for the specified date, print an error message and exit with an error code
    if (!entry){
        std::cerr << "No entry for " << DiaryStore::formatDate(date) << "\n";
        return 1;
    }
    std::cout << entry->content << "\n";
    return 0;
}
