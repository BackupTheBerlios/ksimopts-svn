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
#include "smatrix.h"

#include <iostream>


SMatrix::~SMatrix()
{
  free(SMatrix_);
}

QString
SMatrix::print(void) {
 QString ReturnValue;
 std::complex<double> *tmp;

 ReturnValue="";
 for (int i=0; i<MatrixDimension_; i++) {
  for (int j=0; j<MatrixDimension_; j++) {
   tmp = SMatrix_ + i*MatrixDimension_ + j;
   QString STRtmp;
   STRtmp.sprintf("(%.3f,%.3f) ",(*tmp).real(),(*tmp).imag());
/*   int X=MatrixDimension_*j+i;
   if ((X==S11_) || (X==S12_) || (X==S21_) || (X==S22_)) {
     STRtmp = "S";
   } else {
     if ((*tmp) != std::complex<double>(0.0,0.0)) { STRtmp = "#"; }
     else { STRtmp = "."; }
   }*/
   ReturnValue.append(STRtmp);
  }
  ReturnValue.append("\n");
 }
 return ReturnValue;
}

void
SMatrix::setSchematic(NetList &Schematic) {
 Schematic_=Schematic;
 MatrixDimension_  = Schematic_.RList.count()*2 +
                     Schematic_.LList.count()*2 +
                     Schematic_.CList.count()*2 +
                     Schematic_.CCCSList.count()*4 +
                     Schematic_.CCVSList.count()*4 +
                     Schematic_.VCCSList.count()*4 +
                     Schematic_.VCVSList.count()*4 +
                     Schematic_.OLList.count()*2 +
                     Schematic_.SCList.count();
 QValueList<NodeElement>::Iterator it;
 for (it = Schematic_.Nodes.Nodes.begin(); it != Schematic_.Nodes.Nodes.end(); ++it) {
   if ((*it).count()>2) {MatrixDimension_ += (*it).count();}
 }
 SMatrix_=(std::complex<double> *) calloc(MatrixDimension_*MatrixDimension_,
           sizeof(std::complex<double>));
 Pos_=0;
}

bool
SMatrix::fillMatrix(double Frequency) {
 Pos_=0;
 double W=Frequency*2.0*M_PI;
 int X,Y;

 QValueList<OLElement>::Iterator it3;
 for ( it3 = Schematic_.OLList.begin(); it3 != Schematic_.OLList.end(); ++it3 ){
   addOL(true);
   if ((*it3).startNode()=="S1") { X = Pos_ - 2; }
   if ((*it3).startNode()=="S2") { Y = Pos_ - 2; }
 }
 S11_=MatrixDimension_*X+X;
 S12_=MatrixDimension_*X+Y;
 S21_=MatrixDimension_*Y+X;
 S22_=MatrixDimension_*Y+Y;
 QValueList<SCElement>::Iterator it4;
 for ( it4 = Schematic_.SCList.begin(); it4 != Schematic_.SCList.end(); ++it4 ){
   addSC();
 }
 QValueList<RCLElement>::Iterator it;
 for ( it = Schematic_.RList.begin(); it != Schematic_.RList.end(); ++it ){
  addZ(std::complex<double>((*it).value(),0.0));
 }
 for ( it = Schematic_.LList.begin(); it != Schematic_.LList.end(); ++it ){
  addZ(std::complex<double>(0.0,W*(*it).value()));
 }
 for ( it = Schematic_.CList.begin(); it != Schematic_.CList.end(); ++it ){
  addZ(std::complex<double>(0.0,-1.0/(W*(*it).value())));
 }
 QValueList<CCElement>::Iterator it2;
 for ( it2 = Schematic_.VCCSList.begin(); it2 != Schematic_.VCCSList.end(); ++it2 ){
   addCS(std::complex<double>(-2.0*(*it2).value()*exp(std::complex<double>(0.0,-W*(*it2).tau()))), false, false);
  }
 for ( it2 = Schematic_.VCVSList.begin(); it2 != Schematic_.VCVSList.end(); ++it2 ){
   addCS(std::complex<double>((*it2).value()*exp(std::complex<double>(0.0,-W*(*it2).tau()))), true, false);
  }
 for ( it2 = Schematic_.CCCSList.begin(); it2 != Schematic_.CCCSList.end(); ++it2 ){
   addCS(std::complex<double>(-(*it2).value()*exp(std::complex<double>(0.0,-W*(*it2).tau()))), false, true);
  }
 for ( it2 = Schematic_.CCVSList.begin(); it2 != Schematic_.CCVSList.end(); ++it2 ){
   addCS(std::complex<double>((*it2).value()/2.0*exp(std::complex<double>(0.0,-W*(*it2).tau()))), true, true);
  }
 QValueList<NodeElement>::Iterator it5;
 for ( it5 = Schematic_.Nodes.Nodes.begin(); it5 != Schematic_.Nodes.Nodes.end(); ++it5 ){
  if ((*it5).Numbers_.count()>2) {
    addNode((*it5).Numbers_.count());
    if (!FormulaExists_) {
      int tmpCount = Pos_ - (*it5).Numbers_.count() + 1 ;
      for ( unsigned int i = 0; i < (*it5).Numbers_.count(); i++) {
       ChopUp.List.push_back(ChopUpElement(tmpCount, (*it5).Numbers_[i]));
       ChopUp.List.push_back(ChopUpElement((*it5).Numbers_[i], tmpCount));
       tmpCount++;
     }
    }
  } else {
   if (!FormulaExists_) {
     if ((*it5).Numbers_.count()==2) {
       ChopUp.List.push_back(ChopUpElement((*it5).Numbers_[0], (*it5).Numbers_[1]));
       ChopUp.List.push_back(ChopUpElement((*it5).Numbers_[1], (*it5).Numbers_[0]));
     }
   }
  }
 }
 return true;
}

void
SMatrix::addZ(std::complex<double> Z)
{
  std::complex<double> Result1, Result2;
  std::complex<double> *Destination;

  Result1 = Z/(Z0_2+Z);
  Result2 = Z0_2/(Z0_2+Z);
  Destination=SMatrix_+MatrixDimension_*Pos_+Pos_;
  *Destination++=Result1;
  *Destination=Result2;
  Destination += MatrixDimension_-1;
  *Destination++=Result2;
  *Destination=Result1;
  Pos_+=2;
}

void
SMatrix::addOL(bool change)
{
  std::complex<double> *Destination;

  Destination=SMatrix_+MatrixDimension_*Pos_+Pos_+1;
  *Destination=std::complex<double>(1.0,0.0);
  Destination += MatrixDimension_-1;
  *Destination=std::complex<double>(1.0,0.0);
  if (change) { Pos_+=2; }
}

void
SMatrix::addINOL(bool change)
{
  std::complex<double> *Destination;

  Destination=SMatrix_+MatrixDimension_*Pos_+Pos_;
  *Destination=std::complex<double>(1.0,0.0);
  Destination += MatrixDimension_+1;
  *Destination=std::complex<double>(1.0,0.0);
  if (change) { Pos_+=2; }
}

void
SMatrix::addSC(void)
{
  std::complex<double> *Destination;

  Destination=SMatrix_+MatrixDimension_*Pos_+Pos_;
  *Destination=std::complex<double>(-1.0,0.0);
  Pos_++;
}

void
SMatrix::addCS(std::complex<double> G, bool first, bool second){
  std::complex<double> *Destination;

  if (first) { addOL(false); }
  else { addINOL(false); }
  Destination=SMatrix_+MatrixDimension_*Pos_+Pos_+2;
  *Destination++=G;
  *Destination=-G;
  Destination += MatrixDimension_ -1;
  *Destination++=G;
  *Destination=-G;
  Pos_+=2;
  if (second) { addOL(true); }
  else { addINOL(true); }

}

void
SMatrix::addNode(int count){
  std::complex<double> Result1((2.0-(double)count)/(double)count,0.0);
  std::complex<double> Result2(2.0/(double)count,0.0);
  std::complex<double> *Destination;

  for (int i=0; i<count; i++) {
   for (int j=0; j<count; j++) {
    Destination=SMatrix_+MatrixDimension_*Pos_+Pos_+MatrixDimension_*i+j;
    if (i==j) { *Destination=Result1; }
    else { *Destination=Result2; }
   }
  }
  Pos_ += count;
}

int
SMatrix::createFormula(void) {
  bool *AVector;
  bool *BVector;
  int FormA, FormB, FormC, FormD;
  int count0, count1, count2, count3;
  int ChangeA, ChangeB;
  std::complex<double> A,B,C,D;
  int Row, Column;
  std::complex<double> Null_(0.0,0.0);
  std::complex<double> One_(1.0,0.0);

  if (FormulaExists_) return Formula.List.count();

  fillMatrix(500e6);

#ifdef DEBUG_
  std::cout << print();
#endif

  count0=count1=count2=count3=0;

  AVector = (bool*) calloc(MatrixDimension_, sizeof(bool));
  BVector = (bool*) calloc(MatrixDimension_, sizeof(bool));
  for (int i=0; i<MatrixDimension_; i++) {
   *(AVector+i)=false;
   *(BVector+i)=false;
  }

  qHeapSort( ChopUp.List);
#ifdef DEBUG_
  std::cout << ChopUp.print() << std::endl;
#endif

  QValueList<ChopUpElement>::Iterator it;
  for ( it = ChopUp.List.begin(); it != ChopUp.List.end(); it++ ) {
    ChangeA = (*it).a()-1;
    ChangeB = (*it).b()-1;
    FormD = MatrixDimension_*ChangeB + ChangeA;
    D = *(SMatrix_+FormD);
    Row=0;
    while (Row < MatrixDimension_) {
     while ( ( (*(BVector+Row)) && (Row<MatrixDimension_) ) || (Row==ChangeB) ) Row++;
     if (Row<MatrixDimension_) {
      FormB=MatrixDimension_*Row+ChangeA;
      B = *(SMatrix_+FormB);
      if (B != Null_) {
       Column=0;
       while (Column < MatrixDimension_) {
        while ( ( (*(AVector+Column)) && (Column<MatrixDimension_) ) || (Column==ChangeA) ) Column++;
        if (Column<MatrixDimension_) {
         FormC = MatrixDimension_*ChangeB + Column;
         C = *(SMatrix_+FormC);
         if (C != Null_) {
          FormA = MatrixDimension_*Row + Column;
          A = *(SMatrix_ + FormA);
#ifdef DEBUG_
          std::cout << "*** Start of ChangeA: "<< ChangeA << " ChangeB: " << ChangeB << "\n";
          std::cout << "  A before: " << A << " <" << FormA << ">\n";
          std::cout << "  B: "<<B<<" <"<<FormB<<">\n";
          std::cout << "  C: "<<C<<" <"<<FormC<<">\n";
          std::cout << "  D: "<<D<<" <"<<FormD<<">\n";
#endif
          if ((A==Null_)&&(D==Null_)) {
           Formula.List.push_back(FormulaElement(0, FormA, FormB, FormC, FormD));
           A = B*C;
           count0++;
#ifdef DEBUG_
           std::cout << "  Formula 0: A=B*C\n";
#endif
          } else
          if ((A!=Null_)&&(D==Null_)) {
           Formula.List.push_back(FormulaElement(1, FormA, FormB, FormC, FormD));
           A += B*C;
           count1++;
#ifdef DEBUG_
           std::cout << "  Formula 1: A=A+B*C\n";
#endif
          } else
          if ((A==Null_)&&(D!=Null_)) {
           Formula.List.push_back(FormulaElement(2, FormA, FormB, FormC, FormD));
           A = B*C/(One_-D);
           count2++;
#ifdef DEBUG_
           std::cout << "  Formula 2: A=B*C/(1-D)\n";
#endif
          } else
          if ((A!=Null_)&&(D!=Null_)) {
           Formula.List.push_back(FormulaElement(3, FormA, FormB, FormC, FormD));
           A += B*C/(One_-D);
           count3++;
#ifdef DEBUG_
           std::cout << "  Formula 3: A=A+B*C/(1-D)\n";
#endif
          }
          *(SMatrix_+FormA)=A;
#ifdef DEBUG_
          std::cout << "  A after: " << A << "<" << FormA << ">\n";
#endif
         }
        }
        Column++;
       }
      }
     }
     Row++;
    }
    *(BVector+ChangeB)=true;
    *(AVector+ChangeA)=true;
  }

  FormulaExists_=true;

#ifdef DEBUG_
  std::cout << S11_ << " " << S12_ << " " << S21_ << " " << S22_ << std::endl;
  std::cout << count0 << " " << count1 << " " << count2 << " " << count3 << " (" <<
               count0+count1+count2+count3 << ")" << std::endl;
  std::cout << "S11: (" << s11().real() << "," << s11().imag() << ")\n";
  std::cout << "S12: (" << s12().real() << "," << s12().imag() << ")\n";
  std::cout << "S21: (" << s21().real() << "," << s21().imag() << ")\n";
  std::cout << "S22: (" << s22().real() << "," << s22().imag() << ")\n";
  std::cout << print();
#endif

  return Formula.List.count();
}

bool
SMatrix::calculate(double Frequency){
 fillMatrix(Frequency);

 QValueList<FormulaElement>::Iterator it;
 for ( it = Formula.List.begin(); it != Formula.List.end(); it++) {
   switch((*it).formula()) {
    case 0: *(SMatrix_ + (*it).a()) =  *(SMatrix_ + (*it).b()) * *(SMatrix_ + (*it).c());
            break;
    case 1: *(SMatrix_ + (*it).a()) += *(SMatrix_ + (*it).b()) * *(SMatrix_ + (*it).c());
            break;
    case 2: *(SMatrix_ + (*it).a()) =  *(SMatrix_ + (*it).b()) * *(SMatrix_ + (*it).c()) / (1.0 - *(SMatrix_ + (*it).d()));
            break;
    case 3: *(SMatrix_ + (*it).a()) += *(SMatrix_ + (*it).b()) * *(SMatrix_ + (*it).c()) / (1.0 - *(SMatrix_ + (*it).d()));
            break;
    default: break;
   }
 }
//   std::cout << "S11: (" << s11().real() << "," << s11().imag() << ")  ";
//   std::cout << "S12: (" << s12().real() << "," << s12().imag() << ")  ";
//   std::cout << "S21: (" << s21().real() << "," << s21().imag() << ")  ";
//   std::cout << "S22: (" << s22().real() << "," << s22().imag() << ")\n";

 return true;
}
