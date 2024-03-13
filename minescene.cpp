#include "minescene.h"

MineScene::MineScene(QObject *parent)
    : QGraphicsScene(parent)
{
    m_isGameOver = false;
    m_signedMineNum = 0;
    m_rightMineNum = 0;
    m_soundOpen = true;
}
// 初始化场景
void MineScene::initscene() {
    // 初始化非雷数
    m_remainNoMines = m_sceneRow * m_sceneCol - m_mineNum;
    QVector<MineItem *> itemRow;
    // 创建方块并设置雷区
    for(int i = 0; i < m_sceneCol; i++ ) {
        itemRow.clear();
        for(int j = 0; j < m_sceneRow; j++) {
            QPixmap itemPixMap(":/images/init.png");
            MineItem *item = new MineItem(i, j, itemPixMap);
            item->setPos(i * MAP_W, j * MAP_H); // 置方块的位置
            itemRow.append(item);
            addItem(item);
            // 连接重新开始游戏信号
            connect(item,SIGNAL(sig_restartGame()), this, SIGNAL(sig_sceneNewGame()));
            // 连接重新设置雷数信号
            connect(item,SIGNAL(sig_resetMineNum()), this, SIGNAL(sig_scenedisplayMineNum()));
        }
        this->m_itemVec.append(itemRow);
    }
    // 随机布雷
    for(int k = 0; k < m_mineNum; k++) {
        int randX = rand() % m_sceneRow;
        int randY = rand() % m_sceneCol;

        if (!m_itemVec[randX][randY]->m_isMine) {
            m_itemVec[randX][randY]->m_isMine = true;
            this->countAroundMines(this->m_itemVec[randX][randY]);
        } else {
            k--;
        }
    }
}
// 统计方块周围的雷数
void MineScene::countAroundMines(MineItem *item) {
    if (item == nullptr || !item->m_isMine) {
        return;
    }
    int row = item->m_X;
    int col = item->m_Y;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i < 0 || i >= m_sceneRow || j < 0 || j >= m_sceneCol) {
                continue; // 越界，继续下一次循环
            }
            if (m_itemVec[i][j]->m_isMine) {
                continue; // 找到雷，继续下一次循环
            }
            m_itemVec[i][j]->m_aroundMineNum++;
        }
    }
}
// 打开所有方块
void MineScene::openAllItems() {
    int row = m_sceneRow;
    int col = m_sceneCol;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            MineItem *itemTemp = m_itemVec[i][j];
            itemTemp->m_isOpened = true;
            if(itemTemp->m_isMine) { // 是雷
                itemTemp->setPixmap(QPixmap(":/images/bong.png"));
            } else {
                itemTemp->setPixmap(QPixmap(tr(":/images/") + QString::number(itemTemp->m_aroundMineNum) + tr(".png")));
            }
        }
    }
}

// 扩散
void MineScene::expendWater(MineItem *item) {
    if(NULL == item || item->m_isMine) return;
    for(int i = 0; i < 8; i++) {
        int t_x = item->m_X + t_around[i].x();
        int t_y = item->m_Y + t_around[i].y();
        if(t_x < 0 || t_x >= m_sceneRow || t_y < 0 || t_y >= m_sceneCol) {
            continue;
        } else if(m_itemVec[t_x][t_y]->m_isMine || m_itemVec[t_x][t_y]->m_isOpened) {
            continue;
        } else if(m_itemVec[t_x][t_y]->m_rMouseKeyNum > 0) {
            continue;
        }
        // 设置所找方块已打开
        m_itemVec[t_x][t_y]->m_isOpened = true;
        this->m_remainNoMines--;
        int itemNum = m_itemVec[t_x][t_y]->m_aroundMineNum;
        if(itemNum == 0) { // 递归查找
            expendWater(m_itemVec[t_x][t_y]);
        }
        QString path = tr(":/images/") + QString::number(itemNum) + tr(".png");
        m_itemVec[t_x][t_y]->setPixmap(QPixmap(path));
    }
}

void MineScene::sig_successPassGame()
{
    qDebug() << "sig_successPassGame\n";
}
