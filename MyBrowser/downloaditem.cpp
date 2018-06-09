#include "downloaditem.h"
#include <qurl.h>
#include <qnetworkaccessmanager.h>
#include <qfileinfo.h>
#include <iostream>

DownloadItem::DownloadItem(QObject *parent) 
	: QObject(parent)
	, m_networkManager(new QNetworkAccessManager(this))
	, m_reply(nullptr)
	, m_state(DownloadItem::DownloadInProgress)
	, m_interruptReasonString("") {

}

DownloadItem::DownloadItem(QString path, QUrl url, QObject *parent)
	: QObject(parent)
	, m_networkManager(new QNetworkAccessManager(this))
	, m_reply(nullptr)
	, m_state(DownloadItem::DownloadInProgress)
	, m_totalBytes(0)
	, m_receivedBytes(0)
	, m_bytesCurrentReceived(0)
	, m_downloadPath(path)
	, m_srcUrl(url)
	, m_interruptReasonString("")
	, m_isPaused(false){
	
	fileRename(m_downloadPath);
	m_downloadPath += DOWNLOAD_FILE_SUFFIX;
	fileRename(m_downloadPath);
}

DownloadItem::~DownloadItem(){
}

#ifndef QT_NO_DATASTREAM
QDataStream& operator>>(QDataStream& in, DownloadItem *data)
{
	in >> data->m_totalBytes >> data->m_receivedBytes >> data->m_bytesCurrentReceived >> data->m_downloadPath >> data->m_srcUrl >> data->m_isPaused;
	return in;
}
QDataStream& operator<<(QDataStream& out, DownloadItem *data)
{
	out << data->m_totalBytes << data->m_receivedBytes << data->m_bytesCurrentReceived << data->m_downloadPath << data->m_srcUrl << data->m_isPaused;
	return out;
}
#endif

void DownloadItem::fileRename(QString &fileName) {
	if (QFile::exists(fileName)) {
		QString tempPath;
		QFileInfo fileInfo(fileName);
		QString suffix = "." + fileInfo.completeSuffix();
		QString path_left = fileName.left(fileName.lastIndexOf(suffix));
		for (int i = 1; ; i++) {
			tempPath = path_left + QString("(%1)").arg(i) + suffix;
			if (!QFile::exists(tempPath))
				break;
		}
		fileName = tempPath;
	}
}

inline void DownloadItem::removeFile(QString &fileName) {
	// 删除已下载的临时文件;
	if (QFile::exists(fileName)) {
		QFile::remove(fileName);
	}
}

void DownloadItem::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal) {
	m_receivedBytes = bytesReceived + m_bytesCurrentReceived;
	m_totalBytes = bytesTotal + m_bytesCurrentReceived;

	emit downloadProgress(m_receivedBytes, m_totalBytes);
}

void DownloadItem::onReadyRead() {
	QFile file(m_downloadPath);
	if (file.open(QIODevice::WriteOnly | QIODevice::Append))
	{
		file.write(m_reply->readAll());
	}
	file.close();
}

// 下载完成;
void DownloadItem::onFinished(){
	// http请求状态码;
	QVariant statusCode = m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

	if (m_reply->error() == QNetworkReply::NoError)
	{
		// 重命名临时文件;
		if (QFile::exists(m_downloadPath))
		{
			int index = m_downloadPath.lastIndexOf(DOWNLOAD_FILE_SUFFIX);
			QString realName = m_downloadPath.left(index);
			QFile::rename(m_downloadPath, realName);
		}
	}
	else{
		// 有错误输出错误;
		QString strError = m_reply->errorString();
		std::cout << "__________" + strError.toStdString() << std::endl;
	}
	changeState(DownloadItem::DownloadCompleted);
	stopWork();
}

void DownloadItem::onError(QNetworkReply::NetworkError code){
	m_interruptReasonString = m_reply->errorString();
	
	//closeDownload();
	pause();
	changeState(DownloadItem::DownloadInterrupted);
}

void DownloadItem::stopDownload(){
	stopWork();
	//记录当前已经下载字节数
	m_bytesCurrentReceived = m_receivedBytes;
}

// 停止下载工作;
void DownloadItem::stopWork(){
	if (m_reply) {
		disconnect(m_reply.data(), SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
		disconnect(m_reply.data(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
		disconnect(m_reply.data(), SIGNAL(finished()), this, SLOT(onFinished()));
		disconnect(m_reply.data(), SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
		m_reply->abort();
		m_reply.reset();
	}
}

void DownloadItem::reset(){
	m_bytesCurrentReceived = 0;
	m_receivedBytes = 0;
	m_totalBytes = 0;
	m_interruptReasonString = "";
	m_isPaused = false;
}

inline void DownloadItem::changeState(DownloadItem::DownloadState state) {
	m_state = state;
	emit stateChanged(m_state);
}

// 停止下载按钮被按下，关闭下载，重置参数，并删除下载的临时文件;
void DownloadItem::closeDownload(){
	stopWork();
	reset();
	removeFile(m_downloadPath);
}

void DownloadItem::accept() {
	if (m_receivedBytes <= 0)
		removeFile(m_downloadPath);

	QNetworkRequest request;
	request.setUrl(m_srcUrl);

	if (m_isPaused) {
		QString strRange = QString("bytes=%1-").arg(m_bytesCurrentReceived);
		request.setRawHeader("Range", strRange.toLatin1());
	}

	m_reply.reset(m_networkManager->get(request));

	connect(m_reply.data(), &QNetworkReply::downloadProgress, this, &DownloadItem::onDownloadProgress);
	connect(m_reply.data(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	connect(m_reply.data(), SIGNAL(finished()), this, SLOT(onFinished()));
	connect(m_reply.data(), SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));

	changeState(DownloadItem::DownloadInProgress);
}

void DownloadItem::cancel() {
	closeDownload();
	changeState(DownloadItem::DownloadCancelled);
}

void DownloadItem::pause() {
	if (!m_reply)
		return;
	stopDownload();
	m_isPaused = true;
}

void DownloadItem::resume() {
	accept();
	m_isPaused = false;
}