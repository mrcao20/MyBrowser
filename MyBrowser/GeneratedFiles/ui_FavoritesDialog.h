/********************************************************************************
** Form generated from reading UI file 'FavoritesDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAVORITESDIALOG_H
#define UI_FAVORITESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FavoritesDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *titleLabel;
    QLabel *urlLabel;
    QLineEdit *titleEdit;
    QLineEdit *urlEdit;

    void setupUi(QDialog *FavoritesDialog)
    {
        if (FavoritesDialog->objectName().isEmpty())
            FavoritesDialog->setObjectName(QStringLiteral("FavoritesDialog"));
        FavoritesDialog->resize(417, 189);
        layoutWidget = new QWidget(FavoritesDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 130, 351, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout->addWidget(cancelButton);

        titleLabel = new QLabel(FavoritesDialog);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        titleLabel->setGeometry(QRect(40, 40, 54, 12));
        titleLabel->setAlignment(Qt::AlignCenter);
        urlLabel = new QLabel(FavoritesDialog);
        urlLabel->setObjectName(QStringLiteral("urlLabel"));
        urlLabel->setGeometry(QRect(40, 90, 54, 12));
        urlLabel->setAlignment(Qt::AlignCenter);
        titleEdit = new QLineEdit(FavoritesDialog);
        titleEdit->setObjectName(QStringLiteral("titleEdit"));
        titleEdit->setGeometry(QRect(100, 37, 291, 20));
        urlEdit = new QLineEdit(FavoritesDialog);
        urlEdit->setObjectName(QStringLiteral("urlEdit"));
        urlEdit->setGeometry(QRect(100, 86, 291, 20));

        retranslateUi(FavoritesDialog);
        QObject::connect(okButton, SIGNAL(clicked()), FavoritesDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), FavoritesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FavoritesDialog);
    } // setupUi

    void retranslateUi(QDialog *FavoritesDialog)
    {
        FavoritesDialog->setWindowTitle(QApplication::translate("FavoritesDialog", "Dialog", nullptr));
        okButton->setText(QApplication::translate("FavoritesDialog", "OK", nullptr));
        cancelButton->setText(QApplication::translate("FavoritesDialog", "Cancel", nullptr));
        titleLabel->setText(QApplication::translate("FavoritesDialog", "name:", nullptr));
        urlLabel->setText(QApplication::translate("FavoritesDialog", "url:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FavoritesDialog: public Ui_FavoritesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAVORITESDIALOG_H
