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
#include "finalcost.h"

FinalCost::~FinalCost()
{
}

double
FinalCost::calculate(SParameterList &Calc) {
 QValueList<SParameter>::Iterator it_orig;
 QValueList<SParameter>::Iterator it_calc;
 double Cost=0.0;

 for ( it_orig = Original_.List.begin(), it_calc = Calc.List.begin();
       it_orig != Original_.List.end(); ++it_orig, ++it_calc ){
   double tmps11 = abs(pow(((*it_orig).s11()-(*it_calc).s11())/(*it_orig).s11(),2));
   double tmps12 = abs(pow(((*it_orig).s12()-(*it_calc).s12())/(*it_orig).s12(),2));
   double tmps21 = abs(pow(((*it_orig).s21()-(*it_calc).s21())/(*it_orig).s21(),2));
   double tmps22 = abs(pow(((*it_orig).s22()-(*it_calc).s22())/(*it_orig).s22(),2));
   Cost += tmps11 + tmps12 + tmps21 + tmps22;
 }
 return Cost/Original_.List.count();
}

