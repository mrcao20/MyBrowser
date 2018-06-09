#include "downloadwidget2.h"

#include <QFileInfo>
#include <QUrl>
#include "downloaditem.h"
#include <qdebug.h>
#include <qnetworkaccessmanager.h>
#include "downloaditem.h"

DownloadWidget2::DownloadWidget2(DownloadItem *download, QWidget *parent)
	: QFrame(parent)
	, m_download(download)
	, m_timeAdded(QTime::currentTime())
	, m_currentReceivedBytes(0)
{
	setupUi(this);
	m_dstName->setText(QFileInfo(m_download->path()).fileName());
	m_srcUrl->setText(m_download->url().toDisplayString());

	connect(m_pauseButton, &QPushButton::clicked, this, &DownloadWidget2::changeDownloadState);

	connect(m_cancelButton, &QPushButton::clicked,
		[this](bool) {
		if (m_download->state() == DownloadItem::DownloadInProgress)
			m_download->cancel();
		else
			emit removeClicked(this);
	});

	connect(m_download.data(), &DownloadItem::downloadProgress,
		this, &DownloadWidget2::updateWidget);

	connect(m_download.data(), &DownloadItem::stateChanged,
		this, &DownloadWidget2::updateWidget);

	updateWidget();
	setPauseIcon(m_download->isPaused());
}

void DownloadWidget2::changeDownloadState() {
	if (m_download->isPaused()) {
		m_download->resume();
		m_timeAdded.restart();
	}
	else {
		m_download->pause();
		m_currentReceivedBytes = m_download->receivedBytes();
	}
	setPauseIcon(m_download->isPaused());
}

void DownloadWidget2::setPauseIcon(bool isPause) {
	if (isPause)
		m_pauseButton->setIcon(QIcon(":/images/browser/icon/start.jpg"));
	else
		m_pauseButton->setIcon(QIcon(":/images/browser/icon/pause.jpg"));
}

DownloadWidget2::~DownloadWidget2() {
	if (m_download) {
		m_download->pause();
		if (m_download->isPaused()) {
			QFileInfo fileInfo(m_download->path());
			QString fileName = qApp->applicationDirPath() + "/data/serialization/" + fileInfo.fileName() + ".save";
			QFile file(fileName);
			file.open(QIODevice::WriteOnly);
			QDataStream out(&file);
			out << m_download.data();
			file.close();
		}
	}
}

inline QString DownloadWidget2::withUnit(qreal bytes)
{
	if (bytes < (1 << 10))
		return tr("%L1 B").arg(bytes);
	else if (bytes < (1 << 20))
		return tr("%L1 KiB").arg(bytes / (1 << 10), 0, 'f', 2);
	else if (bytes < (1 << 30))
		return tr("%L1 MiB").arg(bytes / (1 << 20), 0, 'f', 2);
	else
		return tr("%L1 GiB").arg(bytes / (1 << 30), 0, 'f', 2);
}

void DownloadWidget2::updateWidget()
{
	qreal totalBytes = m_download->totalBytes();
	qreal receivedBytes = m_download->receivedBytes();
	qreal bytesPerSecond = (receivedBytes - m_currentReceivedBytes) / m_timeAdded.elapsed() * 1000;

	auto state = m_download->state();
	switch (state) {
	case DownloadItem::DownloadInProgress:
		if (totalBytes >= 0) {
			m_progressBar->setValue(qRound(100 * receivedBytes / totalBytes));
			m_progressBar->setDisabled(false);
			m_progressBar->setFormat(
				tr("%p% - %1 of %2 downloaded - %3/s")
				.arg(withUnit(receivedBytes))
				.arg(withUnit(totalBytes))
				.arg(withUnit(bytesPerSecond)));
		}
		else {
			m_progressBar->setValue(0);
			m_progressBar->setDisabled(false);
			m_progressBar->setFormat(
				tr("unknown size - %1 downloaded - %2/s")
				.arg(withUnit(receivedBytes))
				.arg(withUnit(bytesPerSecond)));
		}
		break;
	case DownloadItem::DownloadCompleted:
		m_pauseButton->hide();
		m_progressBar->setValue(100);
		m_progressBar->setDisabled(true);
		m_progressBar->setFormat(
			tr("completed - %1 downloaded - %2/s")
			.arg(withUnit(receivedBytes))
			.arg(withUnit(bytesPerSecond)));
		break;
	case DownloadItem::DownloadCancelled:
		m_progressBar->setValue(0);
		m_progressBar->setDisabled(true);
		m_progressBar->setFormat(
			tr("cancelled - %1 downloaded - %2/s")
			.arg(withUnit(receivedBytes))
			.arg(withUnit(bytesPerSecond)));
		break;
	case DownloadItem::DownloadInterrupted:
		m_progressBar->setValue(0);
		m_progressBar->setDisabled(true);
		m_progressBar->setFormat(
			tr("interrupted: %1")
			.arg(m_download->interruptReasonString()));
		break;
	}

	if (state == DownloadItem::DownloadInProgress) {
		static QIcon cancelIcon(QStringLiteral(":/images/browser/icon/process-stop.png"));
		m_cancelButton->setIcon(cancelIcon);
		m_cancelButton->setToolTip(tr("Stop downloading"));
	}
	else {
		static QIcon removeIcon(QStringLiteral(":/images/browser/icon/edit-clear.png"));
		m_cancelButton->setIcon(removeIcon);
		m_cancelButton->setToolTip(tr("Remove from list"));
		m_pauseButton->setIcon(QIcon(":/images/browser/icon/start.jpg"));
	}
}