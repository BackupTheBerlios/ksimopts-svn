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
#include "chopuplist.h"

#include <qtextstream.h>

ChopUpList::ChopUpList()
{
}


ChopUpList::~ChopUpList()
{
}

QString
ChopUpList::print(void) {
 QString ReturnValue;
 QValueList<ChopUpElement>::Iterator it;
 QString tmp;

 for ( it = List.begin(); it != List.end(); it++ ) {
   tmp="";
   QTextOStream (&tmp) << (*it).a() <<
        " - " << (*it).b() << "\n";
   ReturnValue.append(tmp);
 }

 return ReturnValue;
}
