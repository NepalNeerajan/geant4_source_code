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
// INCL++ intra-nuclear cascade model
// Pekka Kaitaniemi, CEA and Helsinki Institute of Physics
// Davide Mancusi, CEA
// Alain Boudard, CEA
// Sylvie Leray, CEA
// Joseph Cugnon, University of Liege
//
// INCL++ revision: v5.1.8
//
#define INCLXX_IN_GEANT4_MODE 1

#include "globals.hh"

/*
 * G4INCLIRandomGenerator.hh
 *
 *  \date 7 June 2009
 * \author Pekka Kaitaniemi
 */

#ifndef G4INCLIRANDOMGENERATOR_HH_
#define G4INCLIRANDOMGENERATOR_HH_

#include <vector>

namespace G4INCL {

  typedef std::vector<long> SeedVector;

  class IRandomGenerator {
  public:
    IRandomGenerator() {}
    virtual ~IRandomGenerator() {}

    virtual SeedVector getSeeds() const = 0;
    virtual void setSeeds(const SeedVector &) = 0;
    virtual G4double flat() = 0;
  };

}

#endif /* G4INCLIRANDOMGENERATOR_HH_ */
