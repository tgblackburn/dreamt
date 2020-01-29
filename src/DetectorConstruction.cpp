#include <DetectorConstruction.hpp>

#include <G4NistManager.hh>
#include <G4Material.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>

using namespace CLHEP;

static G4Material *PPMI (void);

DetectorConstruction::DetectorConstruction (const G4String &materialName, G4double thickness)
 {
  fMaterialName = materialName;
  fThickness = thickness;
 }

DetectorConstruction::~DetectorConstruction ()
 {
 }

G4VPhysicalVolume *DetectorConstruction::Construct()
 {
  G4NistManager *nist = G4NistManager::Instance();
  G4Material *material = NULL;

  if (fMaterialName == "PPMI")
    material = PPMI();
  else
    material = nist->FindOrBuildMaterial (fMaterialName);

  if (!material)
    G4cerr << "Material " << fMaterialName << " not found." << G4endl;

  G4Material *vacuum = new G4Material ("intergalactic",   // name
				       1,                 // atomic number
				       1.008 * g/mole,    // mass per mole
				       1.0e-25 * g/cm3,   // mass density
				       kStateGas,
				       2.73 * kelvin,     // temperature
				       3.0e-18 * pascal); // pressure

  // Start by making the world.

  G4Box *worldBox = new G4Box ("worldBox", 0.1*m, 0.1*m, 0.1*m);

  G4LogicalVolume *logicWorld = new G4LogicalVolume (worldBox, vacuum, "world");

  G4VPhysicalVolume *physWorld = new G4PVPlacement (0,               // no rotation
						   G4ThreeVector(), // at origin
						   logicWorld,      // which logical vol
						   "world",         // name of above
						   0,               // no mother volume
						   false,           // not used!
						   0);              // copy ID

  // Make targets etc

  if (material)
   {
    G4Box *foilBox = new G4Box ("foilBox", 0.5 * fThickness, 0.08*m, 0.08*m);

    G4LogicalVolume *logicFoil = new G4LogicalVolume (foilBox, material, "foil");

    G4VPhysicalVolume *physFoil = new G4PVPlacement (0,
						     G4ThreeVector(),
						     logicFoil,
						     "foil",
						     logicWorld,      // world is mother
						     false,
						     0);

    G4cout << "Loaded foil of " << fMaterialName << ", thickness " << fThickness/CLHEP::um << " microns." << G4endl;
    G4cout << material << G4endl;
   }

  return physWorld;
 }

G4Material *PPMI (void)
 {
  G4Element *hydrogen = new G4Element ("Hydrogen", "H", 1.0, 1.01*g/mole);
  G4Element *carbon =   new G4Element ("Carbon",   "C", 6.0, 12.01*g/mole);
  G4Element *nitrogen = new G4Element ("Nitrogen", "N", 7.0, 14.01*g/mole);
  G4Element *oxygen =   new G4Element ("Oxygen",   "O", 8.0, 16.01*g/mole);

  G4Material *PPMI = new G4Material ("Polypyromellitimide", 1.4*g/cm3, 4);
  PPMI->AddElement (carbon, 22);
  PPMI->AddElement (hydrogen, 10);
  PPMI->AddElement (nitrogen, 2);
  PPMI->AddElement (oxygen, 5);

  return PPMI;
 }

/*
G4Material *makeKapton (void)
 {
  G4String name, symbol;
  G4double a, z;
  G4double density;
  G4int nel, ncomponents;

  // define Elements
  a = 1.01*g/mole;
  G4Element* elH  = new G4Element(name="Hydrogen",symbol="H" , z= 1., a);
 
  a = 12.01*g/mole;
  G4Element* elC = new G4Element(name="Carbon", symbol="C", z=6., a);

  a = 14.01*g/mole;
  G4Element* elN  = new G4Element(name="Nitrogen",symbol="N" , z= 7., a);
 
  a = 16.00*g/mole;
  G4Element* elO  = new G4Element(name="Oxygen"  ,symbol="O" , z= 8., a);

// Kapton Dupont de Nemur (density: 1.396-1.430, get middle )

  density = 1.413*g/cm3;
  G4Material* Kapton = new G4Material(name="Kapton", density, nel=4);
  Kapton->AddElement(elO,5);
  Kapton->AddElement(elC,22);
  Kapton->AddElement(elN,2);
  Kapton->AddElement(elH,10);

  return Kapton;
 }
*/
