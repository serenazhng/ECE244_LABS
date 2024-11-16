//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray; // an array of Shape *, double pointers to point to objects of Shape

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

/* FUNCTION DECLARATION */
//bool nameExists(string n, Shape **(&shapesArray), int size);
// bool keyword(string n);
// bool matchType(string t);
void create(stringstream &, Shape ** &, int &, int&);
void move(stringstream &, Shape ** &, int &);
void rotate(stringstream &, Shape ** &, int &);
void draw(stringstream &, Shape ** &, int &);
void erase(stringstream &, Shape **&, int &, int &);
bool matchCommand(string);

int main() {
  string line;
  string command;
  shapesArray = nullptr;  // initialize the array to null pointers

  cout << "> ";        // Prompt for input
  getline(cin, line);  // Get a line from standard input

  while (!cin.eof()) {

    // Put the line in a linestream for parsing
    // Making a new sstream for each line so flags etc. are cleared
    stringstream lineStream(line);

    // Read from string stream into the command
    // The only way this can fail is if the eof is encountered
    lineStream >> command;

    // Check for the command and act accordingly
    // ECE244 Student: Insert your code here
    // make function for each command, check errors within each command
    // depending on command

    if (command == "maxShapes") {
      // check if array has already been made (maxShapes called already)
      if (max_shapes != 0) {
        // call delete function to delete all, objects may have already been created
        for (int i = 0; i < max_shapes; i++) {
          delete shapesArray[i];
          shapesArray[i] = NULL;
        }
        delete [] shapesArray; // delete previous array
        shapesArray = NULL;
        shapeCount = 0;  // once all are deleted, update shapeCount to zero
      }

      lineStream >> max_shapes;
      if(max_shapes < 0){
        cout << "Error: invalid value" << endl;
        //continue;
      } else {
        // create a new array
        shapesArray =
            new Shape *[max_shapes];  // dynamically allocate pointers in array
        cout << "New database: maxshapes is " << max_shapes << endl;
      }
      //continue;  // go back to top of loop
    }

    if (command == "create") {
      // call function, will do all the checking, creating, etc.
      create(lineStream, shapesArray, shapeCount, max_shapes);
      // continue to let user enter next command(s)
      //continue;

    } else if (command == "move") {
      // call function
      move(lineStream, shapesArray, max_shapes);

      //continue;

    } else if (command == "rotate") {
      // call function
      rotate(lineStream, shapesArray, max_shapes);

      //continue;

    } else if (command == "draw") {
      // call function
      draw(lineStream, shapesArray, max_shapes);
      //continue;

    } else if (command == "delete") {
      // call function
      erase(lineStream, shapesArray, shapeCount, max_shapes);
      //continue;

    } else if (!matchCommand(command)){
      cout << "Error: invalid command" << endl;
      //continue;
    }
    // will always continue and go back to top of loop until EOF
    cout << "> ";        // Prompt for input
    getline(cin, line);  // Get a line from standard input
  }  // End input loop until EOF.
  cout << endl;
  // check if maxshapes have been allocated
  if (max_shapes > 0) {
    // delete array before exiting program
    for (int i = 0; i < max_shapes; i++) {
      if(shapesArray[i] != NULL){
        delete shapesArray[i]; // delete all objects prior
        shapesArray[i] = NULL;
      }
    }
    delete [] shapesArray; // delete array
    shapesArray = NULL;
    shapeCount = 0;
  }
  return 0;
}

/* HELPER FUNCTIONS */

// Check if the name exists in database already
// how to pass pointer array to function? by reference
bool nameExists(string n, Shape ** (&shapesArray), int size){
    for(int i = 0; i < size; i ++){
        // check if array is full of empty pointers
        if(shapesArray[i] == NULL){
            return false; // no objects so the name doesn't exist in array yet
        } else {
            if(shapesArray[i] -> getName() == n){ // if the name this pointer is pointing at equals n
                return true; // name already exists
            } else {
                return false; // name doesn't exist, can create new object with this name
            }
        }
    }
}

bool keyword(string n){
    // check if it matches a command name
    for(int i = 0; i < 7; i ++){
        if(n == keyWordsList[i]){
            return true; // matches a keyword
        }
    }

    // check if it matches a shape name
    for(int i = 0; i < 4; i++){
        if(n == shapeTypesList[i]){
            return true; // matches a shape type
        } 
    }
    // neither is satisfied, doesn't match a keyword or shape type
    return false;
}

bool matchCommand(string t){
  // check if it matches a command name
  for(int i = 1; i < 7; i ++){ // start from "maxShapes"
    if(t == keyWordsList[i]){
      return true; // matches a keyword
    }
  }
  // searched array but none matched
  return false;
}

bool matchType(string t){
    // check if it matches a shape type
    for(int i = 0; i < 4; i++){
        if(t == shapeTypesList[i]){
            return true; // matches a shape type
        }
    }
    // searched entire array but none matched
    return false;
}

bool isDigit(stringstream &l){
  int c = l.peek(); // check what the next value is in stringstream, peek only looks doesn't parse it
  
  // Next character must be between 0-9 to be an int, if it's a . or char besides a space, not valid
  if(c >= 0 || c <= 9 || c == 32 || c == -1){ // should i include \n? 
    return true;
  } else {
    return false;
  }
}

// When calling this function, we've already checked that the name exists in the array
int findName(Shape ** (&shapesArray), int max_shapes, string name){
  int p = 0;
  for(int i = 0; i < max_shapes; i++){
    if(shapesArray[i] -> getName() == name){
      p = i;
      return p;
    }
  }
}

void create(stringstream &l, Shape **(&shapesArray), int &shapeCount, int &max_shapes){
  string name; // name
  string type;
  int x;
  int y;
  int xsz;
  int ysz;
  string ex;

  l >> name;
  // check if they only entered command and nothing after
  if(name.empty()){
    cout << "Error: too few arguments" << endl;
    return;
  }

  // Check if argument is of correct type 
  // Technically don't have to check if it's a string??? ... CLARIFY THIS

// Check if name entered is a reserved keyword
  if(keyword(name) == true){
      cout << "Error: invalid shape name" << endl;
      //l.ignore(1000, '\n'); // i think i have to do this to ignore rest of line and get user to re-enter entire line
      return;
  }
// Check if name already exists in array of objects
  if(nameExists(name, shapesArray, max_shapes) == true){
      cout << "Error: shape " << name << " exists" << endl;
      //l.ignore(1000, '\n');
      return;
  }
  // Check if too few arguments
  if (l.eof()) {
    cout << "Error: too few arguments" << endl;
    return;
  }

  // If name makes it through above conditions, move to next entered item
  l >> type;

// Check if shape is an allowed type (go to next string in stream)
  if(matchType(type) == false){
      cout << "Error: invalid shape type" << endl;
      //l.ignore(1000, '\n');
      return;
  }
  // Check if too few arguments
  if (l.eof()) {
    cout << "Error: too few arguments" << endl;
    return;
  }

  // If type makes it through condition, move to next entered item
  l >> x;

  // Check if argument is valid
  if(l.fail()){
    cout << "Error: invalid argument" << endl;
    return;
  }
  // Make sure there's no extra chars or decimals after
  // I can check with this ONLY because the following entered values are also ints!!
  if(isDigit(l) == false){
    cout << "Error: invalid argument" << endl;
    //l.ignore(1000, '\n');
    return;
  }
  // Check if value entered is valid
  if (x < 0) {
    cout << "Error: invalid value" << endl;
    // l.ignore(1000, '\n');
    return;
  }
  // Check if too few arguments
  if (l.eof()) {
    cout << "Error: too few arguments" << endl;
    return;
  }

  // If it's valid, move to next value
  l >> y;

  // Check if argument is valid
  if (l.fail()) {
    cout << "Error: invalid argument" << endl;
    return;
  }
  // Check if argument is valid
  if (isDigit(l) == false) {
    cout << "Error: invalid argument" << endl;
    return;
  }
  // Check if value entered is valid
  if(y < 0){
      cout << "Error: invalid value" << endl;
      return;
  }
  // Check if too few arguments
  if (l.eof()) {
    cout << "Error: too few arguments" << endl;
    return;
  }

  l >> xsz;
  // Check if argument is valid
  if (l.fail()) {
    cout << "Error: invalid argument" << endl;
    return;
  }
  // Check if argument is valid
  if (isDigit(l) == false) {
    cout << "Error: invalid argument" << endl;
    return;
  }
  // Check if value entered is valid
  if (xsz < 0) {
    cout << "Error: invalid value" << endl;
    return;
  }
  // Check if too few arguments
  if (l.eof()) {
    cout << "Error: too few arguments" << endl;
    return;
  }

  l >> ysz;
  // Check if argument is valid
  if(l.fail()){
    cout << "Error: invalid argument" << endl;
    return;
  }
  // Check if argument is valid
  if (isDigit(l) == false) {
    cout << "Error: invalid argument" << endl;
    return;
  }
  // Check if value entered is valid
  if (ysz < 0) {
    cout << "Error: invalid value" << endl;
    return;
  }

  // For x or y size if circle must equal
  if(type == "circle" && xsz != ysz){
      cout << "Error: invalid value" << endl;
      return;
  }

  // Check if too many arguments were entered
  l >> ex;
  if(!ex.empty()){
    cout << "Error: too many arguments" << endl;
    return;
  }

  // Check if array is full
  // * Note: even if LAST spot of array has been deleted previously, if all other spots
  // are filled with objects, the array IS FULL

  if((shapeCount != 0 && shapeCount == max_shapes - 1) || max_shapes == 0 || (max_shapes == 1 && shapeCount == 1)){ // as soon as shapeCount is one less than max_Shapes, the array IS FULL
      cout << "Error: shape array is full" << endl;
      return;
  }

  // If user entered command passes all previous conditions without returning, the line should be free of errors
  // Now we can allocate a new memory space for the object, place all the correct values given by user into object
  // Point to new object based on shapeCount
  // Print that it's been created and return once done

  // After checking array is NOT full, place a new object in shapeCount location

  // MAKE SURE ALL VALUES ENTERED BY USER ARE CORRECT BY THIS POINT!!
  // When creating the object and initializing all values, they MUST be correct

  // Create new shape at shapeCount location (for first create ever, shapeCount = 0)
  shapesArray[shapeCount] = new Shape(name, type, x, xsz, y, ysz);
  shapeCount ++; // increment shapeCount in main (passed by reference)

  // Print confirmation statement
  cout << "Created " << name << ": " << type << " " << x << " " << y << " " << xsz << " " << ysz << endl;
  return;
    
    
}

void move(stringstream &l, Shape **(&shapesArray), int &max_shapes) {
  string name;
  int x;
  int y;
  string ex;  // to hold extra arguments

  l >> name;
  // check if they only entered command and nothing after
  if (name.empty()) {
    cout << "Error: too few arguments" << endl;
    return;
  }

  // Check if invalid shape name
  if (keyword(name) == true) {
    cout << "Error: invalid shape name" << endl;
    return;
  }

  // Check if name exists in array
  if (nameExists(name, shapesArray, max_shapes) == false) {
      cout << "Error: shape " << name << " not found" << endl;
      return;
  }
  // Check if too few arguments
  if(l.eof()){
    cout << "Error: too few arguments" << endl;
    return;
  }

  l >> x;
  // Check if argument is valid
  if (l.fail()) {
    cout << "Error: invalid argument" << endl;
    return;
  }

  if (isDigit(l) == false) {
    cout << "Error: invalid argument" << endl;
    return;
  }

  // Check if value entered is within bounds
  if (x < 0) {
    cout << "Error: invalid value" << endl;
    return;
  }
  // Check if too few arguments
  if (l.eof()) {
    cout << "Error: too few arguments" << endl;
    return;
  }

  l >> y;
  // Check if argument is valid
  if (l.fail()) {
    cout << "Error: invalid argument" << endl;
    return;
  }

  if (isDigit(l) == false) {
    cout << "Error: invalid argument" << endl;
    return;
  }

  // Check if value entered is within bounds
  if(y < 0){
      cout << "Error: invalid value" << endl;
      return;
  }

  // Too many arguments
  l >> ex; // parse extra to see if there's more entered
  if(!ex.empty()){
    cout << "Error: too many arguments" << endl;
    return;
  }

  // If user input passes all conditions without returning, we can go ahead and move the shape
  // First, find where the shape is that matches the name entered
  int p = findName(shapesArray, max_shapes, name);

  // Next, change the values of x and y in that shape object depending on where that name is
  shapesArray[p] -> setXlocation(x);
  shapesArray[p] -> setYlocation(y);

  // Print out move statement and return
  cout << "Moved " << name << " to " << x << " " << y << endl;
  return;

}

// NOTE: MUST CHECK FOR EACH VALUE IN LINE IF ARGUMENT IS OF CORRECT TYPE
void rotate(stringstream &l, Shape **(&shapesArray), int &max_shapes) {
  string name;
  int angle;
  string ex;

  l >> name;
  // check if they only entered command and nothing after
  if (name.empty()) {
    cout << "Error: too few arguments" << endl;
    return;
  }

  // Check if invalid shape name
  if (keyword(name) == true) {
    cout << "Error: invalid shape name" << endl;
    return;
  }

  // Check if name exists in array
  if (nameExists(name, shapesArray, max_shapes) == false) {
    cout << "Error: shape " << name << " not found" << endl;
    return;
  }
  // Check if too few arguments
  if (l.eof()) {
    cout << "Error: too few arguments" << endl;
    return;
  }

  l >> angle;
  // Check if argument is valid
  if (l.fail()) {
    cout << "Error: invalid argument" << endl;
    return;
  }
  if (isDigit(l) == false) {
    cout << "Error: invalid argument" << endl;
    return;
  }

  // Check if value is valid
  if(angle < 0 || angle > 360){
      cout << "Error: invalid value" << endl;
      return;
  }

  // Check if too many arguments
  l >> ex;
  if (!ex.empty()) {
    cout << "Error: too many arguments" << endl;
    return;
  }

  // Passed all conditions, now can proceed with rotating and updating values
  // Find location that matches with name
  int p = findName(shapesArray, max_shapes, name);

  // Update rotation of that shape
  shapesArray[p] -> setRotate(angle);
  cout << "Rotated " << name << " by " << angle << " degrees" << endl;
  return;   
}

void draw(stringstream &l, Shape **(&shapesArray), int &max_shapes) {
  string name;
  string ex;

  l >> name;
  // check if they only entered command and nothing after
  if (name.empty()) {
    cout << "Error: too few arguments" << endl;
    return;
  }

  if(name == "all"){
    // Check if too many arguments
    l >> ex;
    if (!ex.empty()) {
      cout << "Error: too many arguments" << endl;
      return;
    }

    // Draw all the shapes
    cout << "Drew all shapes" << endl;
    for (int i = 0; i < max_shapes; i++) {
      // Check to make sure we don't print deleted or empty objects
      if (shapesArray[i] == NULL) {
        continue;
      }
      shapesArray[i] -> draw();
    }
    return;
  }

  if (name != "all") {
    // Check if invalid shape name
    if (keyword(name) == true) {
      cout << "Error: invalid shape name" << endl;
      return;
    }

    // Check if name exists/ is found
    if (nameExists(name, shapesArray, max_shapes) == false) {
      cout << "Error: shape " << name << " not found" << endl;
      return;
    }

    // Check if too many arguments
    l >> ex;
    if (!ex.empty()) {
      cout << "Error: too many arguments" << endl;
      return;
    }

    // Draw specific shape
    // Find position of shape based on name
    int p = findName(shapesArray, max_shapes, name);
    cout << "Drew ";
    shapesArray[p] -> draw();
    return;
  }
}

// When only ONE shape is erased, that spot cannot be used again which means, can only place new object at rightmost 
// spot in array NOT INCLUDING deleted spaces! Where shapeCount is
void erase(stringstream &l, Shape **(&shapesArray), int &shapeCount, int &max_shapes) {
  string name;
  string ex;

  l >> name;
  // check if they only entered command and nothing after
  if (name.empty()) {
    cout << "Error: too few arguments" << endl;
    return;
  }
  //fix this look at draw function!!!

  if (name != "all") {
    // Check if invalid shape name
    if (keyword(name) == true) {
      cout << "Error: invalid shape name" << endl;
      return;
    }

    // Check if name exists/is found
    if (nameExists(name, shapesArray, max_shapes) == false) {
        cout << "Error: shape " << name << " not found" << endl;
        return;
    }

    // Check if too many arguments
    l >> ex;
    if (!ex.empty()) {
      cout << "Error: too many arguments" << endl;
      return;
    }

    // Delete only the object that matches the name
    // Find position of shape based on name
    // * make into function *
    int p = findName(shapesArray, max_shapes, name);;

    delete shapesArray[p]; // delete specific object
    shapesArray[p] = NULL; // set it to NULL

    // In order to not 'reuse' deleted locations, shapeCount cannot be updated so that we can continue
    // adding to the right of the LAST object created

    cout << "Deleted shape " << name << endl;
    return;

  } else if(name == "all"){
    // Check if too many arguments
    l >> ex;
    if (!ex.empty()) {
      cout << "Error: too many arguments" << endl;
      return;
    }

    // Delete all objects in array
    for (int i = 0; i < max_shapes; i++){
      if(shapesArray[i] != NULL){
        delete shapesArray[i];
        shapesArray[i] = NULL;
      }
    }

    shapeCount = 0; // once all are deleted, update shapeCount to zero
    cout << "Deleted: all shapes" << endl;
    return;
  }
}