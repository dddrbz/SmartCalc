#pragma once

#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>

#include "../count.h"
#include "../credit.h"
#include "../notation.h"
#include "qcustomplot.h"

class SmartCalc : public QWidget {
 public:
  SmartCalc(QWidget *parent = 0);
 private slots:
  void initBasicTab();
  void initBasicCalcLine(QVBoxLayout *vbox);
  void initXLine(QHBoxLayout *hbox, QVBoxLayout *vbox);
  void initBasicTabButtons(QGridLayout *grid, QVBoxLayout *vbox);
  void processBasicButtons();

  void initGraphTab();
  void initGraphCalcLine(QVBoxLayout *vbox);
  void initFunctionScope(QVBoxLayout *vbox);
  void initGraphTabButtons(QGridLayout *grid, QHBoxLayout *ghbox);
  void initGraphSpace(QHBoxLayout *ghbox);
  void drowGraph(char *str);
  void processGraphButtons();

  void initCreditTab();
  void initCreditField(QVBoxLayout *vbox);
  void processAnCalc();
  void processDfCalc();

 private:
  QTabWidget *tabWidget = NULL;

  QWidget *basic = NULL;
  QLineEdit *basicLine = NULL;
  QLineEdit *xLine = NULL;

  QWidget *graph = NULL;
  QLineEdit *graphLine = NULL;
  QCustomPlot *graphSpace = NULL;
  QLineEdit *leftDot = NULL;
  QLineEdit *rightDot = NULL;

  QWidget *credit;
  QLineEdit *sumStr;
  QLineEdit *termStr;
  QLineEdit *rateStr;
  QLabel *creditLbl;

  void transQLineEditToCString(QLineEdit *str, char *result);
};