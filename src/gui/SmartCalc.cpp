#include "SmartCalc.h"

SmartCalc::SmartCalc(QWidget *parent) : QWidget(parent) {
  tabWidget = new QTabWidget(this);

  tabWidget->setTabPosition(QTabWidget::North);
  tabWidget->setGeometry(0, 0, 850, 500);

  basic = new QWidget;
  graph = new QWidget;
  credit = new QWidget;

  tabWidget->addTab(basic, "Basic");
  initBasicTab();

  tabWidget->addTab(graph, "Graph");
  initGraphTab();

  tabWidget->addTab(credit, "Credit");
  initCreditTab();
}

void SmartCalc::initBasicTab() {
  QGridLayout *grid = new QGridLayout();
  QHBoxLayout *hbox = new QHBoxLayout();
  QVBoxLayout *vbox = new QVBoxLayout(basic);

  initBasicCalcLine(vbox);
  initXLine(hbox, vbox);
  initBasicTabButtons(grid, vbox);
}

void SmartCalc::initBasicCalcLine(QVBoxLayout *vbox) {
  basicLine = new QLineEdit("", basic);
  basicLine->setMaxLength(260);
  basicLine->setFixedSize(825, 50);
  basicLine->setAlignment(Qt::AlignRight);
  basicLine->installEventFilter(basic);
  QFont lineFont = basicLine->font();
  lineFont.setPointSize(20);
  basicLine->setFont(lineFont);
  vbox->addWidget(basicLine, 1, Qt::AlignLeft);
}

void SmartCalc::initXLine(QHBoxLayout *hbox, QVBoxLayout *vbox) {
  xLine = new QLineEdit("", basic);
  xLine->setMaxLength(60);
  xLine->setFixedSize(200, 40);
  xLine->setAlignment(Qt::AlignRight);
  xLine->installEventFilter(basic);
  QFont xFont = xLine->font();
  xFont.setPointSize(16);
  xLine->setFont(xFont);
  hbox->addWidget(xLine, 0);

  QLabel *xLabel = new QLabel(" = X");
  xLabel->setStyleSheet("QLabel {color: rgb(105, 105, 105)}");
  QFont xLFont = xLabel->font();
  xLFont.setPointSize(16);
  xLabel->setFont(xLFont);
  hbox->addWidget(xLabel, 1, Qt::AlignLeft);

  QLabel *SCalc = new QLabel("SmartCalcDrowzeeh  ");
  SCalc->setStyleSheet("QLabel {color: rgb(128, 128, 128)}");
  QFont SCFont = SCalc->font();
  SCFont.setPointSize(20);
  SCalc->setFont(SCFont);
  hbox->addWidget(SCalc, 1, Qt::AlignRight);

  vbox->addLayout(hbox);
}

void SmartCalc::initBasicTabButtons(QGridLayout *grid, QVBoxLayout *vbox) {
  QList<QString> values({"cos",  "sin",  "tan",  "7", "8", "9", "+", "C",
                         "acos", "asin", "atan", "4", "5", "6", "-", "CA",
                         "sqrt", "mod",  "^",    "1", "2", "3", "*", "x",
                         "ln",   "log",  ".",    "(", ")", "0", "/", "="});
  QPushButton *btn = NULL;

  int pos = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 8; ++j) {
      btn = new QPushButton(values[pos], basic);
      btn->setFixedSize(100, 80);
      if ((values[pos] == "C") || (values[pos] == "CA") ||
          (values[pos] == "=")) {
        btn->setStyleSheet(
            "QPushButton {background-color: rgb(128, 128, 128); font: 14pt}");
      } else {
        btn->setStyleSheet(
            "QPushButton {background-color: rgb(169, 169, 169); font: 14pt}");
      }
      grid->addWidget(btn, i, j, Qt::AlignTop);
      connect(btn, &QPushButton::clicked, this,
              &SmartCalc::processBasicButtons);
      ++pos;
    }
  }
  vbox->addLayout(grid, 1);
}

void SmartCalc::processBasicButtons() {
  QString button = ((QPushButton *)sender())->text();
  if (button == "=") {
    if (basicLine->text().length() >= 1) {
      double number = 0;
      char notation[261] = {0};
      char result[400] = {0};
      transQLineEditToCString(basicLine, notation);
      if (!translate_notation(notation, result)) {
        basicLine->setText("INPUT ERROR: TRY AGAIN");
      } else {
        QString num;
        char x[61] = {0};
        transQLineEditToCString(xLine, x);
        if (!check_x_string(x)) {
          basicLine->setText("INPUT X ERROR: TRY AGAIN");
        } else {
          double xNumber = atof(x);
          calculate_expression(result, &number, xNumber);
          basicLine->setText(num.setNum(number, 'f', 7));
        }
      }
    }
  } else if (button == "C") {
    if (basicLine->text().length()) {
      QString text = basicLine->text();
      text.chop(1);
      basicLine->setText(text);
    }
  } else if (button == "CA") {
    basicLine->setText("");
    xLine->setText("");
  } else {
    if ((button.count() > 1) && (button != "mod")) {
      button.append("(");
    }
    basicLine->setText(basicLine->text().append(button));
  }
}

void SmartCalc::initGraphTab() {
  QGridLayout *grid = new QGridLayout();
  QHBoxLayout *ghbox = new QHBoxLayout();
  QVBoxLayout *vbox = new QVBoxLayout(graph);
  initGraphCalcLine(vbox);
  initFunctionScope(vbox);
  initGraphTabButtons(grid, ghbox);
  initGraphSpace(ghbox);
  vbox->addLayout(ghbox);
}

void SmartCalc::initGraphCalcLine(QVBoxLayout *vbox) {
  graphLine = new QLineEdit("", basic);
  graphLine->setMaxLength(260);
  graphLine->setFixedSize(825, 50);
  graphLine->setAlignment(Qt::AlignRight);
  graphLine->installEventFilter(basic);
  QFont lineFont = graphLine->font();
  lineFont.setPointSize(20);
  graphLine->setFont(lineFont);
  vbox->addWidget(graphLine, 1, Qt::AlignLeft);
}

void SmartCalc::initFunctionScope(QVBoxLayout *vbox) {
  QHBoxLayout *hbox = new QHBoxLayout();

  QLabel *funcScope = new QLabel("X -> ");
  funcScope->setStyleSheet("QLabel {color: rgb(105, 105, 105)}");
  QFont scopeFont = funcScope->font();
  scopeFont.setPointSize(16);
  funcScope->setFont(scopeFont);
  hbox->addWidget(funcScope, 0);

  leftDot = new QLineEdit("", graph);
  leftDot->setMaxLength(60);
  leftDot->setFixedSize(150, 30);
  leftDot->setAlignment(Qt::AlignRight);
  leftDot->installEventFilter(graph);
  QFont dotFont = leftDot->font();
  dotFont.setPointSize(12);
  leftDot->setFont(dotFont);
  hbox->addWidget(leftDot, 0);

  QLabel *comma = new QLabel(" ,  Y -> ");
  comma->setStyleSheet("QLabel {color: rgb(105, 105, 105)}");
  comma->setFont(scopeFont);
  hbox->addWidget(comma, 0);

  rightDot = new QLineEdit("", graph);
  rightDot->setMaxLength(60);
  rightDot->setFixedSize(150, 30);
  rightDot->setAlignment(Qt::AlignRight);
  rightDot->installEventFilter(graph);
  rightDot->setFont(dotFont);
  hbox->addWidget(rightDot, 1, Qt::AlignLeft);

  vbox->addLayout(hbox);
}

void SmartCalc::initGraphTabButtons(QGridLayout *grid, QHBoxLayout *ghbox) {
  QList<QString> values({"C",  "CA",  "x",    "=",   "cos", "acos", "sqrt",
                         "ln", "sin", "asin", "mod", "log", "tan",  "atan",
                         "^",  "+",   "7",    "8",   "9",   "-",    "4",
                         "5",  "6",   "*",    "1",   "2",   "3",    "/",
                         "(",  ")",   "0",    "."});
  QPushButton *btn = NULL;

  int pos = 0;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 4; ++j) {
      btn = new QPushButton(values[pos], basic);
      btn->setFixedSize(60, 40);
      if ((values[pos] == "C") || (values[pos] == "CA") ||
          (values[pos] == "=")) {
        btn->setStyleSheet(
            "QPushButton {background-color: rgb(128, 128, 128); font: 10pt}");
      } else {
        btn->setStyleSheet(
            "QPushButton {background-color: rgb(169, 169, 169); font: 10pt}");
      }
      grid->addWidget(btn, i, j, Qt::AlignTop);
      connect(btn, &QPushButton::clicked, this,
              &SmartCalc::processGraphButtons);
      ++pos;
    }
  }
  ghbox->addLayout(grid, 1);
}

void SmartCalc::initGraphSpace(QHBoxLayout *ghbox) {
  graphSpace = new QCustomPlot();
  ghbox->addWidget(graphSpace);
}

void SmartCalc::drowGraph(char *str) {
  QVector<double> x, y;
  char xScope[61] = {0};
  char yScope[61] = {0};

  transQLineEditToCString(leftDot, xScope);
  transQLineEditToCString(rightDot, yScope);
  if (xScope[0] && yScope[0] && check_x_string(xScope) &&
      check_x_string(yScope)) {
    double xMax, yMax;
    xMax = fabs(atof(xScope));
    yMax = fabs(atof(yScope));
    double h = 2.0 * xMax / 100.0;
    graphSpace->xAxis->setRange(-xMax, xMax);
    graphSpace->yAxis->setRange(-yMax, yMax);
    for (double X = -xMax; X <= xMax; X += h) {
      double Y;
      calculate_expression(str, &Y, X);
      x.push_back(X);
      y.push_back(Y);
    }
    graphSpace->addGraph();
    graphSpace->graph(0)->addData(x, y);
    graphSpace->replot();
    graphSpace->graph(0)->data()->clear();
  } else {
    graphLine->setText("INPUT SCOPE ERROR: TRY AGAIN");
  }
}

void SmartCalc::processGraphButtons() {
  QString button = ((QPushButton *)sender())->text();
  if (button == "=") {
    if (graphLine->text().length() >= 1) {
      char notation[261] = {0};
      char result[261] = {0};
      transQLineEditToCString(graphLine, notation);
      if (!translate_notation(notation, result)) {
        graphLine->setText("INPUT ERROR: TRY AGAIN");
      } else {
        drowGraph(result);
      }
    }
  } else if (button == "C") {
    if (graphLine->text().length()) {
      QString text = graphLine->text();
      text.chop(1);
      graphLine->setText(text);
    }
  } else if (button == "CA") {
    graphLine->setText("");
    leftDot->setText("");
    rightDot->setText("");
  } else {
    if ((button.count() > 1) && (button != "mod")) {
      button.append("(");
    }
    graphLine->setText(graphLine->text().append(button));
  }
}

void SmartCalc::initCreditTab() {
  QVBoxLayout *vbox = new QVBoxLayout(credit);

  initCreditField(vbox);
}

void SmartCalc::initCreditField(QVBoxLayout *vbox) {
  QHBoxLayout *sumHbox = new QHBoxLayout();
  QLabel *sumLbl = new QLabel("Credit amount: ");
  sumStr = new QLineEdit();
  sumStr->setMaxLength(60);
  QLabel *rubLbl = new QLabel(" RUB.");
  sumHbox->addWidget(sumLbl, 1, Qt::AlignRight);
  sumHbox->addWidget(sumStr, 1);
  sumHbox->addWidget(rubLbl, 1);

  QHBoxLayout *termHbox = new QHBoxLayout();
  QLabel *termLbl = new QLabel("Credit term: ");
  termStr = new QLineEdit();
  termStr->setMaxLength(60);
  QLabel *monthLbl = new QLabel(" months.");
  termHbox->addWidget(termLbl, 1, Qt::AlignRight);
  termHbox->addWidget(termStr, 1);
  termHbox->addWidget(monthLbl, 1);

  QHBoxLayout *rateHbox = new QHBoxLayout();
  QLabel *rateLbl = new QLabel("Interest rate: ");
  rateStr = new QLineEdit();
  rateStr->setMaxLength(60);
  QLabel *perLbl = new QLabel(" %");
  rateHbox->addWidget(rateLbl, 1, Qt::AlignRight);
  rateHbox->addWidget(rateStr, 1);
  rateHbox->addWidget(perLbl, 1);

  QHBoxLayout *btnHbox = new QHBoxLayout();
  QPushButton *calcAn = new QPushButton("Annuity");
  connect(calcAn, &QPushButton::clicked, this, &SmartCalc::processAnCalc);
  btnHbox->addWidget(calcAn, 0, Qt::AlignTop);

  QPushButton *calcDf = new QPushButton("Differentiated");
  connect(calcDf, &QPushButton::clicked, this, &SmartCalc::processDfCalc);
  btnHbox->addWidget(calcDf, 0, Qt::AlignTop);

  creditLbl = new QLabel("");

  vbox->addLayout(sumHbox, 0);
  vbox->addLayout(termHbox, 0);
  vbox->addLayout(rateHbox, 0);
  vbox->addLayout(btnHbox, 0);
  vbox->addWidget(creditLbl, 0, Qt::AlignHCenter | Qt::AlignTop);
}

void SmartCalc::processAnCalc() {
  char sumCStr[61] = {0};
  char termCStr[61] = {0};
  char rateCStr[61] = {0};

  transQLineEditToCString(sumStr, sumCStr);
  transQLineEditToCString(termStr, termCStr);
  transQLineEditToCString(rateStr, rateCStr);
  if (check_x_string(sumCStr) && check_x_string(termCStr) &&
      check_x_string(rateCStr)) {
    if (sumCStr[0] && termCStr[0] && rateCStr[0]) {
      double sum = fabs(atof(sumCStr));
      double term = fabs(atof(termCStr));
      double rate = fabs(atof(rateCStr));

      QString num;
      num.setNum(calc_annuity_payment(sum, term, rate), 'f', 2);
      QString str = "Monthly payment: " + num + ";   ";
      num.setNum(calc_annuity_overpayment(sum, term, rate), 'f', 2);
      str += "Overpayment on a loan: " + num + ";   ";
      num.setNum(calc_annuity_pay(sum, term, rate), 'f', 2);
      str += "Total payment: " + num + ";";
      creditLbl->setText(str);
    } else {
      creditLbl->setText("INPUT ERROR");
    }
  } else {
    creditLbl->setText("INPUT ERROR");
  }
}

void SmartCalc::processDfCalc() {
  char sumCStr[61] = {0};
  char termCStr[61] = {0};
  char rateCStr[61] = {0};

  transQLineEditToCString(sumStr, sumCStr);
  transQLineEditToCString(termStr, termCStr);
  transQLineEditToCString(rateStr, rateCStr);
  if (check_x_string(sumCStr) && check_x_string(termCStr) &&
      check_x_string(rateCStr)) {
    if (sumCStr[0] && termCStr[0] && rateCStr[0]) {
      double sum = fabs(atof(sumCStr));
      double term = fabs(atof(termCStr));
      double rate = fabs(atof(rateCStr));

      QString num;
      num.setNum(calc_differentiated_payment(sum, term, rate, 1), 'f', 2);
      QString str = "Monthly payment: " + num + " ... ";
      num.setNum(calc_differentiated_payment(sum, term, rate, term), 'f', 2);
      str += num + ";   ";
      num.setNum(calc_differentiated_overpayment(sum, term, rate), 'f', 2);
      str += "Overpayment on a loan: " + num + ";   ";
      num.setNum(calc_differentiated_pay(sum, term, rate), 'f', 2);
      str += "Total payment: " + num + ";";
      creditLbl->setText(str);
    } else {
      creditLbl->setText("INPUT ERROR");
    }
  } else {
    creditLbl->setText("INPUT ERROR");
  }
}

void SmartCalc::transQLineEditToCString(QLineEdit *str, char *result) {
  std::string buffer = str->text().toUtf8().constData();
  strcpy(result, buffer.c_str());
  buffer.clear();
}