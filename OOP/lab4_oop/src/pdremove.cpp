#include "DiaryStore.h"
#include <iostream>

int main(int argc, char* argv[]){
    if (argc != 2){ // Expect exactly one argument: the date to remove
        std::cerr << "Usage: pdremove <YYYYMMDD>\n";
        return 1;
    }

    int date;
    // Parse the date argument, which should be in YYYYMMDD format
    try { date = DiaryStore::parseDate(argv[1]); }
    // If parsing fails, print the error message and exit with an error code
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    DiaryStore store;
    // Attempt to remove the entry for the specified date. If it doesn't exist, print an error message and exit with an error code.
    if (!store.remove(date)) {
        std::cerr << "No entry for " << DiaryStore::formatDate(date) << "\n";
        return 1;
    }
    store.save();
    // If the entry was successfully removed, print a confirmation message.
    std::cout << "Removed " << DiaryStore::formatDate(date) << "\n";
    return 0;
}
