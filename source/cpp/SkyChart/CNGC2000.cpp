#include "CNGC2000.h"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

static const struct { std::string id, description; CNGC2000::tObjectType val; } classes[] = {
    { "Gx", "Galaxy", CNGC2000::tObjectType::GALAXY },
    { "OC", "Open star cluster", CNGC2000::tObjectType::OPEN_CLUSTER },
    { "Gb", "Globular star cluster", CNGC2000::tObjectType::GLOB_CLUSTER },
    { "Nb", "Bright emission or reflection nebula", CNGC2000::tObjectType::NEBULA },
    { "Pl", "Planetary nebula", CNGC2000::tObjectType::PLAN_NEBULA },
    { "C+N", "Cluster associated with nebulosity", CNGC2000::tObjectType::CL_AND_NB },
    { "Ast", "Asterism or group of a few stars", CNGC2000::tObjectType::ASTERISM },
    { "Kt", "Knot or nebulous region in an external galaxy", CNGC2000::tObjectType::KNOT },
    { "***", "Triple star", CNGC2000::tObjectType::TRIPPLE_STAR },
    { "D*", "Double star", CNGC2000::tObjectType::DOUBLE_STAR },
    { "*", "Single star", CNGC2000::tObjectType::STAR },
    { "?", "Uncertain type or may not exist", CNGC2000::tObjectType::UNCERTAIN },
    { "-", "Object called nonexistent in the RNGC", CNGC2000::tObjectType::NON_EXISTENT },
    { "PD", "Photographic plate defect", CNGC2000::tObjectType::DEFECT },
    { "", "", CNGC2000::tObjectType::UNKNOWN }
};

static CNGC2000::tObjectType strToType(const std::string& cls)
{
    for (int i = 0; classes[i].val != CNGC2000::tObjectType::UNKNOWN; i++) {
        if (cls == classes[i].id) 
            return classes[i].val;
    }
    return CNGC2000::tObjectType::UNKNOWN;
}

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

CNGC2000::CObjectDesignation::CObjectDesignation(const std::string& sid)
{
    if (sid.substr(0, 1) == "I") {
        cat = tCatalog::IC;
        number = stoi(sid.substr(1));
    }
    else if (sid.length() > 0) {
        cat = tCatalog::NGC;
        number = stoi(sid);
    }
    else {
        cat = tCatalog::UNDEFINED;
        number = 0;
    }
}

CNGC2000::~CNGC2000()
{
    auto begin = m_list.begin(), end = m_list.end();
    while (begin != end) {
        delete* begin;
        begin++;
    }
}

void CNGC2000::clear()
{
    auto begin = m_list.begin(), end = m_list.end();
    while (begin != end) {
        delete* begin;
        begin++;
    }
    m_list.clear();

    m_messier.clear();
    m_ngc.clear();
    m_ic.clear();
}

bool CNGC2000::load(const char* dirPath)
{
    clear();

    bool retval = false;
    try
    {
        std::filesystem::path cat_file = std::filesystem::path(dirPath) / "ngc2000.dat";

        std::fstream newfile;
        newfile.open(cat_file.string().c_str(), std::ios::in);
        if (newfile.is_open()) {
            std::string tp;
            while (getline(newfile, tp)) {
                try
                {
                    /* 1-  5  A5     ---     Name     NGC or IC designation (preceded by I) */
                    CObjectDesignation id(tp.substr(0, 5));

                    /* 7-  9  A3     ---     Type     Object classification (1)*/
                    auto type = strToType(ltrim(tp.substr(6, 3)));

                    /* 11- 12  I2     h       RAh      Right Ascension B2000 (hours) */
                    int rah = stoi(tp.substr(10, 2));

                    /* 14- 17  F4.1   min     RAm      Right Ascension B2000 (minutes) */
                    double ram = 0;
                    strToFloat(tp.substr(13, 4), ram);

                    /* 20  A1     ---     DE-      Declination B2000 (sign) */
                    auto des = (tp.substr(20, 1) == "-" ? -1 : +1);

                    /* 21- 22  I2     deg     DEd      Declination B2000 (degrees) */
                    auto ded = stoi(tp.substr(20, 2));

                    /* 24- 25  I2     arcmin  DEm      Declination B2000 (minutes) */
                    auto dem = stoi(tp.substr(23, 2));

                    /* 30- 32  A3     ---     Const    Constellation */
                    auto con = tp.substr(29, 3);

                    /*     33  A1     ---     l_size   [<] Limit on Size
                       34- 38  F5.1   arcmin  size     ? Largest dimension */

                       /* 41- 44  F4.1   mag     mag      ? Integrated magnitude, visual or photographic
                                                            (see n_mag)*/
                    double mag = invalidMagnitude();
                    strToFloat(tp.substr(40, 4), mag);

                    if (id.number > 0 && id.cat != tCatalog::UNDEFINED) {
                        CDeclination dec = CDeclination::fromDegrees(des * (ded + static_cast<double>(dem) / 60.0));
                        CRightAscension ra = CRightAscension::fromHours(rah + ram / 60.0);
                        CObject* ptr = new CObject(id, type, CEquCoordinates(ra, dec), con, mag);
                        m_list.push_back(ptr);
                        if (id.cat == tCatalog::IC)
                            m_ic.insert({ id.number, ptr });
                        else
                            m_ngc.insert({ id.number, ptr });
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
        std::cerr << "NGC2000: Invalid argument: " << ia.what() << '\n';
        clear();
        retval = false;
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "NGC2000: Out of Range error: " << oor.what() << '\n';
        clear();
        retval = false;
    }
    catch (std::bad_alloc& ba) {
        std::cerr << "NGC2000: Memory allocation error: " << ba.what() << '\n';
        clear();
        retval = false;
    }
    return retval;
}

bool CNGC2000::CObjectDesignation::operator==(const CObjectDesignation& other) const
{
    return cat == other.cat && number == other.number;
}

bool CNGC2000::CObjectDesignation::operator<(const CObjectDesignation& other) const
{
    return (cat == other.cat ? number < other.number : cat < other.cat);
}

CNGC2000::CObject* CNGC2000::find_ngc(int ngc_num) const
{
    auto it = m_ngc.find(ngc_num);
    if (it != m_ngc.end())
        return it->second;
    return NULL;
}

CNGC2000::CObject* CNGC2000::find_ic(int ic_num) const
{
    auto it = m_ic.find(ic_num);
    if (it != m_ic.end())
        return it->second;
    return NULL;
}

CNGC2000::CObject* CNGC2000::find_messier(int m_num) const
{
    auto it = m_messier.find(m_num);
    if (it != m_messier.end())
        return it->second;
    return NULL;
}
