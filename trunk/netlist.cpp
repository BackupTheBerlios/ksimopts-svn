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
#include "netlist.h"

#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qstringlist.h>
#include <qregexp.h>

#include <iostream>


NetList::NetList()
{
}


NetList::~NetList()
{
}

QString
NetList::print(void){
 QString ReturnValue;
 QString tmp;
 QValueList<RCLElement>::Iterator it;
 for ( it = RList.begin(); it != RList.end(); ++it ){
  ReturnValue.append(printRCL(it));
 }
 for ( it = CList.begin(); it != CList.end(); ++it ){
  ReturnValue.append(printRCL(it));
 }
 for ( it = LList.begin(); it != LList.end(); ++it ){
  ReturnValue.append(printRCL(it));
 }
 QValueList<CCElement>::Iterator it2;
 for ( it2 = VCVSList.begin(); it2 != VCVSList.end(); ++it2 ){
   ReturnValue.append(printCC(it2));
  }
 for ( it2 = VCCSList.begin(); it2 != VCCSList.end(); ++it2 ){
   ReturnValue.append(printCC(it2));
  }
 for ( it2 = CCVSList.begin(); it2 != CCVSList.end(); ++it2 ){
   ReturnValue.append(printCC(it2));
  }
 for ( it2 = CCCSList.begin(); it2 != CCCSList.end(); ++it2 ){
   ReturnValue.append(printCC(it2));
  }
 ReturnValue.append(VIn.name() + ":" +
                    VIn.startNode() + " - " +
                    VIn.endNode() + "\n");
 ReturnValue.append(VOut.name() + ":" +
                    VOut.startNode() + " - " +
                    VOut.endNode() + "\n");
 QValueList<OLElement>::Iterator it3;
 for ( it3 = OLList.begin(); it3 != OLList.end(); ++it3 ){
   ReturnValue.append("OL: ");
   ReturnValue.append((*it3).startNode());
   ReturnValue.append(" - ");
   ReturnValue.append((*it3).endNode());
   ReturnValue.append("\n");
  }
 QValueList<SCElement>::Iterator it4;
 for ( it4 = SCList.begin(); it4 != SCList.end(); ++it4 ){
   ReturnValue.append("SC: ");
   ReturnValue.append((*it4).node());
   ReturnValue.append("\n");
  }

 return ReturnValue;
}

void
NetList::loadFromFile(QString filename) {
  QFile file(filename);
  if ( file.open( IO_ReadOnly ) ) {
    QTextStream stream( &file );
    QString line;
    while ( !stream.atEnd() ) {
     line = stream.readLine(); // line of text excluding '\n'
     line = line.stripWhiteSpace();
     QChar ElementFound = line.at(0);
     if ((ElementFound == 'R') ||
         (ElementFound == 'C') ||
         (ElementFound == 'L')) {
       QStringList TempFields = QStringList::split(" ", line);
       QString Name  = TempFields[0].mid(2,255);
       QString Node1 = TempFields[1];
       QString Node2 = TempFields[2];
       QString tmp   = TempFields[3];
       double  Value = tmp.replace(QRegExp("[^0-9.,]*"),"").toDouble();
       Value *= UnitToDouble(TempFields[3].replace(QRegExp("[0-9]*"),""));
       switch (ElementFound){
         case 'R': RList.push_back(RCLElement(Name,Node1,Node2,Value,Value*0.01,Value*100,true));
                   break;
         case 'C': CList.push_back(RCLElement(Name,Node1,Node2,Value,Value*0.01,Value*100,true));
                   break;
         case 'L': LList.push_back(RCLElement(Name,Node1,Node2,Value,Value*0.01,Value*100,true));
                   break;
         default: break;
       }
     }
     if ((ElementFound == 'G') ||
         (ElementFound == 'F') ||
         (ElementFound == 'H') ||
         (ElementFound == 'E')) {
       QStringList TempFields = QStringList::split(" ", line);
       QString Name  = TempFields[0].mid(2,255);
       QString Node1 = TempFields[1];
       QString Node2 = TempFields[2];
       QString Node3 = TempFields[3];
       QString Node4 = TempFields[4];
       QString tmp   = TempFields[5];
       double  Value = tmp.replace(QRegExp("[^0-9.,]*"),"").toDouble();
       Value *= UnitToDouble(TempFields[5].replace(QRegExp("[0-9]*"),""));
       tmp = TempFields[6];
       double Tau=750.0e-15;
       if (tmp != "") {
         Tau = tmp.replace(QRegExp("[^0-9.,]*"),"").toDouble();
         Tau *= UnitToDouble(TempFields[6].replace(QRegExp("[0-9]*"),""));
       }
       switch (ElementFound){
         case 'E': VCVSList.push_back(CCElement(Name,Node1,Node2,Node3,Node4,
                            Value,Value*0.01,Value*100,true,Tau,Tau*0.01,Tau*100,true));
                   break;
         case 'F': CCCSList.push_back(CCElement(Name,Node1,Node2,Node3,Node4,
                            Value,Value*0.01,Value*100,true,Tau,Tau*0.01,Tau*100,true));
                   break;
         case 'G': VCCSList.push_back(CCElement(Name,Node1,Node2,Node3,Node4,
                            Value,Value*0.01,Value*100,true,Tau,Tau*0.01,Tau*100,true));
                   break;
         case 'H': CCVSList.push_back(CCElement(Name,Node1,Node2,Node3,Node4,
                            Value,Value*0.01,Value*100,true,Tau,Tau*0.01,Tau*100,true));
                   break;
         default: break;
       }
     }
     if (ElementFound == 'V'){
       QStringList TempFields = QStringList::split(" ", line);
       QString Name  = TempFields[0].mid(2,255);
       QString Node1 = TempFields[1];
       QString Node2 = TempFields[2];
       if (Name == "Vout" ) {
         VOut.setName(Name);
         VOut.setStartNode(Node1);
         VOut.setEndNode(Node2);
       } else {
         VIn.setName(Name);
         VIn.setStartNode(Node1);
         VIn.setEndNode(Node2);
       }
     }
    }
    file.close();
  }
  addAdditionalElements();
}

double
NetList::UnitToDouble(QString UnitString) {
  double ReturnValue;

  ReturnValue=1;
  switch ((QChar) UnitString.at(0))
  {
    case 'T' :
    case 't' : ReturnValue=1e12;
               break;
    case 'G' :
    case 'g' : ReturnValue=1e9;
               break;
    case 'M' : ReturnValue=1e6;
               break;
    case 'K' :
    case 'k' : ReturnValue=1e3;
               break;
    case 'm' : if (strcasecmp(UnitString,"meg")==0)
                 ReturnValue=1e6;
               else
                 ReturnValue=1e-3;
               break;
    case 'U' :
    case 'u' : ReturnValue=1e-6;
               break;
    case 'N' :
    case 'n' : ReturnValue=1e-9;
               break;
    case 'P' :
    case 'p' : ReturnValue=1e-12;
               break;
    case 'F' :
    case 'f' : ReturnValue=1e-15;
               break;
    default  : break;
  }
  return(ReturnValue);
}

QString
NetList::DoubleToUnits(double Value)
{
  int UnitNr;
  QChar Units[10]={'f','p','n','u','m',' ','k','M','G','T'};

  UnitNr=0;
  while ((Value>=1000)&&(UnitNr<4))
  {
    ++UnitNr;
    Value/=1000;
  }
  while ((Value<1)&&(UnitNr>-5))
  {
    --UnitNr;
    Value*=1000;
  }
  QString ReturnValue;
  ReturnValue.sprintf("%.3f ",Value);
  if ((UnitNr>=-5)&&(UnitNr<=4)) ReturnValue.append(Units[UnitNr+5]);
  return ReturnValue;
}

QString
NetList::printRCL(QValueList<RCLElement>::Iterator RCL) {
 QString ReturnValue;

 ReturnValue.append((*RCL).name() + ": ");
 ReturnValue.append((*RCL).startNode() + " - ");
 ReturnValue.append((*RCL).endNode() + ": ");
 ReturnValue.append(DoubleToUnits((*RCL).min()));
 ReturnValue.append(" : ");
 ReturnValue.append(DoubleToUnits((*RCL).min()));
 ReturnValue.append(" - ");
 ReturnValue.append(DoubleToUnits((*RCL).max()));
 ReturnValue.append("\n");

 return ReturnValue;
}

QString
NetList::printCC(QValueList<CCElement>::Iterator CC) {
 QString ReturnValue;

 ReturnValue.append((*CC).name() + ": ");
 ReturnValue.append((*CC).startNode() + " - ");
 ReturnValue.append((*CC).endNode() + ": ");
 ReturnValue.append((*CC).cstartNode() + " - ");
 ReturnValue.append((*CC).cendNode() + ": ");
 ReturnValue.append(DoubleToUnits((*CC).value()));
 ReturnValue.append(" : ");
 ReturnValue.append(DoubleToUnits((*CC).min()));
 ReturnValue.append(" - ");
 ReturnValue.append(DoubleToUnits((*CC).max()));
 ReturnValue.append(" / ");
 ReturnValue.append(DoubleToUnits((*CC).tau()));
 ReturnValue.append(" : ");
 ReturnValue.append(DoubleToUnits((*CC).taumin()));
 ReturnValue.append(" - ");
 ReturnValue.append(DoubleToUnits((*CC).taumax()));
 ReturnValue.append("\n");

 return ReturnValue;
}

void
NetList::addAdditionalElements(void) {
  if (VIn.startNode().compare(VOut.startNode())==0) {
    OLList.push_back(OLElement("S1", VIn.endNode()));
    OLList.push_back(OLElement("S2", VOut.endNode()));
    SCList.push_back(SCElement(VIn.startNode()));
  } else if (VIn.startNode().compare(VOut.endNode())==0) {
    OLList.push_back(OLElement("S1", VIn.endNode()));
    OLList.push_back(OLElement("S2", VOut.startNode()));
    SCList.push_back(SCElement(VIn.startNode()));
  } else if (VIn.endNode().compare(VOut.startNode())==0) {
    OLList.push_back(OLElement("S1", VIn.startNode()));
    OLList.push_back(OLElement("S2", VOut.endNode()));
    SCList.push_back(SCElement(VIn.endNode()));
  } else if (VIn.endNode().compare(VOut.endNode())==0) {
    OLList.push_back(OLElement("S1", VIn.startNode()));
    OLList.push_back(OLElement("S2", VOut.startNode()));
    SCList.push_back(SCElement(VIn.endNode()));
  }
  createNodeList();
}

void
NetList::createNodeList(void) {
  int counter=1;

 QValueList<OLElement>::Iterator it3;
 for ( it3 = OLList.begin(); it3 != OLList.end(); ++it3 ){
  Nodes.add((*it3).startNode(),counter++);
  Nodes.add((*it3).endNode(),counter++);
 }
 QValueList<SCElement>::Iterator it4;
 for ( it4 = SCList.begin(); it4 != SCList.end(); ++it4 ){
  Nodes.add((*it4).node(),counter++);
 }
 QValueList<RCLElement>::Iterator it;
 for ( it = RList.begin(); it != RList.end(); ++it ){
  Nodes.add((*it).startNode(),counter++);
  Nodes.add((*it).endNode(),counter++);
 }
 for ( it = LList.begin(); it != LList.end(); ++it ){
  Nodes.add((*it).startNode(),counter++);
  Nodes.add((*it).endNode(),counter++);
 }
 for ( it = CList.begin(); it != CList.end(); ++it ){
  Nodes.add((*it).startNode(),counter++);
  Nodes.add((*it).endNode(),counter++);
 }
 QValueList<CCElement>::Iterator it2;
 for ( it2 = VCCSList.begin(); it2 != VCCSList.end(); ++it2 ){
  Nodes.add((*it2).startNode(),counter++);
  Nodes.add((*it2).endNode(),counter++);
  Nodes.add((*it2).cstartNode(),counter++);
  Nodes.add((*it2).cendNode(),counter++);
 }
 for ( it2 = VCVSList.begin(); it2 != VCVSList.end(); ++it2 ){
  Nodes.add((*it2).startNode(),counter++);
  Nodes.add((*it2).endNode(),counter++);
  Nodes.add((*it2).cstartNode(),counter++);
  Nodes.add((*it2).cendNode(),counter++);
 }
 for ( it2 = CCCSList.begin(); it2 != CCCSList.end(); ++it2 ){
  Nodes.add((*it2).startNode(),counter++);
  Nodes.add((*it2).endNode(),counter++);
  Nodes.add((*it2).cstartNode(),counter++);
  Nodes.add((*it2).cendNode(),counter++);
 }
 for ( it2 = CCVSList.begin(); it2 != CCVSList.end(); ++it2 ){
  Nodes.add((*it2).startNode(),counter++);
  Nodes.add((*it2).endNode(),counter++);
  Nodes.add((*it2).cstartNode(),counter++);
  Nodes.add((*it2).cendNode(),counter++);
 }
/* Nodes.add(VIn.startNode(),counter++);
 Nodes.add(VIn.endNode(),counter++);
 Nodes.add(VOut.startNode(),counter++);
 Nodes.add(VOut.endNode(),counter++);
*/
/* QValueList<NodeElement>::Iterator it5;
 for (it5 = Nodes.Nodes.begin(); it5 != Nodes.Nodes.end(); ++it5) {
   std::cout << (*it5).name() << ": " << (*it5).count() << std::endl;
 }*/
}
