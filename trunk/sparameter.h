/***************************************************************************
 *   Copyright (C) 2004 by Carsten Nikiel                                  *
 *   arkaga@gmx.de                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SPARAMETER_H
#define SPARAMETER_H

#include <complex>
#include <qstring.h>


using namespace std;
/**
The types of s-parameters and y-parameters that will be used in the lists that get created over and over during the calculations

@author Carsten Nikiel
*/
class SParameter{
public:
    SParameter();

    SParameter(complex<double> S11, complex<double> S12,
               complex<double> S21, complex<double> S22,
               double Frequency) :
               S11_(S11), S12_(S12), S21_(S21), S22_(S22),
               Frequency_(Frequency) {
      calculateY();
    };

    ~SParameter();

    void setParameters(complex<double> S11, complex<double> S12,
                       complex<double> S21, complex<double> S22,
                       double Frequency);
    double frequency(void)    { return Frequency_; }
    complex<double> s11(void) { return S11_; }
    complex<double> s12(void) { return S12_; }
    complex<double> s21(void) { return S21_; }
    complex<double> s22(void) { return S22_; }
    complex<double> y11(void) { return Y11_; }
    complex<double> y12(void) { return Y12_; }
    complex<double> y21(void) { return Y21_; }
    complex<double> y22(void) { return Y22_; }

    QString print(void);

private:
    void calculateY(void);
    complex<double> S11_;
    complex<double> S12_;
    complex<double> S21_;
    complex<double> S22_;
    complex<double> Y11_;
    complex<double> Y12_;
    complex<double> Y21_;
    complex<double> Y22_;
    double Frequency_;
};

#endif
