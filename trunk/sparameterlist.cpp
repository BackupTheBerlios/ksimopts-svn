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
#include "sparameterlist.h"

#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qregexp.h>

#include <iostream>
#include <complex>

SParameterList::SParameterList()
{
}


SParameterList::~SParameterList()
{
}

void
SParameterList::loadFromFile(QString filename)
{
  QFile file(filename);
  double FreqMultiply=1.0;
  bool S12S21 = true;

  if ( file.open( IO_ReadOnly ) ) {
    QTextStream stream( &file );
    QString line;
    while ( !stream.atEnd() ) {
     line = stream.readLine(); // line of text excluding '\n'
     line = line.stripWhiteSpace();
     if (line.find(QRegExp("MHz"),0) > 0) { FreqMultiply = 1e6; }
     if (line.find(QRegExp("GHz"),0) > 0) { FreqMultiply = 1e9; }
     if (line.find(QRegExp("S12"),0) > line.find(QRegExp("S21"),0)) {
       S12S21 = false;
     }
     if ((line.at(0) != '#')&&(line.at(0) != '!')) {
       QStringList TempFields = QStringList::split(" ", line);
       if (S12S21) {
         List.push_back(SParameter::SParameter(
           complex<double>(TempFields[1].toDouble(), TempFields[2].toDouble()),
           complex<double>(TempFields[3].toDouble(), TempFields[4].toDouble()),
           complex<double>(TempFields[5].toDouble(), TempFields[6].toDouble()),
           complex<double>(TempFields[7].toDouble(), TempFields[8].toDouble()),
           TempFields[0].toDouble()*FreqMultiply));
       } else {
         List.push_back(SParameter(
           complex<double>(TempFields[1].toDouble(), TempFields[2].toDouble()),
           complex<double>(TempFields[5].toDouble(), TempFields[6].toDouble()),
           complex<double>(TempFields[3].toDouble(), TempFields[4].toDouble()),
           complex<double>(TempFields[7].toDouble(), TempFields[8].toDouble()),
           TempFields[0].toDouble()*FreqMultiply));
       }
     }
    }
  }
}

QString
SParameterList::print(void)
{
 QString ReturnValue;

 QValueList<SParameter>::Iterator it;
 for ( it = List.begin(); it != List.end(); ++it ){
  ReturnValue.append((*it).print());
 }

 return ReturnValue;
}
