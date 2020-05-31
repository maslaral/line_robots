#include "addline.h"

AddLine::AddLine(QGraphicsScene *scene, pathLine *item, QUndoStack *undoStack)
{
    mScene = scene;
    mItem = item;
    mUndoStack = undoStack;
}
void AddLine::undo()
{
    if (mUndoStack->count() == 0){
        return;
    } else {
        mScene->removeItem(mItem);
        mItem->cleanIntersections();
    }
}

void AddLine::redo()
{
    mScene->addItem(mItem); //add the line to the scene
    mItem->addIntersections(); //add intersections
}
