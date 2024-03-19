/**
 * @file customgamedialog.h
 * @brief 自定义游戏难度弹窗头文件
 * @author RickRone
 * @date 2024.3.14
 * @version Qt 6.6.2
 */
#ifndef CUSTOMGAMEDIALOG_H
#define CUSTOMGAMEDIALOG_H

#include "common.h"

class CustomGameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CustomGameDialog(QWidget *parent = 0);

    QSpinBox *colSpinBox; // 列分量框
    QSpinBox *rowSpinBox; // 行分量框
    QSpinBox *mineNumSpinBox; // 雷数分量框
    // 读设置
    void readSettings();
    // 写设置
    void writeSettings();

signals:
    void signal_sendCustomset(int,int,int);
};

#endif // CUSTOMGAMEDIALOG_H
