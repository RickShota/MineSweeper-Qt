#include "minescene.h"

MineScene::MineScene(QObject *parent)
    : QGraphicsScene(parent)
{}

void MineScene::initscene() {}
void MineScene::countAroundMines(MineItem *t_item) {}
void MineScene::openAllItems() {}
void MineScene::expendWater(MineItem *t_item) {}

void MineScene::sig_successPassGame()
{
    qDebug() << "sig_successPassGame\n";
}
