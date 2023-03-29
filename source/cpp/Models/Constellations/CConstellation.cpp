#include "CConstellation.h"

static const char* const_names[] = {
	"",
	QT_TRANSLATE_NOOP("CConstellation", "Andromeda"),
	QT_TRANSLATE_NOOP("CConstellation", "Antlia"),
	QT_TRANSLATE_NOOP("CConstellation", "Apus"),
	QT_TRANSLATE_NOOP("CConstellation", "Aquila"),
	QT_TRANSLATE_NOOP("CConstellation", "Aquarius"),
	QT_TRANSLATE_NOOP("CConstellation", "Ara"),
	QT_TRANSLATE_NOOP("CConstellation", "Aries"),
	QT_TRANSLATE_NOOP("CConstellation", "Auriga"),
	QT_TRANSLATE_NOOP("CConstellation", "Bootes"),
	QT_TRANSLATE_NOOP("CConstellation", "Caelum"),
	QT_TRANSLATE_NOOP("CConstellation", "Camelopardalis"),
	QT_TRANSLATE_NOOP("CConstellation", "Capricornus"),
	QT_TRANSLATE_NOOP("CConstellation", "Carina"),
	QT_TRANSLATE_NOOP("CConstellation", "Cassiopeia"),
	QT_TRANSLATE_NOOP("CConstellation", "Centaurus"),
	QT_TRANSLATE_NOOP("CConstellation", "Cepheus"),
	QT_TRANSLATE_NOOP("CConstellation", "Cetus"),
	QT_TRANSLATE_NOOP("CConstellation", "Chamaeleon"),
	QT_TRANSLATE_NOOP("CConstellation", "Circinus"),
	QT_TRANSLATE_NOOP("CConstellation", "Canis Major"),
	QT_TRANSLATE_NOOP("CConstellation", "Canis Minor"),
	QT_TRANSLATE_NOOP("CConstellation", "Cancer"),
	QT_TRANSLATE_NOOP("CConstellation", "Columba"),
	QT_TRANSLATE_NOOP("CConstellation", "Coma Berenices"),
	QT_TRANSLATE_NOOP("CConstellation", "Corona Australis"),
	QT_TRANSLATE_NOOP("CConstellation", "Corona Borealis"),
	QT_TRANSLATE_NOOP("CConstellation", "Crater"),
	QT_TRANSLATE_NOOP("CConstellation", "Crux"),
	QT_TRANSLATE_NOOP("CConstellation", "Corvus"),
	QT_TRANSLATE_NOOP("CConstellation", "Canes Venatici"),
	QT_TRANSLATE_NOOP("CConstellation", "Cygnus"),
	QT_TRANSLATE_NOOP("CConstellation", "Delphinus"),
	QT_TRANSLATE_NOOP("CConstellation", "Dorado"),
	QT_TRANSLATE_NOOP("CConstellation", "Draco"),
	QT_TRANSLATE_NOOP("CConstellation", "Equuleus"),
	QT_TRANSLATE_NOOP("CConstellation", "Eridanus"),
	QT_TRANSLATE_NOOP("CConstellation", "Fornax"),
	QT_TRANSLATE_NOOP("CConstellation", "Gemini"),
	QT_TRANSLATE_NOOP("CConstellation", "Grus"),
	QT_TRANSLATE_NOOP("CConstellation", "Hercules"),
	QT_TRANSLATE_NOOP("CConstellation", "Horologium"),
	QT_TRANSLATE_NOOP("CConstellation", "Hydra"),
	QT_TRANSLATE_NOOP("CConstellation", "Hydrus"),
	QT_TRANSLATE_NOOP("CConstellation", "Indus"),
	QT_TRANSLATE_NOOP("CConstellation", "Lacerta"),
	QT_TRANSLATE_NOOP("CConstellation", "Leo"),
	QT_TRANSLATE_NOOP("CConstellation", "Lepus"),
	QT_TRANSLATE_NOOP("CConstellation", "Libra"),
	QT_TRANSLATE_NOOP("CConstellation", "Leo Minor"),
	QT_TRANSLATE_NOOP("CConstellation", "Lupus"),
	QT_TRANSLATE_NOOP("CConstellation", "Lynx"),
	QT_TRANSLATE_NOOP("CConstellation", "Lyra"),
	QT_TRANSLATE_NOOP("CConstellation", "Mensa"),
	QT_TRANSLATE_NOOP("CConstellation", "Microscopium"),
	QT_TRANSLATE_NOOP("CConstellation", "Monoceros"),
	QT_TRANSLATE_NOOP("CConstellation", "Musca"),
	QT_TRANSLATE_NOOP("CConstellation", "Norma"),
	QT_TRANSLATE_NOOP("CConstellation", "Octans"),
	QT_TRANSLATE_NOOP("CConstellation", "Ophiuchus"),
	QT_TRANSLATE_NOOP("CConstellation", "Orion"),
	QT_TRANSLATE_NOOP("CConstellation", "Pavo"),
	QT_TRANSLATE_NOOP("CConstellation", "Pegasus"),
	QT_TRANSLATE_NOOP("CConstellation", "Perseus"),
	QT_TRANSLATE_NOOP("CConstellation", "Phoenix"),
	QT_TRANSLATE_NOOP("CConstellation", "Pictor"),
	QT_TRANSLATE_NOOP("CConstellation", "Piscis Austrinus"),
	QT_TRANSLATE_NOOP("CConstellation", "Pisces"),
	QT_TRANSLATE_NOOP("CConstellation", "Puppis"),
	QT_TRANSLATE_NOOP("CConstellation", "Pyxis"),
	QT_TRANSLATE_NOOP("CConstellation", "Reticulum"),
	QT_TRANSLATE_NOOP("CConstellation", "Sculptor"),
	QT_TRANSLATE_NOOP("CConstellation", "Scorpius"),
	QT_TRANSLATE_NOOP("CConstellation", "Scutum"),
	QT_TRANSLATE_NOOP("CConstellation", "Serpens"),
	QT_TRANSLATE_NOOP("CConstellation", "Sextans"),
	QT_TRANSLATE_NOOP("CConstellation", "Sagitta"),
	QT_TRANSLATE_NOOP("CConstellation", "Sagittarius"),
	QT_TRANSLATE_NOOP("CConstellation", "Taurus"),
	QT_TRANSLATE_NOOP("CConstellation", "Telescopium"),
	QT_TRANSLATE_NOOP("CConstellation", "Triangulum Australe"),
	QT_TRANSLATE_NOOP("CConstellation", "Triangulum"),
	QT_TRANSLATE_NOOP("CConstellation", "Tucana"),
	QT_TRANSLATE_NOOP("CConstellation", "Ursa Major"),
	QT_TRANSLATE_NOOP("CConstellation", "Ursa Minor"),
	QT_TRANSLATE_NOOP("CConstellation", "Vela"),
	QT_TRANSLATE_NOOP("CConstellation", "Virgo"),
	QT_TRANSLATE_NOOP("CConstellation", "Volans"),
	QT_TRANSLATE_NOOP("CConstellation", "Vulpecula")
};

QString CConstellation::toLatinName(tConstellation c)
{
	assert(c >= tConstellation::And && c <= tConstellation::Vul);
	return QString::fromLatin1(get_constellation_name(static_cast<::tConstellation>(c)));
}

QString CConstellation::toAbbreviation(tConstellation c)
{
	assert(c >= tConstellation::And && c <= tConstellation::Vul);
	return QString::fromLatin1(get_constellation_abbreviation(static_cast<::tConstellation>(c)));
}

QString CConstellation::toLocalName(tConstellation c)
{
	assert(c >= tConstellation::And && c <= tConstellation::Vul);
	return tr(const_names[static_cast<int>(c)]);
}

CConstellation::tConstellation CConstellation::fromLatinName(const QString& str, bool* ok)
{
	QByteArray c_str = str.toLatin1();
	if (!c_str.isEmpty()) {
		const char* c_data = c_str.constData();
		int begin = ::And, end = ::Vul + 1;
		while (begin != end) {
			if (strcmp(c_data, get_constellation_name(static_cast<::tConstellation>(begin))) == 0) {
				if (ok)
					*ok = true;
				return static_cast<tConstellation>(begin);
			}
			++begin;
		}
	}
	if (ok)
		*ok = false;
	return tConstellation::None;
}

CConstellation::tConstellation CConstellation::fromAbbreviation(const QString& str, bool* ok)
{
	QByteArray c_str = str.toLatin1();
	if (!c_str.isEmpty()) {
		const char* c_data = c_str.constData();
		int begin = ::And, end = ::Vul + 1;
		while (begin != end) {
			if (strcmp(c_data, get_constellation_abbreviation(static_cast<::tConstellation>(begin))) == 0) {
				if (ok)
					*ok = true;
				return static_cast<tConstellation>(begin);
			}
			++begin;
		}
	}
	if (ok)
		*ok = false;
	return tConstellation::None;
}
