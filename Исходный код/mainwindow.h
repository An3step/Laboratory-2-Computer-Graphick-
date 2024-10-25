#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ScanDirectory(QString);

    void ShowTable();
private slots:
    void on_ChoiceFolder_clicked();

    void on_ReChoice_clicked();

private:
    Ui::MainWindow *ui;
    QVector<QString> images;
    int imagenumber = 0;
    int c = 0;
    QString text;
};
#endif // MAINWINDOW_H
