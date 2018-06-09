#pragma once
#include "ui_downloadwidget.h"

#include <QFrame>
#include <QTime>
#include <qscopedpointer.h>

QT_BEGIN_NAMESPACE
class DownloadItem;
QT_END_NAMESPACE

// Displays one ongoing or finished download (DownloadItem).
class DownloadWidget2 final : public QFrame, public Ui::DownloadWidget
{
	Q_OBJECT
public:
	// Precondition: The QWebEngineDownloadItem has been accepted.
	explicit DownloadWidget2(DownloadItem *download, QWidget *parent = nullptr);
	~DownloadWidget2();

signals:
	// This signal is emitted when the user indicates that they want to remove
	// this download from the downloads list.
	void removeClicked(DownloadWidget2 *self);

private slots:
	void updateWidget();
	void changeDownloadState();

private:
	void setPauseIcon(bool isPause);

private:
	QString withUnit(qreal bytes);

	QScopedPointer<DownloadItem> m_download;
	QTime m_timeAdded;
	qint64 m_currentReceivedBytes;
};