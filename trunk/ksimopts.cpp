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
    SParameterList SOrig;
    SOrig.loadFromFile("/home/cnikiel/Projects/testfile/test6.s");
    NetList Schematic;
    Schematic.loadFromFile("/home/cnikiel/Projects/testfile/test6.net");

    SMatrix SM(Schematic);
    for (int i =0; i<1; i++) {
      SM.fillMatrix(500e6);
      SM.createFormula();
    }
}

ksimopts::~ksimopts()
{
}

#include "ksimopts.moc"
