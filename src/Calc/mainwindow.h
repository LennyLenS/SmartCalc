#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleValidator>
#include <QMainWindow>

#include "graphwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void PushButtonOperation_click();
  void PushButtonPoint_click();
  void PushButtonNum_click();
  void PushButtonFunc_click();
  void PushButtonClear_click();
  void PushButtonDelete_click();
  void PushButtonLeftBracket_click();
  void PushButtonRightBracket_click();
  void PushButtonEqual_click();
  void PushButtonGraph_clock();

 private:
  Ui::MainWindow *ui;
  bool correctExpression = true;
  QDoubleValidator *validator;
  GraphWindow *graphwindow;
};

#endif  // MAINWINDOW_H
