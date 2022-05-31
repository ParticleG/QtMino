#include "minosmanager.h"

MinosManager::MinosManager(QQuickPaintedItem *parent) : QQuickPaintedItem(parent) {
    qDebug() << "Constructing MinoManager...";

    _dropDownTimer = new QTimer(this);
    _dropDownTimer->setInterval(1000);
    connect(_dropDownTimer, &QTimer::timeout, this, &MinosManager::onDropDown);

    _lockDownTimer = new QTimer(this);
    _lockDownTimer->setInterval(1000);
    connect(_lockDownTimer, &QTimer::timeout, this, &MinosManager::onLockDown);

    _generatedMinosList.resize(14);
    _generatedMinosList.fill(0, 14);
    for (int times = 0; times < 2; ++times) {
        for (int index = 0; index < 7; ++index) {
            _generatedMinosList[index + times * 7] = QRandomGenerator64::global()->generate() % 7 + 1;
            for (int searcher = 0; searcher < index; ++searcher) {
                if (_generatedMinosList[index + times * 7] == _generatedMinosList[searcher + times * 7]) {
                    index--;
                    break;
                }
            }
        }
    }
    _nowMino._state.resize(4);
    _nowMino._type = _generatedMinosList.takeFirst();
    switch (_nowMino._type) {
        case TYPE_I_MINO:
            _nowMino._state[0] = QPoint(-1, 0);
            _nowMino._state[1] = QPoint(0, 0);
            _nowMino._state[2] = QPoint(1, 0);
            _nowMino._state[3] = QPoint(2, 0);
            break;
        case TYPE_O_MINO:
            _nowMino._state[0] = QPoint(0, -1);
            _nowMino._state[1] = QPoint(1, -1);
            _nowMino._state[2] = QPoint(0, 0);
            _nowMino._state[3] = QPoint(1, 0);
            break;
        case TYPE_T_MINO:
            _nowMino._state[0] = QPoint(0, -1);
            _nowMino._state[1] = QPoint(-1, 0);
            _nowMino._state[2] = QPoint(0, 0);
            _nowMino._state[3] = QPoint(1, 0);
            break;
        case TYPE_S_MINO:
            _nowMino._state[0] = QPoint(0, -1);
            _nowMino._state[3] = QPoint(1, -1);
            _nowMino._state[1] = QPoint(-1, 0);
            _nowMino._state[2] = QPoint(0, 0);
            break;
        case TYPE_Z_MINO:
            _nowMino._state[1] = QPoint(-1, -1);
            _nowMino._state[0] = QPoint(0, -1);
            _nowMino._state[2] = QPoint(0, 0);
            _nowMino._state[3] = QPoint(1, 0);
            break;
        case TYPE_J_MINO:
            _nowMino._state[0] = QPoint(-1, -1);
            _nowMino._state[1] = QPoint(-1, 0);
            _nowMino._state[2] = QPoint(0, 0);
            _nowMino._state[3] = QPoint(1, 0);
            break;
        case TYPE_L_MINO:
            _nowMino._state[1] = QPoint(-1, 0);
            _nowMino._state[2] = QPoint(0, 0);
            _nowMino._state[3] = QPoint(1, 0);
            _nowMino._state[0] = QPoint(1, -1);
            break;
        default: break;
    }
    _nowMino._position    = QPoint(4, -1);
    _nowMino._orientation = MOTION_UP;

    qDebug() << "MinoManager Constructed.";
}

void MinosManager::paint(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing, true);
    _paintNowMino(painter);
}

void MinosManager::_paintNowMino(QPainter *painter) {
    painter->save();
    QPointF startPoint(gameManager->_screenWidth / 2.0 - gameManager->_fieldWidth / 2.0, gameManager->_screenHeight / 2.0 - gameManager->_fieldHeight / 2.0);
    for (const auto &monoMino : _nowMino._state) {
        QRectF tempField(QPointF(startPoint.x() + gameManager->_minoEdgeLength * (_nowMino._position.x() + monoMino.x()), startPoint.y() + gameManager->_minoEdgeLength * (_nowMino._position.y() + monoMino.y())),
                         QPointF(startPoint.x() + gameManager->_minoEdgeLength * (_nowMino._position.x() + monoMino.x() + 1), startPoint.y() + gameManager->_minoEdgeLength * (_nowMino._position.y() + monoMino.y() + 1)));
        QRectF tempMino(0.0, 0.0, gameManager->_minoQImage[_nowMino._type].width(), gameManager->_minoQImage[_nowMino._type].height());
        painter->drawImage(tempField, gameManager->_minoQImage[_nowMino._type], tempMino);
    }
    painter->restore();
}

void MinosManager::_generateMinos() {
    _generatedMinosList.resize(13);
    for (int index = 0; index < 7; ++index) {
        _generatedMinosList[index + 6] = QRandomGenerator64::global()->generate() % 7 + 1;
        for (int searcher = 0; searcher < index; ++searcher) {
            if (_generatedMinosList[index + 6] == _generatedMinosList[searcher + 6]) {
                index--;
                break;
            }
        }
    }
}

QPoint MinosManager::_detectCollision(unsigned int _type) {
    switch (_type) {
        case MOTION_UP: break;
        case MOTION_RIGHT: break;
        case MOTION_DOWN: break;
        case MOTION_LEFT: break;
        case MOTION_CLOCKWISE: break;
        case MOTION_CONTER_CLOCKWISE: break;
        case MOTION_FLIP: break;
        case MOTION_HORIZONTAL_MIRROR: break;
        case MOTION_VERTICAL_MIRROR: break;
        default: break;
    }
    return QPoint(0, 0);
}

void MinosManager::_getNextMino() {
    qDebug() << "_generatedMinosList.size(): " << _generatedMinosList.size();
    if (_generatedMinosList.size() <= 6) { _generateMinos(); }
    _nowMino._type = _generatedMinosList.takeFirst();
    switch (_nowMino._type) {
        case TYPE_I_MINO:
            _nowMino._state[0] = QPoint(-1, 0);
            _nowMino._state[1] = QPoint(0, 0);
            _nowMino._state[2] = QPoint(1, 0);
            _nowMino._state[3] = QPoint(2, 0);
            break;
        case TYPE_O_MINO:
            _nowMino._state[0] = QPoint(0, -1);
            _nowMino._state[1] = QPoint(1, -1);
            _nowMino._state[2] = QPoint(0, 0);
            _nowMino._state[3] = QPoint(1, 0);
            break;
        case TYPE_T_MINO:
            _nowMino._state[0] = QPoint(0, -1);
            _nowMino._state[1] = QPoint(-1, 0);
            _nowMino._state[2] = QPoint(0, 0);
            _nowMino._state[3] = QPoint(1, 0);
            break;
        case TYPE_S_MINO:
            _nowMino._state[0] = QPoint(0, -1);
            _nowMino._state[3] = QPoint(1, -1);
            _nowMino._state[1] = QPoint(-1, 0);
            _nowMino._state[2] = QPoint(0, 0);
            break;
        case TYPE_Z_MINO:
            _nowMino._state[1] = QPoint(-1, -1);
            _nowMino._state[0] = QPoint(0, -1);
            _nowMino._state[2] = QPoint(0, 0);
            _nowMino._state[3] = QPoint(1, 0);
            break;
        case TYPE_J_MINO:
            _nowMino._state[0] = QPoint(-1, -1);
            _nowMino._state[1] = QPoint(-1, 0);
            _nowMino._state[2] = QPoint(0, 0);
            _nowMino._state[3] = QPoint(1, 0);
            break;
        case TYPE_L_MINO:
            _nowMino._state[1] = QPoint(-1, 0);
            _nowMino._state[2] = QPoint(0, 0);
            _nowMino._state[3] = QPoint(1, 0);
            _nowMino._state[0] = QPoint(1, -1);
            break;
        default: break;
    }
    _nowMino._position    = QPoint(4, -1);
    _nowMino._orientation = MOTION_UP;
    update();
    _dropDownTimer->start();
}

void MinosManager::_moveNowMino(unsigned int _direction, int _value) {
    switch (_direction) {
        case MOTION_UP: _nowMino._position.ry() -= _value; break;
        case MOTION_RIGHT: _nowMino._position.rx() += _value; break;
        case MOTION_DOWN: _nowMino._position.ry() += _value; break;
        case MOTION_LEFT: _nowMino._position.rx() -= _value; break;
        default: break;
    }
    update();
}

void MinosManager::onGameStart(GameManager *_gameManager) {
    qDebug() << "MinoManager received settings signal.";
    gameManager = _gameManager;
    update();
    _dropDownTimer->start();
}

void MinosManager::onDropDown() {
    if (_nowMino._position.y() < gameManager->_rowCount - 1) {
        _nowMino._position.ry()++;
        update();
    }
    _dropDownTimer->start();
}

void MinosManager::onLockDown() {}

void MinosManager::onMinoHold() {}
