/*
 * LeetCode 332 - Reconstruct Itinerary
 *
 * Given a list of airline tickets, each tickets[i] = [from, to] for one flight,
 * reconstruct the single itinerary that uses every ticket exactly once and starts
 * at "JFK". When several such itineraries exist, return the one that is smallest in
 * lexical order when the airport codes are read as one concatenated string. The
 * input is guaranteed to admit at least one valid itinerary.
 *
 * Input  : vector<vector<string>>& tickets. Output : vector<string> — the airports
 *          visited in order (length tickets.size() + 1).
 *
 * Constraints: 1 <= tickets.length <= 300; codes are 3 uppercase letters; from != to.
 *   Small graph, so an O(E log E) Eulerian-path construction is more than fast enough.
 *
 * Approach: this is an Eulerian path (use each directed edge once) that must be
 *   lexicographically minimal, which Hierholzer's algorithm yields directly. Store
 *   each airport's outgoing destinations in a multiset so the smallest is always at
 *   begin(). Walk greedily: from the current node repeatedly take and remove its
 *   smallest unused destination and recurse into it. When a node runs out of
 *   outgoing edges it is a dead end of the current walk, so append it to the route;
 *   this post-order emission, reversed at the end, produces a valid Eulerian path,
 *   and always choosing the smallest next edge makes it the lexicographically
 *   smallest one. Re-look-up adj[node] each loop iteration rather than caching a
 *   reference, since a recursive call may insert a new key and rehash the map,
 *   which would dangle a held reference.
 *
 * Complexity: O(E log E) time (each of E edges is inserted into and erased from a
 *   multiset), O(E) space for the graph, route, and recursion depth.
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
    unordered_map<string, multiset<string>> adj;   // node -> sorted destinations
    vector<string> route;                          // airports in REVERSE finishing order

    void dfs(const string& node) {
        // Consume the smallest available edge each step. Re-fetch adj[node] every
        // iteration: dfs(next) below may insert a new key and rehash the map,
        // which would invalidate any cached reference to this node's multiset.
        while (true) {
            auto& dests = adj[node];
            if (dests.empty())
                break;                              // no outgoing edges left here
            string next = *dests.begin();           // lexicographically smallest
            dests.erase(dests.begin());             // use that ticket exactly once
            dfs(next);
        }
        // Node is finished (all its edges used): emit it in post-order.
        route.push_back(node);
    }

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (const auto& t : tickets)
            adj[t[0]].insert(t[1]);                 // multiset keeps destinations sorted

        route.reserve(tickets.size() + 1);
        dfs("JFK");                                 // itinerary always starts at JFK

        // Post-order produced the path reversed; flip it to get departure order.
        reverse(route.begin(), route.end());
        return route;
    }
};
