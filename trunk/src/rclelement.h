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
#ifndef RCLELEMENT_H
#define RCLELEMENT_H

#include <qstring.h>

/**
	@author Carsten Nikiel <carsten@nikiel.de>
*/
class RCLElement{
public:
    RCLElement();

    RCLElement(QString name, QString startnode, QString endnode,
               double value, double min, double max,
               bool changeable) :
               Name_(name), StartNode_(startnode), EndNode_(endnode),
               Value_(value), Min_(min), Max_(max),
               Changeable_(changeable) {};

    QString name() { return Name_; }
    void setName(QString name) { Name_ = name; }

    QString startNode() { return StartNode_; }
    void setStartNode(QString startnode) { StartNode_ = startnode; }

    QString endNode() { return EndNode_; }
    void setEndNode(QString endnode) { EndNode_ = endnode; }

    double value() { return Value_; }
    void setValue(double value) { Value_ = value; }

    double min() { return Min_; }
    void setMin(double min) { Min_ = min; }

    double max() { return Max_; }
    void setMax(double max) { Max_ = max; }

    bool isChangeable() { return Changeable_; }
    void setChangeable(bool changeable) { Changeable_ = changeable; }

    ~RCLElement();

private:
    QString Name_;
    QString StartNode_;
    QString EndNode_;
    double Value_;
    double Min_;
    double Max_;
    bool Changeable_;

};

#endif
