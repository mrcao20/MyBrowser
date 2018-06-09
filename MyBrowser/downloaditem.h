#pragma once

#include <qobject.h>
#include <qnetworkreply.h>
#include <qscopedpointer.h>
#include <qdatastream.h>

// 给正在下载的文件添加一个后缀，当文件下载完成时，取消后缀
#define DOWNLOAD_FILE_SUFFIX ".download"

QT_BEGIN_NAMESPACE
class QNetworkAccessManager;
QT_END_NAMESPACE

class DownloadItem : public QObject{

	Q_OBJECT

public:
	enum DownloadState {
		DownloadInProgress,
		DownloadCompleted,
		DownloadCancelled,
		DownloadInterrupted,
	};

	DownloadItem(QString path, QUrl url, QObject *parent = nullptr);
	DownloadItem(QObject *parent = nullptr);
	~DownloadItem();

	DownloadState state() { return m_state; }
	qint64 totalBytes() { return m_totalBytes; }
	qint64 receivedBytes() { return m_receivedBytes; }
	QUrl url() { return m_srcUrl; }
	QString path() { return m_downloadPath.left(m_downloadPath.lastIndexOf(DOWNLOAD_FILE_SUFFIX)); }
	QString completePath() { return m_downloadPath; }
	QString interruptReasonString() { return m_interruptReasonString; }
	bool isPaused() { return m_isPaused; }

#ifndef QT_NO_DATASTREAM
	friend QDataStream& operator>>(QDataStream&, DownloadItem *);
	friend QDataStream& operator<<(QDataStream&, DownloadItem *);
#endif

signals:
	void downloadProgress(qint64, qint64);
	void stateChanged(DownloadItem::DownloadState);

public slots:
	void accept();
	void cancel();
	void pause();
	void resume();

private slots:
	void onDownloadProgress(qint64, qint64);
	void onReadyRead();
	void onFinished();
	void onError(QNetworkReply::NetworkError code);

private:
	void removeFile(QString &);
	void closeDownload();
	void stopDownload();
	void stopWork();
	void reset();
	void changeState(DownloadItem::DownloadState);
	void fileRename(QString &fileName);

private:
	QNetworkAccessManager * m_networkManager;
	QScopedPointer<QNetworkReply> m_reply;
	DownloadState m_state;
	qint64 m_totalBytes;
	qint64 m_receivedBytes;
	qint64 m_bytesCurrentReceived;
	QString m_downloadPath;
	QUrl m_srcUrl;
	QString m_interruptReasonString;
	bool m_isPaused;

};