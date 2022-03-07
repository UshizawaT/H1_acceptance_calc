#include "VisAttributes.hh"

#include "G4Colour.hh"
#include "G4VisAttributes.hh"

using namespace CLHEP;

VisAttributes::VisAttributes() {
  // invisible = G4VisAttributes::Invisible;
  invisible = G4VisAttributes::GetInvisible();

  white = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
  gray = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));
  light_gray = new G4VisAttributes(G4Colour(0.75, 0.75, 0.75));
  black = new G4VisAttributes(G4Colour(0.0, 0.0, 0.0));
  red = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
  green = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
  bgreen = new G4VisAttributes(G4Colour(0.0, 1.0, 0.75));
  blue = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
  cyan = new G4VisAttributes(G4Colour(0.0, 1.0, 1.0));
  magenta = new G4VisAttributes(G4Colour(1.0, 0.0, 1.0));
  yellow = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0));
}

VisAttributes::~VisAttributes() {}

G4VisAttributes* VisAttributes::GetVisAttributes(const G4String& name,
                                                 const G4String& option) const {
  G4VisAttributes* color = 0;

  if (name == "white") color = white;
  if (name == "gray") color = gray;
  if (name == "light_gray") color = light_gray;
  if (name == "black") color = black;
  if (name == "red") color = red;
  if (name == "green") color = green;
  if (name == "bgreen") color = bgreen;
  if (name == "blue") color = blue;
  if (name == "cyan") color = cyan;
  if (name == "magenta") color = magenta;
  if (name == "yellow") color = yellow;

  if (color == 0) {
    G4cout << "ERROR :: visAttributes " << name << " is not implemented"
           << G4endl;
    return 0;
  }

  if (option == "w") {
    color->SetForceWireframe(true);
  }
  if (option == "s") {
    color->SetForceSolid(true);
  }

  return color;
}
