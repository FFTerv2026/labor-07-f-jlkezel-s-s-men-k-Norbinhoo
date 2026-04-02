#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openCsvFile();

private:
    void createMenus();

    QTableWidget *tableWidget;
    QMenu *fileMenu;
    QAction *openAction;
};
#endif // MAINWINDOW_H
