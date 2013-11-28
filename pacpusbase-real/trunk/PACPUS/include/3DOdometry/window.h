#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QFont>
#include <QLCDNumber>
#include <QPushButton>
#include <QSlider>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QWidget>

class window : public QWidget
{
 public:
   QLCDNumber *lcd;
	 QCheckBox  *Ckbx_lidarlayer;
	 QCheckBox  *Ckbx_tracks;

	 window(QWidget *parent = 0);
};
#endif
