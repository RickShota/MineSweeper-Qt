/**
 * @file minescene.h
 * @brief 游戏场景类头文件
 * @author RickRone
 * @date 2024.3.14
 * @version Qt 6.6.2
 */
#ifndef MINESCENE_H
#define MINESCENE_H

#include "common.h"
#include "mineitem.h"
class MineItem;

class MineScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MineScene(QObject *parent = nullptr);

    QVector< QVector< MineItem *> > m_itemVec; // 存储方块的容器
    int m_sceneRow; // 当前场景行数
    int m_sceneCol; // 当前场景列数
    int m_mineNum; // 当前场景雷数
    int m_crrentLeve;// 当前场景难度级别

    int m_signedMineNum; // 右键标记的雷数
    int m_rightMineNum; // 右键标记正确的雷数
    bool m_isGameOver; // 游戏是否结束
    int m_remainNoMines; // 剩余非雷数
    bool m_soundOpen; // 声音开关

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

    void initscene(); // 初始化游戏场景
    void countAroundMines(MineItem *t_item); // 统计方块周围的雷数
    void openAllItems(); // 打开所有的方块
    void expendWater(MineItem *t_item); // 扩散函数
signals:
    void sig_successPassGame(); // 游戏成功过关信号
    void sig_sceneNewGame(); // 重新开始游戏信号
    void sig_scenedisplayMineNum(int); // 显示雷数信号
private:
    // 实现信号


};

#endif // MINESCENE_H
