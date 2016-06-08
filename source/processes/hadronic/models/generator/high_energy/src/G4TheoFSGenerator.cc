// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4TheoFSGenerator.cc,v 1.1 1998/08/22 08:54:35 hpw Exp $
// GEANT4 tag $Name: geant4-00 $
//
// G4TheoFSGenerator
#include "G4DynamicParticle.hh"
#include "G4TheoFSGenerator.hh"
#include "G4ReactionProductVector.hh"
#include "G4ParticleVector.hh"

G4TheoFSGenerator::G4TheoFSGenerator()
{
 theParticleChange = new G4ParticleChange;
}

G4TheoFSGenerator::G4TheoFSGenerator(const G4TheoFSGenerator &right)
{
}


G4TheoFSGenerator::~G4TheoFSGenerator()
{
  delete theParticleChange;
}


const G4TheoFSGenerator & G4TheoFSGenerator::operator=(const G4TheoFSGenerator &right)
{
  G4Exception("G4CrossSectionBase::operator= meant to not be accessable");
  return *this;
}


int G4TheoFSGenerator::operator==(const G4TheoFSGenerator &right) const
{
  return 0;
}

int G4TheoFSGenerator::operator!=(const G4TheoFSGenerator &right) const
{
  return 1;
}


G4VParticleChange * G4TheoFSGenerator::ApplyYourself(const G4Track & thePrimary, G4Nucleus &theNucleus)
{
  // init particle change
  theParticleChange->Initialize(thePrimary);
  theParticleChange->SetStatusChange(fStopAndKill);
  
  // check if models have been registered, and use default, in case this is not true @@
  
  // get result from high energy model
  const G4DynamicParticle * aPart = thePrimary.GetDynamicParticle();
  G4KineticTrackVector * theInitialResult =
               theHighEnergyGenerator->Scatter(theNucleus, *aPart);
  
  // Hand over to transport for intra-nuclear transport
  G4ParticleVector * theTransportResult = 
               theTransport->Propagate(theInitialResult, theHighEnergyGenerator->GetWoundedNucleus());
  
  // Fill particle change
  int i;
  theParticleChange->SetNumberOfSecondaries(theTransportResult->entries());
  for(i=0; i<theTransportResult->entries(); i++)
  {
    theParticleChange->AddSecondary(theTransportResult->at(i));
  }
  
  // some garbage collection
  delete theTransportResult;
  
  // Done
  return theParticleChange;
}
