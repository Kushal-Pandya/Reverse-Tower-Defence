Date: 19/11/2015
Creator: Nicholas Friday
Subject: cis3250
files: manageMapState.c interfaceManageMapState.h (others are auxillary) (includes a make file)
C dependcies: stdio.h stdlib.h math.h (requires -lm when compilled with gcc)

This is the ManageMapState part of our code;
currently still includes my test environment library to make it easier to check if it functions correctly
does not call manage game state yet, as i do not have access to that function yet
it has 2 main functions:
   - updateUnitPositions: This function performs one movement cycle, which includes:
                        -moving all units currently on the path
                        -removing units from the path (pathIndex =-2)  if they reach the end 
                        -adding one new unit to the start of the path (pathIndex = 0)
                    Notes: a unit is considred for being added to the path, if its path index is -1,
                            and only one such unit, based on array order, is added per call
                    Returns: 1, if a new unit was added this iteration, and 0 otherwise (all units are already on the path)

    -updateUnitsWithinRange: This function creates tower and unit pairs, based on:
                                   - if a unit is withing range of that tower
                                   - if that unit is farthest along the path (and still within range)
                                   -i.e. the unit at max tower range is prioritized
                    possible Improvements:
                        -prioritise faster units
                        -prioritise lower or higher hp units
                    returns: the number of unit/tower pairs it created and assigned to the passed in pointer

manageMapState requires:
    -a pre-allocated array of units (unit** unitArray)
    -a pre-allocated array of towers (tower** towerArray)
    -a pre-allocated path (path* pathway)
    -the number of units allocated (int numUnits)
    -the number of towers allocated (int numTowers)
    -the size/lenght of the path (int pathSize)


returns:  nothing ... Let me know if it needs a return value, and what it should indicate

calls: manageGameState

notes: 
    -does not call mananagegameState yet, since that is not completed
    -does not free memory 
    -currently has a main for testing purposes
    

