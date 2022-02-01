#pragma once

class CPlanets
{
public:
	typedef double tJupiterSatellites[4][2];

	explicit CPlanets(double jd_utc = 0);

	void setJD(double jd_utc);

	void Moon(double *ra, double *dec, double *rad = nullptr, double *phase = nullptr) const;
	void Sun(double* ra, double* dec, double* rad = nullptr) const;
	void Mercury(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;
	void Venus(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;
	void Mars(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;
	void Jupiter(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;
	void Saturn(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;
	void Uranus(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;
	void Neptune(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;
	void Pluto(double* ra, double* dec, double* rad = nullptr, double* phase = nullptr) const;

	void JupiterSatellites(tJupiterSatellites& jsat) const {
		return JupiterSatellites(m_jd, jsat);
	}
	static void JupiterSatellites(double jd_utc, tJupiterSatellites& jsat);

private:
	// Julian date (UTC)
	double m_jd;

	// Mercury
	double m_m1, m_u1, m_VL1;

	// Venus
	double m_m2, m_u2, m_VL2;

	// Mars
	double m_m4, m_u4, m_VL4;

	// Jupiter
	double m_m5, m_u5, m_VL5;

	// Saturn
	double m_m6, m_u6, m_VL6;

	// Uranus
	double m_m7, m_u7, m_VL7;

	// Neptune
	double m_m8, m_u8, m_VL8;

	// Pluto
	double m_m9, m_u9, m_VL9;

	// Sun
	double m_ms, m_Ls;
	double m_lambdas, m_betas, m_ds;

	// Moon
	double m_mm, m_um, m_fm, m_om, m_Lm;

	// Miscellaneous
	double m_VT2000, m_eps;

	// Miscellaneous
	double m_t, m_vt;

	void Init();
	void Done(double lr, double br, double* ra, double* de) const;
	void DoneGeoc(double la, double be, double* ra, double* de) const;
	void DoneHelioc(double l, double b, double r, double* ra, double* de, double* rad, double* phase) const;
	void _Moon(double& la, double& be, double& r) const;
	void _Sun(double& la, double& r) const;
	void _Mercury(double& l, double& b, double& r) const;
	void _Venus(double& l, double& b, double& r) const;
	void _Mars(double& l, double& b, double& r) const;
	void _Jupiter(double& l, double& b, double& r) const;
	void _Saturn(double& l, double& b, double& r) const;
	void _Uranus(double& l, double& b, double& r) const;
	void _Neptune(double& l, double& b, double& r) const;
	void _Pluto(double& l, double& b, double& r) const;
};
