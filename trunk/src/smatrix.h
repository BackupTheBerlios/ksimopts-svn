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
#ifndef SMATRIX_H
#define SMATRIX_H

#include <complex>

#include "netlist.h"
#include "chopuplist.h"
#include "formulalist.h"

#include <qstring.h>

/**
	@author Carsten Nikiel <carsten@nikiel.de>
*/
class SMatrix{
public:
//     SMatrix();
    SMatrix(NetList &Schematic) :
     Schematic_(Schematic) {
      SMatrix_=0;
      setSchematic(Schematic);
      Z0_2=std::complex<double>(100.0,0.0);
      FormulaExists_=false;
    };

    ~SMatrix();

    int createFormula(void);

    bool fillMatrix(double Frequency);

    bool calculate(double Frequency);

    QString print(void);

    void setSchematic(NetList &Schematic);

    std::complex<double> s11(void) { return *(SMatrix_+S11_); }
    std::complex<double> s12(void) { return *(SMatrix_+S12_); }
    std::complex<double> s21(void) { return *(SMatrix_+S21_); }
    std::complex<double> s22(void) { return *(SMatrix_+S22_); }

private:
    std::complex<double> *SMatrix_;
    int MatrixDimension_;
    NetList &Schematic_;
    int Pos_;
    std::complex<double> Z0_2;
    bool FormulaExists_;
    int S11_, S12_, S21_, S22_;

    void addZ(std::complex<double>(Z));
    void addOL(bool change);
    void addINOL(bool change);
    void addSC(void);
    void addCS(std::complex<double> Z1, std::complex<double> Z2, bool first, bool second);
    void addNode(int count);

    ChopUpList ChopUp;
    FormulaList Formula;
};

#endif
