#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , lastIndex(-1)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    quoteLabel = new QLabel("Töltés...");
    quoteLabel->setWordWrap(true);
    quoteLabel->setAlignment(Qt::AlignCenter);

    nextButton = new QPushButton("Új idézet generálása");

    layout->addStretch();
    layout->addWidget(quoteLabel);
    layout->addStretch();
    layout->addWidget(nextButton);

    loadQuotes();
    setupStyle();

    connect(nextButton, &QPushButton::clicked, this, &MainWindow::displayNewQuote);

    displayNewQuote();

    setWindowTitle("Napi Motiváció");
    resize(500, 350);
}

MainWindow::~MainWindow()
{

}


void MainWindow::loadQuotes() {
    QFile file("quotes.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        quotes << "Az egyetlen módja annak, hogy nagyszerű munkát végezz, ha szereted, amit csinálsz. - Steve Jobs";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            quotes << line;
        }
    }
    file.close();
}

void MainWindow::displayNewQuote() {
    if (quotes.isEmpty()) return;

    int newIndex;
    do {
        newIndex = QRandomGenerator::global()->bounded(quotes.size());
    } while (newIndex == lastIndex && quotes.size() > 1);

    lastIndex = newIndex;
    quoteLabel->setText(quotes.at(lastIndex));
}

void MainWindow::setupStyle() {
    this->setStyleSheet(
        "QMainWindow { background-color: #2c3e50; }"
        "QLabel { "
        "   color: #ecf0f1; "
        "   font-size: 22px; "
        "   font-italic: italic; "
        "   font-family: 'Segoe UI', sans-serif; "
        "   padding: 20px; "
        "}"
        "QPushButton { "
        "   background-color: #3498db; "
        "   color: white; "
        "   border-radius: 10px; "
        "   padding: 12px; "
        "   font-size: 16px; "
        "   font-weight: bold; "
        "   border: none; "
        "}"
        "QPushButton:hover { background-color: #2980b9; }"
        "QPushButton:pressed { background-color: #1f6391; }"
        );
}
