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
#include "nodelist.h"

NodeList::NodeList()
{
}


NodeList::~NodeList()
{
}

void
NodeList::add(QString Name, int Number) {
  bool new_element = true;
  QValueList<NodeElement>::Iterator it;
  for ( it = Nodes.begin(); it != Nodes.end(); ++it ){
   if (((*it).name().compare(Name)) == 0) {
     (*it).Numbers_.push_back(Number);
     new_element=false;
   }
  }
  if (new_element) {
   NodeElement tmp;
   tmp.setName(Name);
   tmp.Numbers_.push_back(Number);
   Nodes.push_back(tmp);
  }
}

