﻿#include <QApplication>
#include <QWidget>
#include <QTabWidget>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QFileDialog>

void setupUi(QWidget*);
void leader(QTabWidget*, QTextBrowser*&);
void change_color(QTabWidget*, QTextBrowser*);
void choose_file(QTabWidget*, QTextBrowser*);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget* windows = new QWidget;
    setupUi(windows);
    windows->show();
    return a.exec();
}

void setupUi(QWidget *windows)
{
    QTabWidget *tabWidget;
    QTextBrowser *leaderTextBrowser;

    QVBoxLayout *mainLayout = new QVBoxLayout(windows);


    if (windows->objectName().isEmpty())
        windows->setObjectName("Form");
    windows->resize(400, 300);
    windows->setWindowTitle("第15組");

    tabWidget = new QTabWidget(windows);
    tabWidget->setObjectName("tabWidget");


    leader(tabWidget, leaderTextBrowser);

    QWidget* tab_1 = new QWidget;
    tab_1->setObjectName("tab1");
    tabWidget->addTab(tab_1, "組員1");


    QWidget* tab_2 = new QWidget;
    tab_2->setObjectName("tab2");
    tabWidget->addTab(tab_2, "組員2");


    choose_file(tabWidget, leaderTextBrowser);


    tabWidget->setCurrentIndex(0);

    mainLayout->addWidget(tabWidget);
    windows->setLayout(mainLayout);

    QMetaObject::connectSlotsByName(windows);
}

void leader(QTabWidget* tabWidget, QTextBrowser*& leaderTextBrowser) {
    QWidget *tab;
    tab = new QWidget();
    tab->setObjectName("tab");

    QVBoxLayout* tabLayout = new QVBoxLayout(tab);


    leaderTextBrowser = new QTextBrowser(tab);
    leaderTextBrowser->setObjectName("textBrowser");
    leaderTextBrowser->setText("\n\n"
                               "隊長: 41243140 陳稟承\n"
                               "組員1: 41243144 温博鈞\n"
                               "組員2: 41243131 莊笙禾\n"
                               "組員3: 41243142 彭偉倫"
                               "");

    tabLayout->addWidget(leaderTextBrowser);
    tab->setLayout(tabLayout);
    tabWidget->addTab(tab, "隊長");
}

void change_color(QTabWidget* tabWidget, QTextBrowser* leaderTextBrowser) {
    QWidget *tab = new QWidget();
    tab->setObjectName("tab_1");
    QVBoxLayout* tab3Layout = new QVBoxLayout(tab);
    QPushButton *colorButton = new QPushButton("選擇顏色", tab);
    tab3Layout->addWidget(colorButton);

    QObject::connect(colorButton, &QPushButton::clicked, [leaderTextBrowser]() {
        QColor color = QColorDialog::getColor(Qt::white, nullptr, "選擇顏色");
        if (color.isValid()) {
            QTextCursor cursor = leaderTextBrowser->textCursor();
            QTextCharFormat format;
            format.setForeground(color);
            cursor.select(QTextCursor::Document);
            cursor.mergeCharFormat(format);
            leaderTextBrowser->setTextCursor(cursor);
        }
    });

    tab->setLayout(tab3Layout);
    tabWidget->addTab(tab, "組員1");
}

void choose_file(QTabWidget* tabWidget, QTextBrowser* leaderTextBrowser) {
    QWidget* tab = new QWidget();
    tab->setObjectName("tab_3");

    QVBoxLayout* tabLayout = new QVBoxLayout(tab);


    QPushButton* fileButton = new QPushButton("選擇文件", tab);
    tabLayout->addWidget(fileButton);


    QObject::connect(fileButton, &QPushButton::clicked, [leaderTextBrowser]() {
        QString filePath = QFileDialog::getOpenFileName(nullptr, "選擇文件", "", "所有文件 (*.*)");
        if (!filePath.isEmpty()) {

            leaderTextBrowser->setText("<span style=\"color:red;\">選擇的文件路徑為: " + filePath + "</span>");
        }
    });

    tab->setLayout(tabLayout);
    tabWidget->addTab(tab, "組員3");
}
