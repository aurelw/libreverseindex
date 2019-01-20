#include "reverseindex.h"

#include <iostream>

namespace reverseindex {


ReverseIndex::ReverseIndex() {
};


ReverseIndex::~ReverseIndex() {
    for (auto query : _searchQueries) {
        delete query;
    }
}


void ReverseIndex::addSearchQuery(const std::string& query_s, int query_id) {
    _searchQueries.push_back(new std::string(query_s));
    std::string_view query_view(*_searchQueries.back());
    IndexEntry ie;
    for (int i=3; i<query_s.size()-1; i+=4) {
        ie.query_id = 0;
        ie.continue_n_chars = query_s.size() - i - 1;
        auto c_search_query_view = query_view.substr(0, i+1);
        _rindex.insert({c_search_query_view, ie});
    }
    ie.query_id = query_id;
    ie.continue_n_chars = 0;
    _rindex.insert({query_view, ie});
}


std::vector<ReverseIndex::SearchHit> 
ReverseIndex::searchInText(const std::string &text) {
    std::vector<SearchHit> search_hits;
    std::string_view text_view(text);

    for (int text_i=0; text_i<text.size(); text_i++) {
        /* Search starting at text position i. */
        for (int c_query_length = 1; 
             c_query_length+text_i<text.size(); 
             c_query_length++) 
        {
            std::string_view c_query = text_view.substr(text_i, c_query_length);
            bool continue_search = false;
            auto range = _rindex.equal_range(c_query);
            for (auto entry_i=range.first; entry_i!=range.second; entry_i++) {
                auto &index_entry = entry_i->second;
                if (index_entry.continue_n_chars != 0) {
                    continue_search = true;
                } else {
                    search_hits.push_back({text_i, index_entry.query_id});
                }
            }
            if (c_query_length % 4 == 0) {
                if (!continue_search) {
                    break;
                }
            }

        } // for query length
    } // for text

    return search_hits;
}


bool ReverseIndex::hasQuery(const std::string& query_s) {
    return _rindex.count(query_s);
}

} // namespace reverseindex
