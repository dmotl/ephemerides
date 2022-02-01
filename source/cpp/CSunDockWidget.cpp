#include "CSunDockWidget.h"

#include "CSharedData.h"
#include "CJulianDate.h"
#include "CPlanets.h"
#include "Utils.h"

CSunDockWidget::CSunDockWidget(CSharedData* data, QWidget* parent) : QDockWidget(parent), m_sharedData(data),
m_pixmap(QStringLiteral(":/Resources/Sun256.png"))
{
	setupUi(this);
	setWindowTitle(tr("Sun"));

	m_labelSize = label->size();
	QPixmap p = m_pixmap.scaled(m_labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	label->setPixmap(p);
	label->setMinimumSize(1, 1);
	label->setScaledContents(false);
	
	localTimeButton->blockSignals(true);
	localTimeButton->setChecked(true);
	localTimeButton->blockSignals(false);

	reset();

	connect(m_sharedData, &CSharedData::dateTimeChanged, this, &CSunDockWidget::onDateTimeChanged);
	connect(m_sharedData, &CSharedData::geoLocationChanged, this, &CSunDockWidget::onGeoLocationChanged);
}

void CSunDockWidget::resizeEvent(QResizeEvent* ev)
{
	if (m_labelSize != label->size()) {
		m_labelSize = label->size();
		QPixmap p = m_pixmap.scaled(m_labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		label->setPixmap(p);
	}

	QDockWidget::resizeEvent(ev);
}

void CSunDockWidget::onDateTimeChanged()
{
	QDate d = m_sharedData->getSelectedLocalDateTime().date();
	if (m_date != d) {
		m_date = d;
		updateDateTime();
		updateValues();
	}
}

void CSunDockWidget::on_dateEdit_dateChanged(const QDate& date)
{
	if (m_date != date) {
		m_date = date;
		updateDateTime();
		updateValues();
	}
}

void CSunDockWidget::on_lonEdit_textChanged(const QString& text)
{
	CLongitude lon(text.toStdWString());
	if (lon.isValid() && lon != m_geoloc.longitude()) {
		m_geoloc.setLongitude(lon);
		updateValues();
	}
}

void CSunDockWidget::on_lonEdit_editingFinished()
{
	updateGeoLocation();
}
void CSunDockWidget::on_latEdit_editingFinished()
{
	updateGeoLocation();
}

void CSunDockWidget::on_latEdit_textChanged(const QString& text)
{
	CLatitude lat(text.toStdWString());
	if (lat.isValid() && lat != m_geoloc.latitude()) {
		m_geoloc.setLatitude(lat);
		updateValues();
	}
}

void CSunDockWidget::onGeoLocationChanged()
{
	CGeoLocation gl = m_sharedData->geoLocation();
	if (gl != m_geoloc) {
		m_geoloc = gl;
		updateGeoLocation();
		updateValues();
	}
}

void CSunDockWidget::updateDateTime()
{
	if (m_date.isValid()) {
		dateEdit->blockSignals(true);
		dateEdit->setDate(m_date);
		dateEdit->blockSignals(false);
	}
}

void CSunDockWidget::updateGeoLocation()
{
	lonEdit->blockSignals(true);
	if (m_geoloc.longitude().isValid())
		lonEdit->setText(QString::fromStdWString(m_geoloc.longitude().toString()));
	else
		lonEdit->setText(QStringLiteral("***"));
	lonEdit->blockSignals(false);

	latEdit->blockSignals(true);
	if (m_geoloc.latitude().isValid())
		latEdit->setText(QString::fromStdWString(m_geoloc.latitude().toString()));
	else
		latEdit->setText(QStringLiteral("***"));
	latEdit->blockSignals(false);
}

bool CSunDockWidget::computeSunRiseSet(double jd, QDateTime& rise, QDateTime& set) const
{
	static const double eps = HMS_TO_JD(0, 1, 0);

	CJulianDate jd0(jd);

	CJulianDate::tRiseSetResult res_1 = CJulianDate::rcOK;
	double jd_rise = jd0.jd_utc();
	for (int i = 0; i < 10; i++) {
		double last_jd = jd_rise, ra, de;
		CPlanets(jd_rise).Sun(&ra, &de);
		res_1 = jd0.RaDeToRise(ra, de, m_geoloc.longitude().radians(), m_geoloc.latitude().radians(), &jd_rise);
		if (res_1 != CJulianDate::rcOK || fabs(jd_rise - last_jd) < eps)
			break;
	}

	CJulianDate::tRiseSetResult res_2 = CJulianDate::rcOK;
	double jd_set = jd0.jd_utc();
	for (int i = 0; i < 10; i++) {
		double last_jd = jd_set, ra, de;
		CPlanets(jd_set).Sun(&ra, &de);
		res_2 = jd0.RaDeToSet(ra, de, m_geoloc.longitude().radians(), m_geoloc.latitude().radians(), &jd_set);
		if (res_2 != CJulianDate::rcOK || fabs(jd_set - last_jd) < eps)
			break;
	}
	if (res_1 == CJulianDate::rcOK && res_2 == CJulianDate::rcOK) {
		CDateTime dt_rise = CJulianDate(jd_rise).toDateTime();
		rise = QDateTime(QDate(dt_rise.year(), dt_rise.month(), dt_rise.day()), QTime(dt_rise.hour(), dt_rise.minute(), dt_rise.second()), Qt::UTC);
		if (localTimeButton->isChecked())
			rise = rise.toLocalTime();
		CDateTime dt_set = CJulianDate(jd_set).toDateTime();
		set = QDateTime(QDate(dt_set.year(), dt_set.month(), dt_set.day()), QTime(dt_set.hour(), dt_set.minute(), dt_set.second()), Qt::UTC);
		if (localTimeButton->isChecked())
			set = set.toLocalTime();
		return true;
	}
	else {
		rise = set = QDateTime();
		return false;
	}
}

bool CSunDockWidget::computeTwilight(double jd, QDateTime& start, QDateTime& end) const
{
	static const double eps = HMS_TO_JD(0, 1, 0);
	double twel = -DEG_TO_RAD(m_sharedData->twilightElevation());
	CJulianDate jd0(jd);

	CJulianDate::tRiseSetResult res_1 = CJulianDate::rcOK;
	double jd_end = jd0.jd_utc();
	for (int i = 0; i < 10; i++) {
		double last_jd = jd_end, ra, de;
		CPlanets(jd_end).Sun(&ra, &de);
		res_1 = jd0.RaDeToRise(ra, de, m_geoloc.longitude().radians(), m_geoloc.latitude().radians(), &jd_end, twel);
		if (res_1 != CJulianDate::rcOK || fabs(jd_end - last_jd) < eps)
			break;
	}
	CJulianDate::tRiseSetResult res_2 = CJulianDate::rcOK;
	double ra, de, jd_start = jd0.jd_utc();
	for (int i = 0; i < 10; i++) {
		double last_jd = jd_start;
		CPlanets(jd_start).Sun(&ra, &de);
		res_2 = jd0.RaDeToSet(ra, de, m_geoloc.longitude().radians(), m_geoloc.latitude().radians(), &jd_start, twel);
		if (res_2 != CJulianDate::rcOK || fabs(jd_start - last_jd) < eps)
			break;
	}
	if (res_1 == CJulianDate::rcOK && res_2 == CJulianDate::rcOK) {
		CDateTime dt_end = CJulianDate(jd_end).toDateTime();
		end = QDateTime(QDate(dt_end.year(), dt_end.month(), dt_end.day()), QTime(dt_end.hour(), dt_end.minute(), dt_end.second()), Qt::UTC);
		if (localTimeButton->isChecked())
			end = end.toLocalTime();

		CDateTime dt_start = CJulianDate(jd_start).toDateTime();
		start = QDateTime(QDate(dt_start.year(), dt_start.month(), dt_start.day()), QTime(dt_start.hour(), dt_start.minute(), dt_start.second()), Qt::UTC);
		if (localTimeButton->isChecked())
			start = start.toLocalTime();
		return true;
	}
	else {
		start = end = QDateTime();
		return false;
	}
}

void CSunDockWidget::updateValues()
{
	QDateTime mutc = QDateTime(m_date, QTime(0, 0));

	if (!m_date.isValid() || !m_geoloc.isValid()) {
		QString invalidInputStr = tr("Invalid input");
		sunrise->setText(invalidInputStr);
		sunset->setText(invalidInputStr);
		twilightEnd->setText(invalidInputStr);
		twilightStart->setText(invalidInputStr);
	}
	else {
		double jd0 = mutc.addDays(1).toUTC().date().toJulianDay() + 0.5;

		QDateTime rise, set;
		if (computeSunRiseSet(jd0, rise, set)) {
			sunrise->setText(rise.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
			sunset->setText(set.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
		}
		else {
			sunrise->setText(QStringLiteral("***"));
			sunset->setText(QStringLiteral("***"));
		}
		QDateTime start, end;
		if (computeTwilight(jd0, start, end)) {
			twilightStart->setText(start.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
			twilightEnd->setText(end.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
		}
		else {
			twilightStart->setText(QStringLiteral("***"));
			twilightEnd->setText(QStringLiteral("***"));
		}
	}

	if (!m_date.isValid() || !m_geoloc.isValid()) {
		QString invalidInputStr = tr("Invalid input");
		rasc->setText(invalidInputStr);
		decl->setText(invalidInputStr);
	}
	else {
		double jd0 = mutc.addDays(1).toUTC().date().toJulianDay() + 0.5;

		double ra, dec;
		CPlanets(jd0).Sun(&ra, &dec);
		ra = ra * 12 / M_PI;
		if (ra < 0)
			ra = 24 + ra;
		rasc->setText(QString::number(ra, 'f', 4));
		dec = RAD_TO_DEG(dec);
		decl->setText(QString::number(dec, 'f', 4));
	}

}

void CSunDockWidget::on_resetButton_clicked()
{
	reset();
}

void CSunDockWidget::reset()
{
	m_date = m_sharedData->getSelectedLocalDateTime().date();
	updateDateTime();
	m_geoloc = m_sharedData->geoLocation();
	updateGeoLocation();
	updateValues();
}

void CSunDockWidget::on_localTimeButton_toggled(bool checked)
{
	if (checked)
		updateValues();
}

void CSunDockWidget::on_universalTimeButton_toggled(bool checked)
{
	if (checked)
		updateValues();
}