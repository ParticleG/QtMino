#ifndef FIELDMANAGER_H
#define FIELDMANAGER_H

#include "gamemanager.h"

#include <QPainter>

class FieldManager : public QQuickPaintedItem {
    Q_OBJECT
public:
    explicit FieldManager(QQuickPaintedItem *parent = nullptr);

private:
    void _paintFrame(QPainter *painter);
    void _paintBlocks(QPainter *painter);
    void paint(QPainter *painter);

    GameManager *gameManager;

public slots:
    Q_INVOKABLE void onGameStart(GameManager *_gameManager);
signals:
};

#endif // FIELDMANAGER_H
