#include "mainwindow.h"

#include "ui_mainwindow.h"
extern "C" {
#include "../polish.h"
#include "validator.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->Button_0, SIGNAL(clicked()), this, SLOT(PushButtonNum_click()));
  connect(ui->Button_1, SIGNAL(clicked()), this, SLOT(PushButtonNum_click()));
  connect(ui->Button_2, SIGNAL(clicked()), this, SLOT(PushButtonNum_click()));
  connect(ui->Button_3, SIGNAL(clicked()), this, SLOT(PushButtonNum_click()));
  connect(ui->Button_4, SIGNAL(clicked()), this, SLOT(PushButtonNum_click()));
  connect(ui->Button_5, SIGNAL(clicked()), this, SLOT(PushButtonNum_click()));
  connect(ui->Button_6, SIGNAL(clicked()), this, SLOT(PushButtonNum_click()));
  connect(ui->Button_7, SIGNAL(clicked()), this, SLOT(PushButtonNum_click()));
  connect(ui->Button_8, SIGNAL(clicked()), this, SLOT(PushButtonNum_click()));
  connect(ui->Button_9, SIGNAL(clicked()), this, SLOT(PushButtonNum_click()));

  connect(ui->Button_cos, SIGNAL(clicked()), this,
          SLOT(PushButtonFunc_click()));
  connect(ui->Button_sin, SIGNAL(clicked()), this,
          SLOT(PushButtonFunc_click()));
  connect(ui->Button_tan, SIGNAL(clicked()), this,
          SLOT(PushButtonFunc_click()));
  connect(ui->Button_acos, SIGNAL(clicked()), this,
          SLOT(PushButtonFunc_click()));
  connect(ui->Button_asin, SIGNAL(clicked()), this,
          SLOT(PushButtonFunc_click()));
  connect(ui->Button_atan, SIGNAL(clicked()), this,
          SLOT(PushButtonFunc_click()));
  connect(ui->Button_sqrt, SIGNAL(clicked()), this,
          SLOT(PushButtonFunc_click()));
  connect(ui->Button_ln, SIGNAL(clicked()), this, SLOT(PushButtonFunc_click()));
  connect(ui->Button_log, SIGNAL(clicked()), this,
          SLOT(PushButtonFunc_click()));

  connect(ui->Button_mul, SIGNAL(clicked()), this,
          SLOT(PushButtonOperation_click()));
  connect(ui->Button_div, SIGNAL(clicked()), this,
          SLOT(PushButtonOperation_click()));
  connect(ui->Button_minus, SIGNAL(clicked()), this,
          SLOT(PushButtonOperation_click()));
  connect(ui->Button_pow, SIGNAL(clicked()), this,
          SLOT(PushButtonOperation_click()));
  connect(ui->Button_plus, SIGNAL(clicked()), this,
          SLOT(PushButtonOperation_click()));
  connect(ui->Button_mod, SIGNAL(clicked()), this,
          SLOT(PushButtonOperation_click()));

  connect(ui->Button_c, SIGNAL(clicked()), this, SLOT(PushButtonClear_click()));
  connect(ui->Button_delete, SIGNAL(clicked()), this,
          SLOT(PushButtonDelete_click()));

  connect(ui->Button_point, SIGNAL(clicked()), this,
          SLOT(PushButtonPoint_click()));
  connect(ui->Button_x, SIGNAL(clicked()), this, SLOT(PushButtonNum_click()));
  connect(ui->Button_equal, SIGNAL(clicked()), this,
          SLOT(PushButtonEqual_click()));

  connect(ui->Button_left_bracket, SIGNAL(clicked()), this,
          SLOT(PushButtonLeftBracket_click()));
  connect(ui->Button_right_bracket, SIGNAL(clicked()), this,
          SLOT(PushButtonRightBracket_click()));

  connect(ui->Button_graph, SIGNAL(clicked()), this,
          SLOT(PushButtonGraph_clock()));
  validator = new QDoubleValidator;
  ui->y_min_value->setValidator(validator);
  ui->y_max_value->setValidator(validator);
  ui->x_min_value->setValidator(validator);
  ui->x_max_value->setValidator(validator);
  ui->x_value->setValidator(validator);
}

MainWindow::~MainWindow() {
  delete ui;
  delete validator;
}

void MainWindow::PushButtonPoint_click() {
  ui->comment->setText("");
  QPushButton *a = (QPushButton *)sender();
  if (correctExpression) {
    int validate =
        check_push_point(ui->display->toPlainText().toLocal8Bit().data());
    if (validate == 2) {
      ui->display->setPlainText(ui->display->toPlainText() + a->text());
    } else if (validate == 3) {
      ui->comment->setText("Incorrect expression");
    } else {
      ui->comment->setText("Wrong expression's size");
    }
  }
}

void MainWindow::PushButtonNum_click() {
  ui->comment->setText("");
  QPushButton *a = (QPushButton *)sender();
  if (correctExpression) {
    int validate =
        check_push_num(ui->display->toPlainText().toLocal8Bit().data(),
                       a->text().toLocal8Bit().data());
    if (validate == 1) {
      ui->display->setPlainText(a->text());
    } else if (validate == 2) {
      ui->display->setPlainText(ui->display->toPlainText() + a->text());
    } else if (validate == 3) {
      ui->comment->setText("Incorrect expression");
    } else if (validate == 4) {
      ui->comment->setText("Wrong expression's size");
    }
  }
}

void MainWindow::PushButtonFunc_click() {
  ui->comment->setText("");
  QPushButton *a = (QPushButton *)sender();
  if (correctExpression) {
    int validate =
        check_push_func(ui->display->toPlainText().toLocal8Bit().data());
    if (validate == 1) {
      ui->display->setPlainText(a->text() + "(");
    } else if (validate == 2) {
      ui->display->setPlainText(ui->display->toPlainText() + a->text() + "(");
    } else if (validate == 3) {
      ui->comment->setText("Incorrect expression");
    } else if (validate == 4) {
      ui->comment->setText("Wrong expression's size");
    }
  }
}

void MainWindow::PushButtonOperation_click() {
  ui->comment->setText("");
  QPushButton *a = (QPushButton *)sender();
  if (correctExpression) {
    int validate =
        check_push_operation(ui->display->toPlainText().toLocal8Bit().data(),
                             a->text().toLocal8Bit().data());
    if (validate == 1) {
      ui->display->setPlainText(a->text());
    } else if (validate == 2) {
      ui->display->setPlainText(ui->display->toPlainText() + a->text());
    } else if (validate == 3) {
      ui->comment->setText("Incorrect expression");
    } else if (validate == 4) {
      ui->comment->setText("Wrong expression's size");
    }
  }
}

void MainWindow::PushButtonClear_click() {
  ui->display->setPlainText("0");
  ui->comment->setText("");
  correctExpression = true;
}

void MainWindow::PushButtonDelete_click() {
  ui->comment->setText("");
  if (correctExpression) {
    int del_len =
        check_push_delete(ui->display->toPlainText().toLocal8Bit().data());
    QString result_str = ui->display->toPlainText();
    result_str.chop(del_len);
    ui->display->setPlainText(result_str);
  }
}

void MainWindow::PushButtonLeftBracket_click() {
  ui->comment->setText("");
  if (correctExpression) {
    int validate = check_push_left_bracket(
        ui->display->toPlainText().toLocal8Bit().data());
    if (validate == 1) {
      ui->display->setPlainText("(");
    } else if (validate == 2) {
      ui->display->setPlainText(ui->display->toPlainText() + "(");
    } else if (validate == 3) {
      ui->comment->setText("Incorrect expression");
    } else if (validate == 4) {
      ui->comment->setText("Wrong expression's size");
    }
  }
}

void MainWindow::PushButtonRightBracket_click() {
  ui->comment->setText("");
  if (correctExpression) {
    int validate = check_push_right_bracket(
        ui->display->toPlainText().toLocal8Bit().data());
    if (validate == 1) {
      ui->display->setPlainText(")");
    } else if (validate == 2) {
      ui->display->setPlainText(ui->display->toPlainText() + ")");
    } else if (validate == 3) {
      ui->comment->setText("Incorrect expression");
    } else if (validate == 4) {
      ui->comment->setText("Wrong expression's size");
    }
  }
}

void MainWindow::PushButtonEqual_click() {
  ui->comment->setText("");
  if (correctExpression) {
    int validate =
        check_correct(ui->display->toPlainText().toLocal8Bit().data());
    if (validate == 2) {
      double x = 0;
      if (isX(ui->display->toPlainText().toLocal8Bit().data()) == 1 &&
          ui->x_value->text() == "") {
        ui->comment->setText("X is not initialized");
      } else {
        if (ui->x_value->text() != "") {
          x = ui->x_value->text().toDouble();
        }
        double result =
            get_answer(ui->display->toPlainText().toLocal8Bit().data(), x);
        if (QString::number(result) == "nan" ||
            QString::number(result) == "inf" ||
            QString::number(result) == "-inf") {
          ui->comment->setText("Incorrect expression");
        } else {
          ui->display->setPlainText(QString::number(result));
        }
      }
    } else if (validate == 3) {
      ui->comment->setText("Incorrect expression");
    } else if (validate == 4) {
      ui->comment->setText("Wrong expression's size");
    }
  }
}

void MainWindow::PushButtonGraph_clock() {
  QByteArray display = ui->display->toPlainText().toLocal8Bit();
  if (strchr(display.data(), 'x')) {
    double x_min = ui->x_min_value->text().toDouble();
    double y_min = ui->y_min_value->text().toDouble();
    double x_max = ui->x_max_value->text().toDouble();
    double y_max = ui->y_max_value->text().toDouble();
    if (x_max <= x_min || y_max <= y_min) {
      ui->comment->setText("Incorrect range");
    } else if (check_range(x_max, x_min, y_max, y_min)) {
      ui->comment->setText("Incorrect range");
    } else {
      graphwindow = new GraphWindow;
      graphwindow->slot_xMin(x_min);
      graphwindow->slot_xMax(x_max);
      graphwindow->slot_yMin(y_min);
      graphwindow->slot_yMax(y_max);
      graphwindow->plotGraph(display.data());
      graphwindow->setModal(true);
      graphwindow->exec();
    }

  } else {
    ui->comment->setText("Expression has not X");
  }
}
