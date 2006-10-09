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


#ifndef _KSIMoptsPREF_H_
#define _KSIMoptsPREF_H_

#include <kdialogbase.h>
#include <qframe.h>

class ksimoptsPrefPageOne;
class ksimoptsPrefPageTwo;

class ksimoptsPreferences : public KDialogBase
{
    Q_OBJECT
public:
    ksimoptsPreferences();

private:
    ksimoptsPrefPageOne *m_pageOne;
    ksimoptsPrefPageTwo *m_pageTwo;
};

class ksimoptsPrefPageOne : public QFrame
{
    Q_OBJECT
public:
    ksimoptsPrefPageOne(QWidget *parent = 0);
};

class ksimoptsPrefPageTwo : public QFrame
{
    Q_OBJECT
public:
    ksimoptsPrefPageTwo(QWidget *parent = 0);
};

#endif // _KSIMoptsPREF_H_
