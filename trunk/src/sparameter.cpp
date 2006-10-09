/***************************************************************************
 *   Copyright (C) 2006 by Carsten Nikiel   *
 *   carsten@nikiel.de   *
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

#include "sparameter.h"

#include <complex>

#include <qtextstream.h>

SParameter::SParameter()
{
}


SParameter::~SParameter()
{
}

void
SParameter::setParameters(complex<double> S11, complex<double> S12,
                   complex<double> S21, complex<double> S22,
                   double Frequency){
  S11_ = S11;
  S12_ = S12;
  S21_ = S21;
  S22_ = S22;
  Frequency_ = Frequency;
  calculateY();
}

void
SParameter::calculateY(void) {
  complex<double> S12S21 = S12_*S21_;
  complex<double> Nenner = 1.0/((1.0+S11_)*(1.0+S22_) - S12S21);

  Y11_ = ((1.0-S11_)*(1.0+S22_) + S12S21) * Nenner;
  Y12_ = -2.0 * S12_ * Nenner;
  Y21_ = -2.0 * S21_ * Nenner;
  Y22_ = ((1.0+S11_)*(1.0-S22_) + S12S21) * Nenner;
}

QString
SParameter::print(void){
 QString ReturnValue;
 QTextOStream (&ReturnValue) << frequency() << ": "
  << "S11(" << (s11()).real() << "," << (s11()).imag() << ") "
  << "S12(" << (s12()).real() << "," << (s12()).imag() << ") "
  << "S21(" << (s21()).real() << "," << (s21()).imag() << ") "
  << "S22(" << (s22()).real() << "," << (s22()).imag() << ") "
  << "\n";
 return ReturnValue;
}
