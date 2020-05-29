#include "addrobot.h"

AddRobot::AddRobot(pathLine *line, QGraphicsItem *item, QUndoStack *undoStack)
{
    mLine = line;
    mItem = item;
    mUndoStack = undoStack;
}
void AddRobot::undo()
{
    if (mUndoStack->count() == 0){
        return;
    } else {
        mLine->scene()->removeItem(mItem);
    }
}

void AddRobot::redo()
{
    mItem->setParentItem(mLine);
}
