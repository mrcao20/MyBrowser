#include "browser.h"
#include "browserwindow.h"

#include <QWebEngineProfile>
#include <qdir.h>
#include <qwebenginecookiestore.h>

Browser::Browser()
	: m_downloadManagerWidget(new DownloadManagerWidget)
{
    // Quit application if the download manager window is the only remaining window
    m_downloadManagerWidget->setAttribute(Qt::WA_QuitOnClose, false);

    QObject::connect(
        QWebEngineProfile::defaultProfile(), &QWebEngineProfile::downloadRequested,
        m_downloadManagerWidget.data(), &DownloadManagerWidget::downloadRequested);
    QObject::connect(
        &m_otrProfile, &QWebEngineProfile::downloadRequested,
        m_downloadManagerWidget.data(), &DownloadManagerWidget::downloadRequested);
}

BrowserWindow *Browser::createWindow(bool offTheRecord)
{
    auto profile = offTheRecord ? &m_otrProfile : QWebEngineProfile::defaultProfile();
	/*QDir dir;
	QString dirPath = qApp->applicationDirPath() + "/data/webpage";
	if (!dir.exists(dirPath))
		dir.mkdir(dirPath);
	profile->setCachePath(dirPath);*/
    auto mainWindow = new BrowserWindow(this, profile);
    m_windows.append(mainWindow);
	QObject::connect(mainWindow, &BrowserWindow::quit, [this, profile]() {
		if (m_windows.size() <= 1) {
			m_downloadManagerWidget.reset();
			profile->clearHttpCache();
			profile->clearAllVisitedLinks();
		}
	});
    QObject::connect(mainWindow, &QObject::destroyed, [this, mainWindow]() {
        m_windows.removeOne(mainWindow);
    });
    mainWindow->show();
    return mainWindow;
}
