#ifndef COMMANDADD_H
#define COMMANDADD_H
#include <QUndoCommand>
#include <QGraphicsItem>
#include <QGraphicsScene>


class CommandAdd : public QUndoCommand
{
public:
    CommandAdd(QGraphicsScene *scene, QGraphicsItem *item, QUndoStack *undoStack);
    virtual void undo() override;
    virtual void redo() override;
private:
    QGraphicsScene *mScene;
    QGraphicsItem *mItem;
    QUndoStack *mUndoStack;
};

#endif // COMMANDADD_H
