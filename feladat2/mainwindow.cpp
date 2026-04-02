#include "mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    tableWidget = new QTableWidget(this);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setCentralWidget(tableWidget);
    createMenus();
    setWindowTitle("CSV Viewer");
    resize(800, 600);
}

MainWindow::~MainWindow()
{

}


void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    openAction = new QAction(tr("&Open File..."), this);
    openAction->setShortcut(QKeySequence::Open);
    fileMenu->addAction(openAction);
    connect(openAction, &QAction::triggered, this, &MainWindow::openCsvFile);
}

void MainWindow::openCsvFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open CSV File"), "", tr("CSV Files (*.csv);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Could not open file."));
        return;
    }
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(0);
    QTextStream in(&file);
    bool isFirstRow = true;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (isFirstRow) {
            tableWidget->setColumnCount(fields.size());
            tableWidget->setHorizontalHeaderLabels(fields);
            isFirstRow = false;
        } else {
            int currentRow = tableWidget->rowCount();
            tableWidget->insertRow(currentRow);

            for (int i = 0; i < fields.size(); ++i) {
                tableWidget->setItem(currentRow, i, new QTableWidgetItem(fields.at(i).trimmed()));
            }
        }
    }

    file.close();
}
