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
#ifndef VELEMENT_H
#define VELEMENT_H

#include <qstring.h>
/**
@author Carsten Nikiel
*/
class VElement{
public:
    VElement();

    VElement(QString name, QString startNode, QString endNode):
      Name_(name), StartNode_(startNode), EndNode_(endNode) {};

    ~VElement();

    QString name() { return Name_; }
    void setName(QString name) { Name_ = name; }

    QString startNode() { return StartNode_; }
    void setStartNode(QString startnode) { StartNode_ = startnode; }

    QString endNode() { return EndNode_; }
    void setEndNode(QString endnode) { EndNode_ = endnode; }

private:
  QString Name_;
  QString StartNode_;
  QString EndNode_;
};

#endif
