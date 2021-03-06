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
#ifndef FINALCOST_H
#define FINALCOST_H

#include "sparameterlist.h"

/**
	@author Carsten Nikiel <carsten@nikiel.de>
*/
class FinalCost{
public:
    FinalCost(SParameterList &original):
       Original_(original) {};

    void setOrigianl(SParameterList &original) { Original_ = original; }

    ~FinalCost();

double calculate(SParameterList &Calc);

private:
  SParameterList &Original_;
  int Which_;

};

#endif
