/*
project name: git-widget
project author:
    41243140 陳稟承
    41243144 温博鈞
    41243131 莊笙禾
    41243142 彭偉倫
project description:
    這是一個基於 Qt 的簡單應用程式，用來展示隊伍成員的資訊。
    程式包含了多個標籤頁，每個頁面代表一位成員，使用者可以在第一位組員的頁面中透過圖形介面來更改顏色。

project function:
    1. 展示隊長與組員資訊。
    2. 提供一個 GUI 介面供使用者調整文字顏色。
    3. 提供一個 GUI 介面供使用者調整文字樣式。
    4. 提供一個按鈕讓使用者選取資料夾並顯示該檔案位置
*/

#include <QApplication>
#include <QWidget>
#include <QTabWidget>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QTextCursor>
#include <QTextCharFormat>

void setupUi(QWidget*);
void leader(QTabWidget*, QTextBrowser*&);
void change_color(QTabWidget*, QTextBrowser*);

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
    QTextBrowser *leaderTextBrowser;  // 儲存隊長的文字框框

    QVBoxLayout *mainLayout = new QVBoxLayout(windows);

    // windows setting
    if (windows->objectName().isEmpty())
        windows->setObjectName("Form");
    windows->resize(400, 300);
    windows->setWindowTitle("第15組");

    tabWidget = new QTabWidget(windows);
    tabWidget->setObjectName("tabWidget");

    // Tab 1 - 隊長
    leader(tabWidget, leaderTextBrowser);

    // Tab 2 - 組員1
    change_color(tabWidget, leaderTextBrowser);

    // Tab 3 - 組員2
    QWidget* tab_2 = new QWidget;
    tab_2->setObjectName("tab2");
    tabWidget->addTab(tab_2, "組員2");

    // Tab 3 - 組員3
    QWidget* tab_3 = new QWidget;
    tab_3->setObjectName("tab3");
    tabWidget->addTab(tab_3, "組員3");

    // 一開始顯示隊長頁面
    tabWidget->setCurrentIndex(0);

    mainLayout->addWidget(tabWidget);

    windows->setLayout(mainLayout);

    QMetaObject::connectSlotsByName(windows);
}

void leader(QTabWidget* tabWidget, QTextBrowser*& leaderTextBrowser) {
    QWidget *tab;
    tab = new QWidget();
    tab->setObjectName("tab");

    // 新增佈局自動調整大小
    QVBoxLayout* tabLayout = new QVBoxLayout(tab);

    // 新增文字框
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
    /*
    使用QT內建的QColor讓使用者有GUI介面可以調整顏色
    */
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
