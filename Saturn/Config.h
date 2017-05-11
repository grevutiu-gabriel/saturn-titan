//
// File:   Config.h
// Author: M.R.Eggleston
//
// Created on 17 July 2010, 16:13
///

#pragma once

#include <iomanip>
#ifdef NOT_MOC
#include <boost/shared_ptr.hpp>
#endif
#include <QDomDocument>
#include "Fractal.h"
#include "FractalsConfig.h"
#include "KeyString.h"
#include "ColourMaps.h"
#include "TrapConfig.h"

class Config
{
public:
    static boost::shared_ptr<Config> create();
    static boost::shared_ptr<Config> instance();

    FRACTAL_TYPE getFractalType();
    void setFractalType(FRACTAL_TYPE ft);

    void save();
    void save_parameter_file(FRACTAL_TYPE ft, const QString& path);
    bool load_parameter_file(const QString& path);
    void save_scm_file(const QString& path, std::vector<QString> &maps);
    void save_ugr_file(const QString& path, std::vector<QString> &maps);
    FractalConfig &fractal_config();
    
    virtual ~Config();
    
private:
    Config();
    Config(const Config& orig);

    void save_config_file();
    void save_colour_file();

    void save_current_child(QDomDocument*, QDomElement& root);
    void save_fractal_children(QDomDocument*, QDomElement& root);
    void save_fractal_child(QDomDocument*, QDomElement& root, FRACTAL_TYPE ft);
    void save_colour_map_children(QDomDocument*, QDomElement& root);
    void save_colour_map_child(QDomDocument*, QDomElement& root, const QString& name);
    void save_fractal_initialise(QDomDocument*, QDomElement& root);
    void save_fractal_parameters(QDomDocument*, QDomElement& root);
    void save_lyapunov_parameters(QDomDocument*, QDomElement& root);
    void save_complex_parameters(QDomDocument*, QDomElement& root);
    void save_real_parameters(QDomDocument*, QDomElement& root);
    void save_function_parameters(QDomDocument*, QDomElement& root);
    void save_complex_function_parameters(QDomDocument*, QDomElement& root);
    void save_fractal_transforms(QDomDocument*, QDomElement& root);
    void save_complex_plane_transforms(QDomDocument*, QDomElement& root);
    void save_fractal_transforms(QDomDocument*, unsigned int set, QDomElement& root);
    void save_complex_function(QDomDocument*, QDomElement& root, const std::string& func);
    void save_popcorn_colour(QDomDocument*, QDomElement& root);
    void save_fractal_colour(QDomDocument*, QDomElement& root);
    void save_fractal_colour_child(QDomDocument*, QDomElement& root, const QString& tagName, bool inner);
    void save_fractal_starting_position(QDomDocument*, QDomElement& root);
    void save_fractal_current_position(QDomDocument*, QDomElement& root);
    void save_colour_selection(QDomDocument*, QDomElement& root);
    void save_colour_map(QDomDocument*, QDomElement& root);
    void save_orbit_colour_child(QDomDocument*, QDomElement& root);
    void save_fixed_colour(QDomDocument*, QDomElement& root, const std::string& method);
    void save_final_angle(QDomDocument*, QDomElement& root);
    void save_final_magnitude(QDomDocument*, QDomElement& root, std::string& method);
    void save_angle(QDomDocument*, QDomElement& root, std::string& method);
    void save_magnitude(QDomDocument*, QDomElement& root, std::string& method);
    void save_gaussian(QDomDocument*, QDomElement& root, std::string& method);
    void save_trap(QDomDocument* dom, QDomElement& root, std::string& method, bool inner);
    void save_ratio(QDomDocument* dom, QDomElement& root, std::string& method);
    void add_method_attributes(QDomElement& root, const std::string& type);
    void load();
    void load_config_file();
    void load_colour_file();
    void load_current_child(const QDomElement& child);
    void load_fractal_child(const QDomElement& child, bool parameter_file);
    void load_level4_fractal_child(const QDomElement& root);
    void load_colour_map_child(const QDomElement& root, bool parameters);
    void add_component_colours(QDomDocument* dom, QDomElement& root, RGB colour, ColourMap& colours);
    void load_auto_colour(const QDomElement& root, RGB colour, ColourMap &map);
    void load_fractal_initialise(const QDomElement& child);
    void load_fractal_parameters(const QDomElement& child);
    void load_level4_fractal_parameters(const QDomElement& child);
    void load_fractal_transforms(const QDomElement& child);
    void load_level4_fractal_transforms(const QDomElement& child);
    void load_complex_plane_transforms(const QDomElement& root);
    void load_transform_set(unsigned int set, const QDomElement& root);
    void load_level4_transform_set(unsigned int set, const QDomElement& root);
    void load_level4_transform(unsigned int set, const QDomElement& child);
    void load_level4_cp_transform(const QDomElement& root);
    void load_fractal_colour_parameters(const QDomElement& child, bool parameters_file);
    void load_fractal_colour_parameters_child(const QDomElement& root, bool parameters);
    void load_fractal_colour_map(const QDomElement& root, bool parameters);
    void load_trap_parameters(const QDomElement& root, bool inner);
    void get_complex_function_keys(const QDomElement& root, KeyString& keys);
    void adjustParameters(OLD_FRACTAL_TYPE ft);
    void convertBcp_6(COMPLEX_FUNCTION_PARAMETER func, bool julia);
    void convertSingleFunction_6(COMPLEX_FUNCTION_PARAMETER func, bool julia);
    void convertSinczCoscz_6(bool julia);
    void convertZcpac_6(bool julia);
    void convertZpowerC_6();
    void convertCpowerZ_6();
    void convertCombination2_6();
    void convertCombination3_6();
    void convertCombination4_6();
    void convertTzaccp_6(bool julia);
    void convertZaccp_6(bool julia);
    void convertCczcpaczcp_6(bool julia);
    void convertLzcpac_6(bool julia);
    void convertLtzcpac_6(bool julia);
    void convertZazbcgd_6(bool julia);
    void convertMallard_6(bool julia);
    void convertTmallard_6(bool julia);
    void convertCompasses_6(bool julia);
    void convertUnnamed_6(bool julia);
    void convertUnnamed2_6(bool julia);

    QRgb getColour(const std::string &str);

    FRACTAL_TYPE m_ft;

    bool m_file_exists;
    const QString m_directory_path;
    const QString m_config_file_path;
    const QString m_colour_file_path;
    QString m_map1;
    QString m_map2;

    boost::shared_ptr<ColourMaps> m_colour_maps;
    FractalConfig m_fractal_config;
    FractalsConfig m_fractals_config;
    TrapConfig m_trap_config;
    int m_level;

    static boost::shared_ptr<Config> s_instance;
};


