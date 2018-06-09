#include "browser.h"
#include "browserwindow.h"
#include "webview.h"
#include <QApplication>
#include <QWebEngineSettings>

QUrl url(QStringLiteral("https://www.google.com/"));

QUrl commandLineUrlArgument()
{
    const QStringList args = QCoreApplication::arguments();
    for (const QString &arg : args.mid(1)) {
        if (!arg.startsWith(QLatin1Char('-')))
            return QUrl::fromUserInput(arg);
    }
    return url;
}

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	//QApplication::addLibraryPath("./plugins");
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(QStringLiteral(":/images/browser/icon/AppLogoColor.png")));

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
	QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);

    QUrl url = commandLineUrlArgument();
	
	//QNetworkProxy proxy;
	//proxy.setType(QNetworkProxy::Socks5Proxy);//��������
	//proxy.setHostName("127.0.0.1");//���ô����������ַ
	//proxy.setPort(1080);//���ö˿�
	//QNetworkProxy::setApplicationProxy(proxy);

    Browser browser;
    BrowserWindow *window = browser.createWindow();
    window->currentTab()->setUrl(url);

    return app.exec();
}
