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
#ifndef CCELEMENT_H
#define CCELEMENT_H

#include <qstring.h>

/**
@author Carsten Nikiel
*/
class CCElement{
public:
    CCElement();

    CCElement(QString name, QString startnode, QString endnode,
              QString cstartnode, QString cendnode,
               double value, double min, double max,
               bool changeable,
               double tau, double taumin, double taumax,
               bool tauchangeable) :
               Name_(name), StartNode_(startnode), EndNode_(endnode),
               CStartNode_(cstartnode), CEndNode_(cendnode),
               Value_(value), Min_(min), Max_(max),
               Changeable_(changeable), Tau_(tau),TauMin_(taumin),
               TauMax_(taumax), TauChangeable_(tauchangeable) {};

    QString name() { return Name_; }
    void setName(QString name) { Name_ = name; }

    QString startNode() { return StartNode_; }
    void setStartNode(QString startnode) { StartNode_ = startnode; }

    QString endNode() { return EndNode_; }
    void setEndNode(QString endnode) { EndNode_ = endnode; }

    QString cstartNode() { return CStartNode_; }
    void setCStartNode(QString cstartnode) { CStartNode_ = cstartnode; }

    QString cendNode() { return CEndNode_; }
    void setCEndNode(QString cendnode) { CEndNode_ = cendnode; }

    double value() { return Value_; }
    void setValue(double value) { Value_ = value; }

    double min() { return Min_; }
    void setMin(double min) { Min_ = min; }

    double max() { return Max_; }
    void setMax(double max) { Max_ = max; }

    bool isChangeable() { return Changeable_; }
    void setChangeable(bool changeable) { Changeable_ = changeable; }

    double tau() { return Tau_; }
    void setTau(double tau) { Tau_ = tau; }

    double taumin() { return TauMin_; }
    void setTauMin(double taumin) { TauMin_ = taumin; }

    double taumax() { return TauMax_; }
    void setTauMax(double taumax) { TauMax_ = taumax; }

    bool isTauChangeable() { return TauChangeable_; }
    void setTauChangeable(bool tauchangeable) { TauChangeable_ = tauchangeable; }

    ~CCElement();


private:
    QString Name_;
    QString StartNode_;
    QString EndNode_;
    QString CStartNode_;
    QString CEndNode_;
    double Value_;
    double Min_;
    double Max_;
    bool Changeable_;
    double Tau_;
    double TauMin_;
    double TauMax_;
    bool TauChangeable_;

};

#endif
