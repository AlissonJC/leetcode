/*
 * LeetCode 71 - Simplify Path
 *
 * Given an absolute Unix-style path (always starting with '/'), return its simplified
 * canonical form. Rules: '.' is the current directory (a no-op); '..' is the parent
 * directory (step up one level, but never above root); runs of consecutive slashes
 * collapse to one; and any other dot sequence like '...' or '....' is an ordinary,
 * valid name. The canonical path starts with a single '/', separates names by exactly
 * one '/', never ends with '/' (except the root "/"), and contains no '.'/'..' segments.
 *
 * Input  : string path. Output : string — the canonical path.
 *
 * Constraints: 1 <= path.length <= 3000; characters are letters, digits, '.', '/', '_';
 *   path is a valid absolute Unix path.
 *
 * Approach: Split the path on '/', turning it into a list of components, and process
 *   them with a stack (a vector used as one). Empty components (from '//' or the
 *   leading/trailing slash) and '.' are ignored. A '..' pops the stack when it has a
 *   directory to leave, and does nothing at the root — which is exactly why "/../"
 *   simplifies to "/". Every other component, including multi-dot names like '...',
 *   is a real directory and gets pushed. Finally, glue the surviving names together
 *   with single slashes; if none survived, the canonical path is just the root "/".
 *
 * Complexity: O(n) time and O(n) space, where n = path.length().
 */

#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stack;          // names currently on the canonical path
        stringstream ss(path);
        string token;

        // getline with '/' as the delimiter yields each component between slashes,
        // producing empty strings for '//' runs and the leading slash — all skipped.
        while (getline(ss, token, '/')) {
            if (token.empty() || token == ".") {
                continue;              // "" (collapsed slashes) and "." are no-ops
            } else if (token == "..") {
                if (!stack.empty()) stack.pop_back();   // step up; at root, do nothing
            } else {
                stack.push_back(token);                 // ordinary name (incl. "...", "....")
            }
        }

        // Rebuild "/name1/name2/..."; an empty stack means we are at the root.
        string result;
        for (const string& dir : stack) {
            result += '/';
            result += dir;
        }
        return result.empty() ? "/" : result;
    }
};
