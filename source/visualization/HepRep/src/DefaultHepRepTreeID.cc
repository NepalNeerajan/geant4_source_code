// Copyright FreeHEP, 2005.

#include <iostream>

#include "cheprep/DefaultHepRepTreeID.h"

using namespace std;
using namespace HEPREP;

/**
 * @author Mark Donszelmann
 * @version $Id: DefaultHepRepTreeID.cc,v 1.9 2005-06-02 21:28:45 duns Exp $
 */
namespace cheprep {

DefaultHepRepTreeID::DefaultHepRepTreeID(string aName, string aVersion, string aQualifier)
    : name(aName), version(aVersion), qualifier(aQualifier) {
}

DefaultHepRepTreeID::~DefaultHepRepTreeID() {
}

string DefaultHepRepTreeID::getQualifier() {
    return qualifier;
}

void DefaultHepRepTreeID::setQualifier(string qual) {
    this->qualifier = qual;
}

string DefaultHepRepTreeID::getName() {
    return name;
}

string DefaultHepRepTreeID::getVersion() {
    return version;
}

} // cheprep
