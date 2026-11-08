#pragma once
#include <map>
#include <string>

struct DiaryEntry {
    int date;
    std::string content;
};

class DiaryStore {
public:
    DiaryStore();
    void add(int date, const std::string& content);
    bool remove(int date);
    const DiaryEntry* find(int date) const;
    const std::map<int, DiaryEntry>& all() const;
    void save() const;
    static int parseDate(const std::string& s);
    static std::string formatDate(int date);
private:
    std::map<int, DiaryEntry> entries_;
    std::string filepath_;
    void load();
};
