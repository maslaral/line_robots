#ifndef COMMANDADD_H
#define COMMANDADD_H
#include <QUndoCommand>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "pathline.h"


class AddLine : public QUndoCommand
{
public:
    AddLine(QGraphicsScene *scene, pathLine *item, QUndoStack *undoStack);
    virtual void undo() override;
    virtual void redo() override;
private:
    QGraphicsScene *mScene;
    pathLine *mItem;
    QUndoStack *mUndoStack;
};

#endif // COMMANDADD_H
