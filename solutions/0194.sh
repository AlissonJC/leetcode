# LeetCode 194 - Transpose File
#
# Given file.txt holding a rectangular table of space-separated fields, print
# its transpose: the element at row r, column c moves to row c, column r. In
# other words, each original column becomes an output row.
#
# Input  : file.txt — every row has the same number of columns; fields within a
#          row are separated by a single space.
# Output : the transposed table, one original-column-per-line, fields still
#          space-separated.
#
# Example: "name age / alice 21 / ryan 30"  ->  "name alice ryan / age 21 30".
#
# Approach: one awk pass that builds the answer incrementally. For every input
#   row, append its i-th field to the accumulator out[i]; after all rows are
#   read, out[i] holds original column i as a space-joined string, which is
#   exactly output row i. The column count is captured from the first row since
#   the table is guaranteed rectangular.
#
# Complexity: O(rows * cols) time to visit every field once; O(rows * cols)
#   space to hold the transposed text.

awk '
NR == 1 { cols = NF }                  # all rows share this column count
{
    for (i = 1; i <= NF; i++) {
        # Grow the i-th output line by appending the i-th field of this row.
        if (NR == 1)
            out[i] = $i                # first row seeds each line (no leading space)
        else
            out[i] = out[i] " " $i     # later rows append, space-separated
    }
}
END {
    # One line per original column is the transpose.
    for (i = 1; i <= cols; i++)
        print out[i]
}
' file.txt
