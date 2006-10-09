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
#ifndef CHOPUPELEMENT_H
#define CHOPUPELEMENT_H

#include <stdlib.h>

/**
	@author Carsten Nikiel <carsten@nikiel.de>
*/
class ChopUpElement{
public:
    ChopUpElement();

    ChopUpElement(int A, int B) :
      A_(A), B_(B) {};

    int a(void) { return A_; }
    int b(void) { return B_; }

    ~ChopUpElement();
  
  bool operator< ( ChopUpElement &A ) {
   int min;
   if (A_ < B_) { min=A_; }
   else { min=B_; }
   if (min > A.a()) { min=A.a(); }
   if (min > A.b()) { min=A.b(); }
   if ((A_==min)||(B_==min)) {
    return true;
   } else return false;
  }
      
private:
  int A_;
  int B_;

};

#endif
