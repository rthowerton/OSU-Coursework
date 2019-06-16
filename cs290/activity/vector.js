function Vector(x, y){
   this.x = x;
   this.y = y;
}

Vector.prototype.plus = function(vect){
   var newX = this.x + vect.x;
   var newY = this.y + vect.y;
   return new Vector(newX, newY);
};

Vector.prototype.minus = function(vect){
   var newX = this.x - vect.x;
   var newY = this.y - vect.y;
   return new Vector(newX, newY);
};

Vector.prototype.length = function(){
   return Math.sqrt(Math.pow(this.x, 2) + Math.pow(this.y, 2));
}

console.log(new Vector(1, 2).plus(new Vector(2, 3)));//Vector{x: 3, y: 5}
console.log(new Vector(1, 2).minus(new Vector(2, 3)));//Vector{x: -1, y:-1}
console.log(new Vector(3, 4).length());//5
