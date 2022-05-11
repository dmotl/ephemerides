/*!
*  \file      CBound.cpp
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
#include "CBound.h"

#include <locale>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

static void strToFloat(const std::string& str, double& value)
{
    static std::locale c_locale("C");

    std::istringstream iss(str);
    iss.imbue(c_locale);
    iss >> value;
}

static std::string rtrim(const std::string& s)
{
    static const std::string WHITESPACE = " \n\r\t\f\v";

    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

static std::string ltrim(const std::string& s)
{
    static const std::string WHITESPACE = " \n\r\t\f\v";

    size_t startpos = s.find_first_not_of(WHITESPACE);
    return (startpos == std::string::npos) ? "" : s.substr(startpos);
}

CBound::~CBound()
{
    auto begin = m_list.begin(), end = m_list.end();
    while (begin != end) {
        delete* begin;
        begin++;
    }
}

void CBound::clear()
{
    auto begin = m_list.begin(), end = m_list.end();
    while (begin != end) {
        delete* begin;
        begin++;
    }
    m_list.clear();
}


bool CBound::load(const char* dirPath)
{
    clear();

    bool retval = false;
    try
    {
        std::filesystem::path cat_file = std::filesystem::path(dirPath) / "bound_20.dat";

        std::fstream newfile;
        newfile.open(cat_file.string().c_str(), std::ios::in);
        if (newfile.is_open()) {
            std::string tp;
            while (getline(newfile, tp)) {
                try
                {
                    /*   1- 10   F10.7   h       RAhr    Right ascension in decimal hours (J2000) */
                    double rah = invalidRightAscension();
                    strToFloat(tp.substr(0, 10), rah);
                    
                    /* 12- 22   F11.7   deg     DEdeg   Declination in degrees (J2000) */
                    double ded = invalidDeclination();
                    strToFloat(tp.substr(11, 11), ded);

                    /* 24- 27   A4      ---     cst     Constellation abbreviation */
                    auto con = tp.substr(23, 3);
                    int con_suffix = 0;
                    if (tp[26] >= '1' && tp[26] <= '9')
                        con_suffix = tp[26] - '1';

                    /* 29   A1      ---     type    [OI] Type of point (Original or Interpolated) */
                    tPointType type = tp.substr(29, 1) == "O" ? tPointType::ORIGIN : tPointType::INTERPOLATED;

                    if (rah != invalidRightAscension() && ded != invalidDeclination()) {
                        CPoint* ptr = new CPoint(type, CEquCoordinates(CRightAscension::fromHours(rah), CDeclination::fromDegrees(ded)), con, con_suffix);
                        m_list.push_back(ptr);
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
        std::cerr << "Bound: Invalid argument: " << ia.what() << '\n';
        clear();
        retval = false;
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Bound: Out of Range error: " << oor.what() << '\n';
        clear();
        retval = false;
    }
    catch (std::bad_alloc& ba) {
        std::cerr << "Bound: Memory allocation error: " << ba.what() << '\n';
        clear();
        retval = false;
    }
    return retval;
}
