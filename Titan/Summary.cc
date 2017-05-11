//
// File:   Summary.cc
// Author: M.R.Eggleston
//
// Created on 21 September 2011, 13:36
//

#include <limits>

#include "Summary.h"
#include "KeyString.h"

boost::shared_ptr<Summary> Summary::s_instance;

Summary::Summary()
:
m_picture(nullptr)
{
    loadFormulae();
    loadColourMethods();
    loadBailoutMaps();
}

Summary::~Summary()
{
}

boost::shared_ptr<Summary> Summary::create()
{
    if (!s_instance)
    {
        s_instance = boost::shared_ptr<Summary>(new Summary());
    }
    return s_instance;
}

boost::shared_ptr<Summary> Summary::instance()
{
    return s_instance;
}

const QString &Summary::get(Picture* picture)
{
    m_picture = picture;
    m_config = picture->getFractalConfig();
    auto ft = m_config.GetFractalType();
    m_str = "Titan Version 4.2.1\n\n";
    m_str += "Formula: " + fractalTypeToString(ft) + "\n\n";
    m_str += getFormula(ft);
    parameterSummary();
    if (m_config.isLyapunov())
    {
        return lyapunovSummary();
    }
    else
    {
        return bailoutSummary();
    }
}

const QString &Summary::bailoutSummary()
{
    m_str += transforms();
    m_str += "Image centre: " + complexNumberToString(m_config.getImageCentre()) + "\n";
    m_str += "Image width: " + QString::fromStdString(m_config.getImageWidth()) + "\n";
    m_str += "Rotation about image centre: " + QString::number(m_config.getRotation()) + " degrees\n";
    if (!m_config.isOrbitPlotting())
    {
        m_str += "Maximum iterations: " + QString::number(m_config.getMaxIterations()) + "\n";
    }
    bool convergent = m_config.isConvergent();
    BAILOUT type = m_config.getBailout();
    long double limit = m_config.getLimit();
    m_str += "Bailout: " + bailout(type, convergent, limit) + "\n";
    if (m_config.isOrbitPlotting())
    {
        char method = m_config.getOrbitColourType();
        m_str += "Orbit length: " + QString::number(m_config.getMaxIterations()) + "\n";
        int omit = m_config.getStartOrbitIteration();
        if (omit > 0)
        {
            m_str += "Omit plotting first " + QString::number(omit) + " iteration" + (omit > 1 ? "s\n" : "\n");
        }
        int density = m_config.getDensity();
        if (density > 1)
        {
            m_str += "Plot density: " + QString::number(density) + "\n";
        }
        orbitPlot();
        m_str += "Colour method: ";
        if (method == 'a')
        {
            m_str += "accumulation, (the number of times an orbit visits a location)\n";
        }
        else
        {
            if (method == 'b')
            {
                m_str += "sqrt, scale = " + longdoubleToQString(m_config.getOrbitScale()) + "\n";
            }
            else if (method == 'c')
            {
                m_str += "average, interval " + QString::number(m_config.getInterval()) + "\n";
            }
            else if (method == 'd')
            {
                m_str += "logarithm, scale = " + longdoubleToQString(m_config.getOrbitScale()) + "\n";
            }
        }
    }
    else
    {
        m_str += "Colour selection: " + colourSelection() + "\n";
        m_str += "Outer colouring: " + colouringMethod(false) + "\n";
        m_str += "Inner colouring: " + colouringMethod(true) + "\n";
        m_str += orbitTrap(false);
        m_str += orbitTrap(true);
    }
    return m_str;
}

void Summary::orbitPlot()
{
    switch (m_config.getOrbitPlot())
    {
    case OP_ALL:
    default:
        m_str += "Plot all orbits";
        break;
    case OP_ESCAPED:
        m_str += "Plot escaped orbits only";
        break;
    case OP_CAPTIVE:
        m_str += "Plot captive orbits only";
        break;
    }
    m_str += "\n";
}

const QString &Summary::lyapunovSummary()
{
    m_str += "\nPrograms: saturn and titan\n\n";
    m_str += "Initial value of x is 0.5.\n";
    m_str += "A location in the image is represented by (a,b), the value of\n"
             "r is dependent on the sequence, when the sequence value is A\n"
             "r is set to a and when it is B r is set to b. The sequence is\n"
             "is executed for a number of cycles of the sequence to allow for\n"
             "behaviour to settle. When the settling cycles have been completed the\n"
             "lyapunov coefficient is calculated. For each calculation iteration\n"
             "the following expression is evaluated:\n\n"
             "log(abs(r - 2*r*x))/log(2)\n\n"
             "the values are accumulated and the total is divided by the number of\n"
             "iterations. The number of iterations is number of calculation cycles\n"
             "multiplied by the length of the sequence. The Lyapunov co-efficient\n"
             "will be either negative (stability) or positive (chaos)\n\n";
    m_str += "Sequence: " + QString::fromStdString(m_config.getLyapunovSequence()) + "\n";
    auto c = m_config.getImageCentre();
    m_str += "Image centre: a = " + QString::fromStdString(c.r) + ", b = " + QString::fromStdString(c.i) + "\n";
    m_str += "Image width: " + QString::fromStdString(m_config.getImageWidth()) + "\n";
    m_str += "Rotation about image centre: " + QString::number(m_config.getRotation()) + " degrees\n";
    bool negative_multi = (m_config.getMethod(false)[0] == 'v');
    bool positive_multi = (m_config.getMethod(true)[0] == 'v');
    m_str += "Negative coefficient colouring: " + QString(negative_multi ? "multi-colour" : "single colour") + "\n";
    m_str += "Positive coefficient colouring: " + QString(positive_multi ? "multi-colour" : "single colour") + "\n";
    m_str += "\n";
    m_str += "Settling cycles: " + QString::number(m_config.getSettlingCycles()) + "\n";
    m_str += "Calculating cycles: " + QString::number(m_config.getCalculatingCycles()) + "\n";
    return m_str;
}


QString Summary::getFormula(FRACTAL_TYPE ft)
{
    bool exists = (m_formulae.count(ft) != 0);
    QString formula = (exists ? m_formulae[ft] : "To be defined\n\n");
    return formula;
}

void Summary::loadFormulae()
{
    m_formulae[F_MANDELBROT] = "z = transform(z)\n"
                               "z = z^2 + alpha\n\n";
    m_formulae[F_QUADRATIC] = "z = transform(z)\n"
                              "z = alpha*z^2 + beta*z + gamma\n\n";
    m_formulae[F_CUBIC] = "z = transform(z)\n"
                           "z = alpha*z^3 + beta*z^2 + gamma*z + delta\n\n";
    m_formulae[F_ALMOST_CUBIC] = "z = transform(z)\n"
                                 "z = alpha*z^3 + beta*z^2 + gamma*z + delta\n"
                                 "Note: There is an error in the calculation of the imaginary part\n\n";
    m_formulae[F_SINGLE_FUNCTION] = "z = transform(z)\n"
                                    "z = F1(alpha*z) + beta\n\n";
    m_formulae[F_C_POWER_Z] = "z = transform(z)\n"
                              "z = alpha^z + beta\n\n";
    m_formulae[F_2F_PRODUCT] = "z = transform(z)\n"
                               "z = F1(alpha*z)*F2(beta*z) + gamma\n\n";
    m_formulae[F_UNNAMED] =  "z = transform(z)\n"
                             "z = ((z^alpha + beta)^gamma)/(z(z^alpha - beta)^delta)\n\n";
    m_formulae[F_Z_POWER_TANCZ_AC] = "z = transform(z)\n"
                                     "z = z^tan(alpha*z) + beta\n\n";
    m_formulae[F_COMBINATION] = "z = transform(z)\n"
                                "z = alpha*z^beta + gamma*z^delta + epsilon\n\n";
    m_formulae[F_TZACCP] = "z = (transform(z + alpha))^beta\n\n";
    m_formulae[F_BIOMORPH_1] = "z = transform(z)\n"
                               "z = z^alpha + z^z + beta\n\n";
    m_formulae[F_BIOMORPH_2] = "z = transform(z)\n"
                               "z = sin(z) + z^alpha + beta\n\n";
    m_formulae[F_BIOMORPH_3] = "z = transform(z)\n"
                               "z = e^z + z^alpha + beta\n\n";
    m_formulae[F_BIOMORPH_4] = "z = transform(z)\n"
                               "z = sin(z) + e^z + alpha\n\n";
    m_formulae[F_BIOMORPH_5] = "z = transform(z)\n"
                               "z = sinh(z) + alpha\n\n";
    m_formulae[F_MAGNET] = "z = transform(z)\n"
                           "z = ((z^2 + alpha - 1)/(2z + alpha - 2))^2\n\n";
    m_formulae[F_MAGNET_2] = "z = transform(z)\n"
                             "q = z^3 + 3(alpha - 1)z + (alpha -1 )(alpha - 2)\n"
                             "d = 3z^2 + 3(alpha - 2)z + alpha^2 - 3alpha + 3\n"
                             "z = (q/d)^2";
    m_formulae[F_ZAZBCGD] = "z = transform(z)\n"
                            "z = (z^alpha + (z^beta)(c^gamma))^delta\n\n";
    m_formulae[F_COMBINATION_2] = "z = transform(z)\n"
                                  "z = alpha*beta*z^gamma + delta*z^epsilon\n\n";
    m_formulae[F_NOVA] = "z = transform(z)\n"
                         "z = z - alpha*(f(z)/f'(z)) + gamma\n"
                         "f(z) = z^beta - 1\n\n";
    m_formulae[F_NOVA_1] = "z = transform(z)\n"
                           "z = z - alpha(f(z)/f'(z)) + zeta\n"
                           "f(z) = beta*z^gamma - delta*z^epsilon - 1\n\n";
    m_formulae[F_NOVA_2] = "z = transform(z)\n"
                            "z = z - alpha(f(z)/f'(z)) + delta\n"
                            "f(z) = z^beta - (delta-1)z^gamma - delta\n\n";
    m_formulae[F_UNNAMED_2] = "z = transform(z)\n"
                              "z = ((z^alpha + beta)^gamma)/((z^delta)(z^epsilon - beta)^zeta)\n\n";
    m_formulae[F_QUARTIC] = "z = transform(z)\n"
                             "z = alpha*z^4 + beta*z^3 + gamma*z^2 + delta*z + epsilon\n\n";
    m_formulae[F_QUINTIC] = "z = transform(z)\n"
                             "z = alpha*z^5 + beta*z^4 + gamma*z^3 + delta*z^2 + epsilon*z + zeta\n\n";
    m_formulae[F_ZCPTANZ] = "z = transform(z)\n"
                             "z = (z^alpha)tan(z) + beta\n\n";
    m_formulae[F_LYAPUNOV] = "x = r*x*(1 - x)\n\n";
    m_formulae[F_COMPASSES] = "z = transform(z)\n"
                              "z = z^alpha - alpha*(beta^(alpha - 1))z + gamma\n\n";
    m_formulae[F_RN_MANDELBROT] = "z = transform(z)\n"
                                   "z.r = z.r^2 + alpha.r\n"
                                   "z.i = z.i^2 + alpha.i\n"
                                   ".r is the real component\n"
                                   ".i is the imaginary component\n\n";
    m_formulae[F_PICKOVER_POPCORN_4F] = "z = transform(z)\n"
                                        "z.r = z.r - A*f1(z.i + f2(B*z.i)) + alpha.r\n"
                                        "z.i = z.i - C*f3(z.r + f4(D*z.r)) + alpha.i\n"
                                        ".r is the real component\n"
                                        ".i is the imaginary component\n\n";
    m_formulae[F_HYBRID] = "n = norm(z)\n"
                            "z = transform(z)\n"
                            "z = alpha*(z.r/n)^beta + gamma*(z.i/n)^delta + epsilon\n\n";
    m_formulae[F_ZDUCCPAC] = "z = transform(z)\n"
                              "z = (z/unsign(beta))^alpha + beta\n\n";
    m_formulae[F_MALLARD] = "z = transform(z)\n"
                            "z = (F1(z^alpha + beta))^gamma\n\n";
    m_formulae[F_ZCPAC] = "z = transform(z)\n"
                           "z = z^alpha + beta\n\n";
    m_formulae[F_PICKOVER_POPCORN_6F] = "z = transform(z)\n"
                                        "z.r = z.r - A*f1(z.i + f2(B*(z.i + f3(C*z.i)))) + alpha.r\n"
                                        "z.i = z.i - D*f4(z.r + f5(E*(z.r + f6(F*z.r)))) + alpha.i\n"
                                        ".r is the real component\n"
                                        ".i is the imaginary component\n\n";
    m_formulae[F_TZCPAC] = "z = transform(z^alpha) + beta\n\n";
    m_formulae[F_TMALLARD] = "z = (F1(transform(z^alpha) + beta))^gamma\n\n";
    m_formulae[F_FZCPAC] = "z = transform(z)\n"
                            "z = F1(z^alpha + beta)\n\n";
    m_formulae[F_FTZCPAC] =  "z = F1(transform(z^alpha) + beta)\n\n";
    m_formulae[F_ZACCP] = "z = transform(z)\n"
                          "z = (z + alpha)^beta)\n\n";
    m_formulae[F_CCZCPACZCP] = "z = transform(z)\n"
                               "z = alpha*(beta*(z^gamma) + delta*(z^epsilon))\n\n";
    m_formulae[F_ONION_4F] = "z = transform(z)\n"
                             "z = F1(a) + epsilon\n"
                             "a = (alpha*z)/F2(b)\n"
                             "b = (beta*z)/F3(c)\n"
                             "c = (gamma*z)/F4(δz)\n\n";
//    F_ZPFCZ_AC, -> not implemented !
    m_formulae[F_SQRT_CP] = "z = transform(z)\n"
                            "sqrt(z^alpha) + beta\n\n";
    m_formulae[F_COMBINATION_3] = "z = transform(z)\n"
                                  "z = (alpha*z^beta + gamma)^delta + (epsilon*z^zeta + eta)^theta\n\n";
    m_formulae[F_SINGLE_3F_ONION] = "z = transform(z)\n"
                                    "alpha*F1(F2(F3(beta*z + gamma))) + delta\n" ;
    m_formulae[F_DOUBLE_3F_ONION_M] = "z = transform(z)\n"
                                      "alpha*F1(F2(F3(beta*z + gamma)))*F4(F5(F6(delta*z + epsilon))) + zeta\n\n";
    m_formulae[F_DOUBLE_3F_ONION_D] = "z = transform(z)\n"
                                      "alpha*F1(F2(F3(beta*z + gamma)))/F4(F5(F6(delta*z + epsilon))) + zeta\n\n";
    m_formulae[F_C2MFCZAC] = "z = transform(z)\n"
                             "z = alpha*F1(beta*z + gamma)*F2(delta*z + epsilon)\n\n";
    m_formulae[F_C2DFCZAC] = "z = transform(z)\n"
                             "z = alpha*F1(beta*z + gamma)/F2(delta*z + epsilon)\n\n";
    m_formulae[F_M3] = "z = transform(z)\n"
                       "z = z^3 + alpha\n\n";
    m_formulae[F_M4] = "z = transform(z)\n"
                       "z = z^4 + alpha\n\n";
    m_formulae[F_M5] = "z = transform(z)\n"
                       "z = z^5 + alpha\n\n";
    m_formulae[F_M6] = "z = transform(z)\n"
                       "z = z^6 + alpha\n\n";
    m_formulae[F_M7] = "z = transform(z)\n"
                       "z = z^7 + alpha\n\n";
    m_formulae[F_M8] = "z = transform(z)\n"
                       "z = z^8 + alpha\n\n";
    m_formulae[F_M9] =
              "z = transform(z)\n"
              "z = z^9 + alpha\n\n";
    m_formulae[F_M10] =
              "z = transform(z)\n"
              "z = z^9 + alpha\n\n";
    m_formulae[F_ATTRACTORS] =
              "z = transform(z)\n"
              "x = z.r\n"
              "y = z.i\n"
              "a = Af1(By) + Cf2(Dx)\n"
              "b = Ef3(Fx) + Gf4(Hy)\n"
              "z = a +bi + alpha\n\n";
    m_formulae[F_GENERAL_MIXTURE] =
              "z = transform(z)\n"
              "z = (alpha(beta*z^gamma + delta*z^epsilon) + zeta)^eta\n\n";
    m_formulae[F_MIXTURE] =
              "z = transform(z)\n"
              "z = (alpha(2z - z^2) + beta)^2\n\n";
    m_formulae[F_MIXTURE_2] =
              "<b><big>z = transform(z)</big></b><br>"
              "z = (alpha(z - z^2) + beta)^3\n\n";
    m_formulae[F_MIXTURE_3] =
              "z = transform(z)"
              "z = (alpha(z - z^2) + beta)^4\n\n";
    m_formulae[F_MIXTURE_4] =
              "z = transform(z)\n"
              "z = (alpha(z^3 - z^4) + beta)^5\n\n";
    m_formulae[F_PR_MANDELBROT_2] =
              "z = transform(z)\n"
              "a = z^2 + alpha\n"
              "b = z^2 + beta\n"
              "z = ((a + gamma)^-1 + (b + delta)^-1)^-1\n\n";
    m_formulae[F_PR_MANDELBROT_3] =
              "z = transform(z)\n"
              "a = z^2 + alpha\n"
              "b = z^2 + beta\n"
              "c = z^2 + gamma\n"
              "z = ((a + delta)^-1 + (b + epsilon)^-1 + (c + zeta)^-1)^-1\n\n";
    m_formulae[F_PR_SINGLE_FUNCTION_2] =
              "z = transform(z)\n"
              "a = F1(alpha*z) + beta\n"
              "b = F2(gamma*z) + delta\n"
              "z = ((a + epsilon)^-1 + (b + zeta)^-1)^-1\n\n";
    m_formulae[F_HOP] =
              "z = transform(z)\n"
              "x = z.r\n"
              "y = z.i\n"
              "a = y + B*signum(x)*f1(abs(C*x^D + E))\n"
              "b = A - x\n"
              "z = a + bi + alpha\n\n";
    m_formulae[F_QUADRUP_2] =
              "z = transform(z)\n"
              "x = z.r\n"
              "y = z.i\n"
              "p = log(abs(Bx - C)\n"
              "q = log(abs(Cx - B)\n"
              "a = y + B*signum(x)*sin(p)*atan(q^2)\n"
              "b = A - x\n"
              "z = a + bi + alpha\n\n"
              "Note: log is logarithm to base e\n\n";
    m_formulae[F_THREEPLY] =
              "z = transform(z)\n"
              "x = z.r\n"
              "y = z.i\n"
              "a = y - signum(x)*abs(sin(x)*cos(B) + C - x*sin(A + B + C))\n"
              "b = A - x\n"
              "z = a + bi + alpha\n\n";
    m_formulae[F_THREEPLY_2] =
              "z = transform(z)\n"
              "x = z.r\n"
              "y = z.i\n"
              "a = y - signum(x)*abs(sin(x)*cos(B) + C + x*sin(A + B + C))\n"
              "b = A - x\n"
              "z = a + bi + alpha\n\n";
    m_formulae[F_GUMOWSKI_MIRA] = "z = transform(z)\n"
                                  "x = z.r\n"
                                  "y = z.i\n"
                                  "a = By + (2(1 - A)x^2)/(1 + x^2)\n\n"
                                  "b = Cx + (2(1 - A)x^2)/(1 + x^2)\n\n"
                                  "z = a + bi + alpha\n\n";
    m_formulae[F_CHIP] = "z = transform(z)\n"
                         "x = z.r\n"
                         "y = z.i\n"
                         "p = loge(abs(Bx - C))\n"
                         "q = loge(abs(Cx - B))\n"
                         "a = y - signum(x)*cos(p^2)*atan(q^2)\n"
                         "b = A - x\n"
                         "z = a + bi + alpha\n\n";
    m_formulae[F_HEXIC] =
              "z = transform(z)\n"
              "z = alpha*z^6 + beta*z^5 + gamma*z^4 + delta*z^3 + "
              "epsilon*z^2 + zeta*z + eta\n\n";
    m_formulae[F_HEPTIC] =
              "z = transform(z)\n"
              "z = alpha*z^7 + beta*z^6 + gamma*z^5 + delta*z^4 + "
              "epsilon*z^3 + zeta*z^2 + eta*z + theta\n\n";
    m_formulae[F_MANDELBROT_DIVISION] =
              "z = transform(z)\n"
              "z = (z^alpha + beta)/(z^gamma + delta) + epsilon + zeta\n\n";
    m_formulae[F_OCTIC] = 
              "z = transform(z)\n"
              "z = alpha*z^8 + beta*z^7 + gamma*z^6 + delta*z^5 + "
              "epsilon*z^4 + zeta*z^3 + eta*z^2 + theta*z + iota\n\n";
}

void Summary::loadColourMethods()
{
    m_colour_method['i'] = "iteration";
    m_colour_method['f'] = "fixed colour";
    m_colour_method['a'] = "final angle";
    m_colour_method['m'] = "final magnitude";
    m_colour_method['A'] = "angle";
    m_colour_method['M'] = "magnitude";
    m_colour_method['g'] = "gaussian integer";
    m_colour_method['r'] = "ratio";
    m_colour_method['t'] = "distance to orbit trap";
    //
    m_gaussian_type['r'] = "(round)";
    m_gaussian_type['c'] = "(ceiling)";
    m_gaussian_type['f'] = "(floor)";
    m_gaussian_type['t'] = "(truncate)";
    //
    m_gaussian_statistic['a'] = "minimum distance to";
    m_gaussian_statistic['b'] = "iteration at minimum distance to";
    m_gaussian_statistic['c'] = "angle at minimum distance to";
    m_gaussian_statistic['d'] = "maximum distance to";
    m_gaussian_statistic['e'] = "iteration at maximum distance to";
    m_gaussian_statistic['f'] = "angle at maximum distance to";
    m_gaussian_statistic['g'] = "average distance to";
    m_gaussian_statistic['h'] = "minimum angle to";
    m_gaussian_statistic['i'] = "average angle to";
    m_gaussian_statistic['j'] = "maximum angle to";
    m_gaussian_statistic['k'] = "maximum/minimum ratio of distance to";
    m_gaussian_statistic['l'] = "range of distance to ";
    m_gaussian_statistic['m'] = "variance of distance to";
    m_gaussian_statistic['n'] = "standard deviation of distance to";
    m_gaussian_statistic['o'] = "coefficient of variation of distance to";
    //
    m_statistics_type['a'] = "minimum";
    m_statistics_type['b'] = "iteration at minimum";
    m_statistics_type['c'] = "maximum";
    m_statistics_type['d'] = "iteration at maximum";
    m_statistics_type['e'] = "range of";
    m_statistics_type['f'] = "average";
    m_statistics_type['g'] = "variance of";
    m_statistics_type['h'] = "standard deviation of";
    m_statistics_type['i'] = "coefficient of variation of";
    m_statistics_type['j'] = "fractal dimension of";
    m_statistics_type['k'] = "exponential sum of";
    m_statistics_type['l'] = "exponential inverse change sum of";
    //
    m_final_magnitude_option['n'] = "norm(z)";
    m_final_magnitude_option['s'] = "smaller of real(z) & imag(z)";
    m_final_magnitude_option['g'] = "greater of real(z) & imag(z)";
    m_final_magnitude_option['r'] = "real(z)";
    m_final_magnitude_option['R'] = "abs(real(z))";
    m_final_magnitude_option['i'] = "imag(z)";
    m_final_magnitude_option['I'] = "abs(imag(z))";
    m_final_magnitude_option['c'] = "real(z) + imag(z)";
    m_final_magnitude_option['C'] = "abs(real(z) + imag(z))";
    m_final_magnitude_option['p'] = "real(z)*imag(z)";
    m_final_magnitude_option['P'] = "abs(real(z)*imag(z))";
    //
    m_ratio_part['a'] = "smaller(real(z), imag(z))";
    m_ratio_part['b'] = "larger(real(z), imag(z))";
    m_ratio_part['c'] = "abs(real(z))";
    m_ratio_part['d'] = "abs(imag(z))";
    m_ratio_part['e'] = "abs(real(z) + imag(z))";
    m_ratio_part['f'] = "abs(real(z) - imag(z))";
    m_ratio_part['g'] = "abs(real(z)) + abs(imag(z))";
    m_ratio_part['h'] = "abs(abs(real(z)) - abs(imag)))";
    m_ratio_part['i'] = "abs(real(z)*imag(z))";
    m_ratio_part['j'] = "abs(z)";
    m_ratio_part['k'] = "norm(z)";
    //
    m_trap_name['a'] = "Point";
    m_trap_name['b'] = "4 Points";
    m_trap_name['c'] = "Line";
    m_trap_name['d'] = "Cross";
    m_trap_name['e'] = "Square";
    //m_trap_name['f'] = "Grid";
    //m_trap_name['g'] = "Mesh";
    m_trap_name['h'] = "Circle";
    m_trap_name['i'] = "Triangle";
    m_trap_name['j'] = "Triform";
    m_trap_name['k'] = "Asterisk";
    m_trap_name['l'] = "Circle Line";
    m_trap_name['m'] = "Circle Cross";
    m_trap_name['n'] = "Circle Triform";
    m_trap_name['o'] = "Two Quarter Circles";
    m_trap_name['p'] = "Circle Triangle";
    m_trap_name['q'] = "Triangle Circle";
    m_trap_name['r'] = "Circle Square";
    m_trap_name['s'] = "Square Circle";
    m_trap_name['t'] = "Octothorpe";
    m_trap_name['u'] = "Running Track";
    m_trap_name['v'] = "Pinch";
    m_trap_name['w'] = "Steiner Chain";
}

void Summary::loadBailoutMaps()
{
    m_gt_bailout[B_NONE] = "No Bailout";
    m_gt_bailout[B_ABS] = "abs(z)";
    m_gt_bailout[B_NORM] = "norm(z)";
    m_gt_bailout[B_IMAG] = "imag(z)";
    m_gt_bailout[B_IMAG_SQUARED] = "(imag(z))^2";
    m_gt_bailout[B_REAL] = "real(z)";
    m_gt_bailout[B_REAL_SQUARED] = "(real(z))^2";
    m_gt_bailout[B_ABS_PRODUCT] = "abs(real(z)*imag(z))";
    m_gt_bailout[B_MANHATTAN] = "abs(real(z)) + abs(imag(z))";
    m_gt_bailout[B_MANHATTANISH] = "real(z) + imag(z)";
    m_gt_bailout[B_ABS_MANHATTANISH] = "abs(real(z) + image(z))";
    m_gt_bailout[B_MAX_SQUARED] = "(max(real(z), imag(z)))^2";
    m_gt_bailout[B_MIN_SQUARED] = "(min(real(z), imag(z)))^2";
    m_gt_bailout[B_ABS_DIFF] = "abs(real(z) - imag(z))";
    m_lt_bailout[B_NONE] = "No Bailout";
    m_lt_bailout[B_ABS] = "abs(Δz)";
    m_lt_bailout[B_NORM] = "norm(Δz)";
    m_lt_bailout[B_IMAG] = "imag(Δz)";
    m_lt_bailout[B_IMAG_SQUARED] = "(imag(Δz))^2";
    m_lt_bailout[B_REAL] = "real(Δz)";
    m_lt_bailout[B_REAL_SQUARED] = "(real(Δz))^2";
    m_lt_bailout[B_ABS_PRODUCT] = "abs(real(Δz)*imag(Δz))";
    m_lt_bailout[B_MANHATTAN] = "abs(real(Δz)) + abs(imag(Δz))";
    m_lt_bailout[B_MANHATTANISH] = "real(Δz) + imag(Δz)";
    m_lt_bailout[B_ABS_MANHATTANISH] = "abs(real(Δz) + image(Δz))";
    m_lt_bailout[B_MAX_SQUARED] = "(max(real(Δz), imag(Δz)))^2";
    m_lt_bailout[B_MIN_SQUARED] = "(min(real(Δz), imag(Δz)))^2";
    m_lt_bailout[B_ABS_DIFF] = "abs(real(Δz) - imag(Δz))";
}

QString Summary::bailout(BAILOUT type, bool convergent, long double limit)
{
    BailoutMap &map = (convergent ? m_lt_bailout : m_gt_bailout);
    bool exists = (map.count(type) != 0);
    QString str("unknown");
    if (exists)
    {
        str = map[type];
        if (type != B_NONE)
        {
            str += (convergent ? " < " : " > ");
            str += longdoubleToQString(limit);
        }
    }
    return str;
}

QString Summary::transforms()
{
    QString str;
    int size = m_config.getNumberOfComplexPlaneTransforms();
    if (size > 0)
    {
        str += "Complex Plane Transforms\n";
        for (int i = 0; i < size; i++)
        {
            auto t = m_config.getComplexPlaneTransform(i);
            str += "  " + complexFunctionToString(t) + "\n";
        }
        str += "\n";
    }
    if (m_config.transformsDefined())
    {
        str += "Transform sequence: " + QString::fromStdString(m_config.getTransformSequence()) + "\n";
        int sets = m_config.getNumberOfTransformSets();
        for (int i = 0; i < sets; i++)
        {
            str += "Transforms " + QString(QChar(static_cast<char>('A' + i))) + "\n";
            int size = m_config.getNumberOfTransforms(i);
            for (int j = 0; j < size; j++)
            {
                auto t = m_config.getTransform(i, j);
                str += "  " + complexFunctionToString(t) + "\n";
            }
        }
        str += "\n";
    }
    return str;
}

QString  Summary::initialZ()
{
    QString str("z0 = ");
    INITIAL_VALUE type = m_config.getInitialZtype();
    if (type == FIXED)
    {
        str += complexNumberToString(m_config.getInitalZ());
    }
    else
    {
        str += "location in the complex plane";
        if (type == UNTRANSFORMED)
        {
            str += ", ignore transforms";
        }
    }
    return str + "\n";
};


QString Summary::colourSelection()
{
    QString str;
    std::string selection = m_config.getSelection();
    long double limit = m_config.getSelectLimit();
    BAILOUT bailout = m_config.getBailout();
    if (bailout == B_NONE)
    {
        str += "all points are inner";
    }
    else if (selection[0] == 'n')
    {
        str += "outer for bailout otherwise inner";
    }
    else if (selection.length() == 5)
    {
        str += "(";
        str += (selection[0] == 'a' ? "abs(real(z))" : "real(z)");
        str += " " + QString::fromStdString(selection.substr(2,1)) + " ";
        str += longdoubleToQString(limit);
        str += ") ";
        if (selection[4] == 'a')
        {
            str += "AND";
        }
        else if (selection[3] == 'o')
        {
            str += "OR";
        }
        else
        {
            str += "XOR";
        }
        str += " (";
        str += (selection[1] == 'a' ? "abs(imag(z))" : "imag(z)");
        str += " " + QString::fromStdString(selection.substr(3,1)) + " ";
        str += longdoubleToQString(limit);
        str += ") ";
        str += " for outer";
    }
    else
    {
        str += "unknown";
    }
    return str;
}

QString Summary::colouringMethod(bool inner)
{
    QString str;
    std::string method_str = m_config.getMethod(inner);
    char method = method_str[0];
    QString method_name = methodName(method);
    if (method == 'f')
    {
        str += m_colour_method[method];
    }
    else if (method == 'i')
    {
        if (m_config.isSmooth(inner))
        {
            str += "continuous potential";
        }
        else
        {
            str += method_name;
            unsigned int red_offset = m_config.getRedOffset(inner);
            unsigned int green_offset = m_config.getGreenOffset(inner);
            unsigned int blue_offset = m_config.getBlueOffset(inner);
            if (red_offset > 0)
            {
                str += ", red offset = " + QString::number(red_offset);
            }
            if (green_offset > 0)
            {
                str += ", green offset = " + QString::number(green_offset);
            }
            if (blue_offset > 0)
            {
                str += ", blue offset = " + QString::number(blue_offset);
            }
        }
    }
    else
    {
        if (m_config.isAbsLog(inner))
        {
            str += "absolute log of ";
        }
        if (method == 'a')
        {
            str += method_name;
            str += ", scale = " + longdoubleToQString(m_config.getScale(inner));
        }
        else if (method == 'm')
        {
            char option = method_str[1];
            str += method_name + ", " + finalMagnitudeOptionName(option);
            str += ", scale = " + longdoubleToQString(m_config.getScale(inner));
        }
        else if (method == 'A')
        {
            str += statistics(method_str[1]) + " ";
            if (method_str[1] < 'a') str += "change in ";
            str += method_name;
            if ((method_str[1] != 'b') && (method_str[1] !='d') &&
                (method_str[1] != 'B') && (method_str[1] !='D'))
            {
                str += ", scale = " + longdoubleToQString(m_config.getScale(inner));
            }
        }
        else if (method == 'M')
        {
            str += statistics(method_str[1]) + " ";
            if (method_str[1] < 'a') str += "change in ";
            str += method_name;
            if ((method_str[1] != 'b') && (method_str[1] !='d') &&
                (method_str[1] != 'B') && (method_str[1] !='D'))
            {
                str += ", scale = " + longdoubleToQString(m_config.getScale(inner));
            }
        }
        else if (method == 'g')
        {
            str += gaussianStatistic(method_str[2]) + " ";
            str += method_name + " " + gaussianType(method_str[1]);
            if ((method_str[2] != 'b') && (method_str[2] !='e') &&
               (method_str[2] != 'B') && (method_str[2] !='E'))
            {
                str += ", scale = " + longdoubleToQString(m_config.getScale(inner));
            }
        }
        else if (method == 't')
        {
            str += statistics(method_str[2]) + " ";
            if (method_str[2] < 'a') str += "change in ";
            str += method_name;
            if ((method_str[2] != 'b') && (method_str[2] !='d') &&
                (method_str[2] != 'B') && (method_str[2] !='D'))
            {
                str += ", scale = " + longdoubleToQString(m_config.getScale(inner));
            }
        }
        else if (method == 'r')
        {
            str += statistics(method_str[3]) + " ";
            if (method_str[3] < 'a') str += "change in ";
            str += method_name + ", ";
            str += ratio(method_str[1], method_str[2]);
            if ((method_str[3] != 'b') && (method_str[3] !='d') &&
                (method_str[3] != 'B') && (method_str[3] !='D'))
            {
                str += ", scale = " + longdoubleToQString(m_config.getScale(inner));
            }
        }
        unsigned int red_offset = m_config.getRedOffset(inner);
        unsigned int green_offset = m_config.getGreenOffset(inner);
        unsigned int blue_offset = m_config.getBlueOffset(inner);
        if (red_offset > 0)
        {
            str += ", red offset = " + QString::number(red_offset);
        }
        if (green_offset > 0)
        {
            str += ", green offset = " + QString::number(green_offset);
        }
        if (blue_offset > 0)
        {
            str += ", blue offset = " + QString::number(blue_offset);
        }
    }
    return str;
}

QString Summary::methodName(char value)
{
    QString str;
    if (m_colour_method.count(value) != 0)
    {
        str = m_colour_method[value];
    }
    return str;
}

QString Summary::finalMagnitudeOptionName(char value)
{
    QString str;
    if (m_final_magnitude_option.count(value) != 0)
    {
        str = m_final_magnitude_option[value];
    }
    return str;
}

QString Summary::statistics(char value)
{
    if (value < 'a') value = value - 'A' + 'a';
    QString str;
    if (m_statistics_type.count(value) != 0)
    {
        str = m_statistics_type[value];
    }
    return str;
}

QString Summary::gaussianType(char value)
{
    QString str;
    if (m_gaussian_type.count(value) != 0)
    {
        str = m_gaussian_type[value];
    }
    return str;
}

QString Summary::ratio(char q, char d)
{
    QString str;
    if ((m_ratio_part.count(q) != 0) && (m_ratio_part.count(d) != 0))
    {
        str += m_ratio_part[q] + " divided by " + m_ratio_part[d];
    }
    return str;
}

QString Summary::gaussianStatistic(char value)
{
    QString str;
    if (m_gaussian_statistic.count(value) != 0)
    {
        str = m_gaussian_statistic[value];
    }
    return str;
}

QString Summary::orbitTrap(bool inner)
{
    QString str;
    if (m_config.isOrbitTrap(inner))
    {
        std::string method_str = m_config.getMethod(inner);
        KeyString keys(method_str.substr(4));
        str += "\n";
        str += QString(inner ? "Inner Orbit Trap" : "Outer Orbit Trap") + "\n\n";
        str += "Name: " + trapName(method_str[1]) + "\n";
        StringComplex centre(keys.GetKey("r", "0"), keys.GetKey("i", "0"));
        str += "Position: " + complexNumberToString(centre) + "\n";
        OrbitTrap::TRAP_TYPE type = static_cast<OrbitTrap::TRAP_TYPE>(method_str[1] - 'a');
        auto trap = OrbitTrap::getTrap(type, inner);
        if (trap->hasSize())
        {
            str += "Size: " + QString::fromStdString(keys.GetKey("width", "0")) + "\n";
        }
        if (trap->hasRotation())
        {
            str += "Rotation: " + QString::fromStdString(keys.GetKey("rot", "0")) + "\n";
        }
        if (trap->hasCentrePoint())
        {
            str += "Centre Point: " + QString::fromStdString(keys.GetKey("cp", "0") == "1" ? "yes" : "no") + "\n";
        }
        if (type == OrbitTrap::STEINER_CHAIN)
        {
            str += "\nChain Construction:\n\n";
            str += "Number of chain circles: " + QString::fromStdString(keys.GetKey("n", "0")) + "\n";
            str += "Inversion distance: " + QString::fromStdString(keys.GetKey("invd", "0")) + "\n";
            str += "Outer Circle: " + QString(keys.GetKey("outer", "0") == "1" ? "yes" : "no") + "\n";
            str += "Inner Circle: " + QString(keys.GetKey("inner", "0") == "1" ? "yes" : "no") + "\n";
            str += "Chain Circle Triangles: " + QString(keys.GetKey("triangles", "0") == "1" ? "yes" : "no") + "\n";
            str += "Chain Circle Centre Point: " + QString(keys.GetKey("cccp", "0") == "1" ? "yes" : "no") + "\n";
        }
    }
    return str;
}

QString Summary::trapName(char value)
{
    QString str;
    if (m_trap_name.count(value) != 0)
    {
        str = m_trap_name[value];
    }
    return str;
}

void Summary::parameterSummary()
{
    int size = m_config.getNumberOfComplexParameters();
    bool blank_line = false;
    m_str += initialZ();
    if (size > 0) parameter("alpha", 0);
    if (size > 1) parameter("beta", 1);
    if (size > 2) parameter("gamma", 2);
    if (size > 3) parameter("delta", 3);
    if (size > 4) parameter("epsilon", 4);
    if (size > 5) parameter("zeta", 5);
    if (size > 6) parameter("eta", 6);
    if (size > 7) parameter("theta", 7);
    if (size > 8) parameter("iota", 8);
    blank_line = blank_line || (size > 0);
    size = m_config.getNumberOfParameters();
    for (int i = 0; i < size; i++)
    {
        m_str += QString(QChar(static_cast<char>('A' + i))) + " = " + QString::fromStdString(m_config.getParameter(i)) + "\n";
    }
    blank_line = blank_line || (size > 0);
    size = m_config.getNumberOfFunctionParameters();
    for (int i = 0; i < size; i++)
    {
        m_str += "f" + QString::number(i+1) + " = " + functionToString(m_config.getFunctionParameter(i)) + "\n";
    }
    blank_line = blank_line || (size > 0);
    size = m_config.getNumberOfComplexFunctionParameters();
    for (int i = 0; i < size; i++)
    {
        m_str += "F" + QString::number(i+1) + " = " + complexFunctionToString(m_config.getComplexFunctionParameter(i)) + "\n";
    }
    blank_line = blank_line || (size > 0);
    if (blank_line) m_str += "\n";
}

void Summary::parameter(const QString& name, int index)
{
    m_str += name;
    m_str += " = ";
    auto type = m_config.getComplexParameterType(index);
    if (type == PT_NUMBER)
    {
        m_str += complexNumberToString(m_config.getComplexParameter(index)) + "\n";
    }
    else
    {
        if (type == PT_IS_NEG_C)
        {
            m_str += "negative ";
        }
        m_str += "location in the complex plane\n";
    }
}
