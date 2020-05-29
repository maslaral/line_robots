#ifndef ADDROBOT_H
#define ADDROBOT_H
#include <QUndoCommand>
#include <QGraphicsItem>
#include "pathline.h"


class AddRobot : public QUndoCommand
{
public:
    AddRobot(pathLine *line, QGraphicsItem *item, QUndoStack *undoStack);
    virtual void undo() override;
    virtual void redo() override;
private:
    pathLine *mLine;
    QGraphicsItem *mItem;
    QUndoStack *mUndoStack;
};

#endif // COMMANDADD_H
