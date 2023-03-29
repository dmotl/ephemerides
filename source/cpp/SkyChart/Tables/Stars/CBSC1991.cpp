/*!
*  \file      CBSC1991.cpp
*  \author    David Motl
*  \date      2022-05-11
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
#include "CBSC1991.h"

#include "bsc91_tables.h"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

#if 0

//
// Trim trailing whitechars
//
static std::string rtrim(const std::string& s)
{
    static const std::string WHITESPACE = " \n\r\t\f\v";

    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}


//
// Trim leading whitechars
//
static std::string ltrim(const std::string& s)
{
    static const std::string WHITESPACE = " \n\r\t\f\v";

    size_t startpos = s.find_first_not_of(WHITESPACE);
    return (startpos == std::string::npos) ? "" : s.substr(startpos);
}

#endif

CBSC1991_Embedded::CBSC1991_Embedded()
{
    int length = sizeof(bsc91_table) / sizeof(tBSC91Table);
    for (int i = 0; i < length; i++) {
        const tBSC91Table* src = bsc91_table + i;

        CEquCoordinates equ(CRightAscension::fromHours((double)src->ra / 36000.0), CDeclination::fromDegrees((double)src->dec / 3600.0));
        CObject* obj = new CObject(src->bs_id, src->hd_id, equ, (double)src->vmag / 100.0);
        m_list.push_back(obj);
        if (src->bs_id > 0)
            m_bs_id_map.insert({ src->bs_id, obj });
        if (src->hd_id > 0)
            m_hd_id_map.insert({ src->hd_id, obj });
    }
}

CBSC1991_Embedded::~CBSC1991_Embedded()
{
    auto begin = m_list.begin(), end = m_list.end();
    while (begin != end) {
        delete* begin;
        begin++;
    }
}

#if 0

void CBSC1991_Embedded::clear()
{
    auto begin = m_list.begin(), end = m_list.end();
    while (begin != end) {
        delete* begin;
        begin++;
    }
    m_list.clear();

    m_bs_id_map.clear();
    m_hd_id_map.clear();
}

bool CBSC1991_Embedded::load(const char* dirPath)
{
    clear();

    bool retval = false;
    try
    {
        std::filesystem::path cat_file = std::filesystem::path(dirPath) / "catalog";

    std::fstream newfile;
    newfile.open(cat_file.string().c_str(), std::ios::in);
    if (newfile.is_open()) {
        std::string tp;
        while (getline(newfile, tp)) {
            try
            {
                /* 1-  4  I4     ---     HR       [1/9110]+ Harvard Revised Number = Bright Star Number */
                int id = std::stoi(tp.substr(0, 4));

                /* 5- 14  A10    ---     Name     Name, generally Bayer and/or Flamsteed name */
                std::string name = tp.substr(4, 10);

                /* 15- 25  A11    ---     DM       Durchmusterung Identification (zone in bytes 17-19) */
                std::string dm = tp.substr(14, 11);

                /* 26- 31  I6     ---     HD       [1/225300]? Henry Draper Catalog Number */
                std::string hd = tp.substr(25, 5);

                /* 32- 37  I6     ---     SAO      [1/258997]? SAO Catalog Number */
                std::string sao = tp.substr(31, 6);

                /* 38- 41  I4     ---     FK5      ? FK5 star Number */
                std::string fk5 = tp.substr(37, 4);

                /* 76- 77  I2     h       RAh      ?Hours RA, equinox J2000, epoch 2000.0 (1) */
                int rah = stoi(tp.substr(75, 2));

                /* 78- 79  I2     min     RAm      ?Minutes RA, equinox J2000, epoch 2000.0 (1) */
                int ram = stoi(tp.substr(77, 2));

                /* 80- 83  F4.1   s       RAs      ?Seconds RA, equinox J2000, epoch 2000.0 (1) */
                double ras = 0;
                strToFloat(tp.substr(79, 4), ras);

                /* 84  A1     ---     DE-      ?Sign Dec, equinox J2000, epoch 2000.0 (1) */
                int dec_sgn = tp.substr(83, 1) == "-" ? -1 : +1;

                /* 85- 86  I2     deg     DEd      ?Degrees Dec, equinox J2000, epoch 2000.0 (1) */
                int ded = stoi(tp.substr(84, 2));

                /* 87- 88  I2     arcmin  DEm      ?Minutes Dec, equinox J2000, epoch 2000.0 (1) */
                int dem = stoi(tp.substr(86, 2));

                /* 89- 90  I2     arcsec  DEs      ?Seconds Dec, equinox J2000, epoch 2000.0 (1) */
                int des = stoi(tp.substr(88, 2));

                /* 103-107  F5.2   mag     Vmag     ?Visual magnitude (1) */
                double v_mag = invalidMagnitude();
                strToFloat(tp.substr(102, 5), v_mag);

                if (id > 0 && v_mag != invalidMagnitude()) {
                    CDeclination dec = CDeclination::fromDegrees(dec_sgn * (ded + static_cast<double>(dem) / 60.0 + static_cast<double>(des) / 3600.0));
                    CRightAscension ra = CRightAscension::fromHours(rah + static_cast<double>(ram) / 60.0 + static_cast<double>(ras) / 3600.0);
                    CObject* ptr = new CObject(id, CEquCoordinates(ra, dec), v_mag);
                    m_list.push_back(ptr);
                    m_idmap.insert({ id, ptr });
                }
            }
            catch (const std::invalid_argument&) {
                // Silently ignore invalid records
            }
        }
        newfile.close();
    }

    retval = true;
    }
    catch (const std::invalid_argument& ia) {
        std::cerr << "BSC1991: Invalid argument: " << ia.what() << '\n';
        clear();
        retval = false;
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "BSC1991: Out of Range error: " << oor.what() << '\n';
        clear();
        retval = false;
    }
    catch (std::bad_alloc& ba) {
        std::cerr << "BSC1991: Memory allocation error: " << ba.what() << '\n';
        clear();
        retval = false;
    }
    return retval;
}
#endif

CBSC1991_Embedded::CObject* CBSC1991_Embedded::find_bs(int bs_num) const
{
    auto it = m_bs_id_map.find(bs_num);
    if (it != m_bs_id_map.end())
        return it->second;
    return NULL;
}

CBSC1991_Embedded::CObject* CBSC1991_Embedded::find_hd(int hd_num) const
{
    auto it = m_hd_id_map.find(hd_num);
    if (it != m_hd_id_map.end())
        return it->second;
    return NULL;
}
