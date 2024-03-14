/**
 * @file mianitem.h
 * @brief 游戏方块类
 * @author RickRone
 * @date 2024.3.14
 * @version Qt 6.7.2
 */
#ifndef MINEITEM_H
#define MINEITEM_H

#include "common.h"
#include "minescene.h"

class MineItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit MineItem(int t_x, int t_y, QPixmap itemPixMap, QGraphicsItem *p = 0);
    int m_X; // 在容器中的行数
    int m_Y; // 在容器中的列数
    bool m_isMine; // 是否为雷
    bool m_isOpened; // 是否打开
    int m_aroundMineNum; // 周围雷数
    int m_rMouseKeyNum; // 右键点击的次数
    bool m_isRMouse;

    QPoint t_around[8] = {
        QPoint(-1,-1),
        QPoint(-1,0),
        QPoint(-1,1),
        QPoint(0,-1),
        QPoint(0,1),
        QPoint(1,-1),
        QPoint(1,0),
        QPoint(1,1)
    };

    void leftClick(); // 左击
    void rightClick(); // 右击
    // 鼠标点击事件
    void mousePressEvent(QGraphicsSceneMouseEvent *e) override;
signals:
    void sig_restartGame(); // 重开
    void sig_resetMineNum(int t_signedMineNum); // 重设雷数


public slots:


};

#endif // MINEITEM_H
