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
#ifndef NETLIST_H
#define NETLIST_H
#include "rclelement.h"
#include "ccelement.h"
#include "velement.h"
#include "scelement.h"
#include "olelement.h"
#include "nodelist.h"

#include <qvaluelist.h>
#include <qstring.h>
#include <qdom.h>
#include <qfile.h>

/**
	@author Carsten Nikiel <carsten@nikiel.de>
*/
class NetList{
public:
    NetList();

    ~NetList();

    NetList(QString filename) {
      loadFromFile(filename);
    }

    void loadFromFile(QString filename);
    void loadFromXML(QString filename);
    void saveToXML(QString filename);
    QString print(void);

    QValueList<RCLElement> RList;
    QValueList<RCLElement> CList;
    QValueList<RCLElement> LList;
    QValueList<CCElement> VCCSList;
    QValueList<CCElement> CCCSList;
    QValueList<CCElement> CCVSList;
    QValueList<CCElement> VCVSList;
    VElement VIn;
    VElement VOut;
    QValueList<SCElement> SCList;
    QValueList<OLElement> OLList;
    NodeList Nodes;
private:
    double  UnitToDouble(QString UnitString);
    QString DoubleToUnits(double Value);
    void addAdditionalElements();
    void createNodeList();
    QString printRCL(QValueList<RCLElement>::Iterator RCL);
    QString printCC(QValueList<CCElement>::Iterator CC);
    QDomElement XMLRCL(QValueList<RCLElement>::Iterator RCL, QString type);
    QDomElement XMLCC(QValueList<CCElement>::Iterator CC, QString type);
    QDomElement XMLV(VElement V);

};

#endif
