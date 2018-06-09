#ifndef BROWSER_H
#define BROWSER_H

#include "downloadmanagerwidget.h"

#include <QVector>
#include <QWebEngineProfile>
#include <qscopedpointer.h>

class BrowserWindow;

class Browser
{
public:
    Browser();

    QVector<BrowserWindow*> windows() { return m_windows; }

    BrowserWindow *createWindow(bool offTheRecord = false);

    DownloadManagerWidget *downloadManagerWidget() { return m_downloadManagerWidget.data(); }

private:
	QScopedPointer<DownloadManagerWidget> m_downloadManagerWidget;
    QVector<BrowserWindow*> m_windows;
    QWebEngineProfile m_otrProfile;
};
#endif // BROWSER_H
