# dreamt

Code that uses the Geant4 toolkit to simulate photon emission and pair creation from relativistic electron beams passing through metal targets.

## Build

Assuming Geant4 has already been installed:
```bash
cd build
cmake ..
make
```

## Run

```
./dreamt materal thickness energy [number]
```
will run `dreamt` for a target made of `material` (e.g. `G4_Pb` for elemental lead) that is `thickness` (in microns) in depth. The `energy` of the primary electron beam is specified in MeV. The number of primaries is optional: the default is 1e8.

