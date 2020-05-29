#include "addline.h"

AddLine::AddLine(QGraphicsScene *scene, QGraphicsItem *item, QUndoStack *undoStack)
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
    }
}

void AddLine::redo()
{
    mScene->addItem(mItem);
}
