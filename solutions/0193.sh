# LeetCode 193 - Valid Phone Numbers
#
# Given file.txt with one phone number per line, print only the lines that are
# valid phone numbers. A number is valid when it matches exactly one of these
# two formats (each x is a single digit 0-9):
#     (xxx) xxx-xxxx      parentheses around the area code, then a single space
#     xxx-xxx-xxxx        three dash-separated digit groups
#
# Input  : file.txt — one candidate per line, no leading/trailing whitespace.
# Output : every line that is a valid phone number, printed unchanged and in the
#          original order.
#
# Approach: a single anchored extended-regex match with grep. Anchoring the
#   pattern with ^ and $ forces the *entire* line to match, so anything with
#   extra digits or trailing characters is rejected. The two accepted layouts
#   are listed as alternatives inside one group:
#       \([0-9]{3}\) [0-9]{3}-[0-9]{4}    the "(xxx) xxx-xxxx" form
#       [0-9]{3}-[0-9]{3}-[0-9]{4}        the "xxx-xxx-xxxx" form
#   The parentheses are escaped (\( \)) because here they are literal characters
#   in the phone number, not a regex group; the space after \) is the literal
#   space that format requires.
#
# Complexity: O(n) in the number of lines — grep tests each line exactly once.

# -E selects extended regex, enabling {n} quantifiers, | alternation, and ()
# grouping without backslashes. grep prints each matching line verbatim.
grep -E '^(\([0-9]{3}\) [0-9]{3}-[0-9]{4}|[0-9]{3}-[0-9]{3}-[0-9]{4})$' file.txt
