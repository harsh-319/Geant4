//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// -------------------------------------------------------------------
//      GEANT 4 class implementation file 
//
//      CERN, Geneva, Switzerland
//
//      File name:     G4KaonZeroField.cc
//
//      Author:        Alessandro Brunengo (Alessandro.Brunengo@ge.infn.it)
// 
//      Creation date: 5 June 2000
// -------------------------------------------------------------------
#include "G4KaonZeroField.hh"
#include "G4NucleiProperties.hh"
#include "G4VNuclearDensity.hh"
#include "G4FermiMomentum.hh"
#include "G4KaonZero.hh"
#include "G4HadTmpUtil.hh"

G4KaonZeroField::G4KaonZeroField(G4V3DNucleus * nucleus, G4double coeff)
  : G4VNuclearField(nucleus)
{
  theCoeff = coeff;
}


G4KaonZeroField::~G4KaonZeroField()
{ }


const G4KaonZeroField & G4KaonZeroField::operator=(const G4KaonZeroField &)
{
  throw G4HadronicException(__FILE__, __LINE__, "G4KaonZeroField::operator= meant not to be accessible");
  return *this;
}


G4int G4KaonZeroField::operator==(const G4KaonZeroField &) const
{
  throw G4HadronicException(__FILE__, __LINE__, "G4KaonZeroField::operator== meant not to be accessible");
  return 0;
}


G4int G4KaonZeroField::operator!=(const G4KaonZeroField &) const
{
  throw G4HadronicException(__FILE__, __LINE__, "G4KaonZeroField::operator!= meant not to be accessible");
  return 1;
}



G4double G4KaonZeroField::GetField(const G4ThreeVector & aPosition)
{
// Field is 0 out of the nucleus!
  if(aPosition.mag() >= radius) return 0.0;

  G4double kaonMass = G4KaonZero::KaonZero()->GetPDGMass();

  G4int A = theNucleus->GetMassNumber();
  G4int Z = theNucleus->GetCharge();
  G4double bindingEnergy = G4NucleiProperties::GetBindingEnergy(A, Z);
  G4double nucleusMass = Z*proton_mass_c2+(A-Z)*neutron_mass_c2+bindingEnergy;
  G4double reducedMass = kaonMass*nucleusMass/(kaonMass+nucleusMass);

  G4double density = theNucleus->GetNuclearDensity()->GetDensity(aPosition);

  return -2.*pi*hbarc*hbarc/reducedMass*(2.0)*theCoeff*density;
}

G4double G4KaonZeroField::GetBarrier()
{
  return 0;
}





