#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QFileDialog>
#include <QDirIterator>
#include <QTextStream>
#include <QFileInfo>
#include <QProgressDialog>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
   setupUi();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QFormLayout *formLayout = new QFormLayout();

    nameLineEdit = new QLineEdit("*");
    textLineEdit = new QLineEdit();

    QHBoxLayout *dirLayout = new QHBoxLayout();
    directoryComboBox = new QComboBox();
    directoryComboBox->setEditable(true);
    directoryComboBox->addItem(QDir::currentPath());
    directoryComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    browseButton = new QPushButton("Browse...");
    dirLayout->addWidget(directoryComboBox);
    dirLayout->addWidget(browseButton);

    formLayout->addRow("Named:", nameLineEdit);
    formLayout->addRow("Containing text:", textLineEdit);
    formLayout->addRow("In directory:", dirLayout);

    mainLayout->addLayout(formLayout);

    filesTable = new QTableWidget(0, 2);
    filesTable->setHorizontalHeaderLabels({"Filename", "Size"});
    filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    mainLayout->addWidget(filesTable);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    statusLabel = new QLabel("0 file(s) found");
    findButton = new QPushButton("Find");

    bottomLayout->addWidget(statusLabel);
    bottomLayout->addStretch();
    bottomLayout->addWidget(findButton);
    mainLayout->addLayout(bottomLayout);

    connect(browseButton, &QPushButton::clicked, this, &MainWindow::onBrowseClicked);
    connect(findButton, &QPushButton::clicked, this, &MainWindow::onFindClicked);

    setWindowTitle("Find Files");
    resize(700, 450);
}

void MainWindow::onBrowseClicked() {
    QString dir = QFileDialog::getExistingDirectory(this, "Select Directory", directoryComboBox->currentText());
    if (!dir.isEmpty()) {
        directoryComboBox->addItem(dir);
        directoryComboBox->setCurrentText(dir);
    }
}

void MainWindow::onFindClicked() {
    QString path = directoryComboBox->currentText();
    QString fileNamePattern = nameLineEdit->text();
    QString containsText = textLineEdit->text();

    filesTable->setRowCount(0);

    QDirIterator it(path, QStringList() << fileNamePattern, QDir::Files, QDirIterator::Subdirectories);

    QProgressDialog progress("Searching files...", "Cancel", 0, 0, this);
    progress.setWindowModality(Qt::WindowModal);

    int count = 0;
    while (it.hasNext()) {
        it.next();
        if (progress.wasCanceled()) break;

        bool match = false;
        if (containsText.isEmpty()) {
            match = true;
        } else {
            QFile file(it.filePath());
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                if (in.readAll().contains(containsText, Qt::CaseInsensitive)) {
                    match = true;
                }
                file.close();
            }
        }

        if (match) {
            int row = filesTable->rowCount();
            filesTable->insertRow(row);
            QFileInfo info(it.filePath());
            filesTable->setItem(row, 0, new QTableWidgetItem(info.fileName()));
            filesTable->setItem(row, 1, new QTableWidgetItem(QString("%1 KB").arg(info.size() / 1024 + 1)));
            count++;
        }
        QCoreApplication::processEvents();
    }

    statusLabel->setText(QString("%1 file(s) found (Double click on a file to open it)").arg(count));
}
