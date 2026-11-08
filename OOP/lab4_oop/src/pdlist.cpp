#include "DiaryStore.h"
#include <iostream>

int main(int argc, char* argv[]) {
    int start = 0, end = 99999999;

    // Parse command line arguments
    if (argc == 3) {
        try {
            start = DiaryStore::parseDate(argv[1]);
            end   = DiaryStore::parseDate(argv[2]);
        } catch (const std::exception& e) { std::cerr << e.what() << "\n"; return 1; }
    } else if (argc != 1) { // Invalid number of arguments
        std::cerr << "Usage: pdlist [start end]\n";
        return 1;
    }

    DiaryStore store;
    for (auto& [date, entry] : store.all())
        if (date >= start && date <= end) // Print entries in the specified date range
            std::cout << DiaryStore::formatDate(date) << "\n";
    return 0;
}
