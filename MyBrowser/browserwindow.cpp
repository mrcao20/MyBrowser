#include "browser.h"
#include "browserwindow.h"
#include "downloadmanagerwidget.h"
#include "tabwidget.h"
#include "webview.h"
#include <QApplication>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QProgressBar>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWebEngineProfile>
#include <iostream>
#include <cstdlib>
#include "ui_FavoritesDialog.h"
#include <qlistwidget.h>

extern QUrl url;

BrowserWindow::BrowserWindow(Browser *browser, QWebEngineProfile *profile)
	: m_browser(browser)
	, m_profile(profile)
	, m_tabWidget(new TabWidget(profile, this))
	, m_progressBar(new QProgressBar(this))
	, m_historyBackAction(nullptr)
	, m_historyForwardAction(nullptr)
	, m_stopAction(nullptr)
	, m_reloadAction(nullptr)
	, m_stopReloadAction(nullptr)
	, m_urlLineEdit(nullptr)
	, m_favAction(nullptr)
	, proc(nullptr)
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    setFocusPolicy(Qt::ClickFocus);

    QToolBar *toolbar = createToolBar();
    addToolBar(toolbar);
    menuBar()->addMenu(createFileMenu(m_tabWidget));
    menuBar()->addMenu(createEditMenu());
    menuBar()->addMenu(createViewMenu(toolbar));
	//menuBar()->addMenu(createHistoryMenu());
	menuBar()->addMenu(createFavoritesMenu(m_tabWidget));
	menuBar()->addMenu(createToolMenu());
    menuBar()->addMenu(createWindowMenu(m_tabWidget));
	
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    addToolBarBreak();

    m_progressBar->setMaximumHeight(1);
    m_progressBar->setTextVisible(false);
    m_progressBar->setStyleSheet(QStringLiteral("QProgressBar {border: 0px} QProgressBar::chunk {background-color: #da4453}"));

    layout->addWidget(m_progressBar);
    layout->addWidget(m_tabWidget);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(m_tabWidget, &TabWidget::titleChanged, this, &BrowserWindow::handleWebViewTitleChanged);
    connect(m_tabWidget, &TabWidget::linkHovered, [this](const QString& url) {
        statusBar()->showMessage(url);
    });
    connect(m_tabWidget, &TabWidget::loadProgress, this, &BrowserWindow::handleWebViewLoadProgress);
    connect(m_tabWidget, &TabWidget::webActionEnabledChanged, this, &BrowserWindow::handleWebActionEnabledChanged);
    connect(m_tabWidget, &TabWidget::urlChanged, [this](const QUrl &url) {
        m_urlLineEdit->setText(url.toDisplayString());
    });
    connect(m_tabWidget, &TabWidget::favIconChanged, m_favAction, &QAction::setIcon);
    connect(m_urlLineEdit, &QLineEdit::returnPressed, [this]() {
        m_tabWidget->setUrl(QUrl::fromUserInput(m_urlLineEdit->text()));
    });

    QAction *focusUrlLineEditAction = new QAction(this);
    addAction(focusUrlLineEditAction);
    focusUrlLineEditAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
    connect(focusUrlLineEditAction, &QAction::triggered, this, [this] () {
        m_urlLineEdit->setFocus(Qt::ShortcutFocusReason);
    });

    handleWebViewTitleChanged(QString());
    m_tabWidget->createTab();
	
}

QSize BrowserWindow::sizeHint() const
{
    QRect desktopRect = QApplication::desktop()->screenGeometry();
    QSize size = desktopRect.size() * qreal(0.9);
    return size;
}

QMenu *BrowserWindow::createFileMenu(TabWidget *tabWidget)
{
    QMenu *fileMenu = new QMenu(tr("&File"));
    fileMenu->addAction(tr("&New Window"), this, &BrowserWindow::handleNewWindowTriggered, QKeySequence::New);
    fileMenu->addAction(tr("New &Incognito Window"), this, &BrowserWindow::handleNewIncognitoWindowTriggered);

    QAction *newTabAction = new QAction(tr("New &Tab"), this);
    newTabAction->setShortcuts(QKeySequence::AddTab);
    connect(newTabAction, &QAction::triggered, tabWidget, &TabWidget::createTab);
    fileMenu->addAction(newTabAction);

    fileMenu->addAction(tr("&Open File..."), this, &BrowserWindow::handleFileOpenTriggered, QKeySequence::Open);
    fileMenu->addSeparator();

    QAction *closeTabAction = new QAction(tr("&Close Tab"), this);
    closeTabAction->setShortcuts(QKeySequence::Close);
    connect(closeTabAction, &QAction::triggered, [tabWidget]() {
        tabWidget->closeTab(tabWidget->currentIndex());
    });
    fileMenu->addAction(closeTabAction);

    QAction *closeAction = new QAction(tr("&Quit"),this);
    closeAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
    connect(closeAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(closeAction);

    connect(fileMenu, &QMenu::aboutToShow, [this, closeAction]() {
        if (m_browser->windows().count() == 1)
            closeAction->setText(tr("&Quit"));
        else
            closeAction->setText(tr("&Close Window"));
    });
    return fileMenu;
}

QMenu *BrowserWindow::createEditMenu()
{
    QMenu *editMenu = new QMenu(tr("&Edit"));
    QAction *findAction = editMenu->addAction(tr("&Find"));
    findAction->setShortcuts(QKeySequence::Find);
    connect(findAction, &QAction::triggered, this, &BrowserWindow::handleFindActionTriggered);

    QAction *findNextAction = editMenu->addAction(tr("Find &Next"));
    findNextAction->setShortcut(QKeySequence::FindNext);
    connect(findNextAction, &QAction::triggered, [this]() {
        if (!currentTab() || m_lastSearch.isEmpty())
            return;
        currentTab()->findText(m_lastSearch);
    });

    QAction *findPreviousAction = editMenu->addAction(tr("Find &Previous"));
    findPreviousAction->setShortcut(QKeySequence::FindPrevious);
    connect(findPreviousAction, &QAction::triggered, [this]() {
        if (!currentTab() || m_lastSearch.isEmpty())
            return;
        currentTab()->findText(m_lastSearch, QWebEnginePage::FindBackward);
    });

    return editMenu;
}

QMenu *BrowserWindow::createViewMenu(QToolBar *toolbar)
{
    QMenu *viewMenu = new QMenu(tr("&View"));
    m_stopAction = viewMenu->addAction(tr("&Stop"));
    QList<QKeySequence> shortcuts;
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_Period));
    shortcuts.append(Qt::Key_Escape);
    m_stopAction->setShortcuts(shortcuts);
    connect(m_stopAction, &QAction::triggered, [this]() {
        m_tabWidget->triggerWebPageAction(QWebEnginePage::Stop);
    });

    m_reloadAction = viewMenu->addAction(tr("Reload Page"));
    m_reloadAction->setShortcuts(QKeySequence::Refresh);
    connect(m_reloadAction, &QAction::triggered, [this]() {
        m_tabWidget->triggerWebPageAction(QWebEnginePage::Reload);
    });

    QAction *zoomIn = viewMenu->addAction(tr("Zoom &In"));
    zoomIn->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Plus));
    connect(zoomIn, &QAction::triggered, [this]() {
        if (currentTab())
            currentTab()->setZoomFactor(currentTab()->zoomFactor() + 0.1);
    });

    QAction *zoomOut = viewMenu->addAction(tr("Zoom &Out"));
    zoomOut->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Minus));
    connect(zoomOut, &QAction::triggered, [this]() {
        if (currentTab())
            currentTab()->setZoomFactor(currentTab()->zoomFactor() - 0.1);
    });

    QAction *resetZoom = viewMenu->addAction(tr("Reset &Zoom"));
    resetZoom->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_0));
    connect(resetZoom, &QAction::triggered, [this]() {
        if (currentTab())
            currentTab()->setZoomFactor(1.0);
    });


    viewMenu->addSeparator();
    QAction *viewToolbarAction = new QAction(tr("Hide Toolbar"),this);
    viewToolbarAction->setShortcut(tr("Ctrl+|"));
    connect(viewToolbarAction, &QAction::triggered, [toolbar,viewToolbarAction]() {
        if (toolbar->isVisible()) {
            viewToolbarAction->setText(tr("Show Toolbar"));
            toolbar->close();
        } else {
            viewToolbarAction->setText(tr("Hide Toolbar"));
            toolbar->show();
        }
    });
    viewMenu->addAction(viewToolbarAction);

    QAction *viewStatusbarAction = new QAction(tr("Hide Status Bar"), this);
    viewStatusbarAction->setShortcut(tr("Ctrl+/"));
    connect(viewStatusbarAction, &QAction::triggered, [this, viewStatusbarAction]() {
        if (statusBar()->isVisible()) {
            viewStatusbarAction->setText(tr("Show Status Bar"));
            statusBar()->close();
        } else {
            viewStatusbarAction->setText(tr("Hide Status Bar"));
            statusBar()->show();
        }
    });
    viewMenu->addAction(viewStatusbarAction);
    return viewMenu;
}

//QMenu *BrowserWindow::createHistoryMenu() {
//	QMenu *menu = new QMenu("History", this);
//
//	return menu;
//}

QMenu *BrowserWindow::createFavoritesMenu(TabWidget *tabWidget) {
	QMenu *menu = new QMenu("Favorites", this);
	menu->setFixedWidth(230);

	auto readFavorites = [this](QMenu *menu, TabWidget *tabWidget) {
		QFile rootFile(qApp->applicationDirPath() + "/data/favorites/root");
		rootFile.open(QIODevice::ReadOnly | QIODevice::Text);
		QTextStream rootIn(&rootFile);
		QString str;
		while (!(str = rootIn.readLine()).isEmpty()) {
			QStringList strList = str.split(QRegExp("\\s+"));
			QString type = strList.takeFirst();
			QString title;
			QString url;
			if (type == "URL") {
				QString urlStr;
				for (int i = 0; i < strList.size(); i++) {
					QString tempStr = strList.at(i);
					if (i >= strList.size() - 1)
						urlStr += tempStr;
					else
						urlStr = urlStr + tempStr + " ";
				}
				QStringList urlList = urlStr.split(QRegExp("->"));
				title = urlList.at(0);
				url = urlList.at(1);
			}
			else if (type == "DIR") {
				QString dir;
				for (QString tempStr : strList)
					dir += tempStr;
				QMenu *second_menu = new QMenu(dir, menu);
				menu->addMenu(second_menu);
				continue;
			}
			QAction *action = new QAction(title, this);
			menu->addAction(action);
			connect(action, &QAction::triggered, [url, tabWidget]() {
				WebView *webView = tabWidget->createTab();
				webView->setUrl(url);
			});
		}
		rootFile.close();
	};
	
	QAction *add_action = menu->addAction("add this page to favorites");
	connect(add_action, &QAction::triggered, [this, menu, tabWidget]() {
		QDialog dialog(this);
		dialog.setModal(true);
		dialog.setWindowFlags(dialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);
		Ui::FavoritesDialog favoritesDialog;
		favoritesDialog.setupUi(&dialog);

		favoritesDialog.titleEdit->setText(tabWidget->currentWebView()->title());
		favoritesDialog.urlEdit->setText(m_urlLineEdit->text());

		if (dialog.exec() == QDialog::Accepted) {
			QFile rootFile(qApp->applicationDirPath() + "/data/favorites/root");
			if (!rootFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
				return;
			QTextStream rootOut(&rootFile);
			QString title = favoritesDialog.titleEdit->text();
			QString url = favoritesDialog.urlEdit->text();
			rootOut << "URL " << title << "->" << url << endl << flush;
			rootFile.close();
			QAction *action = new QAction(title, this);
			menu->addAction(action);
			connect(action, &QAction::triggered, [url, tabWidget]() {
				WebView *webView = tabWidget->createTab();
				webView->setUrl(url);
			});
		}
	});
	menu->addSeparator();

	readFavorites(menu, tabWidget);
	return menu;
}

QMenu *BrowserWindow::createToolMenu() {
	proxy.setType(QNetworkProxy::Socks5Proxy);//设置类型
	proxy.setHostName("127.0.0.1");//设置代理服务器地址
	proxy.setPort(1080);//设置端口

	QMenu *toolMenu = new QMenu(tr("&Tool"), this);
	QAction *proxyAction = new QAction(tr("Proxy"), toolMenu);
	toolMenu->addAction(proxyAction);
	proxyAction->setCheckable(true); // 设置action是否被选中
	if (m_browser->windows().size() > 0) return toolMenu;
	proxyAction->setChecked(true); // 设置action是否可以被选中
	connect(proxyAction, &QAction::triggered, [this, proxyAction]() {
		if (proxyAction->isCheckable()) {
			proxyAction->setCheckable(false);
			QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
			proc->kill();
			delete proc;
			proc = nullptr;
			url = QUrl(QStringLiteral("https://www.baidu.com/"));
		}
		else {
			if(setProxy())
				proxyAction->setCheckable(true);
			url = QUrl(QStringLiteral("https://www.google.com/"));
		}
	});
	if (!setProxy())
		proxyAction->setCheckable(false);
	return toolMenu;
}

QMenu *BrowserWindow::createWindowMenu(TabWidget *tabWidget)
{
    QMenu *menu = new QMenu(tr("&Window"));

    QAction *nextTabAction = new QAction(tr("Show Next Tab"), this);
    QList<QKeySequence> shortcuts;
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_BraceRight));
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_PageDown));
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_BracketRight));
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_Less));
    nextTabAction->setShortcuts(shortcuts);
    connect(nextTabAction, &QAction::triggered, tabWidget, &TabWidget::nextTab);

    QAction *previousTabAction = new QAction(tr("Show Previous Tab"), this);
    shortcuts.clear();
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_BraceLeft));
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_PageUp));
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_BracketLeft));
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_Greater));
    previousTabAction->setShortcuts(shortcuts);
    connect(previousTabAction, &QAction::triggered, tabWidget, &TabWidget::previousTab);

    connect(menu, &QMenu::aboutToShow, [this, menu, nextTabAction, previousTabAction]() {
        menu->clear();
        menu->addAction(nextTabAction);
        menu->addAction(previousTabAction);
        menu->addSeparator();

        QVector<BrowserWindow*> windows = m_browser->windows();
        int index(-1);
        for (auto window : windows) {
            QAction *action = menu->addAction(window->windowTitle(), this, &BrowserWindow::handleShowWindowTriggered);
            action->setData(++index);
            action->setCheckable(true);
            if (window == this)
                action->setChecked(true);
        }
    });
    return menu;
}

bool BrowserWindow::setProxy() {
	if(proc == nullptr) proc = new QProcess(this);
	connect(proc, &QProcess::readyReadStandardOutput, [this]() {
		std::cout << QString(proc->readAllStandardOutput()).toStdString() << std::endl;
	});
	proc->start("v2ray-v3.16-windows-64\\v2ray.exe");
	if (!proc->waitForStarted()) {
		std::cout << "代理软件启动失败，代理未设置" << std::endl;
		return false;
	}
	QNetworkProxy::setApplicationProxy(proxy);
	return true;
}

QToolBar *BrowserWindow::createToolBar()
{
    QToolBar *navigationBar = new QToolBar(tr("Navigation"));
    navigationBar->setMovable(false);
    navigationBar->toggleViewAction()->setEnabled(false);

    m_historyBackAction = new QAction(this);
    QList<QKeySequence> backShortcuts = QKeySequence::keyBindings(QKeySequence::Back);
    for (auto it = backShortcuts.begin(); it != backShortcuts.end();) {
        // Chromium already handles navigate on backspace when appropriate.
        if ((*it)[0] == Qt::Key_Backspace)
            it = backShortcuts.erase(it);
        else
            ++it;
    }
    // For some reason Qt doesn't bind the dedicated Back key to Back.
    backShortcuts.append(QKeySequence(Qt::Key_Back));
    m_historyBackAction->setShortcuts(backShortcuts);
    m_historyBackAction->setIconVisibleInMenu(false);
    m_historyBackAction->setIcon(QIcon(QStringLiteral(":/images/browser/icon/go-previous.png")));
    m_historyBackAction->setToolTip(tr("Go back in history"));
    connect(m_historyBackAction, &QAction::triggered, [this]() {
        m_tabWidget->triggerWebPageAction(QWebEnginePage::Back);
    });
    navigationBar->addAction(m_historyBackAction);

    m_historyForwardAction = new QAction(this);
    QList<QKeySequence> fwdShortcuts = QKeySequence::keyBindings(QKeySequence::Forward);
    for (auto it = fwdShortcuts.begin(); it != fwdShortcuts.end();) {
        if (((*it)[0] & Qt::Key_unknown) == Qt::Key_Backspace)
            it = fwdShortcuts.erase(it);
        else
            ++it;
    }
    fwdShortcuts.append(QKeySequence(Qt::Key_Forward));
    m_historyForwardAction->setShortcuts(fwdShortcuts);
    m_historyForwardAction->setIconVisibleInMenu(false);
    m_historyForwardAction->setIcon(QIcon(QStringLiteral(":/images/browser/icon/go-next.png")));
    m_historyForwardAction->setToolTip(tr("Go forward in history"));
    connect(m_historyForwardAction, &QAction::triggered, [this]() {
        m_tabWidget->triggerWebPageAction(QWebEnginePage::Forward);
    });
    navigationBar->addAction(m_historyForwardAction);

    m_stopReloadAction = new QAction(this);
    connect(m_stopReloadAction, &QAction::triggered, [this]() {
        m_tabWidget->triggerWebPageAction(QWebEnginePage::WebAction(m_stopReloadAction->data().toInt()));
    });
    navigationBar->addAction(m_stopReloadAction);

    m_urlLineEdit = new QLineEdit(this);
    m_favAction = new QAction(this);
    m_urlLineEdit->addAction(m_favAction, QLineEdit::LeadingPosition);
    m_urlLineEdit->setClearButtonEnabled(true);
    navigationBar->addWidget(m_urlLineEdit);

    auto downloadsAction = new QAction(this);
    downloadsAction->setIcon(QIcon(QStringLiteral(":/images/browser/icon/go-bottom.png")));
    downloadsAction->setToolTip(tr("Show downloads"));
    navigationBar->addAction(downloadsAction);
    connect(downloadsAction, &QAction::triggered, [this]() {
		if (m_browser->downloadManagerWidget()->isVisible())
			m_browser->downloadManagerWidget()->hide();
		else
			m_browser->downloadManagerWidget()->show();
    });

    return navigationBar;
}

void BrowserWindow::handleWebActionEnabledChanged(QWebEnginePage::WebAction action, bool enabled)
{
    switch (action) {
    case QWebEnginePage::Back:
        m_historyBackAction->setEnabled(enabled);
        break;
    case QWebEnginePage::Forward:
        m_historyForwardAction->setEnabled(enabled);
        break;
    case QWebEnginePage::Reload:
        m_reloadAction->setEnabled(enabled);
        break;
    case QWebEnginePage::Stop:
        m_stopAction->setEnabled(enabled);
        break;
    default:
        qWarning("Unhandled webActionChanged signal");
    }
}

void BrowserWindow::handleWebViewTitleChanged(const QString &title)
{
    QString suffix = m_profile->isOffTheRecord()
        ? tr("My Browser (Incognito)")
        : tr("My Browser");

    if (title.isEmpty())
        setWindowTitle(suffix);
    else
        setWindowTitle(title + " - " + suffix);
}

void BrowserWindow::handleNewWindowTriggered()
{
    m_browser->createWindow();
}

void BrowserWindow::handleNewIncognitoWindowTriggered()
{
    m_browser->createWindow(/* offTheRecord: */ true);
}

void BrowserWindow::handleFileOpenTriggered()
{
    QUrl url = QFileDialog::getOpenFileUrl(this, tr("Open Web Resource"), QString(),
                                                tr("Web Resources (*.html *.htm *.svg *.png *.gif *.svgz);;All files (*.*)"));
    if (url.isEmpty())
        return;
    currentTab()->setUrl(url);
}

void BrowserWindow::handleFindActionTriggered()
{
    if (!currentTab())
        return;
    bool ok = false;
    QString search = QInputDialog::getText(this, tr("Find"),
                                           tr("Find:"), QLineEdit::Normal,
                                           m_lastSearch, &ok);
	if (search.isEmpty()) {
		currentTab()->findText("");
	}
	else if (ok && !search.isEmpty()) {
        m_lastSearch = search;
        currentTab()->findText(m_lastSearch, 0, [this](bool found) {
            if (!found)
                statusBar()->showMessage(tr("\"%1\" not found.").arg(m_lastSearch));
        });
    }
}

void BrowserWindow::closeEvent(QCloseEvent *event)
{
    /*if (m_tabWidget->count() > 1) {
        int ret = QMessageBox::warning(this, tr("Confirm close"),
                                       tr("Are you sure you want to close the window ?\n"
                                          "There are %1 tabs open.").arg(m_tabWidget->count()),
                                       QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (ret == QMessageBox::No) {
            event->ignore();
            return;
        }
    }*/
	emit quit();
	if (proc != nullptr) {
		proc->kill();
		proc->waitForFinished();
		delete proc;
	}
    event->accept();
    deleteLater();
}

TabWidget *BrowserWindow::tabWidget() const
{
    return m_tabWidget;
}

WebView *BrowserWindow::currentTab() const
{
    return m_tabWidget->currentWebView();
}

void BrowserWindow::handleWebViewLoadProgress(int progress)
{
    static QIcon stopIcon(QStringLiteral(":/images/browser/icon/process-stop.png"));
    static QIcon reloadIcon(QStringLiteral(":/images/browser/icon/view-refresh.png"));

    if (0 < progress && progress < 100) {
        m_stopReloadAction->setData(QWebEnginePage::Stop);
        m_stopReloadAction->setIcon(stopIcon);
        m_stopReloadAction->setToolTip(tr("Stop loading the current page"));
        m_progressBar->setValue(progress);
    } else {
        m_stopReloadAction->setData(QWebEnginePage::Reload);
        m_stopReloadAction->setIcon(reloadIcon);
        m_stopReloadAction->setToolTip(tr("Reload the current page"));
        m_progressBar->setValue(0);
    }
}

void BrowserWindow::handleShowWindowTriggered()
{
    if (QAction *action = qobject_cast<QAction*>(sender())) {
        int offset = action->data().toInt();
        QVector<BrowserWindow*> windows = m_browser->windows();
        windows.at(offset)->activateWindow();
        windows.at(offset)->currentTab()->setFocus();
    }
}
