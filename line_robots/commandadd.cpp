#include "commandadd.h"

CommandAdd::CommandAdd(QGraphicsScene *scene, QGraphicsItem *item, QUndoStack *undoStack)
{
    mScene = scene;
    mItem = item;
    mUndoStack = undoStack;
}
void CommandAdd::undo()
{
    if (mUndoStack->count() == 0){
        return;
    } else {
        mScene->removeItem(mItem);
    }
}

void CommandAdd::redo()
{
    mScene->addItem(mItem);
}
