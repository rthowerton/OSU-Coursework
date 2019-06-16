function Automobile(year, make, model, type){
   this.year = year;
   this.make = make;
   this.model = model;
   this.type = type;
}

Automobile.prototype.logMe = function(bool){
   if(bool == true){
      console.log(this.year + ' ' + this.make + ' ' + this.model + ' ' + this.type);
   }
   else
      console.log(this.year + ' ' + this.make + ' ' + this.model);
}

var automobiles = [
   new Automobile(1995, "Honda", "Accord", "Sedan"),
   new Automobile(1990, "Ford", "F-150", "Pickup"),
   new Automobile(2000, "GMC", "Tahoe", "SUV"),
   new Automobile(2010, "Toyota", "Tacoma", "Pickup"),
   new Automobile(2005, "Lotus", "Elise", "Roadster"),
   new Automobile(2008, "Subaru", "Outback", "Wagon")
   ];
//sinking sort
function sortArr(comparator, array){
   for(var i = 0; i < array.length; i++){
      for(var j = array.length-1; j > i; j--){
	 if(comparator(array[j], array[i]) == true){
	    var temp = array[i];
	    array[i] = array[j];
	    array[j] = temp;
	 }
      }
   }
}

function yearComparator(auto1, auto2){
   if(auto1.year > auto2.year)
      return true;
   else
      return false;
}

function makeComparator(auto1, auto2){
   //check length of string to get bounds of test
   if(auto1.make.length > auto2.make.length){
      for(var a = 0; a < auto1.make.length; a++){
	 //compare ascii values of characters in strings
	 if(auto1.make[a].charCodeAt() > auto2.make[a].charCodeAt()){
	    return true;//ascii value greater
	 }
	 else{
	    return false;//ascii value less
	 }
      }
   }
   else{
      for(var b = 0; b < auto2.make.length; b++){
	 if(auto1.make[b].charCodeAt() > auto2.make[b].charCodeAt()){
	    return true;
	 }
	 else{
	    return false;
	 }
      }
   }
}

function typeComparator(auto1, auto2){
   //check length of string to get bounds of test
   if(auto1.type.length > auto2.type.length){
      //compare ascii values of characters in strings
      for(var a = 0; a < auto1.type.length; a++){
	 if(auto1.type[a].charCodeAt() > auto2.type[a].charCodeAt()){
	    return true;//ascii value greater
	 }
	 else{
	    return false;//ascii value less
	 }
      }
   }
   else{
      for(var b = 0; b < auto2.type.length; b++){
	 if(auto1.type[b].charCodeAt() > auto2.type[b].charCodeAt()){
	    return true;
	 }
	 else{
	    return false;
	 }
      }
   }
}


console.log("*****");
//sort by year
sortArr(yearComparator, automobiles);
console.log("The cars sorted by year are:");
automobiles[0].logMe(false);
automobiles[1].logMe(false);
automobiles[2].logMe(false);
automobiles[3].logMe(false);
automobiles[4].logMe(false);
automobiles[5].logMe(false);
//sort by make
sortArr(makeComparator, automobiles);
console.log("\nThe cars sorted by make are:");
automobiles[0].logMe(false);
automobiles[1].logMe(false);
automobiles[2].logMe(false);
automobiles[3].logMe(false);
automobiles[4].logMe(false);
automobiles[5].logMe(false);
//sort by type
sortArr(typeComparator, automobiles);
console.log("\nThe cars sorted by type are:");
automobiles[0].logMe(true);
automobiles[1].logMe(true);
automobiles[2].logMe(true);
automobiles[3].logMe(true);
automobiles[4].logMe(true);
automobiles[5].logMe(true);

console.log("*****");
