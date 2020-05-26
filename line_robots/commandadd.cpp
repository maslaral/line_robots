#include "commandadd.h"

CommandAdd::CommandAdd(QGraphicsScene *scene, QGraphicsItem *item)
{
    mScene = scene;
    mItem = item;
}
void CommandAdd::undo()
{
    mScene->removeItem(mItem);
}

void CommandAdd::redo()
{
    mScene->addItem(mItem);
}
