#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

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
    void onFindClicked();
    void onBrowseClicked();


private:
    void setupUi();

    QLineEdit *nameLineEdit;
    QLineEdit *textLineEdit;
    QComboBox *directoryComboBox;
    QPushButton *browseButton;
    QPushButton *findButton;
    QTableWidget *filesTable;
    QLabel *statusLabel;
};
#endif // MAINWINDOW_H
