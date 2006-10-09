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
#ifndef OLELEMENT_H
#define OLELEMENT_H

#include <qstring.h>

/**
	@author Carsten Nikiel <carsten@nikiel.de>
*/
class OLElement{
public:
    OLElement();

    OLElement(QString startNode, QString endNode):
      StartNode_(startNode), EndNode_(endNode) {};

    ~OLElement();

    QString startNode() { return StartNode_; }
    void setStartNode(QString startnode) { StartNode_ = startnode; }

    QString endNode() { return EndNode_; }
    void setEndNode(QString endnode) { EndNode_ = endnode; }

private:
    QString StartNode_;
    QString EndNode_;

};

#endif
