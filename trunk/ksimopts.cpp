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


#include "ksimopts.h"
#include "sparameterlist.h"
#include "netlist.h"
#include "finalcost.h"
#include "smatrix.h"

#include <qlabel.h>

#include <kmainwindow.h>
#include <klocale.h>

#include <iostream>

ksimopts::ksimopts()
    : KMainWindow( 0, "ksimopts" )
{
//    set the shell's ui resource file
//    setXMLFile("ksimoptsui.rc");

    new QLabel( "Only ascii", this, "KSimOpts" );
    SParameterList SOrig, SCalc;
    SOrig.loadFromFile("/home/cnikiel/Projects/testfile/test6.s");
    FinalCost finalcost(SOrig);
    NetList Schematic;
    Schematic.loadFromFile("/home/cnikiel/Projects/testfile/test6.net");

    SMatrix SM(Schematic);
    SM.createFormula();
    
    QValueList<SParameter>::Iterator it;
    for ( it = SOrig.List.begin(); it != SOrig.List.end(); ++it ){
     SM.calculate((*it).frequency());
     SCalc.List.push_back(SParameter::SParameter(
           SM.s11(), SM.s12(), SM.s21(), SM.s22(), (*it).frequency()));
    }
    std::cout << finalcost.calculate(SCalc) << "\n";
}

ksimopts::~ksimopts()
{
}

#include "ksimopts.moc"
