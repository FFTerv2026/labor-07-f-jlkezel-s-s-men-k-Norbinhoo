#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QStringList>

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
    void displayNewQuote();

private:
    void loadQuotes();
    void setupStyle();

    QLabel *quoteLabel;
    QPushButton *nextButton;
    QStringList quotes;
    int lastIndex;
};
#endif // MAINWINDOW_H
