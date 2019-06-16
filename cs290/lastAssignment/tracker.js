//construct the table from the request response
function buildTable(response){
   //create the header row
   var headRow = document.createElement("tr");
   for(param in response[0]){
      if(param == "id"){
	 var newHead = document.createElement("th");//empty header
	 newHead.style.borderStyle = "solid";
	 headRow.appendChild(newHead);
      }
      else{
         var newHead = document.createElement("th");//not empty header
         newHead.textContent = param;
         newHead.style.borderStyle = "solid";
         headRow.appendChild(newHead);
      }
   }
   newTable.appendChild(headRow);

   //create data rows
   for(var a = 0; a < response.length; a++){
      var newRow = document.createElement("tr");
      for(elem in response[a]){
	 var newItem = document.createElement("td");
	 if(elem == "id"){//let nothing go to waste; use the definitelynotid column to hold the delete and edit buttons
	    var deleteButton = makeDeleteButton(response[a][elem]);
	    newItem.appendChild(deleteButton);
	    var editButton = makeEditButton(response[a][elem]);
	    newItem.appendChild(editButton);
	 }
	 else{
	    newItem.textContent = response[a][elem];
	 }
	 newItem.style.borderStyle = "solid";
	 newRow.appendChild(newItem);
      }
      newTable.appendChild(newRow);
   }
}

//make the delete button
function makeDeleteButton(ident){
   var deleteButton = document.createElement("input");
   deleteButton.id = ident;
   deleteButton.type = "button";
   deleteButton.value = "delete";
   deleteButton.addEventListener("click",deleteRow);//button functionality is go!
   return deleteButton;
}

//actually make ajax request to delete
function deleteRow(){
   var num = parseInt(this.id);
   //console.log(num);

   var req = new XMLHttpRequest();
   req.open("GET", "http://flip3.engr.oregonstate.edu:3436/delete?id="+num, false);
   req.send(null);

   getTable();//rebuild table
}

//make the edit button
function makeEditButton(rowId){
   var editButton = document.createElement("input");
   editButton.id = rowId;//row containing edit button
   editButton.type = "button";
   editButton.value = "edit";
   editButton.addEventListener("click",showEdit);//more button functionality
   
   return editButton;
}

//show hidden form that contains inputs to edit
function showEdit(){
   document.getElementById("ident").value = this.id;//hold row number
   document.getElementById("editRow").style.display = "block";//idea for display:block and display:none comes from the user Learner on StackOverflow
}

//get information from the database
function getTable(){
   eraseTable();//remove table from page before rebuilding

   var req = new XMLHttpRequest();
   req.open("GET", "http://flip3.engr.oregonstate.edu:3436/", false);
   req.send(null);
   response = JSON.parse(req.responseText);
   
   buildTable(response);//rebuild here
   document.body.appendChild(newTable);
}

//if table has data, destroy it
function eraseTable(){
   var checkTable = newTable.children;
   if(checkTable.length > 0){
      for(var row = checkTable.length-1; row >= 0; row--){
	 newTable.removeChild(newTable.children[row]);
      }
   }
}

//update specified row
function updateData(){
   var id = document.getElementById("ident").value;//get intended row
   var name = document.getElementById("newName").value;
   var reps = document.getElementById("newReps").value;
   var weight = document.getElementById("newWeight").value;
   var date = document.getElementById("newDate").value;
   var lbs = document.getElementById("newLbs").value;

   var req = new XMLHttpRequest();
   req.open("GET", "http://flip3.engr.oregonstate.edu:3436/update?id="+id+"&name="+name+"&reps="+reps+"&weight="+weight+"&date="+date+"&lbs="+lbs, false);
   req.send(null);

   getTable();//rebuild table
   document.getElementById("editRow").style.display = "none";//re-hide form
}

//insert new data into table
function insertData(){
   var name = document.getElementById("name").value;
   var reps = document.getElementById("reps").value;
   var weight = document.getElementById("weight").value;
   var date = document.getElementById("date").value;
   var lbs = document.getElementById("lbs").value;
   
   var req = new XMLHttpRequest();
   req.open("GET", "http://flip3.engr.oregonstate.edu:3436/insert?name="+name+"&reps="+reps+"&weight="+weight+"&date="+date+"&lbs="+lbs, false);
   req.send(null);

   getTable();//rebuild table
}

var newTable = document.createElement("table");
var response;
newTable.style.borderStyle = "solid";
document.addEventListener("DOMContentLoaded", getTable);
document.getElementById("sub").addEventListener("click", getTable);
document.getElementById("insert").addEventListener("click", insertData);
document.getElementById("update").addEventListener("click", updateData);
