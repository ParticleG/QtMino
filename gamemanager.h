#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#define TYPE_AIR 0
#define TYPE_I_MINO 1
#define TYPE_O_MINO 2
#define TYPE_T_MINO 3
#define TYPE_S_MINO 4
#define TYPE_Z_MINO 5
#define TYPE_J_MINO 6
#define TYPE_L_MINO 7
#define TYPE_TRASH 8
#define TYPE_WALL 9
#define TYPE_HOLO 10

#include <QBitArray>
#include <QDebug>
#include <QImage>
#include <QQuickPaintedItem>
#include <QSettings>

class GameManager : public QQuickItem {
    Q_OBJECT
public:
    explicit GameManager(QQuickItem *parent = nullptr);
    Q_INVOKABLE void loadSettings();
    Q_INVOKABLE void exportSettings();

    QVector<QVector<int>> _data {};
    QVector<QBitArray>    _occupancy {};
    QVector<QImage>       _minoQImage {};
    int                   _rowCount {}, _columnCount {};
    double                _screenHeight {}, _screenWidth {}, _uiScale {}, _frameHeight {}, _frameWidth {}, _fieldHeight {}, _fieldWidth {}, _frameThickness {}, _minoEdgeLength {};

signals:
    void gameStart(GameManager *self);
};

#endif // GAMEMANAGER_H
