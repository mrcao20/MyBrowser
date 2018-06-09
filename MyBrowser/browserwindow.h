#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H
#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include <QTime>
#include <QWebEnginePage>
#include <qprocess.h>
#include <QNetworkProxy>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QProgressBar;
QT_END_NAMESPACE

class Browser;
class TabWidget;
class WebView;

class BrowserWindow : public QMainWindow
{
    Q_OBJECT

public:
    BrowserWindow(Browser *browser, QWebEngineProfile *profile);
    QSize sizeHint() const override;
    TabWidget *tabWidget() const;
    WebView *currentTab() const;
    Browser *browser() { return m_browser; }

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
	void quit();

private slots:
    void handleNewWindowTriggered();
    void handleNewIncognitoWindowTriggered();
    void handleFileOpenTriggered();
    void handleFindActionTriggered();
    void handleShowWindowTriggered();
    void handleWebViewLoadProgress(int);
    void handleWebViewTitleChanged(const QString &title);
    void handleWebActionEnabledChanged(QWebEnginePage::WebAction action, bool enabled);

private:
    QMenu *createFileMenu(TabWidget *tabWidget);
    QMenu *createEditMenu();
    QMenu *createViewMenu(QToolBar *toolBar);
	//QMenu *createHistoryMenu();
	QMenu *createFavoritesMenu(TabWidget *tabWidget);
	QMenu *createToolMenu();
    QMenu *createWindowMenu(TabWidget *tabWidget);
    QToolBar *createToolBar();

	bool setProxy();

private:
    Browser *m_browser;
    QWebEngineProfile *m_profile;
    TabWidget *m_tabWidget;
    QProgressBar *m_progressBar;
    QAction *m_historyBackAction;
    QAction *m_historyForwardAction;
    QAction *m_stopAction;
    QAction *m_reloadAction;
    QAction *m_stopReloadAction;
    QLineEdit *m_urlLineEdit;
    QAction *m_favAction;
    QString m_lastSearch;
	QProcess *proc;

	QNetworkProxy proxy;
};

#endif // BROWSERWINDOW_H
