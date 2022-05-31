#include "fieldmanager.h"

FieldManager::FieldManager(QQuickPaintedItem *parent) : QQuickPaintedItem(parent) {
    qDebug() << "Constructing FieldManager...";
}

void FieldManager::paint(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing, true);
    _paintFrame(painter);
    _paintBlocks(painter);
}

void FieldManager::_paintFrame(QPainter *painter) {
    QPointF _topLeft(gameManager->_screenWidth / 2.0 - gameManager->_frameWidth / 2.0, gameManager->_screenHeight / 2.0 - gameManager->_frameHeight / 2.0);
    QPointF _topRight(gameManager->_screenWidth / 2.0 + gameManager->_frameWidth / 2.0, gameManager->_screenHeight / 2.0 - gameManager->_frameHeight / 2.0);
    QPointF _bottomLeft(gameManager->_screenWidth / 2.0 - gameManager->_frameWidth / 2.0, gameManager->_screenHeight / 2.0 + gameManager->_frameHeight / 2.0);
    QPointF _bottomRight(gameManager->_screenWidth / 2.0 + gameManager->_frameWidth / 2.0, gameManager->_screenHeight / 2.0 + gameManager->_frameHeight / 2.0);
    painter->save();
    painter->setPen(QPen(QColor("gray"), 1));
    for (int row = 1; row < gameManager->_rowCount; ++row) {
        QPointF tempLeft(_topLeft.x() + gameManager->_frameThickness / 2.0, _topLeft.y() + gameManager->_frameThickness / 2.0 + row * gameManager->_minoEdgeLength);
        QPointF tempRight(_topRight.x() + gameManager->_frameThickness / 2.0, _topRight.y() + gameManager->_frameThickness / 2.0 + row * gameManager->_minoEdgeLength);
        painter->drawLine(tempLeft, tempRight);
    }

    for (int column = 1; column < gameManager->_columnCount; ++column) {
        QPointF tempTop(_topLeft.x() + gameManager->_frameThickness / 2.0 + column * gameManager->_minoEdgeLength, _topLeft.y() + gameManager->_frameThickness / 2.0);
        QPointF tempBottom(_bottomLeft.x() + gameManager->_frameThickness / 2.0 + column * gameManager->_minoEdgeLength, _bottomLeft.y() + gameManager->_frameThickness / 2.0);
        painter->drawLine(tempTop, tempBottom);
    }

    painter->setPen(QPen(QColor("white"), 10, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    painter->setBrush(QColor("transparent"));
    painter->drawRect(QRectF(_topLeft, _bottomRight));
    painter->restore();
}

void FieldManager::_paintBlocks(QPainter *painter) {
    painter->save();
    QPointF startPoint(gameManager->_screenWidth / 2.0 - gameManager->_fieldWidth / 2.0, gameManager->_screenHeight / 2.0 - gameManager->_fieldHeight / 2.0);
    for (int row = 0; row < gameManager->_rowCount; ++row) {
        for (int column = 0; column < gameManager->_columnCount; ++column) {
            int tempType = gameManager->_data[row][column];
            if (tempType == 0) break;
            QRectF tempField(QPointF(startPoint.x() + gameManager->_minoEdgeLength * column, startPoint.y() + gameManager->_minoEdgeLength * row),
                             QPointF(startPoint.x() + gameManager->_minoEdgeLength * (column + 1), startPoint.y() + gameManager->_minoEdgeLength * (row + 1)));
            QRectF tempMino(0.0, 0.0, gameManager->_minoQImage[tempType].width(), gameManager->_minoQImage[tempType].height());
            painter->drawImage(tempField, gameManager->_minoQImage[tempType], tempMino);    // Fit mino to the grid size
        }
    }
    painter->restore();
}

void FieldManager::onGameStart(GameManager *_gameManager) {
    qDebug() << "FieldManager received settings signal.";
    gameManager = _gameManager;
    update();
}
