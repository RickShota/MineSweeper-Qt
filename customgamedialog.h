/**
 * @file customgamedialog.h
 * @brief 自定义游戏难度的弹窗
 * @author RickRone
 * @date 2024.3.14
 * @version Qt 6.7.2
 */
#ifndef CUSTOMGAMEDIALOG_H
#define CUSTOMGAMEDIALOG_H

#include "common.h"

class CustomGameDialog : public QDialog
{
public:
    explicit CustomGameDialog(QWidget *parent = 0);

    QSpinBox *colspinbox; // 列分量框
    QSpinBox *rowspinbox; // 行分量框
    QSpinBox *minenumspinbox; // 雷数分量框
};

#endif // CUSTOMGAMEDIALOG_H
