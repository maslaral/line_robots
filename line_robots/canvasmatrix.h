#ifndef CANVASMATRIX_H
#define CANVASMATRIX_H

class Line;

class CanvasMatrix
{
public:
    CanvasMatrix();
    void addLine(Line*);
private:
    Line* matrix[600][600];
};

#endif // CANVASMATRIX_H
