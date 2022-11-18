#ifndef MINOSMANAGER_H
#define MINOSMANAGER_H

#define MOTION_UP 0
#define MOTION_RIGHT 1
#define MOTION_DOWN 2
#define MOTION_LEFT 3
#define MOTION_CLOCKWISE 5
#define MOTION_CONTER_CLOCKWISE 6
#define MOTION_FLIP 7
#define MOTION_HORIZONTAL_MIRROR 8
#define MOTION_VERTICAL_MIRROR 9

#include "gamemanager.h"

#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>
#include <algorithm>

class MinosManager : public QQuickPaintedItem {
    Q_OBJECT
public:
    explicit MinosManager(QQuickPaintedItem *parent = nullptr);
    Q_INVOKABLE void _getNextMino();
    Q_INVOKABLE void _moveNowMino(unsigned int _direction, int _value);

private:
    void paint(QPainter *painter);
    void _paintNowMino(QPainter *painter);
    void _generateMinos();
    QPoint _detectCollision(unsigned int _type);

    GameManager *gameManager;
    QTimer *     _dropDownTimer;
    QTimer *     _lockDownTimer;

    struct _NowMino {
        QVector<QPoint> _state;
        QPoint          _position;
        int             _orientation {}, _type {};
    } _nowMino;

    QVector<int> _generatedMinosList {};

public slots:
    Q_INVOKABLE void onGameStart(GameManager *_gameManager);
    void             onDropDown();
    void             onLockDown();
    void             onMinoHold();
signals:
};

#endif // MINOSMANAGER_H
