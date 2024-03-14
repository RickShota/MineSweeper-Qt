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
// 初始化场景
void MineScene::initscene() {
    qDebug() << "initscene(): in\n";
    // 初始化非雷数
    this->m_remainNoMines = m_sceneRow * m_sceneCol - m_mineNum;
    qDebug() << "initscene(): m_sceneRow=" << m_sceneRow << "\n";
    qDebug() << "initscene(): m_sceneCol=" << m_sceneCol << "\n";
    // 创建方块并设置雷区
    for(int i = 0; i < m_sceneRow; i++ ) {
        QVector<MineItem *> t_vec;
        for(int j = 0; j < m_sceneCol; j++) {
            MineItem *item = new MineItem(i, j, QPixmap(":/images/init.png"));
            item->setPos(j * MAP_H, i * MAP_W); // 置方块的位置
            this->addItem(item);
            t_vec.push_back(item);
        }
        this->m_itemVec.push_back(t_vec);
    }
    qDebug() << "initscene(): setItem\n";
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
    qDebug() << "initscene(): setMine\n";
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
    qDebug() << "initscene(): connect signal\n";
}
// 统计方块周围的雷数
void MineScene::countAroundMines(MineItem *item) {
    if (item == nullptr || !item->m_isMine) {
        return;
    }
    for (int i = 0; i < 8; i++) {
        int t_x = item->m_X + t_around[i].x();
        int t_y = item->m_Y + t_around[i].y();
        if(t_x < 0 || t_x >= this->m_sceneRow || t_y < 0 || t_y >= this->m_sceneCol)
            continue;
        if(m_itemVec[t_x][t_y]->m_isMine)
            continue;
        m_itemVec[t_x][t_y]->m_aroundMineNum++;
    }
}
// 打开所有方块
void MineScene::openAllItems() {
    if(this->m_isGameOver) return;
    for (int i = 0; i < m_sceneRow; i++) {
        for (int j = 0; j < m_sceneRow; j++) {
            m_itemVec[i][j]->m_isOpened = true;
            if(m_itemVec[i][j]->m_isMine) { // 是雷
                m_itemVec[i][j]->setPixmap(QPixmap(":/images/bong.png"));
            } else {
                m_itemVec[i][j]->setPixmap(QPixmap(tr(":/images/") + QString::number(m_itemVec[i][j]->m_aroundMineNum) + tr(".png")));
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


