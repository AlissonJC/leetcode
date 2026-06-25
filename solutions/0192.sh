# LeetCode 192 - Word Frequency
#
# Read the text file words.txt and print every distinct word together with how
# many times it occurs, ordered from the most frequent word down to the least.
#
# Input  : words.txt — contains only lowercase letters and space characters;
#          words are separated by one or more whitespace characters. This is a
#          Shell problem, so the script reads the fixed filename directly rather
#          than from stdin.
# Output : one "word count" line per distinct word, sorted by descending count.
#          Counts are guaranteed unique, so the ordering is unambiguous and no
#          tie-breaking rule is required.
#
# Approach: a classic Unix text-processing pipeline, one stage per transformation.
#   1. tr -s ' ' '\n'        Turn every run of spaces into a single newline, so
#                            each word ends up alone on its own line. The -s
#                            (squeeze) flag collapses multiple spaces into one
#                            separator, handling the "one or more whitespace" rule.
#   2. sort                  Bring identical words next to each other; uniq only
#                            collapses *adjacent* duplicates, so it needs sorted
#                            input to count correctly.
#   3. uniq -c               Collapse each run of equal words into a single line
#                            prefixed by its occurrence count, e.g. "   3 is".
#   4. sort -rn              Reorder those lines by the leading number, highest
#                            first (-n numeric, -r reversed = descending).
#   5. awk '{print $2, $1}'  Swap the two columns from "count word" into the
#                            required "word count" output format.
#
# Complexity: O(n log n) time, dominated by sorting the n words; O(n) space.

# The problem fixes the input filename, so read straight from words.txt.
cat words.txt | tr -s ' ' '\n' | sort | uniq -c | sort -rn | awk '{print $2, $1}'
