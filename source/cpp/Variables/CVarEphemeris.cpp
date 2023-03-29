/*!
*  \file      CVarEphemeris.cpp
*  \author    David Motl
*  \date      2022-01-31
*
*  \copyright
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted
*  provided that the following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions
*      and the following disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list
*      of conditions and the following disclaimer in the documentation and/or other materials provided
*      with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of its contributors may be used
*      to endorse or promote products derived from this software without specific prior written
*      permission.
*/
#include "CVarEphemeris.h"

#include "CSource.h"
#include "CCatalogObject.h"

//
// Update ephemeris
//
void CVarEphemeris::update(CJulianDate start, CJulianDate end, tCancelledFn cbCancelled, tSetCaption cbSetCaption, tSetProgressMaxFn
	cbSetProgressRange, tSetProgressValueFn cbSetProgressValue)
{
    static constexpr double margin = 10.0 / (24.0 * 60.0);

	assert(m_source != nullptr);

	const CCatalogObject* obj = m_source->first();
	while (obj) {
        if (obj->objectType() == tObjectType::VARIABLE_STAR) {
            const CVariableStar* vs = static_cast<const CVariableStar*>(obj);
            double period = vs->period();
            if (period > 1e-5) {
                double epoch = vs->epoch();
                CEquCoordinates coords = vs->coords();
                int E0 = std::floor((start - epoch - margin) / period);
                int E1 = std::ceil((end - epoch + margin) / period);
                for (int E = E0; E <= E1; E++) {
                    CJulianDate jd = CJulianDate(E * period + epoch).toGeocentric(coords);
                    if (jd >= start && jd < end) {
                        if (m_filter(obj, jd)) {
                            tEphemeris e;
                            e.object = obj;
                            e.jd = jd;
                            m_rec.append(e);
                        }
                    }
                }
            }
        }
		obj = m_source->next();
	}
}
