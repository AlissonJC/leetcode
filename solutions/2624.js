/*
 * LeetCode 2624 - Snail Traversal
 *
 * Enhance every array with a snail(rowsCount, colsCount) method that reshapes the 1D
 * array into a rowsCount x colsCount 2D array filled in "snail" order: start at the
 * top-left, travel DOWN the first column, then move to the next column and travel UP,
 * then DOWN again, alternating direction column by column (a boustrophedon fill). The
 * array is only valid when arr.length === rowsCount * colsCount; for any other length
 * the method returns an empty array [].
 *
 * Input  : rowsCount, colsCount (grid dimensions); `this` is the flat source array.
 * Output : the rowsCount x colsCount grid in snail order, or [] if lengths mismatch.
 *
 * Constraints: 0 <= arr.length <= 1e4; 1 <= rowsCount, colsCount <= 1e4; validity is
 *   NOT guaranteed, so the length check must come first.
 *
 * Approach: consume the flat array in blocks of rowsCount consecutive elements -- each
 *   block is one column. For flat index i, column = floor(i / rowsCount) and the offset
 *   within that column is i % rowsCount. Even-numbered columns are laid top-to-bottom
 *   (row = offset); odd-numbered columns are laid bottom-to-top (row = rowsCount - 1 -
 *   offset). That per-column direction flip is exactly the snail's up/down alternation.
 *   Write each element straight into grid[row][column] in a single linear pass.
 *
 * Complexity: O(rowsCount * colsCount) = O(n) time and O(n) space for the output grid.
 */

/**
 * @param {number} rowsCount
 * @param {number} colsCount
 * @return {Array<Array<number>>}
 */
Array.prototype.snail = function(rowsCount, colsCount) {
    // Invalid shape: the flat length must exactly tile the requested grid.
    if (this.length !== rowsCount * colsCount) return [];

    // Allocate the grid up front so we can scatter elements into arbitrary cells.
    const grid = Array.from({ length: rowsCount }, () => new Array(colsCount));

    for (let i = 0; i < this.length; i++) {
        const col = Math.floor(i / rowsCount);   // each column owns rowsCount entries
        const offset = i % rowsCount;            // how far down this column we are
        // Even columns descend; odd columns ascend -- this flip is the snail pattern.
        const row = (col % 2 === 0) ? offset : (rowsCount - 1 - offset);
        grid[row][col] = this[i];
    }

    return grid;
};
