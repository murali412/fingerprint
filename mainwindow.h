#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_register_2_clicked();

    void on_pushButton_2_clicked();

    void on_timeEdit_timeChanged(const QTime &time);

    void on_timeEdit_2_timeChanged(const QTime &time);
    void repat();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
