#ifndef _REVERSE_INDEX_H_
#define _REVERSE_INDEX_H_

#include <map>
#include <string_view>
#include <vector>

namespace reverseindex {

class ReverseIndex {

    public:

        class SearchHit {
            public:
                SearchHit(const int t_pos, const int q_id) 
                    : text_position(t_pos), query_id(q_id) {};
                int text_position;
                int query_id;
        };

    public:

        ReverseIndex();
        ~ReverseIndex();

        /** SETUP **/
        void addSearchQuery(const std::string& query_s, int query_id);

        /** Main search method. Searches all added queries in the given
         ** text. Returns hits. **/
        std::vector<SearchHit> searchInText(const std::string &text);

        bool hasQuery(const std::string& query_s);

    private:

        class IndexEntry {
            public:
                int continue_n_chars;
                int query_id;
        };

        std::multimap<std::string_view, IndexEntry> _rindex;
        std::vector<std::string*> _searchQueries;

};

} // namespace reverseindex

#endif
