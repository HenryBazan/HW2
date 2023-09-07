#include "trendtracker.h"
#include <algorithm>

// Constructor
Trendtracker::Trendtracker(string filename) {
    ifstream file(filename);
    string hashtag;

    // Read hashtags from the file and initialize the Trendtracker
    while (getline(file, hashtag)) {
        Entry entry;
        entry.hashtag = hashtag;
        entry.pop = 0;
        E.push_back(entry);
    }

    // Initialize S to store indices of the top three trends
    for (int i = 0; i < min(3, static_cast<int>(E.size())); ++i) {
        S.push_back(i);
    }
}

int Trendtracker::size() {
    return E.size();
}

void Trendtracker::tweeted(string ht) {
    int index = search(ht);
    if (index != -1) {
        E[index].pop++;
        // Update S with the new index if necessary
        for (int i = 0; i < S.size(); ++i) {
            if (E[S[i]].pop < E[index].pop) {
                S.insert(S.begin() + i, index);
                if (S.size() > 3) {
                    S.pop_back();
                }
                return;
            }
        }
    }
}

int Trendtracker::popularity(string name) {
    int index = search(name);
    if (index != -1) {
        return E[index].pop;
    }
    return -1;
}

string Trendtracker::top_trend() {
    if (!S.empty()) {
        return E[S[0]].hashtag;
    }
    return "";
}

void Trendtracker::top_three_trends(vector<string> &T) {
    T.clear();
    for (int i : S) {
        T.push_back(E[i].hashtag);
    }
}

int Trendtracker::search(string ht) {
    // Binary search for the hashtag in the sorted vector E
    int left = 0;
    int right = E.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (E[mid].hashtag == ht) {
            return mid;
        }
        else if (E[mid].hashtag < ht) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;  // Hashtag not found
}
