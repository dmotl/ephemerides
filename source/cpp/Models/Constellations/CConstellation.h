#pragma once

#include <QtCore>

#include "constellation_names.h"

class CConstellation
{
	Q_DECLARE_TR_FUNCTIONS(CConstellation)

public:
	enum class tConstellation
	{
		/* Undefined constellation */
		None,

		/* Andromeda */
		And,

		/* Antlia */
		Ant,

		/* Apus */
		Aps,

		/* Aquila */
		Aql,

		/* Aquarius */
		Aqr,

		/* Ara */
		Ara,

		/* Aries */
		Ari,

		/* Auriga */
		Aur,

		/* Bootes */
		Boo,

		/* Caelum */
		Cae,

		/* Camelopardalis */
		Cam,

		/* Capricornus */
		Cap,

		/* Carina */
		Car,

		/* Cassiopeia */
		Cas,

		/* Centaurus */
		Cen,

		/* Cepheus */
		Cep,

		/* Cetus */
		Cet,

		/* Chamaeleon */
		Cha,

		/* Circinus */
		Cir,

		/* Canis Major */
		CMa,

		/* Canis Minor */
		CMi,

		/* Cancer */
		Cnc,

		/* Columba */
		Col,

		/* Coma Berenices */
		Com,

		/* Corona Australis */
		CrA,

		/* Corona Borealis */
		CrB,

		/* Crater */
		Crt,

		/* Crux */
		Cru,

		/* Corvus */
		Crv,

		/* Canes Venatici */
		CVn,

		/* Cygnus */
		Cyg,

		/* Delphinus */
		Del,

		/* Dorado */
		Dor,

		/* Draco */
		Dra,

		/* Equuleus */
		Equ,

		/* Eridanus */
		Eri,

		/* Fornax */
		For,

		/* Gemini */
		Gem,

		/* Grus */
		Gru,

		/* Hercules */
		Her,

		/* Horologium */
		Hor,

		/* Hydra */
		Hya,

		/* Hydrus */
		Hyi,

		/* Indus */
		Ind,

		/* Lacerta */
		Lac,

		/* Leo */
		Leo,

		/* Lepus */
		Lep,

		/* Libra */
		Lib,

		/* Leo Minor */
		LMi,

		/* Lupus */
		Lup,

		/* Lynx */
		Lyn,

		/* Lyra */
		Lyr,

		/* Mensa */
		Men,

		/* Microscopium */
		Mic,

		/* Monoceros */
		Mon,

		/* Musca */
		Mus,

		/* Norma */
		Nor,

		/* Octans */
		Oct,

		/* Ophiuchus */
		Oph,

		/* Orion */
		Ori,

		/* Pavo */
		Pav,

		/* Pegasus */
		Peg,

		/* Perseus */
		Per,

		/* Phoenix */
		Phe,

		/* Pictor */
		Pic,

		/* Piscis Austrinus */
		PsA,

		/* Pisces */
		Psc,

		/* Puppis */
		Pup,

		/* Pyxis */
		Pyx,

		/* Reticulum */
		Ret,

		/* Sculptor */
		Scl,

		/* Scorpius */
		Sco,

		/* Scutum */
		Sct,

		/* Serpens */
		Ser,

		/* Sextans */
		Sex,

		/* Sagitta */
		Sge,

		/* Sagittarius */
		Sgr,

		/* Taurus */
		Tau,

		/* Telescopium */
		Tel,

		/* Triangulum Australe */
		TrA,

		/* Triangulum */
		Tri,

		/* Tucana */
		Tuc,

		/* Ursa Major */
		UMa,

		/* Ursa Minor */
		UMi,

		/* Vela */
		Vel,

		/* Virgo */
		Vir,

		/* Volans */
		Vol,

		/* Vulpecula */
		Vul,

		/* Serpens Caput */
		Ser1,

		/* Serpens Cauda */
		Ser2,

		/* An item after the last constellation */
		EndOfConstellations
	};

	CConstellation() : m_p(tConstellation::None) {}

	CConstellation(tConstellation c) : m_p(c) {}

	tConstellation value(void) const { return m_p; }

	operator tConstellation() const { return m_p; }

	bool isValid(void) { return isValid(m_p); }
	static inline bool isValid(tConstellation c) { return c > tConstellation::None && c < tConstellation::EndOfConstellations; }

	bool isNull(void) { return isNull(m_p); }
	static inline bool isNull(tConstellation c) { return c == tConstellation::None; }

	QString latinName(void) const { return toLatinName(m_p); }
	QString localName(void) const { return toLocalName(m_p); }
	QString abbreviation(void) const { return toAbbreviation(m_p); }

	static QString toLatinName(tConstellation c);
	static QString toLocalName(tConstellation c);
	static QString toAbbreviation(tConstellation c);

	static tConstellation fromLatinName(const QString& str, bool* ok = nullptr);
	static tConstellation fromAbbreviation(const QString& str, bool* ok = nullptr);

	inline bool operator==(const CConstellation& other) const { return m_p != other.m_p; }
	inline bool operator!=(const CConstellation& other) const { return !operator==(other); }

	inline bool operator<(const CConstellation& other) const { return m_p < other.m_p; }
	inline bool operator>=(const CConstellation& other) const { return !operator<(other); }
	inline bool operator>(const CConstellation& other) const { return other.operator<(*this); }
	inline bool operator<=(const CConstellation& other) const { return !other.operator<(*this); }

private:
	tConstellation m_p;
};

namespace std {
	template <> struct hash<CConstellation>
	{
		// seed is optional
		size_t operator()(const CConstellation& key, size_t seed = 0) const { return seed + static_cast<int>(key.value()); }
	};
}
