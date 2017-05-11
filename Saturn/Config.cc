//
// File:   Config.cc
// Author: M.R.Eggleston
//
// Created on 17 July 2010, 16:13
//

#include <boost/scoped_ptr.hpp>
#include <exception>
#include <iostream>
#include <limits>

#include <QByteArray>
#include <QDir>
#include <QString>

#include "Config.h"
#include "Utilities.h"
#include "FractalsConfig.h"
#include "KeyString.h"


boost::shared_ptr<Config> Config::s_instance;

boost::shared_ptr<Config> Config::create()
{
    if (!s_instance)
    {
        s_instance = boost::shared_ptr<Config>(new Config());
        s_instance->load();
    }
    return s_instance;
}

boost::shared_ptr<Config> Config::instance()
{
    return s_instance;
}

Config::Config()
:
m_ft(F_MANDELBROT),
m_file_exists(false),
m_directory_path(QDir::homePath() + "/.saturn-4.2"),
m_config_file_path(m_directory_path + "/config.xml"),
m_colour_file_path(m_directory_path + "/colour.xml"),
m_colour_maps(ColourMaps::instance()),
m_level(9)
{
}

Config::~Config()
{
}

void Config::save_parameter_file(FRACTAL_TYPE ft, const QString& path)
{
    boost::scoped_ptr<QDomDocument> dom(new QDomDocument());
    auto root = dom->createElement("saturn_parameters");
    dom->appendChild(root);
    root.setAttribute("level", LEVEL);
    root.setAttribute("hpixels", m_fractals_config.getWidth());
    root.setAttribute("vpixels", m_fractals_config.getHeight());
    save_fractal_child(dom.get(), root, ft);
    if (m_fractals_config.isOrbitPlotting())
    {
        save_colour_map_child(dom.get(), root, m_fractals_config.getColourMap());
    }
    else
    {
        save_colour_map_child(dom.get(), root, m_fractals_config.getColourMap(false));
        save_colour_map_child(dom.get(), root, m_fractals_config.getColourMap(true));
    }
    QByteArray doc_bytes = dom->toByteArray();
    QFile file(path);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(doc_bytes, doc_bytes.size());
    }
    else
    {
        std::cout << "error " << file.error() << std::endl;
    }
    file.close();
}

void Config::save()
{
    save_config_file();
    save_colour_file();
}

void Config::save_config_file()
{
    boost::scoped_ptr<QDomDocument> dom(new QDomDocument());
    auto root = dom->createElement("saturn");
    dom->appendChild(root);
    save_current_child(dom.get(), root);
    save_fractal_children(dom.get(), root);
    QByteArray doc_bytes = dom->toByteArray();
    QFile backup(m_config_file_path + "~");
    backup.remove();
    QFile new_backup(m_config_file_path);
    new_backup.rename(m_config_file_path + "~");
    QFile file(m_config_file_path);
    file.open(QIODevice::WriteOnly);
    file.write(doc_bytes, doc_bytes.size());
    file.close();
}

void Config::save_colour_file()
{
    boost::scoped_ptr<QDomDocument> dom(new QDomDocument());
    auto root = dom->createElement("saturn");
    dom->appendChild(root);
    save_colour_map_children(dom.get(), root);
    QByteArray doc_bytes = dom->toByteArray();
    if (doc_bytes.size() > 0)
    {
        QFile backup(m_colour_file_path + "~");
        QFile new_backup(m_colour_file_path);
        new_backup.rename(m_colour_file_path + "~");
        QFile file(m_colour_file_path);
        file.open(QIODevice::WriteOnly);
        file.write(doc_bytes, doc_bytes.size());
        file.close();
    }
}

void Config::load()
{
    load_colour_file();
    load_config_file();
}

void Config::load_config_file()
{
    // Does config directory exist.
    boost::scoped_ptr<QDomDocument> dom(new QDomDocument());
    QDir directory(QDir::homePath());
    if (!directory.exists(m_directory_path))
    {
        if (!directory.mkpath(m_directory_path))
        {
            std::cout << "failed to create " << m_directory_path.toStdString() << std::endl;
        }
    }
    bool ok = false;
    // Does config.xml exist.
    if (directory.exists(m_config_file_path))
    {
        boost::shared_ptr<Config> cfg = Config::instance();
        QFile file(m_config_file_path);
        if (file.open(QIODevice::ReadOnly))
        {
            ok = dom->setContent(&file);
            file.close();
        }
    }
    if (ok)
    {
        // The document contains one node saturn
        QDomElement root = dom->documentElement();
        if (!root.isNull())
        {
            // Node should be saturn
            if (root.tagName() == "saturn")
            {
                // is Saturn's config file 
                QDomElement child = root.firstChildElement();
                while (!child.isNull())
                {
                    if (child.tagName() == "current")
                    {
                        load_current_child(child);
                    }
                    else if (child.tagName() == "fractal")
                    {
                        m_fractal_config = FractalConfig();
                        load_fractal_child(child, false);
                        m_fractals_config.SetFractal(m_fractal_config);
                    }
                    child = child.nextSiblingElement();
                }
            }
        }
    }
}

void Config::load_colour_file()
{
    boost::scoped_ptr<QDomDocument> dom(new QDomDocument());
    QDir directory(QDir::homePath());
    bool ok = false;
    // Does config.xml exist.
    if (directory.exists(m_colour_file_path))
    {
        boost::shared_ptr<Config> cfg = Config::instance();
        QFile file(m_colour_file_path);
        if (file.open(QIODevice::ReadOnly))
        {
            ok = dom->setContent(&file);
            file.close();
        }
    }
    if (ok)
    {
        // The document contains one node saturn
        QDomElement root = dom->documentElement();
        if (!root.isNull())
        {
            // Node should be saturn
            if (root.tagName() == "saturn")
            {
                // is Saturn's config file 
                QDomElement child = root.firstChildElement();
                while (!child.isNull())
                {
                    if (child.tagName() == "colourmap")
                    {
                        load_colour_map_child(child, false);
                    }
                    child = child.nextSiblingElement();
                }
            }
        }
    }
}

void Config::save_current_child(QDomDocument* dom, QDomElement& root)
{
    auto tag = dom->createElement("current");
    tag.setAttribute("fractaltype", static_cast<int>(m_ft));
    tag.setAttribute("hpixels", m_fractals_config.getWidth());
    tag.setAttribute("vpixels", m_fractals_config.getHeight());
    root.appendChild(tag);
}

void Config::save_fractal_children(QDomDocument* dom, QDomElement& root)
{
    FractalsConfig::VectorFractalId &fractals = m_fractals_config.getAllFractals();
    for (auto it = fractals.begin(); it != fractals.end(); it++)
    {
        save_fractal_child(dom, root, it->type);
    }
}

void Config::save_fractal_child(QDomDocument* dom, QDomElement& root, FRACTAL_TYPE ft)
{
    FractalsConfig &f = m_fractals_config;
    f.SetFractalType(ft);
    auto tag = dom->createElement("fractal");
    tag.setAttribute("name", f.getName());
    tag.setAttribute("id", static_cast<int>(ft));
    tag.setAttribute("orbit", static_cast<int>(f.isOrbitPlotting()));
    int precision = f.getPrecision();
    if ((!f.isOrbitPlotting()) && (precision != 0))
    {
        tag.setAttribute("precision", precision);
    }
    root.appendChild(tag);
    save_fractal_initialise(dom, tag);
    save_fractal_parameters(dom, tag);
    save_fractal_transforms(dom, tag);
    save_fractal_colour(dom, tag);
    save_fractal_starting_position(dom, tag);
    save_fractal_current_position(dom, tag);
}

void Config::save_fractal_colour(QDomDocument* dom, QDomElement& root)
{
    // Add colour node
    auto colour_tag = dom->createElement("colour");
    root.appendChild(colour_tag);
    if (m_fractals_config.isOrbitPlotting() || m_fractals_config.isSingleOrbit())
    {
        save_orbit_colour_child(dom, colour_tag);
    }
    else
    {
        save_fractal_colour_child(dom, colour_tag, "outer", false);
        save_fractal_colour_child(dom, colour_tag, "inner", true);
    }
}

void Config::save_fractal_colour_child(QDomDocument* dom, QDomElement& root, const QString& tagName, bool inner)
{
    auto tag = dom->createElement(tagName);
    root.appendChild(tag);
    FractalsConfig &f = m_fractals_config;
    if (!inner)
    {
        save_colour_selection(dom, root);
    }
    f.setInner(inner);
    std::string method = f.getMethod(inner);
    if (method.empty())
    {
        method = "i";
    }
    if (method[0] == 'f')
    {
        save_fixed_colour(dom, tag, method);
    }
    else
    {
        save_colour_map(dom, tag);
        if (method == "a")
        {
            save_final_angle(dom, tag);
        }
        else if (method[0] == 'm')
        {
            save_final_magnitude(dom, tag, method);
        }
        else if (method[0] == 'g')
        {
            save_gaussian(dom, tag, method);
        }
        else if (method[0] == 'M')
        {
            save_magnitude(dom, tag, method);
        }
        else if (method[0] == 'A')
        {
            save_angle(dom, tag, method);
        }
        else if (method[0] == 'r')
        {
            save_ratio(dom, tag, method);
        }
        else if (method[0] == 't')
        {
            save_trap(dom, tag, method, false);
        }
        else if (method[0] == 'i')
        {
            auto child_tag = dom->createElement("iteration");
            child_tag.setAttribute("smooth", static_cast<int>(f.getSmooth()));
            tag.appendChild(child_tag);
        }
        if (f.getAbsLog())
        {
            auto child_tag = dom->createElement("abslog");
            tag.appendChild(child_tag);
        }
    }
}

void Config::save_fractal_initialise(QDomDocument* dom, QDomElement& root)
{
    auto initialise_tag = dom->createElement("initialise");
    root.appendChild(initialise_tag);
    FractalsConfig &f = m_fractals_config;
    if (f.GetFractalType() != F_LYAPUNOV)
    {
        auto z0_tag = dom->createElement("z0");
        z0_tag.setAttribute("type", static_cast<int>(f.getInitialValues()));
        if (f.getInitialValues() == FIXED)
        {
            z0_tag.setAttribute("r", QString::fromStdString(f.getFixedInitialValue().r));
            z0_tag.setAttribute("i", QString::fromStdString(f.getFixedInitialValue().i));
        }
        initialise_tag.appendChild(z0_tag);
    }
}

void Config::save_complex_function(QDomDocument* dom, QDomElement& root, const std::string& func)
{
    auto func_tag = dom->createElement("complex_function");
    KeyString keys(func);
    if (keys.GetKey("pair", "n") == "n")
    {
        func_tag.setAttribute("pair", "n");
        auto id = static_cast<COMPLEX_FUNCTION_PARAMETER>(keys.GetKeyAsInt("id", 0));
        func_tag.setAttribute("id", QString::fromStdString(keys.GetKey("id", "0")));
        if (hasParameter(id))
        {
            func_tag.setAttribute("r", QString::fromStdString(keys.GetKey("r", "0.0")));
            func_tag.setAttribute("i", QString::fromStdString(keys.GetKey("i", "0.0")));
        }
        else if (hasSize(id))
        {
            func_tag.setAttribute("size", QString::fromStdString(keys.GetKey("size", "1.0")));
        }
        else if (hasRotation(id))
        {
            func_tag.setAttribute("rotation", QString::fromStdString(keys.GetKey("rotation", "0.0")));
        }
        func_tag.setAttribute("name", complexFunctionAsString(id));
    }
    else
    {
        func_tag.setAttribute("pair", "y");
        auto rid = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("rid", 0));
        auto iid = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("iid", 0));
        func_tag.setAttribute("rid", QString::fromStdString(keys.GetKey("rid", "0")));
        if (hasParameter(rid))
        {
            func_tag.setAttribute("r", QString::fromStdString(keys.GetKey("r", "0.0")));
        }
        func_tag.setAttribute("iid", QString::fromStdString(keys.GetKey("iid", "0")));
        if (hasParameter(iid))
        {
            func_tag.setAttribute("i",QString::fromStdString( keys.GetKey("i", "0.0")));
        }
        func_tag.setAttribute("name", functionAsString(rid) + "," + functionAsString(iid));
    }
    root.appendChild(func_tag);
}

void Config::save_lyapunov_parameters(QDomDocument* dom, QDomElement& root)
{
    FractalsConfig &f = m_fractals_config;
    QDomElement tag = dom->createElement("sequence");
    tag.setAttribute("value", QString::fromStdString(f.getLyapunovSequence()));
    root.appendChild(tag);
    tag = dom->createElement("settling");
    tag.setAttribute("value", f.getSettlingCycles());
    root.appendChild(tag);
    tag = dom->createElement("calculating");
    tag.setAttribute("value", f.getCalculatingCycles());
    root.appendChild(tag);
}

void Config::save_complex_parameters(QDomDocument* dom, QDomElement& root)
{
    FractalsConfig &f = m_fractals_config;
    int modifiers = f.getNumberOfComplexParameters();
    for (int i = 0; i < modifiers; i++)
    {
        auto tag = dom->createElement("complex_param");
        tag.setAttribute("r", QString::fromStdString(f.getComplexParameter(i).r));
        tag.setAttribute("i", QString::fromStdString(f.getComplexParameter(i).i));
        tag.setAttribute("c", static_cast<int>(f.getComplexParameterType(i)));
        root.appendChild(tag);
    }
}

void Config::save_real_parameters(QDomDocument* dom, QDomElement& root)
{
    FractalsConfig &f = m_fractals_config;
    int modifiers = f.getNumberOfParameters();
    for (int i = 0; i < modifiers; i++)
    {
        auto tag = dom->createElement("param");
        tag.setAttribute("value", QString::fromStdString(f.getParameter(i)));
        root.appendChild(tag);
    }
}

void Config::save_function_parameters(QDomDocument* dom, QDomElement& root)
{
    FractalsConfig &f = m_fractals_config;
    int modifiers = f.getNumberOfFunctionParameters();
    for (int i = 0; i < modifiers; i++)
    {
        auto tag = dom->createElement("function");
        KeyString keys(f.getFunctionParameter(i));
        auto id = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("id", 0));
        tag.setAttribute("id", QString::fromStdString(keys.GetKey("id", "0")));
        tag.setAttribute("name", functionAsString(id));
        if (hasParameter(id))
        {
            tag.setAttribute("p", QString::fromStdString(keys.GetKey("p", "0.0")));
        }
        root.appendChild(tag);
    }
}

void Config::save_complex_function_parameters(QDomDocument* dom, QDomElement& root)
{
    FractalsConfig &f = m_fractals_config;
    int modifiers = f.getNumberOfComplexFunctionParameters();
    for (int i = 0; i < modifiers; i++)
    {
        save_complex_function(dom, root, f.getComplexFunctionParameter(i));
    }
}

void Config::save_fractal_parameters(QDomDocument* dom, QDomElement& root)
{
    auto parameters_tag = dom->createElement("parameters");
    root.appendChild(parameters_tag);
    FractalsConfig &f = m_fractals_config;
    if (f.GetFractalType() == F_LYAPUNOV)
    {
        save_lyapunov_parameters(dom, parameters_tag);
    }
    else
    {
        QDomElement tag = dom->createElement("bailout");
        tag.setAttribute("type", longdoubleToQString(f.getBailout()));
        tag.setAttribute("limit", longdoubleToQString(f.getLimit()));
        parameters_tag.appendChild(tag);
        tag = dom->createElement("max_iterations");
        tag.setAttribute("value", f.getMaxIterations());
        parameters_tag.appendChild(tag);
        if (f.isOrbitPlotting())
        {
            tag = dom->createElement("start_orbit_iteration");
            tag.setAttribute("value", f.getStartOrbitIteration());
            parameters_tag.appendChild(tag);
            tag = dom->createElement("plot");
            tag.setAttribute("area", f.getCalculatingArea());
            tag.setAttribute("type", static_cast<int>(f.getOrbitPlots()));
            parameters_tag.appendChild(tag);
            tag = dom->createElement("plot_density");
            tag.setAttribute("value", f.getDensity());
            parameters_tag.appendChild(tag);
       }
    }
    save_complex_parameters(dom, parameters_tag);
    save_real_parameters(dom, parameters_tag);
    save_function_parameters(dom, parameters_tag);
    save_complex_function_parameters(dom, parameters_tag);
}

void Config::save_fractal_transforms(QDomDocument* dom, QDomElement& root)
{
    FractalsConfig &f = m_fractals_config;
    if (f.GetFractalType() != F_LYAPUNOV)
    {
        if (f.transformsDefined())
        {
            QDomElement transforms_root = dom->createElement("transforms");
            root.appendChild(transforms_root);
            auto tag = dom->createElement("sequence");
            tag.setAttribute("value", QString::fromStdString(f.getTransformSequence()));
            transforms_root.appendChild(tag);
            save_complex_plane_transforms(dom, transforms_root);
            int number_of_sets = f.getNumberOfTransformSets();
            for (int i = 0; i < number_of_sets; i++)
            {
                save_fractal_transforms(dom, i, transforms_root);
            }
        }
    }
}

void Config::save_complex_plane_transforms(QDomDocument* dom, QDomElement& root)
{
    FractalsConfig &f = m_fractals_config;
    unsigned int number_of_transforms = f.getNumberOfComplexPlaneTransforms();
    if (number_of_transforms != 0)
    {
        auto cp_tag = dom->createElement("complex_plane");
        root.appendChild(cp_tag);
        for (unsigned int i = 0; i < number_of_transforms; i++)
        {
            auto transform = f.getComplexPlaneTransform(i);
            save_complex_function(dom, cp_tag, transform);
        }
    }
}

void Config::save_fractal_transforms(QDomDocument* dom, unsigned int set, QDomElement& root)
{
    // A transform must exist in order for it to used in the transform
    // sequence so empty sets need to be saved.
    FractalsConfig &f = m_fractals_config;
    int number_of_transforms = f.getNumberOfTransforms(set);
    auto set_tag = dom->createElement("set");
    set_tag.setAttribute("id", set);
    root.appendChild(set_tag);
    for (auto i = 0; i < number_of_transforms; i++)
    {
        auto transform = f.getTransform(set, i);
        save_complex_function(dom, set_tag, transform);
    }
}


void Config::save_colour_map_children(QDomDocument* dom, QDomElement& root)
{
    unsigned int colour_map_number = 0;
    QStrings &names = m_colour_maps->getNames();
    if (names.begin() != names.end())
    {
        for (auto it = names.begin(); it != names.end(); it++)
        {
            save_colour_map_child(dom, root, *it);
            colour_map_number++;
        }
    }
}

void Config::save_colour_map_child(QDomDocument* dom, QDomElement& root, const QString& name)
{
    if (!m_colour_maps->isDefault(name))
    {
        ColourMap colours = m_colour_maps->getColourMap(name);
        auto type = colours.getType();
        auto colourmap_tag = dom->createElement("colourmap");
        colourmap_tag.setAttribute("name", name);
        colourmap_tag.setAttribute("type", static_cast<int>(type));
        root.appendChild(colourmap_tag);
        if (type == ColourMap::CM_MANUAL)
        {
            auto first = colours.getColoursMap().begin();
            auto last = colours.getColoursMap().end();
            for (auto it = first; it != last; it++)
            {
                int index = it->first;
                QColor c = it->second;
                auto rgb_tag = dom->createElement("rgb");
                rgb_tag.setAttribute("index", index);
                rgb_tag.setAttribute("red", c.red());
                rgb_tag.setAttribute("green", c.green());
                rgb_tag.setAttribute("blue", c.blue());
                colourmap_tag.appendChild(rgb_tag);
            }
        }
        else if (type == ColourMap::CM_COMPONENT)
        {
            add_component_colours(dom, colourmap_tag, RGB_RED, colours);
            add_component_colours(dom, colourmap_tag, RGB_GREEN, colours);
            add_component_colours(dom, colourmap_tag, RGB_BLUE, colours);
        }
        else
        {
            Waveform::AutoColour colour;
            QString rgb[3] = { "red", "green", "blue" };
            RGB colour_id[3] = { RGB_RED, RGB_GREEN, RGB_BLUE };
            for (int i = 0; i < 3; i++)
            {
                colours.getAutoColour(colour_id[i], colour);
                auto colour_tag = dom->createElement(rgb[i]);
                colour_tag.setAttribute("hoffset", colour.hoffset);
                colour_tag.setAttribute("voffset", colour.voffset);
                colour_tag.setAttribute("maximum", colour.maximum);
                colour_tag.setAttribute("wave", static_cast<int>(colour.wave));
                colour_tag.setAttribute("cycles", colour.cycles);
                colourmap_tag.appendChild(colour_tag);
            }
        }
    }
}

void Config::add_component_colours(QDomDocument* dom, QDomElement& root, RGB colour, ColourMap& colours)
{
    IntMap map;   
    QString tag_string;
    switch(colour)
    {
    default:
    case RGB_RED:
        tag_string = "red";
        map = colours.getRedMap();
        break;
    case RGB_GREEN:
        tag_string = "green";
        map = colours.getGreenMap();
        break;
    case RGB_BLUE:
        tag_string = "blue";
        map = colours.getBlueMap();
        break;
    }
    for (auto it = map.begin(); it != map.end(); it++)
    {
        int index = it->first;
        int c = it->second;
        auto colour_tag = dom->createElement(tag_string);
        colour_tag.setAttribute("index", index);
        colour_tag.setAttribute("value", c);
        root.appendChild(colour_tag);
    }
}

FRACTAL_TYPE Config::getFractalType()
{
    return m_ft;
}

void Config::setFractalType(FRACTAL_TYPE ft)
{
    m_ft = ft;
}

QRgb Config::getColour(const std::string &str)
{
    int red = 0;
    int green = 0;
    int blue = 0;
    try
    {
        std::istringstream input(str);
        char junk;
        input >> junk;  // 'f'
        input >> junk;  // ','
        input >> red;
        input >> junk;
        input >> green;
        input >> junk;
        input >> blue;
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return qRgb(red, green, blue);
}

void Config::load_current_child(const QDomElement& child)
{
    m_ft = static_cast<FRACTAL_TYPE>(child.attribute("fractaltype").toUInt());
    m_fractals_config.setWidth(child.attribute("hpixels").toInt());
    m_fractals_config.setHeight(child.attribute("vpixels").toInt());
}

void Config::load_fractal_child(const QDomElement& root, bool parameters)
{
    auto ft = static_cast<FRACTAL_TYPE>(root.attribute("id").toInt());
    m_fractal_config.SetFractalType(ft);
    m_fractal_config.setOrbitPlotting(root.attribute("orbit").toInt() == 1);
    auto str = root.attribute("precision");
    if (!str.isEmpty())
    {
        int precision = str.toInt();
        if ((precision > BASE_PRECISION) && ((precision % 16) == 0))
        {
            m_fractal_config.setPrecision(precision);
        }
    }
    else
    {
        m_fractal_config.setPrecision(0);
    }
    m_fractal_config.deleteTransforms();
    QDomElement child = root.firstChildElement();
    while (!child.isNull())
    {
        QString name = child.tagName();
        if (name == "transforms")
        {
            load_fractal_transforms(child);
        }
        else if (name == "parameters")
        {
           load_fractal_parameters(child);
        }
        else if (name == "colour")
        {
            load_fractal_colour_parameters(child, parameters);
        }
        else if (name == "startposition")
        {
            unsigned int rotation = child.attribute("angle").toInt();
            m_fractal_config.setStartingCentre(StringComplex(child.attribute("r").toStdString(),
                                                             child.attribute("i").toStdString()));
            m_fractal_config.setStartingWidth(child.attribute("l").toStdString());
            m_fractal_config.setStartingRotation(rotation);
        }
        else if (name == "currentposition")
        {
            unsigned int rotation = child.attribute("angle").toInt();
            m_fractal_config.setImageCentre(StringComplex(child.attribute("r").toStdString(),
                                                          child.attribute("i").toStdString()));
            m_fractal_config.setImageWidth(child.attribute("l").toStdString());
            m_fractal_config.setRotation(rotation);
        }
        else if (name == "initialise")
        {
            load_fractal_initialise(child);
        }
        child = child.nextSiblingElement();
    }
}


void Config::load_level4_fractal_child(const QDomElement& root)
{
    OLD_FRACTAL_TYPE old_ft = static_cast<OLD_FRACTAL_TYPE>(root.attribute("id").toUInt());
    FRACTAL_TYPE ft = convert(old_ft);
    m_fractal_config.SetFractalType(ft);
    m_fractal_config.setOrbitPlotting(root.attribute("orbit").toInt() == 1);
    m_fractal_config.deleteTransforms();
    QString name;
    QDomElement child = root.firstChildElement();
    while (!child.isNull())
    {
        name = child.tagName();
        if (name == "transforms")
        {
            load_level4_fractal_transforms(child);
        }
        else if (name == "parameters")
        {
            load_level4_fractal_parameters(child);
            adjustParameters(old_ft);
        }
        else if (name == "colour")
        {
            load_fractal_colour_parameters(child, true);
        }
        else if (name == "startposition")
        {
            int rotation = child.attribute("angle").toUInt();
            if (rotation > 180) rotation = rotation - 360;
            m_fractal_config.setStartingCentre(StringComplex(child.attribute("r").toStdString(),
                                                             child.attribute("i").toStdString()));
            m_fractal_config.setStartingWidth(child.attribute("l").toStdString());
            m_fractal_config.setStartingRotation(rotation);
        }
        else if (name == "currentposition")
        {
            int rotation = child.attribute("angle").toUInt();
            if (rotation > 180) rotation = rotation - 360;
            m_fractal_config.setImageCentre(StringComplex(child.attribute("r").toStdString(),
                                                          child.attribute("i").toStdString()));
            m_fractal_config.setImageWidth(child.attribute("l").toStdString());
            m_fractal_config.setRotation(rotation);
        }
        else if (name == "initialise")
        {
            load_fractal_initialise(child);
        }
        child = child.nextSiblingElement();
    }
}


void Config::load_fractal_initialise(const QDomElement& root)
{
    QDomElement child = root.firstChildElement(); 
    if (child.tagName() == "z0")
    {
        auto value = child.attribute("type").toInt();
        auto type = static_cast<INITIAL_VALUE>(value);
        m_fractal_config.setInitialZtype(type);
        StringComplex fixed;
        if (type == FIXED)
        {
            fixed = StringComplex(child.attribute("r").toStdString(),
                                  child.attribute("i").toStdString());
        }
        m_fractal_config.setInitialZ(fixed);
    }
}

void Config::get_complex_function_keys(const QDomElement& child, KeyString& keys)
{
    bool pair = (child.attribute("pair") == "y");
    if (pair)
    {
        keys.SetKey("pair", "y");
        auto id = child.attribute("rid");
        keys.SetKey("rid", id.toStdString());
        auto rid = static_cast<FUNCTION_PARAMETER>(id.toInt());
        if (hasParameter(rid))
        {
            keys.SetKey("r", child.attribute("r").toStdString());
        }
        id = child.attribute("iid");
        keys.SetKey("iid", id.toStdString());
        auto iid = static_cast<FUNCTION_PARAMETER>(id.toInt());
        if (hasParameter(iid))
        {
            keys.SetKey("i", child.attribute("i").toStdString());
        }
    }
    else
    {
        keys.SetKey("pair", "n");
        auto id_str = child.attribute("id");
        keys.SetKey("id", id_str.toStdString());
        auto id = static_cast<COMPLEX_FUNCTION_PARAMETER>(id_str.toInt());
        if (hasParameter(id))
        {
            keys.SetKey("r", child.attribute("r").toStdString());
            keys.SetKey("i", child.attribute("i").toStdString());
        }
        else if (hasSize(id))
        {
            keys.SetKey("size", child.attribute("size").toStdString());
        }
        else if (hasRotation(id))
        {
            keys.SetKey("rotation", child.attribute("rotation").toStdString());
        }
    }
}


void Config::load_level4_cp_transform(const QDomElement& child)
{
    FractalConfig &f = m_fractal_config;
    auto id = static_cast<TRANSFORM>(child.attribute("type").toInt());
    long double re = stringToLongDouble(child.attribute("r").toStdString());
    long double im = stringToLongDouble(child.attribute("i").toStdString());
    int rotation = child.attribute("rot").toInt();
    long double size = stringToLongDouble(child.attribute("s").toStdString());
    if (id == T_TRANSLATION)
    {
        if ((re != 0.0L) || (im != 0.0L))
        {
            f.addComplexPlaneTransform(convertTranslation(re, im));
        }
    }
    else if (id == T_ROTATION)
    {
        if (rotation != 0)
        {
            f.addComplexPlaneTransform(convertRotation(rotation));
        }
    }
    else if (id == T_SCALE)
    {
        if ((re != 1.0L) || (im != 1.0L))
        {
            f.addComplexPlaneTransform(convertScale(re, im));
        }
    }
    else if (id == T_POWER)
    {
        f.addComplexPlaneTransform(convertPower(re, im));
    }
    else if (id == T_EXP)
    {
        f.addComplexPlaneTransform(convertExp());
    }
    else if (id == T_LOG)
    {
        f.addComplexPlaneTransform(convertLog());
    }
    else
    {
        if ((re != 0.0L) || (im != 0.0L))
        {
            f.addComplexPlaneTransform(convertTranslation((re != 0.0L ? -re : 0.0L),(im != 0.0L ? -im : 0.0L)));
        }
        if (rotation > 0.0L)
        {
            f.addComplexPlaneTransform(convertRotation(360 - rotation));
        }
        else if (id == T_UNSIGN_REAL)
        {
            f.addComplexPlaneTransform(convertUnsignReal());
        }
        else if (id == T_SIGN_REAL)
        {
            f.addComplexPlaneTransform(convertSignReal());
        }
        else if (id == T_REVERSE_SIGN_REAL)
        {
            f.addComplexPlaneTransform(convertReverseSignReal());
        }
        else if (id == T_UNSIGN_IMAGINARY)
        {
            f.addComplexPlaneTransform(convertUnsignImaginary());
        }
        else if (id == T_SIGN_IMAGINARY)
        {
            f.addComplexPlaneTransform(convertSignImaginary());
        }
        else if (id == T_REVERSE_SIGN_IMAGINARY)
        {
            f.addComplexPlaneTransform(convertReverseSignImaginary());
        }
        else if ((id == T_CIRCLE_IN) || (id == T_INVERSE_FOLD_IN) ||
                 (id == T_CIRCLE_OUT) || (id == T_INVERSE_FOLD_OUT) ||
                 (id == T_CIRCLE_REFLECT) || (id == T_INVERSE_REFLECT))
        {
            f.addComplexPlaneTransform(convertCircleTransform(id, size));
        }
        else if (id == T_TOP_RIGHT)
        {
            f.addComplexPlaneTransform(convertTopRight());
        }
        else if (id == T_BOTTOM_RIGHT)
        {
            f.addComplexPlaneTransform(convertBottomRight());
        }
        else if (id == T_TOP_LEFT)
        {
            f.addComplexPlaneTransform(convertTopLeft());
        }
        else if (id == T_BOTTOM_LEFT)
        {
            f.addComplexPlaneTransform(convertBottomLeft());
        }
        if (rotation > 0.0L)
        {
            f.addComplexPlaneTransform(convertRotation(rotation));
        }
        if ((re != 0.0L) || (im != 0.0L))
        {
            f.addComplexPlaneTransform(convertTranslation(re, im));
        }
    }
}

void Config::load_level4_transform(unsigned int set, const QDomElement& child)
{
    FractalConfig &f = m_fractal_config;
    auto id = static_cast<TRANSFORM>(child.attribute("type").toInt());
    long double re = stringToLongDouble(child.attribute("r").toStdString());
    long double im = stringToLongDouble(child.attribute("i").toStdString());
    int rotation = child.attribute("rot").toInt();
    long double size = stringToLongDouble(child.attribute("size").toStdString());
    if (id == T_TRANSLATION)
    {
        if ((re != 0.0L) || (im != 0.0L))
        {
            f.addTransform(set, convertTranslation(re, im));
        }
    }
    else if (id == T_ROTATION)
    {
        if (rotation != 0)
        {
            f.addTransform(set, convertRotation(rotation));
        }
    }
    else if (id == T_SCALE)
    {
        if ((re != 1.0L) || (im != 1.0L))
        {
            f.addTransform(set, convertScale(re, im));
        }
    }
    else if (id == T_POWER)
    {
        f.addTransform(set, convertPower(re, im));
    }
    else if (id == T_EXP)
    {
        f.addTransform(set, convertExp());
    }
    else if (id == T_LOG)
    {
        f.addTransform(set, convertLog());
    }
    else
    {
        if ((re != 0.0L) || (im != 0.0L))
        {
            f.addTransform(set, convertTranslation((re != 0.0L ? -re : 0.0L),(im != 0.0L ? -im : 0.0L)));
        }
        if (rotation > 0.0L)
        {
            f.addTransform(set, convertRotation(360 - rotation));
        }
        else if (id == T_UNSIGN_REAL)
        {
            f.addTransform(set, convertUnsignReal());
        }
        else if (id == T_SIGN_REAL)
        {
            f.addTransform(set, convertSignReal());
        }
        else if (id == T_REVERSE_SIGN_REAL)
        {
            f.addTransform(set, convertReverseSignReal());
        }
        else if (id == T_UNSIGN_IMAGINARY)
        {
            f.addTransform(set, convertUnsignImaginary());
        }
        else if (id == T_SIGN_IMAGINARY)
        {
            f.addTransform(set, convertSignImaginary());
        }
        else if (id == T_REVERSE_SIGN_IMAGINARY)
        {
            f.addTransform(set, convertReverseSignImaginary());
        }
        else if ((id == T_CIRCLE_IN) || (id == T_INVERSE_FOLD_IN) ||
                (id == T_CIRCLE_OUT) || (id == T_INVERSE_FOLD_OUT) ||
                (id == T_CIRCLE_REFLECT) || (id == T_INVERSE_REFLECT))
        {
            f.addTransform(set, convertCircleTransform(id, size));
        }
        else if (id == T_TOP_RIGHT)
        {
            f.addTransform(set, convertTopRight());
        }
        else if (id == T_BOTTOM_RIGHT)
        {
            f.addTransform(set, convertBottomRight());
        }
        else if (id == T_TOP_LEFT)
        {
            f.addTransform(set, convertTopLeft());
        }
        else if (id == T_BOTTOM_LEFT)
        {
            f.addTransform(set, convertBottomLeft());
        }
        if (rotation > 0.0L)
        {
            f.addTransform(set, convertRotation(rotation));
        }
        if ((re != 0.0L) || (im != 0.0L))
        {
            f.addTransform(set, convertTranslation(re, im));
        }
    }
}

void Config::load_fractal_parameters(const QDomElement& root)
{
    FractalConfig &f = m_fractal_config;
    int cp_index = 0;
    int p_index = 0;
    int f_index = 0;
    int cf_index = 0;
    QString name;
    QDomElement child = root.firstChildElement();
    while (!child.isNull())
    {
        name = child.tagName();
        if (name == "bailout")
        {
            f.setBailout(static_cast<BAILOUT>(child.attribute("type").toUInt()));
            f.setLimit(stringToLongDouble(child.attribute("limit").toStdString()));
        }
        else if (name == "max_iterations")
        {
            f.setMaxIterations(child.attribute("value").toInt());
        }
        else if (name == "start_orbit_iteration")
        {
            f.setOmit(child.attribute("value").toUInt());
        }
        else if (name == "complex_param")
        {
            std::string r = child.attribute("r").toStdString();
            std::string i = child.attribute("i").toStdString();
            auto type = static_cast<PARAMETER_TYPE>(child.attribute("c").toUInt());
            f.setComplexParameter(cp_index, StringComplex(r, i), type);
            cp_index++;
        }
        else if (name == "param")
        {
            f.setParameter(p_index, child.attribute("value").toStdString());
            p_index++;
        }
        else if (name == "function")
        {
            KeyString keys;
            keys.SetKey("id", child.attribute("id").toStdString());
            auto id = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("id", 0));
            if (hasParameter(id))
            {
                keys.SetKey("p", child.attribute("p").toStdString());
            }
            f.setFunctionParameter(f_index, keys.String());
            f_index++;
        }
        else if (name == "complex_function")
        {
            KeyString keys;
            get_complex_function_keys(child, keys);
            f.setComplexFunctionParameter(cf_index, keys.String());
            cf_index++;
        }
        else if (name == "sequence")
        {
            f.setLyapunovSequence(child.attribute("value").toStdString());
        }
        else if (name == "settling")
        {
            f.setSettlingCycles(child.attribute("value").toUInt());
        }
        else if (name == "calculating")
        {
            f.setCalculatingCycles(child.attribute("value").toUInt());
        }
        else if (name == "plot")
        {
            auto type = child.attribute("type").toUInt();
            f.setArea(child.attribute("area").toUInt());
            f.setOrbitPlot(static_cast<ORBIT_PLOTS>(type));
        }
        else if (name == "plot_density")
        {
            f.setDensity(child.attribute("value").toInt()); 
        }
        child = child.nextSiblingElement();
    }
}


void Config::load_level4_fractal_parameters(const QDomElement& root)
{
    FractalConfig& f = m_fractal_config;
    int cp_index = 0;
    int p_index = 0;
    int f_index = 0;
    int cf_index = 0;
    QString name;
    QDomElement child = root.firstChildElement();
    while (!child.isNull())
    {
        name= child.tagName();
        if (name == "bailout")
        {
            f.setBailout(static_cast<BAILOUT>(child.attribute("type").toUInt()));
            f.setLimit(stringToLongDouble(child.attribute("limit").toStdString()));
        }
        else if (name == "max_iterations")
        {
            f.setMaxIterations(child.attribute("value").toInt());
        }
        else if (name == "start_orbit_iteration")
        {
            f.setOmit(child.attribute("value").toUInt());
        }
        else if (name == "complex_param")
        {
            std::string r = child.attribute("r").toStdString();
            std::string i = child.attribute("i").toStdString();
            auto type = static_cast<PARAMETER_TYPE>(child.attribute("c").toUInt());
            f.setComplexParameter(cp_index, StringComplex(r, i), type);
            cp_index++;
        }
        else if (name == "param")
        {
            f.setParameter(p_index, child.attribute("value").toStdString());
            p_index++;
        }
        else if (name == "function")
        {
            int value = child.attribute("value").toInt();
            auto id = static_cast<OLD_FUNCTION_PARAMETER>(value);
            f.setFunctionParameter(f_index, convert(id));
            f_index++;
        }
        else if (name == "complex_function")
        {
            int value = child.attribute("value").toUInt();
            auto id = static_cast<OLD_COMPLEX_FUNCTION_PARAMETER>(value);
            f.setComplexFunctionParameter(cf_index, convert(id));
            cf_index++;
        }
        else if (name == "sequence")
        {
            f.setLyapunovSequence(child.attribute("value").toStdString());
        }
        else if (name == "settling")
        {
            f.setSettlingCycles(child.attribute("value").toUInt());
        }
        else if (name == "calculating")
        {
            f.setCalculatingCycles(child.attribute("", "value").toUInt());
        }
        else if (name == "plot")
        {
            auto type = child.attribute("type").toUInt();
            f.setArea(child.attribute("area").toUInt());
            f.setOrbitPlot(static_cast<ORBIT_PLOTS>(type));
        }
        child = child.nextSiblingElement();
    }
}

void Config::load_fractal_transforms(const QDomElement& root)
{
    FractalConfig& f = m_fractal_config;
    f.deleteTransforms();
    QString name;
    QDomElement child = root.firstChildElement();
    while (!child.isNull())
    {
        name = child.tagName();
        if (name == "sequence")
        {
            f.setTransformSequence(child.attribute("value").toStdString());
        }
        else if (name == "set")
        {
            unsigned int set = child.attribute("id").toUInt();
            load_transform_set(set, child);
        }
        else if (name == "complex_plane")
        {
            load_complex_plane_transforms(child);
        }
        child = child.nextSiblingElement();
    }
}

void Config::load_level4_fractal_transforms(const QDomElement& root)
{
    FractalConfig& f = m_fractal_config;
    f.deleteTransforms();
    f.addTransformSet(1); // Add transform set A
    f.addTransformSet(2); // Add transform set B
    QString name;
    QDomElement child = root.firstChildElement();
    while (!child.isNull())
    {
        name = child.tagName();
        if (name == "sequence")
        {
            f.setTransformSequence(child.attribute("value").toStdString());
        }
        else if (name == "A")
        {
            load_level4_transform_set(0, child);
        }
        else if (name == "B")
        {
            load_level4_transform_set(1, child);
        }
        else if (name == "C")
        {
            load_level4_transform_set(2, child);
        }
        child = child.nextSiblingElement();
    }
}

void Config::load_complex_plane_transforms(const QDomElement& root)
{
    FractalConfig& f = m_fractal_config;
    QString name;
    QDomElement child = root.firstChildElement();
    while (!child.isNull())
    {
        name = child.tagName();
        if (name == "complex_function")
        {
            KeyString keys;
            get_complex_function_keys(child, keys);
            f.addComplexPlaneTransform(keys.String());
        }
        child = child.nextSiblingElement();
    }
}

void Config::load_transform_set(unsigned int set, const QDomElement& root)
{
    FractalConfig &f = m_fractal_config;
    f.addTransformSet(set);
    QString name;
    QDomElement child = root.firstChildElement();
    while (!child.isNull())
    {
        name = child.tagName();
        if (name == "complex_function")
        {
            KeyString keys;
            get_complex_function_keys(child, keys);
            f.addTransform(set, keys.String());
        }
        child = child.nextSiblingElement();
    }
}


void Config::load_level4_transform_set(unsigned int set, const QDomElement& root)
{
    FractalConfig &f = m_fractal_config;
    f.addTransformSet(set);
    QDomElement child = root.firstChildElement();
    while (!child.isNull())
    {
        if (child.tagName() == "transform")
        {
            if (set == 2)
            {
                load_level4_cp_transform(child);
            }
            else
            {
                load_level4_transform(set, child);
            }
        }
        child = child.nextSiblingElement();
    }
}


void Config::load_fractal_colour_parameters(const QDomElement& root, bool parameters_file)
{
    FractalConfig &f = m_fractal_config;
    QString name;
    QDomElement child = root.firstChildElement();
    while (!child.isNull())
    {
        name = child.tagName();
        if (name == "map")
        {
            f.setInner(false);
            load_fractal_colour_map(child, parameters_file);
        }
        else if (name == "orbit")
        {
            f.setInner(false);
            f.enableOrbitBackground(false);
            QDomElement orbit_child = child.firstChildElement();
            while (!orbit_child.isNull())
            {
                name = orbit_child.tagName();
                if (name == "map")
                {
                    if (parameters_file)
                    {
                        m_map1 = orbit_child.attribute("name");
                        f.setOrbitRedOffset(m_level < 7 ? orbit_child.attribute("offset").toUInt()
                                                        : orbit_child.attribute("red_offset").toUInt());
                        f.setOrbitGreenOffset(m_level < 7 ? orbit_child.attribute("offset").toUInt()
                                                     : orbit_child.attribute("green_offset").toUInt());
                        f.setOrbitBlueOffset(m_level < 7 ? orbit_child.attribute("offset").toUInt()
                                                    :orbit_child.attribute("blue_offset").toUInt());
                        f.setComponentOrder(m_level < 7 ? CO_RGB
                                                        : static_cast<COMPONENT_ORDER>(orbit_child.attribute("order").toUInt()));
                    }
                    else
                    {
                        f.setOrbitColourMapName(orbit_child.attribute("name"));
                        f.setOrbitRedOffset(orbit_child.attribute("red_offset").toUInt());
                        f.setOrbitGreenOffset(orbit_child.attribute("green_offset").toUInt());
                        f.setOrbitBlueOffset(orbit_child.attribute("blue_offset").toUInt());
                        f.setComponentOrder(static_cast<COMPONENT_ORDER>(orbit_child.attribute("order").toUInt()));
                    }
                }
                else if (name == "accumulation")
                {
                    f.setOrbitColourType('a');
                }
                else if (name == "sqrt")
                {
                    f.setOrbitScale(stringToLongDouble(orbit_child.attribute("scale").toStdString()));
                    f.setOrbitColourType('b');
                }
                else if (name == "average")
                {
                    f.setOrbitColourInterval(orbit_child.attribute("intervals").toUInt());
                    f.setOrbitColourType('c');
                }
                else if (name == "log")
                {
                    f.setOrbitScale(stringToLongDouble(orbit_child.attribute("scale").toStdString()));
                    f.setOrbitColourType('d');
                }
                else if (name == "background")
                {
                    int r = orbit_child.attribute("red").toInt();
                    int g = orbit_child.attribute("green").toInt();
                    int b = orbit_child.attribute("blue").toInt();
                    f.setOrbitBackground(QColor(r,g,b));
                    f.enableOrbitBackground(true);
                }
                orbit_child = orbit_child.nextSiblingElement();
            }
        }
        else if (name == "outer")
        {
            f.setInner(false);
            load_fractal_colour_parameters_child(child, parameters_file);
        }
        else if (name == "inner")
        {
            f.setInner(true);
            load_fractal_colour_parameters_child(child, parameters_file);
        }
        else if (name == "select")
        {
            m_fractal_config.setSelection(child.attribute("type").toStdString());
            m_fractal_config.setSelectLimit(stringToLongDouble(child.attribute("limit").toStdString()));
        }
        child = child.nextSiblingElement();
    }
}

void Config::load_fractal_colour_parameters_child(const QDomElement& root, bool parameters)
{
    bool abslog = false;
    QString name;
    QDomElement child = root.firstChildElement();
    while (!child.isNull())
    {
        name = child.tagName();
        if (name == "map")
        {
            load_fractal_colour_map(child, parameters);
        }
        else if (name == "abslog")
        {
            abslog = true;
        }
        else if (name == "iteration")
        {
            m_fractal_config.setMethod("i");
            m_fractal_config.setSmooth(child.attribute("smooth").toUInt() == 1);
        }
        else if (name == "fixed")
        {
            QString fixed("f,");
            fixed += child.attribute("r");
            fixed += ",";
            fixed += child.attribute("g");
            fixed += ",";
            fixed += child.attribute("b");
            m_fractal_config.setMethod(fixed.toStdString());
        }
        else if (name == "final_angle")
        {
            m_fractal_config.setMethod("a");
            m_fractal_config.setScale(stringToLongDouble(child.attribute("scale").toStdString()));
            m_fractal_config.setSmooth(child.attribute("smooth").toUInt() == 1);
        }
        else if (name == "final_magnitude")
        {
            std::string magnitude("m");
            magnitude += child.attribute("type").toStdString();
            m_fractal_config.setMethod(magnitude);
            m_fractal_config.setScale(stringToLongDouble(child.attribute("scale").toStdString()));
            m_fractal_config.setSmooth(child.attribute("smooth").toUInt() == 1);
        }
        else if (name == "gaussian")
        {
            std::string magnitude("g");
            magnitude += child.attribute("type").toStdString();
            m_fractal_config.setMethod(magnitude);
            m_fractal_config.setScale(stringToLongDouble(child.attribute("scale").toStdString()));
            m_fractal_config.setSmooth(child.attribute("smooth").toUInt() == 1);
        }
        else if (name == "magnitude")
        {
            std::string magnitude("M");
            magnitude += child.attribute("type").toStdString();
            m_fractal_config.setMethod(magnitude);
            m_fractal_config.setScale(stringToLongDouble(child.attribute("scale").toStdString()));
            m_fractal_config.setSmooth(child.attribute("smooth").toUInt() == 1);
        }
        else if (name == "angle")
        {
            std::string magnitude("A");
            magnitude += child.attribute("type").toStdString();
            m_fractal_config.setMethod(magnitude);
            m_fractal_config.setScale(stringToLongDouble(child.attribute("scale").toStdString()));
            m_fractal_config.setSmooth(child.attribute("smooth").toUInt() == 1);
        }
        else if (name == "ratio")
        {
            std::string magnitude("r");
            magnitude += child.attribute("type").toStdString();
            m_fractal_config.setMethod(magnitude);
            m_fractal_config.setScale(stringToLongDouble(child.attribute("scale").toStdString()));
            m_fractal_config.setSmooth(child.attribute("smooth").toUInt() == 1);
        }
        else if (name == "trap")
        {
            load_trap_parameters(child, true);
        }
        child = child.nextSiblingElement();
    }
    m_fractal_config.setAbsLog(abslog);
}


void Config::load_colour_map_child(const QDomElement& root, bool parameters)
{
    ColourMap map;
    QDomElement child = root.firstChildElement();
    QString map_name = root.attribute("name");
    ColourMap::MAP_TYPE type = ColourMap::CM_MANUAL;
    if (parameters && m_level < 7)
    {
        bool is_auto = (root.attribute("auto").toInt() == 1);
        type = (is_auto ?ColourMap::CM_AUTO : ColourMap::CM_MANUAL);
    }
    else
    {
        type = static_cast<ColourMap::MAP_TYPE>(root.attribute("type").toInt());
    }
    map.setType(type);
    QString tag_name;
    while (!child.isNull())
    {
        tag_name = child.tagName();
        if (tag_name == "rgb")
        {
            unsigned int index = child.attribute("index").toUInt();
            QRgb colour = qRgb(child.attribute("red").toInt(),
                               child.attribute("green").toInt(),
                               child.attribute("blue").toInt());
            map.setColour(index, colour);
        }
        else if ((tag_name == "red") && (type == ColourMap::CM_AUTO)) 
        {
            load_auto_colour(child, RGB_RED, map);
        }
        else if ((tag_name == "green") && (type == ColourMap::CM_AUTO)) 
        {
            load_auto_colour(child, RGB_GREEN, map);
        }
        else if ((tag_name == "blue") && (type == ColourMap::CM_AUTO)) 
        {
            load_auto_colour(child, RGB_BLUE, map);
        }
        else if (tag_name == "red")
        {
            unsigned int index = child.attribute("index").toUInt();
            unsigned int value = child.attribute("value").toUInt();
            map.setRed(index, value);
        }
        else if (tag_name == "green")
        {
            unsigned int index = child.attribute("index").toUInt();
            unsigned int value = child.attribute("value").toUInt();
            map.setGreen(index, value);
        }
        else if (tag_name == "blue")
        {
            unsigned int index = child.attribute("index").toUInt();
            unsigned int value = child.attribute("value").toUInt();
            map.setBlue(index, value);
        }
        child = child.nextSiblingElement();
    }
    QString assigned_map_name = m_colour_maps->setColours(map_name, map, parameters);
    if (map_name == m_map1)
    {
        m_map1 = assigned_map_name;
    }
    if (map_name == m_map2)
    {
        m_map2 = assigned_map_name;
    }
}

void Config::load_auto_colour(const QDomElement& child, RGB colour, ColourMap &map)
{
    Waveform::AutoColour auto_colour;
    auto_colour.hoffset = child.attribute("hoffset").toInt();
    auto_colour.voffset = child.attribute("voffset").toInt();
    auto_colour.maximum = child.attribute("maximum").toInt();
    auto_colour.wave = static_cast<Waveform::WAVE>(child.attribute("wave").toUInt());
    auto_colour.cycles = child.attribute("cycles").toUInt();
    map.setAutoColour(colour, auto_colour);
}

void Config::save_fractal_starting_position(QDomDocument* dom, QDomElement& root)
{
    auto tag = dom->createElement("startposition");
    tag.setAttribute("r", QString::fromStdString(m_fractals_config.getStartingCentre().r));
    tag.setAttribute("i", QString::fromStdString(m_fractals_config.getStartingCentre().i));
    tag.setAttribute("l", QString::fromStdString(m_fractals_config.getStartingWidth()));
    tag.setAttribute("angle", m_fractals_config.getStartingRotation());
    root.appendChild(tag);
}

void Config::save_fractal_current_position(QDomDocument* dom, QDomElement& root)
{
    auto tag = dom->createElement("currentposition");
    tag.setAttribute("r", QString::fromStdString(m_fractals_config.getCentre().r));
    tag.setAttribute("i", QString::fromStdString(m_fractals_config.getCentre().i));
    tag.setAttribute("l", QString::fromStdString(m_fractals_config.getCurrentWidth()));
    tag.setAttribute("angle", m_fractals_config.getRotation());
    root.appendChild(tag);
}

void Config::save_colour_selection(QDomDocument* dom, QDomElement& root)
{
    if (m_fractals_config.GetFractalType() != F_LYAPUNOV)
    {
        auto tag = dom->createElement("select");
        std::string selection = m_fractals_config.getSelection();
        if (selection.length() != 5)
        {
            selection = "normz";
        }
        tag.setAttribute("type", QString::fromStdString(selection));
        tag.setAttribute("limit", longdoubleToQString(m_fractals_config.getSelectLimit()));
        root.appendChild(tag);
    }
}

void Config::save_colour_map(QDomDocument* dom, QDomElement& root)
{
    FractalsConfig& f = m_fractals_config;
    auto tag = dom->createElement("map");
    tag.setAttribute("name", f.getColourMap());
    tag.setAttribute("order", f.getComponentOrder());
    tag.setAttribute("red_offset", f.getRedOffset());
    tag.setAttribute("green_offset", f.getGreenOffset());
    tag.setAttribute("blue_offset", f.getBlueOffset());
    if (f.GetFractalType() == F_LYAPUNOV)
    {
        tag.setAttribute("scale", longdoubleToQString(f.getColourScale()));
        tag.setAttribute("smooth", f.getSmooth());
    }
    root.appendChild(tag);
}

void Config::save_orbit_colour_child(QDomDocument* dom, QDomElement& root)
{
    auto tag = dom->createElement("orbit");
    root.appendChild(tag);
    FractalsConfig& f = m_fractals_config;
    f.setInner(false);
    auto map_tag = dom->createElement("map");
    map_tag.setAttribute("name", f.getColourMap());
    map_tag.setAttribute("order", f.getComponentOrder());
    map_tag.setAttribute("red_offset", f.getRedOffset());
    map_tag.setAttribute("green_offset", f.getGreenOffset());
    map_tag.setAttribute("blue_offset", f.getBlueOffset());
    tag.appendChild(map_tag);
    char type = f.getOrbitColourType();
    QDomElement child_tag;
    switch (type)
    {
    default:
    case 'a':
        child_tag = dom->createElement("accumulation");
        break;
    case 'b':
        child_tag = dom->createElement("sqrt");
        child_tag.setAttribute("scale", longdoubleToQString(f.getOrbitScale()));
        break;
    case 'c':
        child_tag = dom->createElement("average");
        child_tag.setAttribute("intervals", f.getOrbitColourInterval());
        break;
    case 'd':
        child_tag = dom->createElement("log");
        child_tag.setAttribute("scale", longdoubleToQString(f.getOrbitScale()));
        break;
    }
    tag.appendChild(child_tag);
    if (f.hasOrbitBackground())
    {
        QColor colour = f.getOrbitBackground();
        child_tag = dom->createElement("background");
        child_tag.setAttribute("red", colour.red());
        child_tag.setAttribute("green", colour.green());
        child_tag.setAttribute("blue", colour.blue());
        tag.appendChild(child_tag);
    }
}    

void Config::save_fixed_colour(QDomDocument* dom, QDomElement& root, const std::string &method)
{
    auto tag = dom->createElement("fixed");
    QRgb colour = getColour(method);
    tag.setAttribute("r", qRed(colour));
    tag.setAttribute("g", qGreen(colour));
    tag.setAttribute("b", qBlue(colour));
    root.appendChild(tag);
}

void Config::save_final_angle(QDomDocument* dom, QDomElement& root)
{
    FractalsConfig& f = m_fractals_config;
    auto tag = dom->createElement("final_angle");
    tag.setAttribute("scale", longdoubleToQString(f.getColourScale()));
    tag.setAttribute("smooth", f.getSmooth());
    root.appendChild(tag);
}

void Config::save_final_magnitude(QDomDocument* dom, QDomElement& root, std::string &method)
{
    auto tag = dom->createElement("final_magnitude");
    if (method.length() != 2)
    {
        method = "mn";
    }
    std::string type = method.substr(1,1);
    add_method_attributes(tag, type);
    root.appendChild(tag);
}

void Config::save_gaussian(QDomDocument* dom, QDomElement& root, std::string &method)
{
    auto tag = dom->createElement("gaussian");
    if (method.length() != 3)
    {
        method = "gac";
    }
    std::string type = method.substr(1,2);
    add_method_attributes(tag, type);
    root.appendChild(tag);
}

void Config::save_magnitude(QDomDocument* dom, QDomElement& root, std::string &method)
{
    auto tag = dom->createElement("magnitude");
    if (method.length() != 2)
    {
        method = "Ma";
    }
    std::string type = method.substr(1,1);
    add_method_attributes(tag, type);
    root.appendChild(tag);
}

void Config::save_angle(QDomDocument* dom, QDomElement& root, std::string &method)
{
    auto tag = dom->createElement("angle");
    if (method.length() != 2)
    {
        method = "Aa";
    }
    std::string type = method.substr(1,1);
    add_method_attributes(tag, type);
    root.appendChild(tag);
}

void Config::save_ratio(QDomDocument* dom, QDomElement& root, std::string &method)
{
    auto tag = dom->createElement("ratio");
    if (method.length() != 4)
    {
        method = "raba";
    }
    std::string type = method.substr(1,3);
    add_method_attributes(tag, type);
    root.appendChild(tag);
}

void Config::save_trap(QDomDocument* dom, QDomElement& root, std::string &method, bool inner)
{
    TrapConfig &t = m_trap_config;
    auto trap_tag = dom->createElement("trap");
    if (method.length() < 3)
    {
        method = "taa,cp=0,i=0.0,r=0.0,rot=0.0";
    }
    std::string type = method.substr(1,2);
    add_method_attributes(trap_tag, type);
    OrbitTrap::TRAP_TYPE trap = static_cast<OrbitTrap::TRAP_TYPE>(method[1] - 'a');
    t.setTrapType(inner, trap);
    t.configFromString(method.substr(3));
    LongComplex pos = t.getPosition();
    auto child_tag = dom->createElement("position");
    child_tag.setAttribute("r", longdoubleToQString(real(pos)));
    child_tag.setAttribute("i", longdoubleToQString(imag(pos)));
    long double width = t.getWidth();
    long double hieght = width; // to be added later when closest distance to an ellipse is implemented
    child_tag = dom->createElement("size");
    child_tag.setAttribute("w", longdoubleToQString(width));
    child_tag.setAttribute("h", longdoubleToQString(hieght));
    trap_tag.appendChild(child_tag);
    child_tag = dom->createElement("centre_point");
    child_tag.setAttribute("value", t.getCentrePoint());
    trap_tag.appendChild(child_tag);
    if (t.hasRotation())
    {
        child_tag = dom->createElement("rotation"); //  check
        child_tag.setAttribute("value", t.getRotation());
        trap_tag.appendChild(child_tag);
    }
    if (t.isSteinerChain())
    {
        child_tag = dom->createElement("chain");
        child_tag.setAttribute("n", t.getChainCircles());
        child_tag.setAttribute("invd", longdoubleToQString(t.getInversionDistance()));
        child_tag.setAttribute("crot", longdoubleToQString(t.getConstructionRotation()));
        child_tag.setAttribute("inner", t.getInnerCircle());
        child_tag.setAttribute("outer", t.getOuterCircle());
        child_tag.setAttribute("triangles", t.getTriangles());
        child_tag.setAttribute("cp", t.getCentrePoints());
        trap_tag.appendChild(child_tag);
    }
    root.appendChild(trap_tag);
}

void Config::add_method_attributes(QDomElement& child, const std::string &type)
{
    FractalsConfig &f = m_fractals_config;
    child.setAttribute("type", QString::fromStdString(type));
    child.setAttribute("scale", longdoubleToQString(f.getColourScale()));
    child.setAttribute("smooth", f.getSmooth());
}


void Config::load_fractal_colour_map(const QDomElement& child, bool parameters)
{
    FractalConfig& f = m_fractal_config;
    QString &map = (f.isInner() ? m_map2 : m_map1);
    if (parameters)
    {
        map = child.attribute("name");
        f.setRedOffset(m_level < 7 ? child.attribute("offset").toUInt()
                                   : child.attribute("red_offset").toUInt());
        f.setGreenOffset(m_level < 7 ? child.attribute("offset").toUInt()
                                     : child.attribute("green_offset").toUInt());
        f.setBlueOffset(m_level < 7 ? child.attribute("offset").toUInt()
                                    : child.attribute("blue_offset").toUInt());
        f.setComponentOrder(m_level < 7 ? CO_RGB
                                        : static_cast<COMPONENT_ORDER>(child.attribute("order").toUInt()));
    }
    else
    {
        f.setColourMapName(child.attribute("name"));
        f.setRedOffset(child.attribute("red_offset").toUInt());
        f.setGreenOffset(child.attribute("green_offset").toUInt());
        f.setBlueOffset(child.attribute("blue_offset").toUInt());
        f.setComponentOrder(static_cast<COMPONENT_ORDER>(child.attribute("order").toUInt()));
    }
    if (m_fractal_config.GetFractalType() == F_LYAPUNOV)
    {
        f.setMethod("v");
        f.setScale(stringToLongDouble(child.attribute("scale").toStdString()));
        f.setSmooth(child.attribute("smooth").toUInt());
    }
}

void Config::load_trap_parameters(const QDomElement& root, bool inner)
{
    std::string method = "t";
    method += root.attribute("type").toStdString();
    m_fractal_config.setScale(stringToLongDouble(root.attribute("scale").toStdString()));
    m_fractal_config.setSmooth(root.attribute("smooth").toUInt() == 1);
    OrbitTrap::TRAP_TYPE trap = static_cast<OrbitTrap::TRAP_TYPE>(method[1] - 'a');
    m_trap_config.setTrapType(inner, trap);
    QString name;
    QDomElement child = root.firstChildElement();
    while (!child.isNull())
    {
        name = child.tagName();
        if (name == "position")
        {
            long double r = stringToLongDouble(child.attribute("r").toStdString());
            long double i = stringToLongDouble(child.attribute("i").toStdString());
            m_trap_config.setPosition(LongComplex(r, i));
        }
        else if (name == "size")
        {
            long double w = stringToLongDouble(child.attribute("w").toStdString());
            m_trap_config.setWidth(w);
        }
        else if (name == "centre_point")
        {
            m_trap_config.setCentrePoint(child.attribute("value").toUInt() == 1);
        }
        else if (name == "rotation")
        {
            m_trap_config.setRotation(child.attribute("value").toUInt());
        }
        else if (name == "chain")
        {
            m_trap_config.setChainCircles(child.attribute("n").toUInt());
            m_trap_config.setInversionDistance(stringToLongDouble(child.attribute("invd").toStdString()));
            m_trap_config.setConstructionRotation(stringToLongDouble(child.attribute("crot").toStdString()));
            m_trap_config.setInnerCircle(child.attribute("inner").toUInt() == 1);
            m_trap_config.setOuterCircle(child.attribute("outer").toUInt() == 1);
            m_trap_config.setTriangles(child.attribute("triangles").toUInt() == 1);
            m_trap_config.setCentrePoints(child.attribute("cp").toUInt() == 1);
        }
        child = child.nextSiblingElement();
    }
    method += "," + m_trap_config.configAsString();
    m_fractal_config.setMethod(method);
}

bool Config::load_parameter_file(const QString& path)
{
    m_fractal_config = FractalConfig();
    m_map1 = "";
    m_map2 = "";
    m_fractal_config.deleteTransforms();
    boost::scoped_ptr<QDomDocument> dom(new QDomDocument());
    QDir directory(QDir::homePath());
    bool ok = false;
    if (directory.exists(path))
    {
        boost::shared_ptr<Config> cfg = Config::instance();
        QFile file(path);
        if (file.open(QIODevice::ReadOnly))
        {
            ok = dom->setContent(&file);
            file.close();
        }
    }
    if (ok)
    {
        ok = false;
        QDomElement root = dom->documentElement();
        if (!root.isNull())
        {
            // Node should be saturn
            QString name = root.tagName();
            if (name == "saturn_parameters")
            {
                m_level = root.attribute("level").toInt();
                ok = ((m_level >= 3) && (m_level <= LEVEL));
                if (ok)
                {
                    QString str = root.attribute("hpixels");
                    if (!str.isEmpty())
                    {
                        m_fractal_config.setWidth(str.toUInt());
                        m_fractal_config.setHeight(root.attribute("vpixels").toUInt());
                    }
                    QDomElement child = root.firstChildElement();
                    while (!child.isNull())
                    {
                        QString name = child.tagName();
                        if (name == "fractal")
                        {
                            m_fractal_config.setDensity(1);
                            unsigned int id = child.attribute("id").toUInt();
                            if (m_level > 4)
                            {
                                load_fractal_child(child, true);
                            }
                            else
                            {
                                auto old_ft = static_cast<OLD_FRACTAL_TYPE>(id);
                                if ((old_ft == FT_TZDRICPAC) || (old_ft == FT_TZDRICPAC_J))
                                {
                                    // This fractal has been deleted
                                    ok = false;
                                    break;
                                }
                                load_level4_fractal_child(child);
                            }
                        }
                        else if (name == "colourmap")
                        {
                            load_colour_map_child(child, true);
                        }
                        child = child.nextSiblingElement();
                    }
                    if (m_fractal_config.isOrbitPlotting())
                    {
                        m_fractal_config.setOrbitColourMapName(m_map1);
                    }
                    else
                    {
                        m_fractal_config.setColourMapName(m_map1, false);
                        m_fractal_config.setColourMapName(m_map2, true);
                    }
                }
            }
        }
    }
    return ok;
}

void Config::save_scm_file(const QString& path, std::vector<QString>& maps)
{
    boost::scoped_ptr<QDomDocument> dom(new QDomDocument());
    auto root = dom->createElement("saturn_colour_maps");
    dom->appendChild(root);
    for (auto it = maps.begin(); it != maps.end(); it++)
    {
         save_colour_map_child(dom.get(), root, *it);
    }
    QByteArray doc_bytes = dom->toByteArray();
    QFile file(path);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(doc_bytes, doc_bytes.size());
    }
    else
    {
        std::cout << "error " << file.error() << std::endl;
    }
    file.close();
}

void Config::adjustParameters(OLD_FRACTAL_TYPE ft)
{
    FractalConfig& f = m_fractal_config;
    switch (ft)
    {
    case FT_MANDELBROT: f.setComplexParameterType(0, PT_IS_C); break;
    case FT_QUADRATIC: f.setComplexParameterType(2, PT_IS_C); break;
    case FT_CUBIC: f.setComplexParameterType(3, PT_IS_C); break;
    case FT_ALMOST_CUBIC: f.setComplexParameterType(3, PT_IS_C); break;
    case FT_BAD_COMPLEX_POWER: convertBcp_6(CFP_BCP, false); break;
    case FT_BCP_J: convertBcp_6(CFP_BCP, true); break;
    case FT_BCP2: convertBcp_6(CFP_BCP2, false); break;
    case FT_BCP2_J: convertBcp_6(CFP_BCP2, true); break;
    case FT_COSCZ: convertSingleFunction_6(CFP_COS, false); break;
    case FT_COSCZ_J: convertSingleFunction_6(CFP_COS, true); break;
    case FT_SINCZ: convertSingleFunction_6(CFP_SIN, false); break;
    case FT_SINCZ_J: convertSingleFunction_6(CFP_SIN, true); break;
    case FT_TANCZ: convertSingleFunction_6(CFP_TAN, false); break;
    case FT_TANCZ_J: convertSingleFunction_6(CFP_TAN, true); break;
    case FT_ZCPAC: convertZcpac_6(false); break;
    case FT_ZCPAC_J: convertZcpac_6(true); break;
    case FT_Z_POWER_C: convertZpowerC_6(); break;
    case FT_SINCZ_COSCZ: convertSinczCoscz_6(false); break;
    case FT_SINCZ_COSCZ_J: convertSinczCoscz_6(true); break;
    case FT_C_POWER_Z: convertCpowerZ_6(); break;
    case FT_NOVA: f.setComplexParameterType(2, PT_IS_C); break;
    case FT_NOVA_1: f.setComplexParameterType(5, PT_IS_C); break;
    case FT_NOVA_2: f.setComplexParameterType(3, PT_IS_C); break;
    case FT_QUARTIC: f.setComplexParameterType(4, PT_IS_C); break;
    case FT_QUINTIC: f.setComplexParameterType(5, PT_IS_C); break;
    case FT_MAGNET: f.setComplexParameterType(0, PT_IS_C); break;
    case FT_MAGNET_2: f.setComplexParameterType(0, PT_IS_C); break;
    case FT_SQRT_CPOWER: f.setComplexParameterType(1, PT_IS_C); break;
    case FT_COMPASSES: convertCompasses_6(false); break;
    case FT_COMPASSES_J: convertCompasses_6(true); break;
    case FT_PP_MANDELBROT_4F: f.setComplexParameterType(0, PT_IS_C); break;
    case FT_PP_MANDELBROT_6F: f.setComplexParameterType(0, PT_IS_C); break;
    case FT_COMBINATION: f.setComplexParameterType(4, PT_IS_C); break;
    case FT_COMBINATION_2: convertCombination2_6(); break;
    case FT_COMBINATION_3: convertCombination3_6(); break;
    case FT_COMBINATION_4: convertCombination4_6(); break;
    case FT_UNNAMED: convertUnnamed_6(false); break;
    case FT_UNNAMED_J: convertUnnamed_6(true); break;
    case FT_UNNAMED_2: convertUnnamed2_6(false); break;
    case FT_UNNAMED_2_J: convertUnnamed2_6(true); break;
    case FT_TZACCP: convertTzaccp_6(false); break;
    case FT_TZACCP_J: convertTzaccp_6(true); break;
    case FT_ZACCP: convertZaccp_6(false); break;
    case FT_ZACCP_J: convertZaccp_6(true); break;
    case FT_CCZCPACZCP: convertCczcpaczcp_6(false); break;
    case FT_CCZCPACZCP_J: convertCczcpaczcp_6(true); break;
    case FT_LZCPAC: convertLzcpac_6(false); break;
    case FT_LZCPAC_J: convertLzcpac_6(true); break;
    case FT_LTZCPAC: convertLtzcpac_6(false); break;
    case FT_LTZCPAC_J: convertLtzcpac_6(true); break;
    case FT_TZCPAC: f.setComplexParameterType(1, PT_IS_C); break;
    case FT_MALLARD: convertMallard_6(false); break;
    case FT_MALLARD_J: convertMallard_6(true); break;
    case FT_TMALLARD: convertTmallard_6(false); break;
    case FT_TMALLARD_J: convertTmallard_6(true); break;
    case FT_ONION_4F: f.setComplexParameterType(4, PT_IS_C); break;
    case FT_SINGLE_3F_ONION: f.setComplexParameterType(3, PT_IS_C); break;
    case FT_DOUBLE_3F_ONION_M: f.setComplexParameterType(5, PT_IS_C); break;
    case FT_DOUBLE_3F_ONION_D: f.setComplexParameterType(5, PT_IS_C); break;
    case FT_ZCPTANZ: f.setComplexParameterType(1, PT_IS_C); break;
    case FT_C2MFCZAC: f.setComplexParameterType(4, PT_IS_C); break;
    case FT_C2DFCZAC: f.setComplexParameterType(4, PT_IS_C); break;
    case FT_Z_POWER_TANCZ: f.setComplexParameterType(0, PT_IS_C); break;
    case FT_RN_MANDELBROT: f.setComplexParameterType(0, PT_IS_C); break;
    case FT_ZAZBCGD: convertZazbcgd_6(false); break;
    case FT_ZAZBCGD_J: convertZazbcgd_6(true); break;
    case FT_HYBRID: f.setComplexParameterType(4, PT_IS_C); break;
    case FT_ZDUCCPAC: f.setComplexParameterType(1, PT_IS_C); break;
    default: break;
    }
}

void Config::convertBcp_6(COMPLEX_FUNCTION_PARAMETER func, bool julia)
{
    FractalConfig& f = m_fractal_config;
    auto power = f.getComplexParameter(0);
    if (julia)
    {
        f.setComplexParameter(1, f.getComplexParameter(1), PT_NUMBER);
    }
    else
    {
        f.setComplexParameterType(1, PT_IS_C);
    }
    f.setComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(func));
    function_string += ",r=" + power.r;
    function_string += ",i=" + power.i;
    f.setComplexFunctionParameter(0, function_string);
}

void Config::convertSingleFunction_6(COMPLEX_FUNCTION_PARAMETER func, bool julia)
{
    FractalConfig &f = m_fractal_config;
    auto power = f.getComplexParameter(0);
    f.setComplexParameterType(0, (julia ? PT_NUMBER : PT_IS_C));
    f.setComplexParameter(1, StringComplex(), PT_NUMBER);
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(func));
    f.setComplexFunctionParameter(0, function_string);
}

void Config::convertSinczCoscz_6(bool julia)
{
    FractalConfig &f = m_fractal_config;
    auto p = f.getComplexParameter(0);
    if (julia)
    {
        f.setComplexParameter(0, p, PT_NUMBER);
        f.setComplexParameter(1, p, PT_NUMBER);
    }
    else
    {
        f.setComplexParameterType(0, PT_IS_C);
        f.setComplexParameterType(1, PT_IS_C);
    }
    f.setComplexParameter(2, StringComplex(), PT_NUMBER);
    std::string function_string = "pair=n,id=";
    f.setComplexFunctionParameter(0, function_string + intToString(static_cast<int>(CFP_SIN)));
    f.setComplexFunctionParameter(1, function_string + intToString(static_cast<int>(CFP_COS)));
}

void Config::convertZcpac_6(bool julia)
{
    FractalConfig& f = m_fractal_config;
    f.setComplexParameterType(0, PT_NUMBER);
    f.setComplexParameterType(1, (julia ? PT_NUMBER : PT_IS_C));
}

void Config::convertZpowerC_6()
{
    FractalConfig& f = m_fractal_config;
    f.setComplexParameter(0, StringComplex(), PT_IS_C);
    f.setComplexParameter(1, StringComplex(), PT_IS_C);
}

void Config::convertCpowerZ_6()
{
    FractalConfig& f = m_fractal_config;
    f.setComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    f.setComplexParameter(1, StringComplex("0", "0"), PT_IS_C);
}

void Config::convertCombination2_6()
{
    FractalConfig& f = m_fractal_config;
    f.setComplexParameterType(4, PT_NUMBER);
    StringComplex p[4];
    for (int i = 0; i < 4; i++)
    {
        p[i] = f.getComplexParameter(i);
    }
    for (int i = 0; i < 4; i++)
    {
        f.setComplexParameter(i+1, p[i], PT_NUMBER);
    }
    f.setComplexParameter(0, StringComplex(), PT_IS_C);
}

void Config::convertCombination3_6()
{
    FractalConfig& f = m_fractal_config;
    StringComplex p[6];
    for (int i = 0; i < 6; i++)
    {
        p[i] = f.getComplexParameter(i);
    }
    f.setComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    f.setComplexParameter(1, p[0], PT_NUMBER);
    f.setComplexParameter(2, p[1], PT_NUMBER);
    f.setComplexParameter(3, p[2], PT_NUMBER);
    f.setComplexParameter(4, StringComplex("1", "0"), PT_IS_C);
    f.setComplexParameter(5, p[3], PT_NUMBER);
    f.setComplexParameter(6, p[4], PT_NUMBER);
    f.setComplexParameter(7, p[5], PT_NUMBER);
}

void Config::convertCombination4_6()
{
    FractalConfig& f = m_fractal_config;
    StringComplex p[6];
    for (int i = 0; i < 6; i++)
    {
        p[i] = f.getComplexParameter(i);
    }
    f.setComplexParameter(0, p[0], PT_NUMBER);
    f.setComplexParameter(1, p[1], PT_NUMBER);
    f.setComplexParameter(2, StringComplex("1", "0"), PT_IS_C);
    f.setComplexParameter(3, p[2], PT_NUMBER);
    f.setComplexParameter(4, p[3], PT_NUMBER);
    f.setComplexParameter(5, p[4], PT_NUMBER);
    f.setComplexParameter(6, StringComplex("1", "0"), PT_IS_C);
    f.setComplexParameter(7, p[5], PT_NUMBER);
}

void Config::convertTzaccp_6(bool julia)
{
    FractalConfig& f = m_fractal_config;
    if (julia)
    {
        auto p = f.getComplexParameter(0);
        f.setComplexParameter(0, f.getComplexParameter(1), PT_NUMBER);
        f.setComplexParameter(1, p, PT_NUMBER);
    }
    else
    {
        f.setComplexParameterType(0, PT_IS_C);
        f.setComplexParameter(1, f.getComplexParameter(0), PT_NUMBER);
    }
}

void Config::convertZaccp_6(bool julia)
{
    FractalConfig& f = m_fractal_config;
    if (julia)
    {
        f.setComplexParameterType(0, PT_NUMBER);
    }
    else
    {
        f.setComplexParameterType(0, PT_IS_C);
        f.setComplexParameter(1, f.getComplexParameter(0),PT_NUMBER);
    }
}

void Config::convertCczcpaczcp_6(bool julia)
{
    FractalConfig& f = m_fractal_config;
    if (julia)
    {
        StringComplex p[5];
        for (int i = 0; i < 5; i++)
        {
            p[i] = f.getComplexParameter(i);
        }
        f.setComplexParameter(0, p[0], PT_NUMBER);
        f.setComplexParameter(1, p[1], PT_NUMBER);
        f.setComplexParameter(2, p[2], PT_NUMBER);
        f.setComplexParameter(3, p[3], PT_NUMBER);
        f.setComplexParameter(4, p[4], PT_NUMBER);
    }
    else
    {
        StringComplex p[4];
        for (int i = 0; i < 4; i++)
        {
            p[i] = f.getComplexParameter(i);
        }
        f.setComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
        f.setComplexParameter(1, p[0], PT_NUMBER);
        f.setComplexParameter(2, p[1], PT_NUMBER);
        f.setComplexParameter(3, p[2], PT_NUMBER);
        f.setComplexParameter(4, p[3], PT_NUMBER);
    }
}

void Config::convertLzcpac_6(bool julia)
{
    FractalConfig& f = m_fractal_config;
    f.setComplexParameterType(1, (julia ? PT_NUMBER : PT_IS_C));
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(CFP_LOG));
    f.setComplexFunctionParameter(0, function_string);
}

void Config::convertLtzcpac_6(bool julia)
{
    FractalConfig& f = m_fractal_config;
    f.setComplexParameterType(1, (julia ? PT_NUMBER : PT_IS_C));
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(CFP_LOG));
    f.setComplexFunctionParameter(0, function_string);
}

void Config::convertZazbcgd_6(bool julia)
{
    FractalConfig& f = m_fractal_config;
    if (julia)
    {
        f.setComplexParameterType(2, PT_NUMBER);
    }
    else
    {
        f.setComplexParameter(4, f.getComplexParameter(3), PT_NUMBER);
        f.setComplexParameter(3, f.getComplexParameter(2), PT_NUMBER);
        f.setComplexParameter(2, StringComplex("1", "0"), PT_IS_C);
    }
}

void Config::convertMallard_6(bool julia)
{
    FractalConfig& f = m_fractal_config;
    if (julia)
    {
        auto p = f.getComplexParameter(2);
        f.setComplexParameter(2, f.getComplexParameter(1), PT_NUMBER);
        f.setComplexParameter(1, p, PT_NUMBER);
    }
    else
    {
        f.setComplexParameter(2, f.getComplexParameter(1), PT_NUMBER);
        f.setComplexParameterType(1, PT_IS_C);
    }
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(CFP_LOG));
    f.setComplexFunctionParameter(0, function_string);
}

void Config::convertTmallard_6(bool julia)
{
    FractalConfig& f = m_fractal_config;
    if (julia)
    {
        f.setComplexParameterType(1, PT_NUMBER);
    }
    else
    {
        f.setComplexParameter(2, f.getComplexParameter(1), PT_NUMBER);
        f.setComplexParameterType(1, PT_IS_C);
    }
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(CFP_LOG));
    f.setComplexFunctionParameter(0, function_string);
}

void Config::convertCompasses_6(bool julia)
{
    FractalConfig& f = m_fractal_config;
    if (julia)
    {
        f.setComplexParameterType(1, PT_NUMBER);
    }
    else
    {
        f.setComplexParameter(2, f.getComplexParameter(1), PT_NUMBER);
        f.setComplexParameterType(1, PT_IS_C);
    }
}

void Config::convertUnnamed_6(bool julia)
{
    FractalConfig& f = m_fractal_config;
    if (julia)
    {
        StringComplex p[4];
        for (int i = 0; i < 4; i++)
        {
            p[i] = f.getComplexParameter(i);
        }
        f.setComplexParameter(0, p[0], PT_NUMBER);
        f.setComplexParameter(1, p[3], PT_NUMBER);
        f.setComplexParameter(2, p[1], PT_NUMBER);
        f.setComplexParameter(3, p[2], PT_NUMBER);
    }
    else
    {
        StringComplex p[3];
        for (int i = 0; i < 3; i++)
        {
            p[i] = f.getComplexParameter(i);
        }
        f.setComplexParameter(0, p[0], PT_NUMBER);
        f.setComplexParameter(1, StringComplex("1", "0"), PT_IS_C);
        f.setComplexParameter(2, p[1], PT_NUMBER);
        f.setComplexParameter(3, p[2], PT_NUMBER);
    }
}

void Config::convertUnnamed2_6(bool julia)
{
    FractalConfig& f = m_fractal_config;
    if (julia)
    {
        StringComplex p[6];
        for (int i = 0; i < 6; i++)
        {
            p[i] = f.getComplexParameter(i);
        }
        f.setComplexParameter(0, p[0], PT_NUMBER);
        f.setComplexParameter(1, p[5], PT_NUMBER);
        f.setComplexParameter(2, p[1], PT_NUMBER);
        f.setComplexParameter(3, p[2], PT_NUMBER);
        f.setComplexParameter(4, p[3], PT_NUMBER);
        f.setComplexParameter(5, p[4], PT_NUMBER);
    }
    else
    {
        StringComplex p[5];
        for (int i = 0; i < 5; i++)
        {
            p[i] = f.getComplexParameter(i);
        }
        f.setComplexParameter(0, p[0], PT_NUMBER);
        f.setComplexParameter(1, StringComplex("1", "0"), PT_IS_C);
        f.setComplexParameter(2, p[1], PT_NUMBER);
        f.setComplexParameter(3, p[2], PT_NUMBER);
        f.setComplexParameter(4, p[3], PT_NUMBER);
        f.setComplexParameter(5, p[4], PT_NUMBER);
    }
}

FractalConfig &Config::fractal_config()
{
    return m_fractal_config;
}