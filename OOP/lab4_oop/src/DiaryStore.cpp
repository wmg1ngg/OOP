#include "DiaryStore.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include <iomanip>

DiaryStore::DiaryStore() {
    // Check for environment variable PD_DATA, if not set use "diary.dat"
    const char* env = std::getenv("PD_DATA");
    filepath_ = (env && env[0]) ? env : "diary.dat";
    load();
}

// Parses a date string in the format YYYYMMDD and returns an integer representation (YYYYMMDD).
int DiaryStore::parseDate(const std::string& s) {
    if (s.size() != 8)
        throw std::invalid_argument("Date must be YYYYMMDD: " + s); // Check length
    for (char c : s)
        if (!std::isdigit((unsigned char)c))
            throw std::invalid_argument("Date must be YYYYMMDD: " + s);// Check all characters are digits
    return std::stoi(s);
}

std::string DiaryStore::formatDate(int date) {
    // Format an integer date (YYYYMMDD) into a string "YYYY-MM-DD".
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << date / 10000 << "-"
        << std::setw(2) << std::setfill('0') << (date / 100) % 100 << "-"
        << std::setw(2) << std::setfill('0') << date % 100;
    return oss.str();
}

void DiaryStore::load() {
    // Load diary entries from the file specified by filepath_.
    std::ifstream ifs(filepath_);
    if (!ifs.is_open()) return;

    std::string line;
    int cur = -1;
    std::ostringstream buf;

    // Read the file line by line, looking for lines that start with "DATE " to identify new entries.
    while (std::getline(ifs, line)) {
        // Check if the line starts with "DATE " to identify a new diary entry.
        if (line.rfind("DATE ", 0) == 0) {
            if (cur != -1) {
                std::string c = buf.str();
                if (!c.empty() && c.back() == '\n') c.pop_back();
                entries_[cur] = {cur, c};
                buf.str(""); buf.clear();
            }
            try {
                cur = parseDate(line.substr(5));
            }
            catch (...) { cur = -1; }
        } else if (cur != -1) {
            // If the line does not start with "DATE ", it is part of the content of the current diary entry.
            buf << line << "\n";
        }
    }

    // After the loop, if there is an entry being processed, save it to the entries_ map.
    if (cur != -1) {
        std::string c = buf.str();
        if (!c.empty() && c.back() == '\n') c.pop_back();
        entries_[cur] = {cur, c};
    }
}

// Add a new diary entry with the specified date and content. If an entry with the same date already exists, it will be overwritten.
void DiaryStore::add(int date, const std::string& content) {
    entries_[date] = {date, content};
}

// Remove the diary entry with the specified date. Returns true if an entry was removed, false if no entry with that date exists.
bool DiaryStore::remove(int date) {
    return entries_.erase(date) > 0;
}

// Find and return a pointer to the diary entry with the specified date. Returns nullptr if no entry with that date exists.
const DiaryEntry* DiaryStore::find(int date) const {
    auto it = entries_.find(date);
    return it == entries_.end() ? nullptr : &it->second;
}

// Return a const reference to the map of all diary entries, where the key is the date and the value is the DiaryEntry struct.
const std::map<int, DiaryEntry>& DiaryStore::all() const {
    return entries_;
}

// Save all diary entries to the file specified by filepath_. Each entry is written in the format "DATE YYYYMMDD" followed by the content of the entry on the next line.
void DiaryStore::save() const {
    std::ofstream ofs(filepath_, std::ios::trunc);
    if (!ofs.is_open())
        throw std::runtime_error("Cannot write to: " + filepath_);
    for (auto& [date, entry] : entries_)
        ofs << "DATE " << date << "\n" << entry.content << "\n";
}
