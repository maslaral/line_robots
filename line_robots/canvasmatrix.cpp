/* ========================================================
   Purpose: The Canvas Matrix class represents the board in
            a matrix format. This is used to store pointers
            to the lines and robots that are created. For
            example, adding a line to the board also calls
            the addLine function which saves pointers to
            the matrix locations where the line is placed.
-----------------------------------------------------------
   Notes:   This is a requirement because the drawings
            in Qt don't store the actual object. They
            essentially just render a graphic. If we want
            to access the object on the board, we'll need to
            use some sort of underlying matrix that is the
            same size as the board (in this case, 600 x 600).
            Thus getting the position of a click on the
            canvas, should relate directly to a cell in the
            matrix.
=========================================================*/
#include "canvasmatrix.h"
#include "line.h"

CanvasMatrix::CanvasMatrix()
{
    // filling the array with nullptrs
    for (int i = 0; i < 600; i++) {
        for (int j = 0; j < 600; j++) {
            matrix[i][j] = nullptr;
        }
    }
}

void CanvasMatrix::addLine(Line* newLine)
{
    // getting starting and ending coordinates
    int x1 = newLine->getStartX();
    int y1 = newLine->getStartY();
    int x2 = newLine->getEndX();
    int y2 = newLine->getEndY();

    // setting the matrix cells from start to
    // end as pointers to the line
    if (x1 < x2) {
        for (int i = 0; i < (x2 - x1); i++) {
            matrix[x1 + i][y1] = newLine;
        }
    } else if (x1 > x2) {
        for (int i = 0; i < (x1 - x2); i++) {
            matrix[x1 - i][y1] = newLine;
        }
    } else if (y1 < y2) {
        for (int i = 0; i < (y2 - y1); i++) {
            matrix[x1][y1 + i] = newLine;
        }
    } else {
        for (int i = 0; i < (y1 - y2); i++) {
            matrix[x1][y1 - i] = newLine;
        }
    }
}
