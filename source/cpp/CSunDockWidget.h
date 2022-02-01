#pragma once

#include <QtWidgets>

#include "CGeoLocation.h"

#include "ui_CSunDockWidget.h"

class CSharedData;

class CSunDockWidget : public QDockWidget, private Ui::CSunDockWidget
{
	Q_OBJECT

public:
	CSunDockWidget(CSharedData* data, QWidget* parent);

protected:
	void resizeEvent(QResizeEvent*) override;

protected slots:
	void onDateTimeChanged();
	void onGeoLocationChanged();

	void on_dateEdit_dateChanged(const QDate& date);
	void on_lonEdit_textChanged(const QString& text);
	void on_latEdit_textChanged(const QString& text);

	void on_lonEdit_editingFinished();
	void on_latEdit_editingFinished();

	void on_resetButton_clicked();
	void on_localTimeButton_toggled(bool checked);
	void on_universalTimeButton_toggled(bool checked);

private:
	CSharedData* m_sharedData;
	QDate m_date;
	CGeoLocation m_geoloc;

	QPixmap m_pixmap;
	QSize m_labelSize;

	void reset();
	void updateDateTime();
	void updateGeoLocation();
	void updateValues();

	bool computeSunRiseSet(double jd0, QDateTime& rise, QDateTime& set) const;
	bool computeTwilight(double jd0, QDateTime& start, QDateTime& end) const;
};
