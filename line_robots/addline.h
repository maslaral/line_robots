#ifndef COMMANDADD_H
#define COMMANDADD_H
#include <QUndoCommand>
#include <QGraphicsItem>
#include <QGraphicsScene>


class AddLine : public QUndoCommand
{
public:
    AddLine(QGraphicsScene *scene, QGraphicsItem *item, QUndoStack *undoStack);
    virtual void undo() override;
    virtual void redo() override;
private:
    QGraphicsScene *mScene;
    QGraphicsItem *mItem;
    QUndoStack *mUndoStack;
};

#endif // COMMANDADD_H
