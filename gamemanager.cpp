#include "gamemanager.h"

GameManager::GameManager(QQuickItem *parent) : QQuickItem(parent) {
    qDebug() << "Constructing GameManager...";

    QSettings qSettings;
    _frameThickness = qSettings.value("QtMino_FrameThickness", 10).toUInt();
    _data.reserve(_frameThickness * 2);
    _occupancy.reserve(_frameThickness * 2);
    _minoQImage.resize(255);

    qDebug() << "GameManager Constructed.";
}

void GameManager::loadSettings() {
    qDebug() << "Loading settings...";

    QSettings qSettings;

    _rowCount       = qSettings.value("QtMino_FieldHeight", 20).toUInt();
    _columnCount    = qSettings.value("QtMino_FieldWidth", 10).toUInt();
    _uiScale        = qSettings.value("QtMino_uiScale", 0.8).toDouble();
    _frameThickness = qSettings.value("QtMino_FrameThickness", 10.0).toDouble();

    _screenHeight = height();
    _screenWidth  = width();

    if (_screenHeight * _columnCount >= _screenWidth * _rowCount) {
        _fieldWidth     = _screenWidth * _uiScale - _frameThickness * 2.0;
        _fieldHeight    = _fieldWidth * static_cast<double>(_rowCount) / static_cast<double>(_columnCount);
        _frameWidth     = _fieldWidth + _frameThickness;
        _frameHeight    = _fieldHeight + _frameThickness;
        _minoEdgeLength = _fieldWidth / static_cast<double>(_columnCount);
    } else {
        _fieldHeight    = _screenHeight * _uiScale - _frameThickness * 2.0;
        _fieldWidth     = _fieldHeight * static_cast<double>(_columnCount) / static_cast<double>(_rowCount);
        _frameHeight    = _fieldHeight + _frameThickness;
        _frameWidth     = _fieldWidth + _frameThickness;
        _minoEdgeLength = _fieldHeight / static_cast<double>(_rowCount);
    }

    QVector<int> tempLineData(_columnCount, TYPE_AIR);
    _data.fill(tempLineData, _rowCount);

    QBitArray tempLineOccupancy(_columnCount);
    _occupancy.fill(tempLineOccupancy, _rowCount);

    _minoQImage[TYPE_AIR].load(":/skins/normal/transparent.png");
    _minoQImage[TYPE_I_MINO].load(":/skins/normal/skyblue.png");
    _minoQImage[TYPE_O_MINO].load(":/skins/normal/yellow.png");
    _minoQImage[TYPE_T_MINO].load(":/skins/normal/pink.png");
    _minoQImage[TYPE_S_MINO].load(":/skins/normal/green.png");
    _minoQImage[TYPE_Z_MINO].load(":/skins/normal/red.png");
    _minoQImage[TYPE_J_MINO].load(":/skins/normal/blue.png");
    _minoQImage[TYPE_L_MINO].load(":/skins/normal/orange.png");
    _minoQImage[TYPE_TRASH].load(":/skins/normal/gray.png");
    _minoQImage[TYPE_WALL].load(":/skins/normal/lightgray.png");
    _minoQImage[TYPE_HOLO].load(":/skins/normal/holo.png");

    qDebug() << "settings loaded.";
}

void GameManager::exportSettings() {
    qDebug() << "GameManager emited settings signal.";
    emit gameStart(this);
}
