/**
 * @file minescene.cpp
 * @brief 游戏场景类源文件
 * @author RickRone
 * @date 2024.3.14
 * @version Qt 6.6.2
 */
#include "minescene.h"
#include "mineitem.h"

MineScene::MineScene(QObject *parent)
    : QGraphicsScene(parent)
{
    m_isGameOver = false;
    m_signedMineNum = 0;
    m_rightMineNum = 0;
    m_soundOpen = true;
}

/**
 * @brief MineScene::initscene
 * @details 初始化场景
 */
void MineScene::initscene() {
    qDebug() << "initscene(): in\n";
    // 初始化非雷数
    this->m_remainNoMines = m_sceneRow * m_sceneCol - m_mineNum;
    qDebug() << "initscene(): m_sceneRow =" << m_sceneRow;
    qDebug() << "initscene(): m_sceneCol =" << m_sceneCol;
    // 创建方块并设置雷区
    for(int i = 0; i < m_sceneRow; i++ ) {
        QVector<MineItem *> t_vec;
        for(int j = 0; j < m_sceneCol; j++) {
            MineItem *item = new MineItem(i, j, QPixmap(":/images/init.png"));
            item->setPos(j * MAP_W, i * MAP_H); // 置方块的位置
            this->addItem(item);
            t_vec.push_back(item);
        }
        this->m_itemVec.push_back(t_vec);
    }
    // 随机布雷
    srand(time(NULL));
    for(int k = 0; k < m_mineNum; k++) {
        int randX = rand() % m_sceneRow;
        int randY = rand() % m_sceneCol;

        if (!m_itemVec[randX][randY]->m_isMine) {
            m_itemVec[randX][randY]->m_isMine = true;
            this->countAroundMines(this->m_itemVec[randX][randY]);
        }
    }
    // 连接信号
    for(int i = 0; i < m_sceneRow; i++) {
        for(int j = 0; j < m_sceneCol; j++) {
            // 连接重新开始游戏信号
            connect(
                this->m_itemVec[i][j],
                SIGNAL(sig_restartGame()),
                this,
                SIGNAL(sig_sceneNewGame())
            );
            // 连接重新设置雷数信号
            connect(
                this->m_itemVec[i][j],
                SIGNAL(sig_resetMineNum(int)),
                this,
                SIGNAL(sig_scenedisplayMineNum(int))
            );
        }
    }
}

/**
 * @brief MineScene::countAroundMines
 * @param item
 * @details 统计方块周围的雷数
 */
void MineScene::countAroundMines(MineItem *item) {
    if (item == nullptr || !item->m_isMine)
        return;
    // 遍历周围8个方向的方块，判断是否为雷
    for (int i = 0; i < 8; i++) {
        int t_x = item->m_X + t_around[i].x();
        int t_y = item->m_Y + t_around[i].y();
        if(t_x < 0 || t_x >= this->m_sceneRow || t_y < 0 || t_y >= this->m_sceneCol)
            continue; // 如果超出边界，不统计
        if(m_itemVec[t_x][t_y]->m_isMine)
            continue; // 如果当前方块是雷，不统计
        m_itemVec[t_x][t_y]->m_aroundMineNum++; // 周围方块雷数+1
    }
}

/**
 * @brief MineScene::openAllItems
 * @details 打开所有方块
 */
void MineScene::openAllItems() {
    if(this->m_isGameOver) return;
    for (int i = 0; i < m_sceneRow; i++) {
        for (int j = 0; j < m_sceneCol; j++) {
            m_itemVec[i][j]->m_isOpened = true;
            if(m_itemVec[i][j]->m_isMine) { // 是雷
                m_itemVec[i][j]->setPixmap(QPixmap(":/images/bong.png"));
            } else { // 不是雷
                m_itemVec[i][j]->setPixmap(QPixmap(tr(":/images/") + QString::number(m_itemVec[i][j]->m_aroundMineNum) + tr(".png")));
            }
        }
    }
}

/**
 * @brief MineScene::expendWater
 * @param item
 * @details 用于展开空白区域
 */
void MineScene::expendWater(MineItem *item) {
    if(NULL == item || item->m_isMine) return;
    // 遍历周围8个方向的方块，判断是否可以展开
    for(int i = 0; i < 8; i++) {
        int t_x = item->m_X + t_around[i].x();
        int t_y = item->m_Y + t_around[i].y();
        if(t_x < 0 || t_x >= m_sceneRow || t_y < 0 || t_y >= m_sceneCol) {
            continue; // 如果超出边界，不展开
        } else if(m_itemVec[t_x][t_y]->m_isMine || m_itemVec[t_x][t_y]->m_isOpened) {
            continue; // 如果是雷或已经被打开，不展开
        } else if(m_itemVec[t_x][t_y]->m_rMouseKeyNum > 0) {
            continue; // 如果右键标记了雷，不展开
        }
        // 若满足展开条件，将该方块标记为已打开，更新剩余非雷数
        m_itemVec[t_x][t_y]->m_isOpened = true;
        this->m_remainNoMines--;
        int itemNum = m_itemVec[t_x][t_y]->m_aroundMineNum;
        if(itemNum == 0) { // 如果周围方块是空白，进行递归展开
            expendWater(m_itemVec[t_x][t_y]);
        }
        // 根据周围方块的数字，显示对应的数字图片
        QString path = tr(":/images/") + QString::number(itemNum) + tr(".png");
        m_itemVec[t_x][t_y]->setPixmap(QPixmap(path));
    }
}


