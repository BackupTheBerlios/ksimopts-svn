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
#ifndef FORMULAELEMENT_H
#define FORMULAELEMENT_H

/**
	@author Carsten Nikiel <carsten@nikiel.de>
*/
class FormulaElement{
public:
    FormulaElement();

    FormulaElement(int Formula, int A, int B, int C, int D):
      Formula_(Formula), A_(A), B_(B), C_(C), D_(D) {}

    int a(void) { return A_; }
    int b(void) { return B_; }
    int c(void) { return C_; }
    int d(void) { return D_; }
    int formula(void) { return Formula_; }

    ~FormulaElement();

private:
    int Formula_;
    int A_;
    int B_;
    int C_;
    int D_;

};

#endif
