#include "reverseindex.h"

#include <iostream>

using namespace reverseindex;

void printSearchHits(const std::vector<ReverseIndex::SearchHit> &hits) 
{
    for (const auto &hit : hits) {
        std::cout << "Hit [" << hit.text_position << "] - " << hit.query_id
                  << std::endl;
    }
    std::cout << "----------------------------------------------" << std::endl;
}

int main() {
    ReverseIndex ri;

    ri.addSearchQuery("Hund", 1);
    ri.addSearchQuery("Bahnhof", 2);
    ri.addSearchQuery("AWD", 3);
    ri.addSearchQuery("Bahnhofs Eigner", 3);

    std::cout << "Has query 'Hund': " << ri.hasQuery("Hund") << std::endl;

    std::string text = "Eine kleine Heuschrecke wird vom Hund gefressen.";
    auto search_hits = ri.searchInText(text);
    printSearchHits(search_hits);

    text = "Keiner mag AWD drives.";
    search_hits = ri.searchInText(text);
    printSearchHits(search_hits);

    std::cout << "Has query 'Hund': " << ri.hasQuery("Hund") << std::endl;
    return 0;
}
