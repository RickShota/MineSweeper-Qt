/**
 * @file herodialog.h
 * @brief 排行榜弹窗
 * @author RickRone
 * @date 2024.3.14
 * @version Qt 6.6.2
 */
#ifndef HERODIALOG_H
#define HERODIALOG_H

#include "common.h"

class HeroDialog : public QDialog
{
    Q_OBJECT
public:
    explicit HeroDialog(QWidget *parent = 0);

    QLabel *lowrecordtimelabel;         //初级纪录时间
    QLabel *middlerecordtimelabel;      //中级纪录时间
    QLabel *heightrecordtimelabel;      //高级纪录时间
    QLabel *minerecordtimelabel;

    QLabel *lowrecordnamelabel;         //初级纪录姓名
    QLabel *middlerecordnamelabel;      //中级纪录姓名
    QLabel *heightrecordnamelabel;      //高级纪录姓名
    QLabel *minerecordnamelabel;

    // 读取
    void readSettings();
    // 初始化数据
    void initHeroRecord();

public slots:
    // 重新设置英雄榜数据
    void slot_reset();

};

#endif // HERODIALOG_H
