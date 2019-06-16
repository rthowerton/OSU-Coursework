function buildTable(){
   //create the header row
   var headRow = document.createElement("tr");
   for(var i = 0; i < 4; i++){
      var newHead = document.createElement("th");
      newHead.textContent = "Header " + (i+1);
      newHead.style.borderStyle = "solid";
      headRow.appendChild(newHead);
   }
   newTable.appendChild(headRow);

   //create data rows
   for(var a = 0; a < 3; a++){
      var newRow = document.createElement("tr");
      for(var b = 0; b < 4; b++){
	 var newItem = document.createElement("td");
	 newItem.textContent = (b+1) + ", " + (a+1);
	 newItem.style.borderStyle = "solid";
	 newItem.setAttribute("class", (b+1));
	 newRow.appendChild(newItem);
      }
      newTable.appendChild(newRow);
   }
}

function makeButtons(){
   var left = document.createElement("button");
   left.textContent = "Left";
   left.setAttribute("id", "leftButton");
   document.body.appendChild(left);
   
   var up = document.createElement("button");
   up.textContent = "Up";
   up.setAttribute("id", "upButton");
   document.body.appendChild(up);
   
   var down = document.createElement("button");
   down.textContent = "Down";
   down.setAttribute("id", "downButton");
   document.body.appendChild(down);
   
   var right = document.createElement("button");
   right.textContent = "Right";
   right.setAttribute("id", "rightButton");
   document.body.appendChild(right);

   var mark = document.createElement("button");
   mark.textContent = "Mark Cell";
   mark.setAttribute("id", "markButton");
   document.body.appendChild(mark);
}

function select(index){
   index.style.borderWidth = "thick";
   index.setAttribute("id", "selected");
}

function deselect(index){
   index.style.borderWidth = "medium";
   index.removeAttribute("id");
}

function mark(){
   var toMark = document.getElementById("selected");
   toMark.style.background = "yellow";
}

function moveLeft(){
   var move = document.getElementById("selected");
   if(move.previousElementSibling != null){
      deselect(move);
      select(move.previousElementSibling);
   }
}

function moveUp(){
   var move = document.getElementById("selected");
   var pos = move.getAttribute("class");
   var par = move.parentNode;
   if(par.previousElementSibling.children[0].tagName != "TH"){
      par = par.previousElementSibling;
      deselect(move);
      select(par.children[pos-1]);
   }
}

function moveDown(){
   var move = document.getElementById("selected");
   var pos = move.getAttribute("class");
   var par = move.parentNode;
   if(par.nextElementSibling != null){
      par = par.nextElementSibling;
      deselect(move);
      select(par.children[pos-1]);
   }
}

function moveRight(){
   var move = document.getElementById("selected");
   if(move.nextElementSibling != null){
      deselect(move);
      select(move.nextElementSibling);
   }
}


var newTable = document.createElement("table");
buildTable();
newTable.style.borderStyle = "solid";
document.body.appendChild(newTable);
makeButtons();
var table = document.firstElementChild;
select(table.getElementsByTagName("td")[0]);
document.getElementById("leftButton").addEventListener("click", moveLeft);
document.getElementById("upButton").addEventListener("click", moveUp);
document.getElementById("downButton").addEventListener("click", moveDown);
document.getElementById("rightButton").addEventListener("click", moveRight);
document.getElementById("markButton").addEventListener("click", mark);
