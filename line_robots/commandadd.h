#ifndef COMMANDADD_H
#define COMMANDADD_H
#include <QUndoCommand>
#include <QGraphicsItem>
#include <QGraphicsScene>


class CommandAdd : public QUndoCommand
{
public:
    CommandAdd(QGraphicsScene *scene, QGraphicsItem *item);
    virtual void undo() override;
    virtual void redo() override;
private:
    QGraphicsScene *mScene;
    QGraphicsItem *mItem;
};

#endif // COMMANDADD_H
