# LeetCode 195 - Tenth Line
#
# Given file.txt, print only its 10th line. If the file has fewer than 10 lines,
# print nothing at all.
#
# Input  : file.txt — an arbitrary number of text lines.
# Output : the 10th line exactly, or empty output when the file is shorter than
#          10 lines.
#
# Approach: address line 10 directly with sed. The -n flag turns off sed's
#   default "print every line" behaviour, and the "10p" command prints only the
#   line numbered 10. When the file has fewer than 10 lines there is no line 10
#   to match, so sed prints nothing — exactly the required behaviour for the
#   short-file edge case, with no explicit length check needed.
#
#   The statement hints at several solutions; two equivalent alternatives are:
#       awk 'NR == 10' file.txt             print the record numbered 10
#       tail -n +10 file.txt | head -n 1    skip to line 10, then take one line
#
# Complexity: O(n) in the number of lines scanned.

# -n: suppress automatic printing; '10p': print line 10 only (nothing if absent).
sed -n '10p' file.txt
