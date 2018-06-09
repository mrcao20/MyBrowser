#ifndef DOWNLOADMANAGERWIDGET_H
#define DOWNLOADMANAGERWIDGET_H

#include "ui_downloadmanagerwidget.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
class QWebEngineDownloadItem;
QT_END_NAMESPACE

class DownloadWidget2;

// Displays a list of downloads.
class DownloadManagerWidget final : public QWidget, public Ui::DownloadManagerWidget
{
    Q_OBJECT
public:
    explicit DownloadManagerWidget(QWidget *parent = nullptr);
	~DownloadManagerWidget();

    // Prompts user with a "Save As" dialog. If the user doesn't cancel it, then
    // the QWebEngineDownloadItem will be accepted and the DownloadManagerWidget
    // will be shown on the screen.
public slots:
    void downloadRequested(QWebEngineDownloadItem *webItem);

private:
    void add(DownloadWidget2 *downloadWidget);
    void remove(DownloadWidget2 *downloadWidget);

    int m_numDownloads;
};

#endif // DOWNLOADMANAGERWIDGET_H
