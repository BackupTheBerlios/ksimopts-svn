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
//    STRtmp.sprintf("(%.3f,%.3f) ",(*tmp).real(),(*tmp).imag());
   if ((*tmp) != std::complex<double>(0.0,0.0)) { STRtmp = "#"; }
   else { STRtmp = "."; }
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
 double W=Frequency*2*M_PI;
 QValueList<RCLElement>::Iterator it;
 for ( it = Schematic_.RList.begin(); it != Schematic_.RList.end(); ++it ){
  addZ(std::complex<double>((*it).value(),0.0));
 }
 for ( it = Schematic_.LList.begin(); it != Schematic_.LList.end(); ++it ){
  addZ(std::complex<double>(0.0,W*(*it).value()));
 }
 for ( it = Schematic_.CList.begin(); it != Schematic_.CList.end(); ++it ){
  addZ(std::complex<double>(0.0,1.0/(W*(*it).value())));
 }
 QValueList<SCElement>::Iterator it4;
 for ( it4 = Schematic_.SCList.begin(); it4 != Schematic_.SCList.end(); ++it4 ){
   addSC();
 }
 QValueList<CCElement>::Iterator it2;
 for ( it2 = Schematic_.VCCSList.begin(); it2 != Schematic_.VCCSList.end(); ++it2 ){
   addVCCS(std::complex<double>(-(*it2).value()*50.0*exp(std::complex<double>(0.0,-W*(*it2).tau()))));
  }
 for ( it2 = Schematic_.VCVSList.begin(); it2 != Schematic_.VCVSList.end(); ++it2 ){
   addVCVS(std::complex<double>((*it2).value()*exp(std::complex<double>(0.0,-W*(*it2).tau()))/2.0));
  }
 for ( it2 = Schematic_.CCCSList.begin(); it2 != Schematic_.CCCSList.end(); ++it2 ){
   addCCCS(std::complex<double>(-(*it2).value()*exp(std::complex<double>(0.0,-W*(*it2).tau()))));
  }
 for ( it2 = Schematic_.CCVSList.begin(); it2 != Schematic_.CCVSList.end(); ++it2 ){
   addCCVS(std::complex<double>((*it2).value()/50.0*exp(std::complex<double>(0.0,-W*(*it2).tau()))));
  }
 QValueList<OLElement>::Iterator it3;
 for ( it3 = Schematic_.OLList.begin(); it3 != Schematic_.OLList.end(); ++it3 ){
   addOL(true);
 }
 QValueList<NodeElement>::Iterator it5;
 for ( it5 = Schematic_.Nodes.Nodes.begin(); it5 != Schematic_.Nodes.Nodes.end(); ++it5 ){
  if ((*it5).Numbers_.count()>2) {
    addNode((*it5).Numbers_.count());
    int tmpCount = Pos_ - (*it5).Numbers_.count() + 1 ;
    for ( int i = 0; i < (*it5).Numbers_.count(); i++) {
     ChopUp.List.push_back(ChopUpElement(tmpCount, (*it5).Numbers_[i]));
     ChopUp.List.push_back(ChopUpElement((*it5).Numbers_[i], tmpCount));
     tmpCount++;
/*     std::cout << (*it5).Numbers_.count() << ": " << tmpCount
        << "(" << MatrixDimension_ << ")" << std::endl;*/
    }
  } else {
   if ((*it5).Numbers_.count()==2) {
     ChopUp.List.push_back(ChopUpElement((*it5).Numbers_[0], (*it5).Numbers_[1]));
     ChopUp.List.push_back(ChopUpElement((*it5).Numbers_[1], (*it5).Numbers_[0]));
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
SMatrix::addVCCS(std::complex<double> G){
  std::complex<double> *Destination;

  addINOL(false);
  Destination=SMatrix_+MatrixDimension_*Pos_+Pos_+2;
  *Destination++=G;
  *Destination=-G;
  Destination += MatrixDimension_ -1;
  *Destination++=G;
  *Destination=-G;
  Pos_+=2;
  addINOL(true);
}

void
SMatrix::addVCVS(std::complex<double> E){
  std::complex<double> *Destination;

  addOL(false);
  Destination=SMatrix_+MatrixDimension_*Pos_+Pos_+2;
  *Destination++=E;
  *Destination=-E;
  Destination += MatrixDimension_ -1;
  *Destination++=-E;
  *Destination=E;
  Pos_+=2;
  addINOL(true);
}

void
SMatrix::addCCVS(std::complex<double> H){
  std::complex<double> *Destination;

  addOL(false);
  Destination=SMatrix_+MatrixDimension_*Pos_+Pos_+2;
  *Destination++=H;
  *Destination=-H;
  Destination += MatrixDimension_ -1;
  *Destination++=H;
  *Destination=-H;
  Pos_+=2;
  addOL(true);
}

void
SMatrix::addCCCS(std::complex<double> F){
  std::complex<double> *Destination;

  addINOL(false);
  Destination=SMatrix_+MatrixDimension_*Pos_+Pos_+2;
  *Destination++=F;
  *Destination=-F;
  Destination += MatrixDimension_ -1;
  *Destination++=F;
  *Destination=-F;
  Pos_+=2;
  addOL(true);
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

  count0=count1=count2=count3=0;
//   std::cout << "start the formula creation\n";

  AVector = (bool*) calloc(MatrixDimension_, sizeof(bool));
  BVector = (bool*) calloc(MatrixDimension_, sizeof(bool));
  for (int i=0; i<MatrixDimension_; i++) {
   *(AVector+i)=false;
   *(BVector+i)=false;
  }

//   std::cout << "Init done\n";

  QValueList<ChopUpElement>::Iterator it;
  for ( it = ChopUp.List.begin(); it != ChopUp.List.end(); it++ ) {
    ChangeA = (*it).a()-1;
    ChangeB = (*it).b()-1;

//     std::cout << ChangeA << " - " << ChangeB << std::endl;

    FormD = MatrixDimension_*ChangeB + ChangeA;
    D = *(SMatrix_+FormD);
    Row=0;
    while (Row < MatrixDimension_) {
     while ((*(BVector+Row))&&(Row<MatrixDimension_)) Row++;
     if (Row==ChangeB) Row++;
     if (Row<MatrixDimension_) {
      FormB=MatrixDimension_*Row+ChangeA;
      B = *(SMatrix_+FormB);
      if (B != Null_) {
//        std::cout << "Found B==NULL\n";
       Column=0;
       while (Column < MatrixDimension_) {
        while ((*(AVector+Column))&&(Column<MatrixDimension_)) Column++;
        if (Column==ChangeA) Column++;
        if (Column<MatrixDimension_) {
         FormC = MatrixDimension_*ChangeB + Column;
         C = *(SMatrix_+FormC);
         if (C != Null_) {
//            std::cout << "Found C==NULL\n";
          FormA = MatrixDimension_*Row + Column;
          A = *(SMatrix_ + FormA);
          if ((A==Null_)&&(D==Null_)) {
           Formula.List.push_back(FormulaElement(0, FormA, FormB, FormC, FormD));
           A = B*C;
           count0++;
//            std::cout << "Formula 0: " << Column << "/" << Row << "\n";
          } else 
          if ((A!=Null_)&&(D==Null_)) {
           Formula.List.push_back(FormulaElement(1, FormA, FormB, FormC, FormD));
           A += B*C;
           count1++;
//            std::cout << "Formula 1: " << Column << "/" << Row << "\n";
          } else
          if ((A==Null_)&&(D!=Null_)) {
           Formula.List.push_back(FormulaElement(2, FormA, FormB, FormC, FormD));
           A = B*C/(One_-D);
           count2++;
//            std::cout << "Formula 2: " << Column << "/" << Row << "\n";
          } else
          if ((A!=Null_)&&(D!=Null_)) {
           Formula.List.push_back(FormulaElement(3, FormA, FormB, FormC, FormD));
           A += B*C/(One_-D);
           count3++;
//            std::cout << "Formula 3: " << Column << "/" << Row << "\n";
          }
          *(SMatrix_+FormA)=A;
         }
        }
//         std::cout << "End of Column: " << Column << std::endl;
        Column++;
       }
      }
     }
//      std::cout << "End of Row: " << Row << std::endl;
     Row++;
    }
    *(BVector+ChangeB)=true;
    *(AVector+ChangeA)=true;
//     std::cout << ChangeA << " - " << ChangeB << std::endl;
  }

//   std::cout << Formula.print() << std::endl;
//   std::cout << Formula.List.count() << std::endl;
//   std::cout << ChopUp.print() << std::endl;
  FormulaExists_=true;

  Row=Column=0;
  int X1,X2,Y1,Y2;
  while (Column<MatrixDimension_) {
   if(!*(AVector+Column)) {
    X1=Column++;
    break;
   }
   Column++;
  }
  while (Column<MatrixDimension_) {
   if(*(AVector+Column)==false) {
    X2=Column++;
    break;
   }
   Column++;
  }
  while (Row<MatrixDimension_) {
   if(*(BVector+Row)==false) {
    Y1=Row++;
    break;
   }
   Row++;
  }
  while (Row<MatrixDimension_) {
   if(*(BVector+Row)==false) {
    Y2=Row++;
    break;
   }
   Row++;
  }
  S11_=MatrixDimension_*Y1+X1;
  S12_=MatrixDimension_*Y1+X2;
  S21_=MatrixDimension_*Y2+X1;
  S22_=MatrixDimension_*Y2+X2;

  std::cout << S11_ << " " << S12_ << " " << S21_ << " " << S22_ << std::endl;
  std::cout << X1 << " " << X2 << " " << Y1 << " " << Y2 << std::endl;
  std::cout << count0 << " " << count1 << " " << count2 << " " << count3 << std::endl;

  std::cout << "S11: (" << s11().real() << "," << s11().imag() << ")\n";
  std::cout << "S12: (" << s12().real() << "," << s12().imag() << ")\n";
  std::cout << "S21: (" << s21().real() << "," << s21().imag() << ")\n";
  std::cout << "S22: (" << s22().real() << "," << s22().imag() << ")\n";
  std::cout << print();

  return Formula.List.count();
}

