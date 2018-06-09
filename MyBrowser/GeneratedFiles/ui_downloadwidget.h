/********************************************************************************
** Form generated from reading UI file 'downloadwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADWIDGET_H
#define UI_DOWNLOADWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DownloadWidget
{
public:
    QGridLayout *m_topLevelLayout;
    QLabel *m_dstName;
    QPushButton *m_cancelButton;
    QProgressBar *m_progressBar;
    QLabel *m_srcUrl;
    QPushButton *m_pauseButton;

    void setupUi(QFrame *DownloadWidget)
    {
        if (DownloadWidget->objectName().isEmpty())
            DownloadWidget->setObjectName(QStringLiteral("DownloadWidget"));
        DownloadWidget->resize(147, 78);
        DownloadWidget->setStyleSheet(QLatin1String("#DownloadWidget {\n"
"  background: palette(button);\n"
"  border: 1px solid palette(dark);\n"
"  margin: 0px;\n"
"}"));
        m_topLevelLayout = new QGridLayout(DownloadWidget);
        m_topLevelLayout->setObjectName(QStringLiteral("m_topLevelLayout"));
        m_topLevelLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        m_dstName = new QLabel(DownloadWidget);
        m_dstName->setObjectName(QStringLiteral("m_dstName"));
        m_dstName->setStyleSheet(QLatin1String("font-weight: bold\n"
""));

        m_topLevelLayout->addWidget(m_dstName, 0, 0, 1, 1);

        m_cancelButton = new QPushButton(DownloadWidget);
        m_cancelButton->setObjectName(QStringLiteral("m_cancelButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_cancelButton->sizePolicy().hasHeightForWidth());
        m_cancelButton->setSizePolicy(sizePolicy);
        m_cancelButton->setStyleSheet(QLatin1String("QPushButton {\n"
"  margin: 1px;\n"
"  border: none;\n"
"}\n"
"QPushButton:pressed {\n"
"  margin: none;\n"
"  border: 1px solid palette(shadow);\n"
"  background: palette(midlight);\n"
"}"));
        m_cancelButton->setFlat(false);

        m_topLevelLayout->addWidget(m_cancelButton, 0, 2, 1, 1);

        m_progressBar = new QProgressBar(DownloadWidget);
        m_progressBar->setObjectName(QStringLiteral("m_progressBar"));
        m_progressBar->setStyleSheet(QStringLiteral("font-size: 12px"));
        m_progressBar->setValue(24);

        m_topLevelLayout->addWidget(m_progressBar, 2, 0, 1, 3);

        m_srcUrl = new QLabel(DownloadWidget);
        m_srcUrl->setObjectName(QStringLiteral("m_srcUrl"));
        m_srcUrl->setMaximumSize(QSize(350, 16777215));
        m_srcUrl->setStyleSheet(QStringLiteral(""));

        m_topLevelLayout->addWidget(m_srcUrl, 1, 0, 1, 3);

        m_pauseButton = new QPushButton(DownloadWidget);
        m_pauseButton->setObjectName(QStringLiteral("m_pauseButton"));
        sizePolicy.setHeightForWidth(m_pauseButton->sizePolicy().hasHeightForWidth());
        m_pauseButton->setSizePolicy(sizePolicy);
        m_pauseButton->setStyleSheet(QLatin1String("QPushButton {\n"
"  margin: 1px;\n"
"  border: none;\n"
"}\n"
"QPushButton:pressed {\n"
"  margin: none;\n"
"  border: 1px solid palette(shadow);\n"
"  background: palette(midlight);\n"
"}"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/browser/icon/pause.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        m_pauseButton->setIcon(icon);

        m_topLevelLayout->addWidget(m_pauseButton, 0, 1, 1, 1);


        retranslateUi(DownloadWidget);

        QMetaObject::connectSlotsByName(DownloadWidget);
    } // setupUi

    void retranslateUi(QFrame *DownloadWidget)
    {
        m_dstName->setText(QApplication::translate("DownloadWidget", "TextLabel", nullptr));
        m_srcUrl->setText(QApplication::translate("DownloadWidget", "TextLabel", nullptr));
        Q_UNUSED(DownloadWidget);
    } // retranslateUi

};

namespace Ui {
    class DownloadWidget: public Ui_DownloadWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADWIDGET_H
