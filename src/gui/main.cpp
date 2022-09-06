#include "SmartCalc.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  SmartCalc window;

  window.move(600, 600);
  window.setWindowTitle("Calc buttons");
  window.setWindowIcon(QIcon("./source/icon.png"));
  window.setStyleSheet("background-color: rgb(192, 192, 192)");
  window.show();

  return app.exec();
}
