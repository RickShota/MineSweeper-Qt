#include "mineitem.h"
#include "minescene.h"
// 游戏方块类
MineItem::MineItem(int t_x, int t_y, QPixmap itemPixMap, QGraphicsItem *p)
    : QGraphicsPixmapItem(itemPixMap, p), m_X(t_x), m_Y(t_y)
{
    m_isMine = false;
    m_isOpened = false;
    m_aroundMineNum = 0;
    m_rMouseKeyNum = 0;
    m_isRMouse = false;
}

// 根据右键点击次数修改方块状态
void MineItem::mousePressEvent(QGraphicsSceneMouseEvent *e) {
    if(e->button() == Qt::LeftButton)
        leftClick();
    else if(e->button() == Qt::RightButton)
        rightClick();
}
// 左击开雷
void MineItem::leftClick() {
    // 获取当前场景
    MineScene *mineScene = (MineScene *)this->scene();
    // 游戏结束||方块已打开
    if(mineScene->m_isGameOver || this->m_isOpened) return;
    // 方块已被右击1次
    if(this->m_rMouseKeyNum == 1) return;
    m_isOpened = true;
    // 打开后的情形
    if(m_isMine) {
        // 设置图片
        this->setPixmap(QPixmap(":/images/bong.png"));
        // 播放声音
        if(mineScene->m_soundOpen) {
            playSound(":/sounds/bong.wav");
        }
        // 打开所有方块
        mineScene->openAllItems();
        mineScene->m_isGameOver = true;
        QMessageBox::information((QWidget*)mineScene->parent(), tr("扫雷失败"), "扫雷失败，恭喜踩雷", QMessageBox::Ok);
        emit sig_restartGame(); // 发送重开信号
        return;
    } else {
        if(!m_aroundMineNum) { // 周围没雷
            this->setPixmap(QPixmap(":/images/0.png"));
            mineScene->expendWater(this); // 扩散
        } else { // 周围有雷
            QString path = tr(":/images/") + QString::number(m_aroundMineNum) + tr(".png");
            this->setPixmap(QPixmap(path));
        }
        // 将场景非雷数-1
        mineScene->m_remainNoMines--;
        if(mineScene->m_remainNoMines == 0) { // 剩余雷为0则胜利
            if(mineScene->m_soundOpen) {
                playSound(":/sounds/win.wav");
            }
            mineScene->openAllItems();
            mineScene->m_isGameOver = true;
            emit mineScene->sig_successPassGame(); // 发送成功信号
        }
    }
}
// 右击标记
void MineItem::rightClick() {
    MineScene *mineScene = (MineScene *)this->scene();
    // 游戏结束||方块已打开
    if(mineScene->m_isGameOver || this->m_isOpened) return;
    if(mineScene->m_soundOpen) {
        playSound(":/sounds/time.wav");
    }
    m_rMouseKeyNum++;
    if(m_rMouseKeyNum == 1) { // 标记旗帜
        m_isRMouse = true;
        mineScene->m_signedMineNum++; // 标记雷数+1
        this->setPixmap(QPixmap(":/images/flag.png"));
        emit this->sig_resetMineNum(mineScene->m_signedMineNum); // 发送重设雷数信号
        if(this->m_isMine) { // 若方块是雷，正确标记+1
            mineScene->m_rightMineNum++;
        }
    } else if(m_rMouseKeyNum == 2) { // 标记问号
        m_isRMouse = true;
        mineScene->m_signedMineNum--; // 标记雷数-1
        this->setPixmap(QPixmap(":/images/question.png"));
        emit sig_resetMineNum(mineScene->m_signedMineNum);
        if(this->m_isMine) { // 若方块是雷，正确标记+1
            mineScene->m_rightMineNum++;
        }
    } else if(m_rMouseKeyNum == 3) { // 取消标记
        m_isRMouse = false;
        this->setPixmap(QPixmap(":/images/init.png"));
        m_rMouseKeyNum = 0;
    }
}

